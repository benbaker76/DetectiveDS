#ifndef __CSAVE_H__
#define __CSAVE_H__

#include <nds.h>
#include "Globals.h"

union IFConvert
{
	u32 Int;
    float Float;
};

class CCharacter;
class CSprite;
class CRoom;
class CDoor;
class CItem;
class CEvent;

class CSave
{
public:
	CSave(int bufferSize, CCharacter** characterArray, CSprite** spriteArray, CRoom** roomArray, CItem** itemArray, CEvent** eventArray);
	~CSave();
	
	int ReadBuffer(const char* pFileName);
	int WriteBuffer(const char* pFileName);
	
	void ReadUInt64(u64* value);
	void ReadUInt32(u32* value);
	void ReadUInt16(u16* value);
	void ReadByte(byte* value);
	void ReadBool(bool* value);
	void ReadFloat(float* value);
	void ReadString(char* value);
	void ReadRect(Rect* pRect);
	void ReadPoint(Point* pPoint);
	void ReadPointF(PointF* pPointF);
	void ReadSize(Size* pSize);
	void ReadCharacter(CCharacter** pCharacter);
	void ReadRoom(CRoom** pRoom);
	void ReadDoor(CDoor** pDoor);
	void ReadPadding(int count);

	void WriteUInt64(u64 value);
	void WriteUInt32(u32 value);
	void WriteUInt16(u16 value);
	void WriteByte(byte value);
	void WriteBool(bool value);
	void WriteFloat(float value);
	void WriteString(const char* value);
	void WriteRect(Rect* pRect);
	void WritePoint(Point* pPoint);
	void WritePointF(PointF* pPointF);
	void WriteSize(Size* pSize);
	void WriteCharacter(CCharacter* pCharacter);
	void WriteRoom(CRoom* pRoom);
	void WriteDoor(CDoor* pDoor);
	void WritePadding(int count);
	
	void ToString();
	void ToString(int start, int size);
	
	int GetBufferPos() const { return m_bufferPos; }
	void SetBufferPos(int bufferPos) { m_bufferPos = bufferPos; }
	
private:

	char *m_pBuffer;
	int m_bufferPos;
	int m_bufferSize;
	
	CCharacter** m_characterArray;
	CSprite** m_spriteArray;
	CRoom** m_roomArray;
	CItem** m_itemArray;
	CEvent** m_eventArray;
};

#endif

