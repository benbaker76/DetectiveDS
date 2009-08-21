#include "Map.h"
#include "TDG.h"

CMap::CMap(int width, int height, const u32* pTiles, int tilesLen, const u16* pMap, int mapLen, const u16* pPalette, int paletteLen)
{
	m_width = width;
	m_height = height;
	m_pTiles = pTiles;
	m_tilesLen = tilesLen;
	m_pMap = pMap;
	m_mapLen = mapLen;
	m_pPalette = pPalette;
	m_paletteLen = paletteLen;
}

CMap::~CMap()
{
}

void CMap::Draw()
{
	dmaCopy(m_pTiles, BG_TILE_RAM_SUB(BG2_TILE_BASE_SUB), m_tilesLen);
	dmaCopy(m_pMap, BG_MAP_RAM_SUB(BG2_MAP_BASE_SUB), m_mapLen);
	dmaCopy(m_pPalette, BG_PALETTE_SUB, m_paletteLen);
}

void CMap::ScrollLeft()
{
	if(m_x > 0)
		m_x--;
	
	BACKGROUND_SUB.scroll[2].x = m_x;
}

void CMap::ScrollRight()
{
	if(m_x < m_width + 256)
		m_x++;
	
	BACKGROUND_SUB.scroll[2].x = m_x;
}
