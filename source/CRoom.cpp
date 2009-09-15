#include <stdio.h>
#include "CRoom.h"
#include "TDG.h"
#include "Text.h"
#include "lz77.h"

CRoom::CRoom(RoomType roomType, PMAP pMap, PMAP pOverlay, const unsigned char* pColMap, int centreY)
{
	m_roomType = roomType;
	m_pMap = pMap;
	m_pOverlay = pOverlay;
	m_pColMap = pColMap;
	m_overlayY = pMap->Height;
	m_centreY = centreY;
	
	for(int i=0; i<MAX_DOORS; i++)
		m_doorArray[i] = NULL;
		
	GetColMapRect(COL_TORCH_ANIM1, &m_rectTorch[TORCHRECT_TORCH1]);
	GetColMapRect(COL_TORCH_ANIM2, &m_rectTorch[TORCHRECT_TORCH2]);
	GetColMapRect(COL_TORCH_ANIM3, &m_rectTorch[TORCHRECT_TORCH3]);
	
	GetColMapRect(COL_FIREPLACE_ANIM, &m_rectFireplace);
	
	//char buf[256];
	//sprintf(buf, "X:%d, Y:%d, Width:%d, Height:%d", m_rectFireplace.X, m_rectFireplace.Y, m_rectFireplace.Width, m_rectFireplace.Height);
	//fprintf(stderr, buf);

	GetColMapRect(COL_TORCH1, &m_rectArray[ROOMRECT_TORCH1]);
	GetColMapRect(COL_TORCH2, &m_rectArray[ROOMRECT_TORCH2]);
	GetColMapRect(COL_FIREPLACE1, &m_rectArray[ROOMRECT_FIREPLACE1]);
	GetColMapRect(COL_FIREPLACE2, &m_rectArray[ROOMRECT_FIREPLACE2]);
	GetColMapRect(COL_FIREPLACE3, &m_rectArray[ROOMRECT_FIREPLACE3]);
}

CRoom::~CRoom()
{
}

void CRoom::Initialize(int x)
{
	m_x = x;
	
	if(x + 256 > m_pMap->Width) m_x = m_pMap->Width - 256;
	if(m_x < 0) m_x = 0;
	
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

void CRoom::Animate(int elapsedTime)
{
	m_lastUpdate += elapsedTime;
	
	if(m_lastUpdate > 100)
	{
		m_lastUpdate = 0;
		
		int num = rand() % 2;
		
		if(num == 0)
		{
			for(int i=0; i<MAX_TORCH_RECT; i++)
				if(!DoorIntersect(&m_rectTorch[i]))
					MoveMap(&m_rectArray[ROOMRECT_TORCH1], &m_rectTorch[i]);
		} else
		{
			for(int i=0; i<MAX_TORCH_RECT; i++)
				if(!DoorIntersect(&m_rectTorch[i]))
					MoveMap(&m_rectArray[ROOMRECT_TORCH2], &m_rectTorch[i]);
		}
		
		switch(m_frameNum)
		{
			case 0:
				MoveMap(&m_rectArray[ROOMRECT_FIREPLACE1], &m_rectFireplace);
				break;
			case 1:
				MoveMap(&m_rectArray[ROOMRECT_FIREPLACE2], &m_rectFireplace);
				break;
			case 2:
				MoveMap(&m_rectArray[ROOMRECT_FIREPLACE3], &m_rectFireplace);
				break;
		}
		
		if(m_frameNum++ == 3)
			m_frameNum = 0;
	}
}

bool CRoom::DoorIntersect(PRECT pRect)
{
	for(int i=0; i < MAX_DOORS; i++)
	{
		CDoor* pDoor = m_doorArray[i];
		
		if(pDoor != NULL)
			if(pDoor->GetDoorState() == DOORSTATE_OPEN && IntersectRect(pDoor->pRectOpen(), pRect))
				return true;
	}
	
	return false;
}

void CRoom::MoveMap(PRECT rectSrc, PRECT rectDst)
{
	if(IsRectEmpty(rectSrc) || IsRectEmpty(rectDst))
		return;
		
	if(rectSrc->Width != rectDst->Width || rectSrc->Height != rectSrc->Height)
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


CDoor* CRoom::GetRoomDoor(CRoom* pRoom)
{
	for(int i=0; i<MAX_DOORS; i++)
	{
		if(m_doorArray[i]->pRoomOut() == pRoom)
			return m_doorArray[i];
	}
	
	return NULL;
}

u8 CRoom::ColMap(int x, int y)
{
	if(m_pColMap != NULL)
	{
		if(x >=0 && x < m_pMap->Width / 8 && y >=0 && y < m_pMap ->Height / 8)
			return *(m_pColMap + x + y * (m_pMap->Width / 8));
	}
	
	return 0;
}