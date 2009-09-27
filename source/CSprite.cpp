#include <stdio.h>
#include <math.h>
#include "CSprite.h"
#include "TDG.h"

CSprite::CSprite(SpriteType spriteType, const u32* pBmp, const u32* frameArray, int frameTotal)
{
	m_spriteType = spriteType;
	m_pBmp = pBmp;
	m_pTiles = NULL;
	m_tilesLen = 0;
	m_pPalette = NULL;
	m_paletteLen = 0;
	m_frameArray = frameArray;
	m_frameTotal = frameTotal;
	m_bitmapSprite = true;
	
	m_frameNum = 0;
	m_frameCount = 0;
	
	m_x = 0;
	m_y = 0;
	
	m_oamIndex = spriteType;
	m_priority = 1;
	
	m_alpha = 0xF;
	
	m_hFlip = false;
	
	//m_gfxMain = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_Bmp);
	m_gfxSub = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_Bmp);
}

CSprite::CSprite(SpriteType spriteType, const u32* pTiles, int tilesLen, const u16* pPalette, int paletteLen, const u32* frameArray, int frameTotal)
{
	m_spriteType = spriteType;
	m_pBmp = NULL;
	m_pTiles = pTiles;
	m_tilesLen = tilesLen;
	m_pPalette = pPalette;
	m_paletteLen = paletteLen;
	m_frameArray = frameArray;
	m_frameTotal = frameTotal;
	m_bitmapSprite = false;
	
	m_frameNum = 0;
	m_frameCount = 0;
	
	m_x = 0;
	m_y = 0;
	
	m_oamIndex = spriteType;
	m_priority = 1;
	
	m_alpha = 0xF;
	
	//m_gfxMain = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	m_gfxSub = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
}

CSprite::~CSprite()
{
}

void CSprite::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void CSprite::Update()
{
	m_frameCount++;
	
	if(m_frameCount > 9)
	{
		m_frameCount = 0;
	
		GetNextFrame();
	}
}

void CSprite::GetNextFrame()
{
	if (m_frameType == FRAME_NONE)
		return;
	
	bool frameFound = false;
	
	for(++m_frameNum; m_frameNum < m_frameTotal; m_frameNum++)
	{
		if(m_frameArray[m_frameNum] & m_frameType)
		{
			frameFound = true;
			break;
		}
	}
	
	if (!frameFound)
	{
		for(m_frameNum = 0; m_frameNum < m_frameTotal; m_frameNum++)
		{
			if(m_frameArray[m_frameNum] & m_frameType)
			{
				frameFound = true;
				break;
			}
		}
	}
	
	if (!frameFound)
		m_frameNum = 0;
}

void CSprite::Hide()
{
	if(m_bitmapSprite)
	{
		//oamSet(&oamMain, m_oamIndex, m_x, m_y,	0, 0, SpriteSize_32x32, SpriteColorFormat_Bmp, m_gfxMain, -1, false, true, m_hFlip, false, false);
		oamSet(&oamSub, m_oamIndex, m_x, m_y,	0, 0, SpriteSize_32x32, SpriteColorFormat_Bmp, m_gfxSub, -1, false, true, m_hFlip, false, false);
	}
	else
	{
		//oamSet(&oamMain, m_oamIndex, m_x, m_y,	0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxMain, -1, false, true, m_hFlip, false, false);
		oamSet(&oamSub, m_oamIndex, m_x, m_y,	0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxSub, -1, false, true, m_hFlip, false, false);
	}
}

void CSprite::Draw()
{
	if(m_bitmapSprite)
	{
		//dmaCopy(m_pBmp + (m_frameNum * 512), m_gfxMain, 32 * 32 * 2);
		dmaCopy(m_pBmp + (m_frameNum * 512), m_gfxSub, 32 * 32 * 2);
		
		//oamSet(&oamMain, m_oamIndex, m_x - (m_hFlip ? 8 : 0), m_y, m_priority, m_alpha, SpriteSize_32x32, SpriteColorFormat_Bmp, m_gfxMain, -1, false, false, m_hFlip, false, false);	
		oamSet(&oamSub, m_oamIndex, m_x - (m_hFlip ? 8 : 0), m_y, m_priority, m_alpha, SpriteSize_32x32, SpriteColorFormat_Bmp, m_gfxSub, -1, false, false, m_hFlip, false, false);	
	}
	else
	{
		//dmaCopy(m_pTiles + (m_frameNum * 256), m_gfxMain, 32 * 32);
		dmaCopy(m_pTiles + (m_frameNum * 256), m_gfxSub, 32 * 32);
	
		//oamSet(&oamMain, m_oamIndex,m_x - (m_hFlip ? 8 : 0), m_y, m_priority, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxMain, -1, false, false, m_hFlip, false, false);	
		oamSet(&oamSub, m_oamIndex, m_x - (m_hFlip ? 8 : 0), m_y, m_priority, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxSub, -1, false, false, m_hFlip, false, false);	
	}
}

void CSprite::SetFrameType(FrameType frameType)
{
	if(m_frameType != frameType)
	{
		m_frameType = frameType;
		GetNextFrame();
	}
}
