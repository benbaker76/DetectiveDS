#include "Room.h"

CRoom::CRoom(RoomType roomType, CMap* pMap)
{
	m_roomType = roomType;
	m_pMap = pMap;
}

CRoom::~CRoom()
{
}
