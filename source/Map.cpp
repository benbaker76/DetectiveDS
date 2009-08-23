#include <stdio.h>
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

void CMap::Initialize(int x)
{
	m_x = x;
	
	dmaCopy(m_pTiles, BG_TILE_RAM_SUB(BG2_TILE_BASE_SUB), m_tilesLen);
	dmaCopy(m_pPalette, BG_PALETTE_SUB, m_paletteLen);
	
	BG_PALETTE_SUB[0] = 0;
	BACKGROUND_SUB.scroll[2].x = (m_x & 0xFF);
	
	Draw();
}

void CMap::Draw()
{
	if((m_x & 0xFF) == 255)
		dmaCopy(m_pMap + ((m_x / 256) * 1024), BG_MAP_RAM_SUB(BG2_MAP_BASE_SUB), 4096);
	else				
		dmaCopy(m_pMap + ((m_x / 256) * 1024), BG_MAP_RAM_SUB(BG2_MAP_BASE_SUB), 4096);
}

bool CMap::Scroll(DirectionType directionType)
{
	switch(directionType)
	{
		case DIRECTION_LEFT:
			if(m_x > 0)
			{
				BACKGROUND_SUB.scroll[2].x = ((--m_x) & 0xFF);
				
				if((m_x & 0xFF) == 255)
					dmaCopy(m_pMap + ((m_x / 256) * 1024), BG_MAP_RAM_SUB(BG2_MAP_BASE_SUB), 4096);
				
				return true;
			}
			break;
		case DIRECTION_RIGHT:
			if(m_x < m_width - 256)
			{				
				BACKGROUND_SUB.scroll[2].x = ((++m_x) & 0xFF);
				
				if((m_x & 0xFF) == 0)				
					dmaCopy(m_pMap + ((m_x / 256) * 1024), BG_MAP_RAM_SUB(BG2_MAP_BASE_SUB), 4096);
		
				return true;
			}
			break;
		case DIRECTION_UP:
		case DIRECTION_DOWN:
			break;
	}

	return false;
}

