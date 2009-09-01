#ifndef __CMAP_H__
#define __CMAP_H__

#include <nds.h>

#define MAX_MAPS		20

enum DirectionType
{
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
};

enum MapType
{
	MAP_CELLAR,
	MAP_CLOCK,
	MAP_DRAWING,
	MAP_HALL1,
	MAP_HALL2,
	MAP_HALL3,
	MAP_HALL4,
	MAP_KITCHEN,
	MAP_LANDING,
	MAP_LIBRARY,
	MAP_OUTSIDE1,
	MAP_OUTSIDE2,
	MAP_PASSAGE1,
	MAP_PASSAGE2,
	MAP_ROOM1,
	MAP_ROOM2,
	MAP_STAIRS,
	MAP_STUDY,
	MAP_GARDEN,
	MAP_GRAVEYARD
};

class CMap
{
public:
	CMap(int width, int height, const u32* pTiles, int tilesLen, const u16* pMap, int mapLen, const u16* pPalette, int paletteLen);
	~CMap();
	
	void Initialize(int x);
	void InitializeOverlay();
	void Draw();
	bool Scroll(DirectionType directionType);
	
	void SetX(int x) { m_x = x; }
	void SetY(int y) { m_y = y; }
	
	void SetOverlay(const u32* pTiles, int tilesLen, const u16* pMap, int mapLen) { m_pTilesOverlay = pTiles; m_tilesOverlayLen = tilesLen; m_pMapOverlay = pMap; m_mapOverlayLen = mapLen; }
	
	int X() const { return m_x; }
	int Y() const { return m_y; }
	int Width() const { return m_width; }
	int Height() const { return m_height; }

private:
	const u32* m_pTiles;
	const u16* m_pMap;
	const u16* m_pPalette;
	
	int m_tilesLen;
	int m_mapLen;
	int m_paletteLen;
	
	const u32* m_pTilesOverlay;
	const u16* m_pMapOverlay;
	
	int m_tilesOverlayLen;
	int m_mapOverlayLen;
	
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};

#endif
