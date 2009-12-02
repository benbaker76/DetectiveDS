#include <nds.h>
#include <stdio.h>
#include <malloc.h>
#include <fat.h>
#include <unistd.h>
#include "CSave.h"

#include "CRoom.h"
#include "CDoor.h"

#include "efs_lib.h"    // include EFS lib

CSave::CSave(int bufferSize, CCharacter** characterArray, CSprite** spriteArray, CRoom** roomArray, CItem** itemArray, CEvent** eventArray)
{
	m_bufferPos = 0;
	m_bufferSize = bufferSize;
	m_pBuffer = (char *) malloc(bufferSize);
	
	m_characterArray = characterArray;
	m_spriteArray = spriteArray;
	m_roomArray = roomArray;
	m_itemArray = itemArray;
	m_eventArray = eventArray;
}

CSave::~CSave()
{
	free(m_pBuffer);
}

int CSave::ReadBuffer(const char* fileName)
{
	FILE *pFile;
	struct stat fileStat;
	size_t result;

	pFile = fopen(fileName, "rb");
	
	if(pFile == NULL)
		return 0;

	if(stat(fileName, &fileStat) != 0)
	{
		fclose(pFile);
		return 0;
	}

	result = fread(m_pBuffer, 1, fileStat.st_size, pFile);
	
	if(result != (uint) fileStat.st_size)
	{
		fclose(pFile);
		return 0;
	}

	fclose(pFile);
	
	return result;
}

int CSave::WriteBuffer(const char* fileName)
{
	FILE *pFile;
	struct stat fileStat;
	size_t result;

	pFile = fopen(fileName, "wb+");
	
	if(pFile == NULL)
		return 0;
		
	if(stat(fileName, &fileStat) != 0)
	{
		fclose(pFile);
		return 0;
	}

	result = fwrite(m_pBuffer, 1, fileStat.st_size, pFile);
	
	if(result != (uint) fileStat.st_size)
	{
		fclose(pFile);
		return 0;
	}

	fclose(pFile);
	
	return result;
}

void CSave::ReadUInt64(u64* value)
{
	*value = (u64)m_pBuffer[m_bufferPos++];
	*value |= (u64)m_pBuffer[m_bufferPos++] << 8LL;
	*value |= (u64)m_pBuffer[m_bufferPos++] << 16LL;
	*value |= (u64)m_pBuffer[m_bufferPos++] << 24LL;
	*value |= (u64)m_pBuffer[m_bufferPos++] << 32LL;
	*value |= (u64)m_pBuffer[m_bufferPos++] << 40LL;
	*value |= (u64)m_pBuffer[m_bufferPos++] << 48LL;
	*value |= (u64)m_pBuffer[m_bufferPos++] << 56LL;
}

void CSave::ReadUInt32(u32* value)
{
	*value = m_pBuffer[m_bufferPos++];
	*value |= m_pBuffer[m_bufferPos++] << 8;
	*value |= m_pBuffer[m_bufferPos++] << 16;
	*value |= m_pBuffer[m_bufferPos++] << 24;
}

void CSave::ReadUInt16(u16* value)
{
	*value = m_pBuffer[m_bufferPos++];
	*value |= m_pBuffer[m_bufferPos++] << 8;
}

void CSave::ReadByte(byte* value)
{
	*value = m_pBuffer[m_bufferPos++];
}

void CSave::ReadBool(bool* value)
{
	*value = m_pBuffer[m_bufferPos++];
}

bool CSave::ReadBool()
{
	return m_pBuffer[m_bufferPos++];
}

void CSave::ReadFloat(float* value)
{
	IFConvert ifconvert;
	u32 integer;
	
	ReadUInt32(&integer);
	
	ifconvert.Int = integer;
	*value = ifconvert.Float;
}

void CSave::ReadString(char* value)
{
	do
	{
		*value++ = m_pBuffer[m_bufferPos];
	} while(m_pBuffer[m_bufferPos++] != '\0');
}

void CSave::ReadRect(Rect* pRect)
{
	ReadUInt32((u32*)&pRect->X);
	ReadUInt32((u32*)&pRect->Y);
	ReadUInt32((u32*)&pRect->Width);
	ReadUInt32((u32*)&pRect->Height);
}

void CSave::ReadPoint(Point* pPoint)
{
	ReadUInt32((u32*)&pPoint->X);
	ReadUInt32((u32*)&pPoint->Y);
}

void CSave::ReadPointF(PointF* pPointF)
{
	ReadFloat(&pPointF->X);
	ReadFloat(&pPointF->Y);
}

void CSave::ReadSize(Size* pSize)
{
	ReadUInt32((u32*)&pSize->Width);
	ReadUInt32((u32*)&pSize->Height);
}

void CSave::ReadCharacter(CCharacter** pCharacter)
{
	byte charType;
	*pCharacter = NULL;
	
	ReadByte((byte*) &charType);
	
	if(charType == -1)
		return;
	
	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		if(m_characterArray[i]->GetCharacterType() == charType)
		{
			*pCharacter = m_characterArray[i];
			
			return;
		}
	}
}

