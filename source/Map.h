#ifndef __CMAP_H__
#define __CMAP_H__

#include <nds.h>

#define MAX_MAPS		18

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
	MAP_STUDY
};

class CMap
{
public:
	CMap(const u32* pTiles, int tilesLen, const u16* pMap, int mapLen, const u16* pPalette, int paletteLen);
	~CMap();
	
	void Draw();
	bool ScrollLeft();
	bool ScrollRight();

private:
	const u32* m_pTiles;
	const u16* m_pMap;
	const u16* m_pPalette;
	
	int m_tilesLen;
	int m_mapLen;
	int m_paletteLen;
	
	int m_x;
	int m_y;
};

#endif
