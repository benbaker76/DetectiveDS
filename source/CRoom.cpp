#include "CRoom.h"

CRoom::CRoom(RoomType roomType, CMap* pMap, const unsigned char* colMap)
{
	m_roomType = roomType;
	m_pMap = pMap;
	m_colMap = colMap;
			
	for(int i=0; i<MAX_DOORS; i++)
		m_doorArray[i] = NULL;
}

CRoom::~CRoom()
{
}

void CRoom::Initialize(int x)
{
	m_pMap->Initialize(x);
}

void CRoom::Draw()
{
	m_pMap->Draw();
}

bool CRoom::Scroll(DirectionType directionType)
{
	return m_pMap->Scroll(directionType);
}
