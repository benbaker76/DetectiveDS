#ifndef __CDOOR_H__
#define __CDOOR_H__

#include "TDG.h"

#define MAX_DOORS		10
#define MAX_DOOR_RECT	5

enum DoorType
{
	DOOR_NONE = 0,
	DOOR_DOOR1 = COL_DOOR1,
	DOOR_DOOR2 = COL_DOOR2,
	DOOR_DOOR3 = COL_DOOR3,
	DOOR_DOOR4 = COL_DOOR4,
	DOOR_DOOR5 = COL_DOOR5,
	DOOR_DOOR6 = COL_DOOR6,
	DOOR_DOOR7 = COL_DOOR7,
	DOOR_SECRET_PASSAGE = COL_SECRET_PASSAGE
};

enum DoorState
{
	DOORSTATE_HIDDEN,
	DOORSTATE_CLOSED,
	DOORSTATE_OPEN,
	DOORSTATE_LOCKED
};

enum DoorRect
{
	DOORRECT_CLOSED,
	DOORRECT_OPEN,
	DOORRECT_SMALL_CLOSED,
	DOORRECT_SMALL_OPEN,
	DOORRECT_SMALL_HIDDEN
};

class CRoom;

class CDoor
{
public:
	CDoor(DoorType doorType, DoorState doorState, CRoom* pRoomIn, CRoom* pRoomOut);
	~CDoor();
	
	void Initialize();
	void SetDoorState(DoorState doorState);
	void Draw();
	
	PRECT pRect() const { return (PRECT) &m_rect; }
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
	
	RECT m_rect;
	RECT m_rectArray[MAX_DOOR_RECT];
	
	void GetPosition();
};

#endif
