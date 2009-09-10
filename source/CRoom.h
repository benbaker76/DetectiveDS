#ifndef __CROOM_H__
#define __CROOM_H__

#include <nds.h>
#include "Globals.h"

#define MAX_ROOMS			31
#define MAX_DOORS			9
#define MAX_ROOM_RECT		5
#define MAX_TORCH_RECT		3

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

enum RoomRect
{
	ROOMRECT_TORCH1,
	ROOMRECT_TORCH2,
	ROOMRECT_FIREPLACE1,
	ROOMRECT_FIREPLACE2,
	ROOMRECT_FIREPLACE3
};

enum TorchRect
{
	TORCHRECT_TORCH1,
	TORCHRECT_TORCH2,
	TORCHRECT_TORCH3
};

class CDoor;

class CRoom
{
public:
	CRoom(RoomType roomType, PMAP pMap, PMAP pOverlay, const u8* colMap);
	~CRoom();
	
	void Initialize(int x);
	void InitializeDoors();
	void InitializeOverlay();
	void Draw();
	void Animate(int elapsedTime);
	bool DoorIntersect(PRECT pRect);
	void MoveMap(PRECT rectSrc, PRECT rectDest);
	bool Scroll(DirectionType directionType);
	
	void SetDoor(int doorType, CDoor* pDoor) { m_doorArray[doorType] = pDoor; }
	CDoor* GetDoor(int doorType) const { return m_doorArray[doorType]; }
	CDoor* GetRoomDoor(CRoom* pRoom);
	
	void SetX(int x) { m_x = x; }
	
	void SetOverlay(PMAP pOverlay, int overlayY) { m_pOverlay = pOverlay; m_overlayY = overlayY; }
	void SetColMap(const u8* pColMap) { m_pColMap = pColMap; }
	
	RoomType GetRoomType() { return m_roomType; }
	
	int X() const { return m_x; }
	int Width() const { return m_pMap->Width; }
	int Height() const { return m_pMap->Height; }
	int OverlayY() const { return m_overlayY; }
	u8 ColMap(int x, int y) const { return (m_pColMap == NULL ? 0 : *(m_pColMap + x + y * (m_pMap->Width / 8))); }
	bool GetColMapRect(CollisionType, PRECT rect);

private:
	RoomType m_roomType;
	PMAP m_pMap;
	PMAP m_pOverlay;
	const u8* m_pColMap;
	
	int m_x;
	
	int m_overlayY;
	
	RECT m_rectArray[MAX_ROOM_RECT];
	RECT m_rectTorch[MAX_TORCH_RECT];
	RECT m_rectFireplace;
	
	int m_lastUpdate;
	int m_frameNum;
	
	CDoor* m_doorArray[MAX_DOORS];
};

#endif
