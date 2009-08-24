#ifndef __CDOOR_H__
#define __CDOOR_H__

#include "TDG.h"

#define MAX_DOORS		10

enum DoorType
{
	DOOR_NONE,
	DOOR_DOOR1,
	DOOR_DOOR2,
	DOOR_DOOR3,
	DOOR_DOOR4,
	DOOR_DOOR5,
	DOOR_DOOR6,
	DOOR_DOOR7,
	DOOR_SECRET_PASSAGE1,
	DOOR_SECRET_PASSAGE2
};

enum DoorState
{
	DOORSTATE_CLOSED,
	DOORSTATE_OPEN,
	DOORSTATE_LOCKED
};

class CRoom;

class CDoor
{
public:
	CDoor(DoorType doorType, DoorState doorState, CRoom* pRoomIn, CRoom* pRoomOut);
	~CDoor();
	
	void Initialize();
	
	int X() const { return m_x; }
	int Y() const { return m_y; }
	DoorType GetDoorType() const { return  m_doorType; };
	DoorState GetDoorState() const { return  m_doorState; };
	CRoom* pRoomIn() const { return m_pRoomIn; }
	CRoom* pRoomOut() const { return m_pRoomOut; }
	CDoor* pDoorOut() const { return m_pDoorOut; }

private:
	DoorType m_doorType;
	DoorState m_doorState;
	CRoom* m_pRoomIn;
	CRoom* m_pRoomOut;
	CDoor* m_pDoorOut;
	
	int m_x;
	int m_y;
	
	void GetPosition();
};

#endif
