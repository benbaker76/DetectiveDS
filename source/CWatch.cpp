#include <stdio.h>
#include "TDG.h"

CWatch::CWatch(int x, int y)
{
	m_x = x - 16;
	m_y = y - 16;
	
	m_gfxHours = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
	m_gfxMinutes = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
	m_gfxSeconds = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	dmaCopy(sprite_watchTiles + 256 * 0, m_gfxHours, 32 * 32);
	dmaCopy(sprite_watchTiles + 256 * 1, m_gfxMinutes, 32 * 32);
	dmaCopy(sprite_watchTiles + 256 * 2, m_gfxSeconds, 32 * 32);
}

CWatch::~CWatch()
{
}

void CWatch::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void CWatch::Hide()
{
	oamSet(&oamSub, 125, m_x, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxHours, 0, false, true, false, false, false);
	oamSet(&oamSub, 126, m_x, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxMinutes, 1, false, true, false, false, false);
	oamSet(&oamSub, 127, m_x, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxSeconds, 2, false, true, false, false, false);
}

void CWatch::Draw(CTime* pTime)
{
	int hourHandRotation = (pTime->Hours * 30) + (pTime->Minutes * 0.5);
	int minuteHandRotation = (pTime->Minutes * 6);
	int secondHandRotation = (pTime->Seconds * 6);
	
	oamRotateScale(&oamSub, 0, degreesToAngle(-hourHandRotation), intToFixed(1, 8), intToFixed(1, 8));
	oamRotateScale(&oamSub, 1, degreesToAngle(-minuteHandRotation), intToFixed(1, 8), intToFixed(1, 8));
	oamRotateScale(&oamSub, 2, degreesToAngle(-secondHandRotation), intToFixed(1, 8), intToFixed(1, 8));
	
	oamSet(&oamSub, 125, m_x, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxHours,	0,	false, false, false, false,	 false);
	oamSet(&oamSub, 126, m_x, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxMinutes, 1, false, false, false, false, false);
	oamSet(&oamSub, 127, m_x, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxSeconds, 2, false, false, false, false, false);
}