void CSave::ReadRoom(CRoom** pRoom)
{
	byte roomType;
	*pRoom = NULL;

	ReadByte((byte*) &roomType);
	
	if(roomType == -1)
		return;
	
	for(int i=0; i<MAX_ROOMS; i++)
	{
		if(m_roomArray[i]->GetRoomType() == roomType)
		{
			*pRoom = m_roomArray[i];
			
			return;
		}
	}
}

void CSave::ReadItem(CItem** pItem)
{
	byte itemType;
	*pItem = NULL;

	ReadByte((byte*) &itemType);
	
	if(itemType == -1)
		return;
	
	for(int i=0; i<MAX_ITEMS; i++)
	{
		if(m_itemArray[i]->GetItemType() == itemType)
		{
			*pItem = m_itemArray[i];
			
			return;
		}
	}
}

void CSave::ReadDoor(CDoor** pDoor)
{
	int doorId;
	*pDoor = NULL;

	ReadUInt32((u32*)&doorId);
	
	if(doorId == -1)
		return;
	
	for(int i=0; i<MAX_ROOMS; i++)
	{
		if(m_roomArray[i]->TryGetDoor(doorId, pDoor))
			return;
	}
}

void CSave::ReadPadding(int count)
{
	m_bufferPos += count;
}


void CSave::WriteUInt64(u64 value)
{
	m_pBuffer[m_bufferPos++] = value & 0xFFLL;
	m_pBuffer[m_bufferPos++] = (value >> 8LL) & 0xFFLL;
	m_pBuffer[m_bufferPos++] = (value >> 16LL) & 0xFFLL;
	m_pBuffer[m_bufferPos++] = (value >> 24LL) & 0xFFLL;
	m_pBuffer[m_bufferPos++] = (value >> 32LL) & 0xFFLL;
	m_pBuffer[m_bufferPos++] = (value >> 40LL) & 0xFFLL;
	m_pBuffer[m_bufferPos++] = (value >> 48LL) & 0xFFLL;
	m_pBuffer[m_bufferPos++] = (value >> 56LL) & 0xFFLL;
}

void CSave::WriteUInt32(u32 value)
{
	m_pBuffer[m_bufferPos++] = value & 0xFF;
	m_pBuffer[m_bufferPos++] = (value >> 8) & 0xFF;
	m_pBuffer[m_bufferPos++] = (value >> 16) & 0xFF;
	m_pBuffer[m_bufferPos++] = (value >> 24) & 0xFF;
}

void CSave::WriteUInt16(u16 value)
{
	m_pBuffer[m_bufferPos++] = value & 0xFF;
	m_pBuffer[m_bufferPos++] = (value >> 8) & 0xFF;
}

void CSave::WriteByte(byte value)
{
	m_pBuffer[m_bufferPos++] = value;
}

void CSave::WriteBool(bool value)
{
	m_pBuffer[m_bufferPos++] = value;
}

void CSave::WriteFloat(float value)
{
	IFConvert ifconvert;
	
	ifconvert.Float = value;
	
	WriteUInt32(ifconvert.Int);
}

void CSave::WriteString(const char* value)
{
	do
	{
		WriteByte(*value);
	} while(*value++ != '\0');
}

void CSave::WriteRect(Rect* pRect)
{
	WriteUInt32(pRect->X);
	WriteUInt32(pRect->Y);
	WriteUInt32(pRect->Width);
	WriteUInt32(pRect->Height);
}

void CSave::WritePoint(Point* pPoint)
{
	WriteUInt32(pPoint->X);
	WriteUInt32(pPoint->Y);
}

void CSave::WritePointF(PointF* pPointF)
{
	WriteFloat(pPointF->X);
	WriteFloat(pPointF->Y);
}

void CSave::WriteSize(Size* pSize)
{
	WriteUInt32(pSize->Width);
	WriteUInt32(pSize->Height);
}

void CSave::WriteCharacter(CCharacter* pCharacter)
{
	if(pCharacter == NULL)
		WriteByte(-1);
	else
		WriteByte(pCharacter->GetCharacterType());
}

void CSave::WriteRoom(CRoom* pRoom)
{
	if(pRoom == NULL)
		WriteByte(-1);
	else
		WriteByte(pRoom->GetRoomType());
}

void CSave::WriteItem(CItem* pItem)
{
	if(pItem == NULL)
		WriteByte(-1);
	else
		WriteByte(pItem->GetItemType());
}

void CSave::WriteDoor(CDoor* pDoor)
{
	if(pDoor == NULL)
		WriteUInt32(-1);
	else
		WriteUInt32(pDoor->GetDoorId());
}

void CSave::WritePadding(int count)
{
	for(int i=0; i<count; i++)
		WriteByte(0);
}

void CSave::ToString()
{
	static char buf[8];
	
	for(int i=0; i<m_bufferSize; i++)
	{
		sprintf(buf, "0x%02x", m_pBuffer[i]);
		fprintf(stderr, buf);
	}
}

void CSave::ToString(int start, int size)
{
	static char buf[8];
	
	for(int i=start; i<start + size; i++)
	{
		sprintf(buf, "0x%02x", m_pBuffer[i]);
		fprintf(stderr, buf);
	}
}
