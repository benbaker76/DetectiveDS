#ifndef __CROOM_H__
#define __CROOM_H__

#include <nds.h>
#include "Globals.h"
#include "CTimer.h"

#define MAX_ROOMS			37
#define MAX_DOORS			9
#define MAX_ROOM_RECT		7

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
	ROOM_UTILITY,
	ROOM_GARDEN,
	ROOM_GRAVEYARD,
	ROOM_COURTYARD,
	ROOM_ANGUS_LANDING,
	ROOM_ANGUS_ROOM,
	ROOM_ANGUS_SECRET,
	ROOM_ANGUS_STAIRS
};

enum RoomRect
{
	ROOMRECT_TORCH1,
	ROOMRECT_TORCH2,
	ROOMRECT_TORCH3,
	ROOMRECT_FIREPLACE1,
	ROOMRECT_FIREPLACE2,
	ROOMRECT_FIREPLACE3,
	ROOMRECT_CLOCK
};

class CDoor;

class CRoom
{
public:
	CRoom(RoomType roomType, PMAP pMap, PMAP pOverlay, const u8* colMap, int centreY);
	~CRoom();
	
	void Initialize(int x);
	void InitializeDoors();
	void InitializeOverlay();
	void Draw();
	void Animate(CTime* pTime);
	bool DoorIntersect(PRECT pRect);
	void MoveMap(PRECT rectSrc, PRECT rectDest);
	bool Scroll(DirectionType directionType);
	
	void SetDoor(int doorType, CDoor* pDoor) { m_doorArray[doorType] = pDoor; }
	CDoor* GetDoor(int doorType) const { return m_doorArray[doorType]; }
	CDoor* GetRoomDoor(CRoom* pRoom);
	
	void SetX(int x) { m_x = x; }
	
	void SetOverlay(PMAP pOverlay, int overlayY) { m_pOverlay = pOverlay; m_overlayY = overlayY; }
	void SetColMap(const u8* pColMap) { m_pColMap = pColMap; }
	
	void SetPalette(u16* pPalette) { dmaCopy(pPalette, BG_PALETTE_SUB, 512); }
	void RestorePalette() { dmaCopy(m_pMap->pPalette, BG_PALETTE_SUB, m_pMap->PaletteLen); }
	
	RoomType GetRoomType() { return m_roomType; }
	
	int X() const { return m_x; }
	int Width() const { return m_pMap->Width; }
	int Height() const { return m_pMap->Height; }
	int OverlayY() const { return m_overlayY; }
	int CentreY() const { return m_centreY; }
	u8 ColMap(int x, int y);
	bool GetColMapRect(CollisionType, PRECT rect);

private:
	RoomType m_roomType;
	PMAP m_pMap;
	PMAP m_pOverlay;
	const u8* m_pColMap;
	
	int m_x;
	int m_centreY;

	int m_overlayY;
	
	RECT m_rectSrc[MAX_ROOM_RECT];
	RECT m_rectDst[MAX_ROOM_RECT];
	
	u16 m_clockTiles[6 * 32];
	
	int m_lastUpdate;
	int m_frameNum;
	
	CDoor* m_doorArray[MAX_DOORS];
};

#endif
