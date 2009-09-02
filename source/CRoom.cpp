#include <stdio.h>
#include "CRoom.h"
#include "TDG.h"
#include "lz77.h"

CRoom::CRoom(RoomType roomType, PMAP pMap, PMAP pOverlay, const unsigned char* pColMap)
{
	m_roomType = roomType;
	m_pMap = pMap;
	m_pOverlay = pOverlay;
	m_pColMap = pColMap;
	m_overlayY = pMap->Height;
	
	for(int i=0; i<MAX_DOORS; i++)
		m_doorArray[i] = NULL;
}

CRoom::~CRoom()
{
}

void CRoom::Initialize(int x)
{
	m_x = x;
	
	//dmaCopy(m_pMap->pTiles, BG_TILE_RAM_SUB(BG3_TILE_BASE_SUB), m_pMap->TilesLen);
	decompressToVRAM(m_pMap->pTiles, BG_TILE_RAM_SUB(BG3_TILE_BASE_SUB));
	dmaCopy(m_pMap->pPalette, BG_PALETTE_SUB, m_pMap->PaletteLen);
	
	DC_FlushAll();
	
	BG_PALETTE_SUB[0] = 0;
	BACKGROUND_SUB.scroll[2].x = (m_x & 0xFF);
	BACKGROUND_SUB.scroll[3].x = (m_x & 0xFF);
	
	InitializeOverlay();
	
	Draw();
}

void CRoom::InitializeOverlay()
{
	if(m_pOverlay != NULL)
	{
		//dmaCopy(m_pOverlay->pTiles, BG_TILE_RAM_SUB(BG2_TILE_BASE_SUB), m_pOverlay->TilesLen);
		decompressToVRAM(m_pOverlay->pTiles, BG_TILE_RAM_SUB(BG2_TILE_BASE_SUB));
	}
	else
		dmaFillHalfWords(0, BG_MAP_RAM_SUB(BG2_MAP_BASE_SUB), 4096);
}

void CRoom::Draw()
{
	dmaCopy(m_pMap->pMap + ((m_x / 256) * 1024), BG_MAP_RAM_SUB(BG3_MAP_BASE_SUB), 4096);
	
	if(m_pOverlay != NULL)
		dmaCopy(m_pOverlay->pMap + ((m_x / 256) * 1024), BG_MAP_RAM_SUB(BG2_MAP_BASE_SUB), 4096);
}

bool CRoom::Scroll(DirectionType directionType)
{
	switch(directionType)
	{
		case DIRECTION_LEFT:
			if(m_x > 0)
			{
				BACKGROUND_SUB.scroll[2].x = (--m_x & 0xFF);
				BACKGROUND_SUB.scroll[3].x = (m_x & 0xFF);
				
				if((m_x & 0xFF) == 255)
					Draw();
				
				return true;
			}
			break;
		case DIRECTION_RIGHT:
			if(m_x < m_pMap->Width - 256)
			{
				BACKGROUND_SUB.scroll[2].x = (++m_x & 0xFF);			
				BACKGROUND_SUB.scroll[3].x = (m_x & 0xFF);
				
				if((m_x & 0xFF) == 0)				
					Draw();
		
				return true;
			}
			break;
		case DIRECTION_UP:
		case DIRECTION_DOWN:
			break;
	}

	return false;
}
