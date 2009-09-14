#include <nds.h>
#include "TDG.h"
#include "CSelector.h"

CSelector::CSelector()
{
	m_gfxLeft = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	m_gfxMiddle1 = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	m_gfxMiddle2 = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	m_gfxMiddle3 = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	m_gfxRight = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	dmaCopy(sprite_miscTiles + 256 * 3, m_gfxLeft, 32 * 32);
	dmaCopy(sprite_miscTiles + 256 * 4, m_gfxMiddle1, 32 * 32);
	dmaCopy(sprite_miscTiles + 256 * 4, m_gfxMiddle2, 32 * 32);
	dmaCopy(sprite_miscTiles + 256 * 4, m_gfxMiddle3, 32 * 32);
	dmaCopy(sprite_miscTiles + 256 * 5, m_gfxRight, 32 * 32);
}

CSelector::~CSelector()
{
}

void CSelector::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void CSelector::Hide()
{
	oamSet(&oamMain, 123, m_x + 32 * 0, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxLeft, 0, false, true, false, false, false);
	oamSet(&oamMain, 124, m_x + 32 * 1, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxMiddle3, 1, false, true, false, false, false);
	oamSet(&oamMain, 125, m_x + 32 * 2, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxMiddle3, 1, false, true, false, false, false);
	oamSet(&oamMain, 126, m_x + 32 * 3, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxMiddle3, 1, false, true, false, false, false);
	oamSet(&oamMain, 127, m_x + 32 * 4 - 16, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxRight, 2, false, true, false, false, false);
}

void CSelector::Draw()
{
	oamSet(&oamMain, 123, m_x + 32 * 0, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxLeft,	0,	false, false, false, false,	 false);
	oamSet(&oamMain, 124, m_x + 32 * 1, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxMiddle3, 1, false, false, false, false, false);
	oamSet(&oamMain, 125, m_x + 32 * 2, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxMiddle3, 1, false, false, false, false, false);
	oamSet(&oamMain, 126, m_x + 32 * 3, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxMiddle3, 1, false, false, false, false, false);
	oamSet(&oamMain, 127, m_x + 32 * 4 - 16, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxRight, 2, false, false, false, false, false);
}
