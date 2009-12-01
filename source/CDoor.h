#ifndef __CDOOR_H__
#define __CDOOR_H__

#include "TDG.h"

#define MAX_DOORS		9
#define MAX_DOOR_RECT	6

enum DoorType
{
	DOOR_NONE = COL_NOTHING_HERE,
	DOOR_DOOR1 = COL_DOOR1,
	DOOR_DOOR2 = COL_DOOR2,
	DOOR_DOOR3 = COL_DOOR3,
	DOOR_DOOR4 = COL_DOOR4,
	DOOR_DOOR5 = COL_DOOR5,
	DOOR_DOOR6 = COL_DOOR6,
	DOOR_DOOR7 = COL_DOOR7,
	DOOR_DOOR8 = COL_DOOR8
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
	DOORRECT_HIDDEN,
	DOORRECT_SMALL_CLOSED,
	DOORRECT_SMALL_OPEN,
	DOORRECT_SMALL_HIDDEN
};

class CRoom;

class CDoor
{
public:
	CDoor(DoorType doorType, DoorState doorState, CRoom* pRoomIn, CRoom* pRoomOut, ItemType doorKeyItemType);
	~CDoor();
	
	bool Initialize();
	void SetDoorState(DoorState doorState);
	void Draw();
	void Draw(CRoom* pCurrentRoom);
	
	Point* pPoint() const { return m_point; }
	Rect* pRect() const { return m_rect; }
	Rect* pRectOpen() const { return m_rectOpen; }
	DoorType GetDoorType() const { return  m_doorType; };
	DoorState GetDoorState() const { return  m_doorState; };
	CRoom* pRoomIn() const { return m_pRoomIn; }
	CRoom* pRoomOut() const { return m_pRoomOut; }
	CDoor* pDoorOut() const { return m_pDoorOut; }
	
	ItemType GetKeyItemType() const { return m_keyItemType; }
	
	void Reset() { m_doorState = m_defaultDoorState; }
	
	bool Hidden() const { return m_hidden; }
	
	int GetDoorId() const { return m_doorId; }

private:
	int m_doorId;
	DoorType m_doorType;
	DoorState m_doorState;
	DoorState m_defaultDoorState;
	
	CRoom* m_pRoomIn;
	CRoom* m_pRoomOut;
	CDoor* m_pDoorOut;
	
	bool m_hidden;
	bool m_topDoor;
	
	Point* m_point;
	Rect* m_rect;
	Rect* m_rectOpen;
	Rect* m_rectArray[MAX_DOOR_RECT];
	
	ItemType m_keyItemType;
	
	void GetPosition();
};

#endif
