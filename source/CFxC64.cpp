#include <nds.h>
#include <math.h>
#include "TDG.h"
#include "Gfx.h"
#include "CFxManager.h"
#include "CFxC64.h"
#include "Text.h"

void CFxC64::Initialize()
{
	m_colorWait = 0;
	m_colorOffset = 0;
	
	dmaCopy(intro_blankTiles, BG_TILE_RAM_SUB(BG1_TILE_BASE_SUB), intro_blankTilesLen);
	dmaCopy(intro_blankMap, BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB), intro_blankMapLen);
	
	dmaCopy(intro_blankTiles, BG_TILE_RAM(BG3_TILE_BASE), intro_blankTilesLen);
	dmaCopy(intro_blankMap, BG_MAP_RAM(BG3_MAP_BASE), intro_blankMapLen);
}

void CFxC64::Shutdown()
{
}

void CFxC64::Reset()
{
}

void CFxC64::UpdateVBlank()
{
}

void CFxC64::UpdateHBlank()
{
	if(m_colorWait++ == 4)
	{
		m_colorWait = 0;
		
		m_colorOffset = rand() % 8;
	}
	
	BG_PALETTE[1] = g_c64Pal[m_colorOffset];
	BG_PALETTE_SUB[1] = g_c64Pal[m_colorOffset];
}
