#ifndef __CROOM_H__
#define __CROOM_H__

#include <nds.h>
#include "ColMap.h"
#include "Globals.h"
#include "CTimer.h"
#include "CAnimation.h"
#include "CItemCache.h"

#define MAX_ROOMS			39
#define MAX_DOORS			9
#define MAX_ROOM_SRC_RECT	48
#define MAX_ROOM_DST_RECT	19

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
	ROOM_LAUNDRY,
	ROOM_GARDEN,
	ROOM_GRAVEYARD,
	ROOM_COURTYARD,
	ROOM_ANGUS_LANDING,
	ROOM_ANGUS_ROOM,
	ROOM_ANGUS_SECRET,
	ROOM_ANGUS_STAIRS,
	ROOM_DINING,
	ROOM_SEWERS
};

enum SrcRect
{
	SRCRECT_TORCH1,
	SRCRECT_TORCH2,
	SRCRECT_TORCH3,
	SRCRECT_FIREPLACE1,
	SRCRECT_FIREPLACE2,
	SRCRECT_FIREPLACE3,
	SRCRECT_FIREPLACE4,
	SRCRECT_FIREPLACE5,
	SRCRECT_FIREPLACE6,
	SRCRECT_SAFE1,
	SRCRECT_SAFE2,
	SRCRECT_SAFE3,
	SRCRECT_LIGHT1,
	SRCRECT_LIGHT2,
	SRCRECT_LIGHT3,
	SRCRECT_LIGHT4,
	SRCRECT_EYES1,
	SRCRECT_EYES2,
	SRCRECT_EYES3,
	SRCRECT_EYES4,
	SRCRECT_EYES5,
	SRCRECT_EYES6,
	SRCRECT_STATUE,
	SRCRECT_TROPHY,
	SRCRECT_SWORD,
	SRCRECT_BALL_ON_CHAIN,
	SRCRECT_PENDULUM1,
	SRCRECT_PENDULUM2,
	SRCRECT_PENDULUM3,
	SRCRECT_FOUNTAIN1,
	SRCRECT_FOUNTAIN2,
	SRCRECT_FOUNTAIN3,
	SRCRECT_CABINET1,
	SRCRECT_CABINET2,
	SRCRECT_FAUCET1,
	SRCRECT_FAUCET2,
	SRCRECT_FAUCET3,
	SRCRECT_FAUCET4,
	SRCRECT_LEAK1,
	SRCRECT_LEAK2,
	SRCRECT_LEAK3,
	SRCRECT_LEAK4,
	SRCRECT_LEAK5,
	SRCRECT_LEAK6,
	SRCRECT_LEAK7,
	SRCRECT_LEAK8,
	SRCRECT_BULB1,
	SRCRECT_BULB2
};

enum DstRect
{
	DSTRECT_TORCH1,
	DSTRECT_TORCH2,
	DSTRECT_TORCH3,
	DSTRECT_FIREPLACE,
	DSTRECT_SAFE,
	DSTRECT_CLOCK,
	DSTRECT_LIGHT1,
	DSTRECT_LIGHT2,
	DSTRECT_EYES,
	DSTRECT_STATUE,
	DSTRECT_TROPHY,
	DSTRECT_SWORD,
	DSTRECT_BALL_ON_CHAIN,
	DSTRECT_PENDULUM,
	DSTRECT_FOUNTAIN,
	DSTRECT_CABINET,
	DSTRECT_FAUCET,
	DSTRECT_LEAK,
	DSTRECT_BULB
};

class CDoor;
class CSave;

class CRoom
{
public:
	CRoom(RoomType roomType, Map* pMap, Map* pOverlay, const u8* colMap, int centreY);
	~CRoom();
	
	void Initialize(int x);
	void InitializeDoors();
	void Reset();
	void InitializeOverlay();
	void Draw();
	void Update(CTime* pTime);
	bool DoorIntersect(Rect* pRect);
	void MoveMap(Rect* rectSrc, Rect* rectDest);
	bool Scroll(DirectionType directionType);
	
	void SetDoor(int doorType, CDoor* pDoor) { m_doorArray[doorType] = pDoor; }
	CDoor* GetDoor(int doorType) const { return m_doorArray[doorType]; }
	bool TryGetRoomDoor(CRoom* pRoom, CDoor** pDoor);
	bool TryGetDoor(int doorId, CDoor** pDoor);
	
	void SetX(int x) { m_x = x; }
	
	void SetOverlay(Map* pOverlay) { m_pOverlay = pOverlay; }
	void SetOverlay(Map* pOverlay, int overlayY) { m_pOverlay = pOverlay; m_overlayY = overlayY; }
	
	Map* GetOverlay() const { return m_pOverlay; }
	
	void SetMap(Map* pMap) { m_pMap = pMap; }
	Map* GetMap() const { return m_pMap; }
	
	void SetColMap(const u8* pColMap) { m_pColMap = pColMap; }
	const u8* GetColMap() const { return m_pColMap; }
	
	void SetPalette(u16* pPalette) { dmaCopy(pPalette, BG_PALETTE_SUB, 512); }
	void RestorePalette() { dmaCopy(m_pMap->pPalette, BG_PALETTE_SUB, m_pMap->PaletteLen); }
	
	void AddItemCache(int index, CollisionType colType) { m_itemCache[index] = new CItemCache(ITEMLOCATION_ROOM, colType, this); }
	void AddItems(int index, CItem* item1, CItem* item2, CItem* item3, CItem* item4, CItem* item5) { m_itemCache[index]->AddItems(item1, item2, item3, item4, item5); }
	void AddItem(int index, CItem* item, bool force) { m_itemCache[index]->AddItem(item, force); }
	void RemoveItem(int index, CItem* item) { m_itemCache[index]->RemoveItem(item); }
	CItemCache* GetItemCache(int index) const { return m_itemCache[index]; }
	
	void SetAnimFrame(DstRect dstRect, int frameNum) { m_animArray[dstRect]->SetFrame(frameNum); }
	void SetAnimState(DstRect dstRect, AnimationState animState) { m_animArray[dstRect]->SetState(animState); }
	AnimationState GetAnimState(DstRect dstRect) const { return m_animArray[dstRect]->GetState(); }
	int GetAnimFrameNum(DstRect dstRect) const { return m_animArray[dstRect]->FrameNum(); }
	
	RoomType GetRoomType() { return m_roomType; }
	
	int X() const { return m_x; }
	int Width() const { return m_pMap->Width; }
	int Height() const { return m_pMap->Height; }
	int OverlayY() const { return m_overlayY; }
	int CentreY() const { return m_centreY; }
	u8 ColMap(int x, int y);
	bool GetColMapRect(CollisionType, Rect** rect);
	
	void Save(CSave* pSave);
	void Load(CSave* pSave);

private:
	RoomType m_roomType;
	Map* m_pMap;
	Map* m_pOverlay;
	const u8* m_pColMap;
	
	int m_x;
	int m_centreY;

	int m_overlayY;
	
	Rect* m_rectSrc[MAX_ROOM_SRC_RECT];
	Rect* m_rectDst[MAX_ROOM_DST_RECT];
	
	CAnimation* m_animArray[MAX_ROOM_DST_RECT];
	
	u16 m_clockTiles[6 * 32];
	
	CDoor* m_doorArray[MAX_DOORS];
	CItemCache* m_itemCache[MAX_ITEM_CACHE];
};

#endif
