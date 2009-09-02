#ifndef __CROOM_H__
#define __CROOM_H__

#include <nds.h>
#include "Globals.h"

#define MAX_ROOMS			31
#define MAX_DOORS			10

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
	ROOM_LIBRARY,
	ROOM_GARDEN,
	ROOM_GRAVEYARD
};

class CDoor;

class CRoom
{
public:
	CRoom(RoomType roomType, PMAP pMap, PMAP pOverlay, const unsigned char* colMap);
	~CRoom();
	
	void Initialize(int x);
	void InitializeOverlay();
	void Draw();
	bool Scroll(DirectionType directionType);
	
	void SetDoor(int doorType, CDoor* pDoor) { m_doorArray[doorType] = pDoor; }
	CDoor* GetDoor(int doorType) const { return m_doorArray[doorType]; }
	
	void SetX(int x) { m_x = x; }
	void SetY(int y) { m_y = y; }
	
	void SetOverlay(PMAP pOverlay, int overlayY) { m_pOverlay = pOverlay; m_overlayY = overlayY; }
	
	int X() const { return m_x; }
	int Y() const { return m_y; }
	int Width() const { return m_pMap->Width; }
	int Height() const { return m_pMap->Height; }
	int OverlayY() const { return m_overlayY; }
	u8 ColMap(int x, int y) const { return (m_pColMap == NULL ? 0 : *(m_pColMap + x + y * (m_pMap->Width / 8))); }

private:
	RoomType m_roomType;
	PMAP m_pMap;
	PMAP m_pOverlay;
	const u8* m_pColMap;
	
	int m_x;
	int m_y;
	
	int m_overlayY;
	
	CDoor* m_doorArray[MAX_DOORS];
};

#endif
