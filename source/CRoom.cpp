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

void CRoom::InitializeDoors()
{
	for(int i=0; i < MAX_DOORS; i++)
	{
		CDoor* pDoor = m_doorArray[i];
		
		if(pDoor != NULL)
			pDoor->Initialize();
	}
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

	for(int i=0; i < MAX_DOORS; i++)
		if(m_doorArray[i] != NULL)
			m_doorArray[i]->Draw();
}

void CRoom::MoveMap(PRECT rectSrc, PRECT rectDst)
{
	if(IsRectEmpty(rectSrc) || IsRectEmpty(rectDst))
		return;

	int scrollX = m_x / 256;

	for(int y=0; y<rectDst->Height; y++)
	{
		for(int x=0; x<rectDst->Width; x++)
		{
			int dstX = (rectDst->X + x) / 32;
			
			if(dstX >= scrollX && dstX < scrollX + 2)
			{
				int srcX = (rectSrc->X + x) / 32;
				int srcY = (rectSrc->Y + y) * 32;
				int dstY = (rectDst->Y + y) * 32;
				int srcRemX = ((rectSrc->X + x) % 32);
				int dstRemY = ((rectDst->X + x) % 32);
				
				const u16* pSrc = m_pMap->pMap + (srcX * 1024) + srcRemX + srcY;
				u16* pDst = BG_MAP_RAM_SUB(BG3_MAP_BASE_SUB) + (((scrollX + dstX) * 1024) & 0x7FF) + dstRemY + dstY;
						
				*pDst = *pSrc;
			}
			
		}
	}
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

bool CRoom::GetColMapRect(CollisionType colType, PRECT rect)
{
	bool mapFound = false;
	
	for(int y=0; y < m_pMap->Height / 8; y++)
	{
		for(int x=0; x < m_pMap->Width / 8; x++)
		{	
			if(ColMap(x, y) == colType)
			{
				if(!mapFound)
				{
					mapFound = true;			
					rect->X = x;
					rect->Y = y;
				}
				
				rect->Width = (x - rect->X) + 1;
				rect->Height = (y - rect->Y) + 1;
			}
		}
	}
	
	return mapFound;
}