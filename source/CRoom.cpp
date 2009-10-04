#include <stdio.h>
#include "CRoom.h"
#include "TDG.h"
#include "Text.h"
#include "lz77.h"
#include "Gfx.h"

CRoom::CRoom(RoomType roomType, Map* pMap, Map* pOverlay, const unsigned char* pColMap, int centreY)
{
	m_roomType = roomType;
	m_pMap = pMap;
	m_pOverlay = pOverlay;
	m_pColMap = pColMap;
	m_overlayY = pMap->Height;
	m_centreY = centreY;
	
	for(int i=0; i<MAX_DOORS; i++)
		m_doorArray[i] = NULL;
	
	for(int i=0; i<MAX_ROOM_SRC_RECT; i++)
		m_rectSrc[i] = NULL;
		
	for(int i=0; i<MAX_ROOM_DST_RECT; i++)
		m_rectDst[i] = NULL;
		
	for(int i=0; i<MAX_ROOM_DST_RECT; i++)
		m_animArray[i] = NULL;
		
	//char buf[256];
	//sprintf(buf, "X:%d, Y:%d, Width:%d, Height:%d", m_rectFireplace.X, m_rectFireplace.Y, m_rectFireplace.Width, m_rectFireplace.Height);
	//fprintf(stderr, buf);

	GetColMapRect(COL_SRC_TORCH1, &m_rectSrc[SRCRECT_TORCH1]);
	GetColMapRect(COL_SRC_TORCH2, &m_rectSrc[SRCRECT_TORCH2]);
	GetColMapRect(COL_SRC_FIREPLACE1, &m_rectSrc[SRCRECT_FIREPLACE1]);
	GetColMapRect(COL_SRC_FIREPLACE2, &m_rectSrc[SRCRECT_FIREPLACE2]);
	GetColMapRect(COL_SRC_FIREPLACE3, &m_rectSrc[SRCRECT_FIREPLACE3]);
	GetColMapRect(COL_SRC_FIREPLACE4, &m_rectSrc[SRCRECT_FIREPLACE4]);
	GetColMapRect(COL_SRC_FIREPLACE5, &m_rectSrc[SRCRECT_FIREPLACE5]);
	GetColMapRect(COL_SRC_FIREPLACE6, &m_rectSrc[SRCRECT_FIREPLACE6]);
	GetColMapRect(COL_SRC_SAFE1, &m_rectSrc[SRCRECT_SAFE1]);
	GetColMapRect(COL_SRC_SAFE2, &m_rectSrc[SRCRECT_SAFE2]);
	GetColMapRect(COL_SRC_SAFE3, &m_rectSrc[SRCRECT_SAFE3]);
	GetColMapRect(COL_SRC_LIGHT1, &m_rectSrc[SRCRECT_LIGHT1]);
	GetColMapRect(COL_SRC_LIGHT2, &m_rectSrc[SRCRECT_LIGHT2]);
	GetColMapRect(COL_SRC_LIGHT3, &m_rectSrc[SRCRECT_LIGHT3]);
	GetColMapRect(COL_SRC_LIGHT4, &m_rectSrc[SRCRECT_LIGHT4]);
	GetColMapRect(COL_SRC_EYES1, &m_rectSrc[SRCRECT_EYES1]);
	GetColMapRect(COL_SRC_EYES2, &m_rectSrc[SRCRECT_EYES2]);
	GetColMapRect(COL_SRC_EYES3, &m_rectSrc[SRCRECT_EYES3]);
	GetColMapRect(COL_SRC_EYES4, &m_rectSrc[SRCRECT_EYES4]);
	GetColMapRect(COL_SRC_EYES5, &m_rectSrc[SRCRECT_EYES5]);
	GetColMapRect(COL_SRC_EYES6, &m_rectSrc[SRCRECT_EYES6]);
	GetColMapRect(COL_SRC_STATUE, &m_rectSrc[SRCRECT_STATUE]);
	GetColMapRect(COL_SRC_TROPHY, &m_rectSrc[SRCRECT_TROPHY]);
	GetColMapRect(COL_SRC_SWORD, &m_rectSrc[SRCRECT_SWORD]);
	GetColMapRect(COL_SRC_BALL_ON_CHAIN, &m_rectSrc[SRCRECT_BALL_ON_CHAIN]);
	GetColMapRect(COL_SRC_PENDULUM1, &m_rectSrc[SRCRECT_PENDULUM1]);
	GetColMapRect(COL_SRC_PENDULUM2, &m_rectSrc[SRCRECT_PENDULUM2]);
	GetColMapRect(COL_SRC_PENDULUM3, &m_rectSrc[SRCRECT_PENDULUM3]);
	GetColMapRect(COL_SRC_FOUNTAIN1, &m_rectSrc[SRCRECT_FOUNTAIN1]);
	GetColMapRect(COL_SRC_FOUNTAIN2, &m_rectSrc[SRCRECT_FOUNTAIN2]);
	GetColMapRect(COL_SRC_FOUNTAIN3, &m_rectSrc[SRCRECT_FOUNTAIN3]);
	GetColMapRect(COL_SRC_CABINET1, &m_rectSrc[SRCRECT_CABINET1]);
	GetColMapRect(COL_SRC_CABINET2, &m_rectSrc[SRCRECT_CABINET2]);
	GetColMapRect(COL_SRC_FAUCET1, &m_rectSrc[SRCRECT_FAUCET1]);
	GetColMapRect(COL_SRC_FAUCET2, &m_rectSrc[SRCRECT_FAUCET2]);
	GetColMapRect(COL_SRC_FAUCET3, &m_rectSrc[SRCRECT_FAUCET3]);
	GetColMapRect(COL_SRC_FAUCET4, &m_rectSrc[SRCRECT_FAUCET4]);
	GetColMapRect(COL_SRC_LEAK1, &m_rectSrc[SRCRECT_LEAK1]);
	GetColMapRect(COL_SRC_LEAK2, &m_rectSrc[SRCRECT_LEAK2]);
	GetColMapRect(COL_SRC_LEAK3, &m_rectSrc[SRCRECT_LEAK3]);
	GetColMapRect(COL_SRC_LEAK4, &m_rectSrc[SRCRECT_LEAK4]);
	GetColMapRect(COL_SRC_LEAK5, &m_rectSrc[SRCRECT_LEAK5]);
	GetColMapRect(COL_SRC_LEAK6, &m_rectSrc[SRCRECT_LEAK6]);
	GetColMapRect(COL_SRC_LEAK7, &m_rectSrc[SRCRECT_LEAK7]);
	GetColMapRect(COL_SRC_LEAK8, &m_rectSrc[SRCRECT_LEAK8]);
	GetColMapRect(COL_SRC_BULB1, &m_rectSrc[SRCRECT_BULB1]);
	GetColMapRect(COL_SRC_BULB2, &m_rectSrc[SRCRECT_BULB2]);
	
	if(GetColMapRect(COL_DST_TORCH1, &m_rectDst[DSTRECT_TORCH1]))
		m_animArray[DSTRECT_TORCH1] = new CAnimation(ANIMTYPE_RANDOM, 0, 5, 2);
	
	if(GetColMapRect(COL_DST_TORCH2, &m_rectDst[DSTRECT_TORCH2]))
		m_animArray[DSTRECT_TORCH2] = new CAnimation(ANIMTYPE_RANDOM, 0, 5, 2);
	
	if(GetColMapRect(COL_DST_TORCH3, &m_rectDst[DSTRECT_TORCH3]))
		m_animArray[DSTRECT_TORCH3] = new CAnimation(ANIMTYPE_RANDOM, 0, 5, 2);
	
	if(GetColMapRect(COL_DST_FIREPLACE, &m_rectDst[DSTRECT_FIREPLACE]))
		m_animArray[DSTRECT_FIREPLACE] = new CAnimation(ANIMTYPE_FORWARD, 0, 5, 6);
		
	if(GetColMapRect(COL_DST_SAFE, &m_rectDst[DSTRECT_SAFE]))
		m_animArray[DSTRECT_SAFE] = new CAnimation(ANIMTYPE_MANUAL, 0, 0, 3);
	
	if(GetColMapRect(COL_DST_CLOCK, &m_rectDst[DSTRECT_CLOCK]))
		m_animArray[DSTRECT_CLOCK] = new CAnimation(ANIMTYPE_FORWARD, 0, 5, 1);
	
	if(GetColMapRect(COL_DST_LIGHT1, &m_rectDst[DSTRECT_LIGHT1]))
		m_animArray[DSTRECT_LIGHT1] = new CAnimation(ANIMTYPE_RANDOM, 0, 5, 4);
	
	if(GetColMapRect(COL_DST_LIGHT2, &m_rectDst[DSTRECT_LIGHT2]))
		m_animArray[DSTRECT_LIGHT2] = new CAnimation(ANIMTYPE_RANDOM, 0, 5, 4);
	
	if(GetColMapRect(COL_DST_EYES, &m_rectDst[DSTRECT_EYES]))
		m_animArray[DSTRECT_EYES] = new CAnimation(ANIMTYPE_PINGPONG, 300, 5, 6);
		
	if(GetColMapRect(COL_DST_STATUE, &m_rectDst[DSTRECT_STATUE]))
		m_animArray[DSTRECT_STATUE] = new CAnimation(ANIMTYPE_MANUAL, 0, 0, 1);
		
	if(GetColMapRect(COL_DST_TROPHY, &m_rectDst[DSTRECT_TROPHY]))
		m_animArray[DSTRECT_TROPHY] = new CAnimation(ANIMTYPE_MANUAL, 0, 0, 1);
		
	if(GetColMapRect(COL_DST_SWORD, &m_rectDst[DSTRECT_SWORD]))
		m_animArray[DSTRECT_SWORD] = new CAnimation(ANIMTYPE_MANUAL, 0, 0, 1);
		
	if(GetColMapRect(COL_DST_BALL_ON_CHAIN, &m_rectDst[DSTRECT_BALL_ON_CHAIN]))
		m_animArray[DSTRECT_BALL_ON_CHAIN] = new CAnimation(ANIMTYPE_MANUAL, 0, 0, 1);
		
	if(GetColMapRect(COL_DST_PENDULUM, &m_rectDst[DSTRECT_PENDULUM]))
		m_animArray[DSTRECT_PENDULUM] = new CAnimation(ANIMTYPE_PINGPONG, 0, 20, 3);
		
	if(GetColMapRect(COL_DST_FOUNTAIN, &m_rectDst[DSTRECT_FOUNTAIN]))
		m_animArray[DSTRECT_FOUNTAIN] = new CAnimation(ANIMTYPE_FORWARD, 0, 5, 3);
		
	if(GetColMapRect(COL_DST_CABINET, &m_rectDst[DSTRECT_CABINET]))
		m_animArray[DSTRECT_CABINET] = new CAnimation(ANIMTYPE_MANUAL, 0, 0, 2);
		
	if(GetColMapRect(COL_DST_FAUCET, &m_rectDst[DSTRECT_FAUCET]))
		m_animArray[DSTRECT_FAUCET] = new CAnimation(ANIMTYPE_FORWARD, 100, 5, 4);
		
	if(GetColMapRect(COL_DST_LEAK, &m_rectDst[DSTRECT_LEAK]))
		m_animArray[DSTRECT_LEAK] = new CAnimation(ANIMTYPE_FORWARD, 300, 5, 8);
		
	if(GetColMapRect(COL_DST_BULB, &m_rectDst[DSTRECT_BULB]))
		m_animArray[DSTRECT_BULB] = new CAnimation(ANIMTYPE_RANDOM, 0, 30, 2);
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
	
	SaveTiles(m_rectDst[DSTRECT_CLOCK], m_clockTiles);	
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

void CRoom::ResetDoors()
{
	for(int i=0; i < MAX_DOORS; i++)
	{
		CDoor* pDoor = m_doorArray[i];
		
		if(pDoor != NULL)
			pDoor->ResetDoorState();
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
	
	Update(NULL);
}

void CRoom::Update(CTime* pTime)
{
	if(m_animArray[DSTRECT_TORCH1] != NULL)
		if(m_animArray[DSTRECT_TORCH1]->Update())
			if(!DoorIntersect(m_rectDst[DSTRECT_TORCH1]))
				MoveMap(m_rectSrc[SRCRECT_TORCH1 + m_animArray[DSTRECT_TORCH1]->FrameNum()], m_rectDst[DSTRECT_TORCH1]);
	
	if(m_animArray[DSTRECT_TORCH2] != NULL)	
		if(m_animArray[DSTRECT_TORCH2]->Update())
			if(!DoorIntersect(m_rectDst[DSTRECT_TORCH2]))
				MoveMap(m_rectSrc[SRCRECT_TORCH1 + m_animArray[DSTRECT_TORCH2]->FrameNum()], m_rectDst[DSTRECT_TORCH2]);

	if(m_animArray[DSTRECT_TORCH3] != NULL)
		if(m_animArray[DSTRECT_TORCH3]->Update())
			if(!DoorIntersect(m_rectDst[DSTRECT_TORCH3]))
				MoveMap(m_rectSrc[SRCRECT_TORCH1 + m_animArray[DSTRECT_TORCH3]->FrameNum()], m_rectDst[DSTRECT_TORCH3]);
	
	if(m_animArray[DSTRECT_CLOCK] != NULL)
	{
		if(m_animArray[DSTRECT_CLOCK]->Update())
		{
			if(!IsRectEmpty(m_rectDst[DSTRECT_CLOCK]))
			{
				RestoreTiles(m_rectDst[DSTRECT_CLOCK], m_clockTiles);
				
				if(pTime != NULL)
					DrawTime(pTime, 124, 89);
			}
		}
	}
	
	if(m_animArray[DSTRECT_FIREPLACE] != NULL)
		if(m_animArray[DSTRECT_FIREPLACE]->Update())
			MoveMap(m_rectSrc[SRCRECT_FIREPLACE1 + m_animArray[DSTRECT_FIREPLACE]->FrameNum()], m_rectDst[DSTRECT_FIREPLACE]);

	if(m_animArray[DSTRECT_SAFE] != NULL)
		if(m_animArray[DSTRECT_SAFE]->Update())
			MoveMap(m_rectSrc[SRCRECT_SAFE1 + m_animArray[DSTRECT_SAFE]->FrameNum()], m_rectDst[DSTRECT_SAFE]);

	if(m_animArray[DSTRECT_LIGHT1] != NULL)
		if(m_animArray[DSTRECT_LIGHT1]->Update())
			if(!DoorIntersect(m_rectDst[DSTRECT_LIGHT1]))
				MoveMap(m_rectSrc[SRCRECT_LIGHT1 + m_animArray[DSTRECT_LIGHT1]->FrameNum()], m_rectDst[DSTRECT_LIGHT1]);
	
	if(m_animArray[DSTRECT_LIGHT2] != NULL)
		if(m_animArray[DSTRECT_LIGHT2]->Update())
			MoveMap(m_rectSrc[SRCRECT_LIGHT1 + m_animArray[DSTRECT_LIGHT2]->FrameNum()], m_rectDst[DSTRECT_LIGHT2]);
	
	if(m_animArray[DSTRECT_EYES] != NULL)
		if(m_animArray[DSTRECT_EYES]->Update())
			MoveMap(m_rectSrc[SRCRECT_EYES1 + m_animArray[DSTRECT_EYES]->FrameNum()], m_rectDst[DSTRECT_EYES]);

	if(m_animArray[DSTRECT_STATUE] != NULL)
		if(m_animArray[DSTRECT_STATUE]->Update())
			MoveMap(m_rectSrc[SRCRECT_STATUE], m_rectDst[DSTRECT_STATUE]);

	if(m_animArray[DSTRECT_TROPHY] != NULL)
		if(m_animArray[DSTRECT_TROPHY]->Update())
			MoveMap(m_rectSrc[SRCRECT_TROPHY], m_rectDst[DSTRECT_TROPHY]);

	if(m_animArray[DSTRECT_SWORD] != NULL)
		if(m_animArray[DSTRECT_SWORD]->Update())
			MoveMap(m_rectSrc[SRCRECT_SWORD], m_rectDst[DSTRECT_SWORD]);

	if(m_animArray[DSTRECT_BALL_ON_CHAIN] != NULL)
		if(m_animArray[DSTRECT_BALL_ON_CHAIN]->Update())
			MoveMap(m_rectSrc[SRCRECT_BALL_ON_CHAIN], m_rectDst[DSTRECT_BALL_ON_CHAIN]);

	if(m_animArray[DSTRECT_PENDULUM] != NULL)
		if(m_animArray[DSTRECT_PENDULUM]->Update())
			MoveMap(m_rectSrc[SRCRECT_PENDULUM1 + m_animArray[DSTRECT_PENDULUM]->FrameNum()], m_rectDst[DSTRECT_PENDULUM]);
	
	if(m_animArray[DSTRECT_FOUNTAIN] != NULL)
		if(m_animArray[DSTRECT_FOUNTAIN]->Update())
			MoveMap(m_rectSrc[SRCRECT_FOUNTAIN1 + m_animArray[DSTRECT_FOUNTAIN]->FrameNum()], m_rectDst[DSTRECT_FOUNTAIN]);
	
	if(m_animArray[DSTRECT_CABINET] != NULL)
		if(m_animArray[DSTRECT_CABINET]->Update())
			MoveMap(m_rectSrc[SRCRECT_CABINET1 + m_animArray[DSTRECT_CABINET]->FrameNum()], m_rectDst[DSTRECT_CABINET]);

	if(m_animArray[DSTRECT_FAUCET] != NULL)
		if(m_animArray[DSTRECT_FAUCET]->Update())
			MoveMap(m_rectSrc[SRCRECT_FAUCET1 + m_animArray[DSTRECT_FAUCET]->FrameNum()], m_rectDst[DSTRECT_FAUCET]);

	if(m_animArray[DSTRECT_LEAK] != NULL)
		if(m_animArray[DSTRECT_LEAK]->Update())
			MoveMap(m_rectSrc[SRCRECT_LEAK1 + m_animArray[DSTRECT_LEAK]->FrameNum()], m_rectDst[DSTRECT_LEAK]);

	if(m_animArray[DSTRECT_BULB] != NULL)
		if(m_animArray[DSTRECT_BULB]->Update())
			MoveMap(m_rectSrc[SRCRECT_BULB1 + m_animArray[DSTRECT_BULB]->FrameNum()], m_rectDst[DSTRECT_BULB]);
}

bool CRoom::DoorIntersect(Rect* pRect)
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

void CRoom::MoveMap(Rect* rectSrc, Rect* rectDst)
{
	if(IsRectEmpty(rectSrc) || IsRectEmpty(rectDst))
		return;
		
	if(rectSrc->Width != rectDst->Width || rectSrc->Height != rectDst->Height)
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

bool CRoom::GetColMapRect(CollisionType colType, Rect** rect)
{
	bool mapFound = false;
	
	*rect = NULL;
	
	for(int y=0; y < m_pMap->Height / 8; y++)
	{
		for(int x=0; x < m_pMap->Width / 8; x++)
		{	
			if(ColMap(x, y) == colType)
			{
				if(!mapFound)
				{
					mapFound = true;
					*rect = new Rect(0, 0, 0, 0);
					(*rect)->X = x;
					(*rect)->Y = y;
				}
				
				(*rect)->Width = (x - (*rect)->X) + 1;
				(*rect)->Height = (y - (*rect)->Y) + 1;
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
