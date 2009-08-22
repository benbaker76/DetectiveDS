#ifndef __CROOM_H__
#define __CROOM_H__

#include "TDG.h"

#define MAX_ROOMS			30

#define ROOM_FLOOR_TOP		144
#define ROOM_FLOOR_BOTTOM	184
#define ROOM_HORIZ_CENTRE	128
#define ROOM_VERT_CENTRE	168

enum RoomType
{
	ROOM_SNIDE,
	ROOM_REVEREND,
	ROOM_BENTLEY,
	ROOM_COOK,
	ROOM_GABRIEL,
	ROOM_CYNTHIA,
	ROOM_PROFESSOR,
	ROOM_DOCTOR,
	ROOM_MAJOR,
	ROOM_DINGLE,
	ROOM_OUTSIDE1,
	ROOM_OUTSIDE2,
	ROOM_OUTSIDE3,
	ROOM_OUTSIDE4,
	ROOM_OUTSIDE5,
	ROOM_PASSAGE1,
	ROOM_PASSAGE2,
	ROOM_PASSAGE3,
	ROOM_HALL1,
	ROOM_HALL2,
	ROOM_HALL3,
	ROOM_HALL4,
	ROOM_LANDING,
	ROOM_KITCHEN,
	ROOM_STAIRS,
	ROOM_STUDY,
	ROOM_CLOCK,
	ROOM_CELLAR,
	ROOM_DRAWING,
	ROOM_LIBRARY
};

class CRoom
{
public:
	CRoom(RoomType roomType, CMap* pMap);
	~CRoom();
	
	CMap* pMap() const { return m_pMap; }

private:
	RoomType m_roomType;
	CMap* m_pMap;
};

#endif
