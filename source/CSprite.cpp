#include <stdio.h>
#include "CSprite.h"
#include "TDG.h"

//CSprite::CSprite(SpriteType spriteType, const u32* pTiles, int tilesLen, const u16* pPalette, int paletteLen, const int* frameArray, int frameCount)
CSprite::CSprite(SpriteType spriteType, const u32* pBmp, const int* frameArray, int frameCount)
{
	m_spriteType = spriteType;
	m_pBmp = pBmp;
	//m_pTiles = pTiles;
	//m_tilesLen = tilesLen;
	//m_pPalette = pPalette;
	//m_paletteLen = paletteLen;
	m_frameArray = frameArray;
	m_frameCount = frameCount;
	
	m_frameNum = 0;
	m_lastUpdate = 0;
	
	m_x = 0;
	m_y = 0;
	
	m_oamIndex = spriteType;
	
	m_alpha = 0xF;
	
	//m_gfxSub = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
	m_gfxSub = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_Bmp);
	//dmaCopy(m_pPalette, SPRITE_PALETTE_SUB, m_paletteLen);
}

CSprite::~CSprite()
{
}

void CSprite::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void CSprite::Animate(int elapsedTime)
{
	m_lastUpdate += elapsedTime;
	
	if (m_frameType == FRAME_NONE)
		return;
	
	if(m_lastUpdate > 200)
	{
		m_lastUpdate = 0;
	
		bool frameFound = false;
		
		for(++m_frameNum; m_frameNum < m_frameCount; m_frameNum++)
		{
			if(m_frameArray[m_frameNum] & m_frameType)
			{
				frameFound = true;
				break;
			}
		}
		
		if (!frameFound)
		{
			for(m_frameNum = 0; m_frameNum < m_frameCount; m_frameNum++)
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
}

void CSprite::Hide()
{
	//oamSet(&oamSub, m_oamIndex, m_x, m_y,	0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxSub, -1, false, true, false, false, false);
	oamSet(&oamSub, m_oamIndex, m_x, m_y,	0, 0, SpriteSize_32x32, SpriteColorFormat_Bmp, m_gfxSub, -1, false, true, false, false, false);
	
}

void CSprite::Draw()
{
	//dmaCopy(m_pTiles + (m_frameNum * 256), m_gfxSub, 32 * 32);
	dmaCopy(m_pBmp + (m_frameNum * 512), m_gfxSub, 32 * 32 * 2);
	
	oamSet(&oamSub,						// sub graphics engine context
		m_oamIndex,						// oam index (0 to 127)
		m_x, m_y,						// x and y pixel location of the sprite
		1,								// priority, lower renders last (on top)
		m_alpha,						// this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,
		//SpriteColorFormat_256Color,
		SpriteColorFormat_Bmp,
		m_gfxSub,						// pointer to the loaded graphics
		-1,								// sprite rotation data  
		false,							// double the size when rotating?
		false,							// hide the sprite?
		false,							// horizontal flip?
		false,							// vertical flip?
		false);							// mosaic?
		
}

void CSprite::SetFrameType(FrameType frameType)
{
	if(m_frameType != frameType)
	{
		m_frameType = frameType;
		Animate(1000);
	}
}
