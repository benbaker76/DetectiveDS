#include <nds.h>
#include <math.h>
#include "TDG.h"
#include "Gfx.h"
#include "CFxManager.h"
#include "CFxLeak.h"
#include "Text.h"

const u32 g_frameMap[19] = { 0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 6, 7 };

void CFxLeak::Initialize()
{
	m_xOffset = 0;
	m_frameNum = 0;
	m_frameCount = 0;
	m_frameRate = 0;
	m_waiting = true;
	
	m_gfx = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);
	
	dmaCopy(sprite_fx_leakTiles, m_gfx,  16 * 16);
}

void CFxLeak::Shutdown()
{
	Reset();
}

void CFxLeak::Reset()
{
	oamSet(&oamSub, 31, m_location.X - m_xOffset, m_location.Y, 1, 0, SpriteSize_16x16, SpriteColorFormat_256Color, m_gfx, -1, false, true, false, false, false);
}

void CFxLeak::UpdateVBlank()
{
	dmaCopy(sprite_fx_leakTiles + g_frameMap[m_frameNum] * 64, m_gfx, 16 * 16);

	oamSet(&oamSub, 31, m_location.X - m_xOffset, m_location.Y, 1, 0, SpriteSize_16x16, SpriteColorFormat_256Color, m_gfx, -1, false, false, false, false, false);
	
	if(m_waiting)
	{
		if(++m_frameCount == 100)
		{
			m_frameCount = 0;
			m_waiting = false;
			
			mmEffectEx(&g_sfx_waterdrip);
		}
		
		return;
	}
	
	if(m_location.Y < m_endPoint.Y)
		m_location.Y++;

	if(++m_frameCount == m_frameRate)
	{
		m_frameCount = 0;
		m_frameNum++;
		
		if(m_location.Y == m_endPoint.Y)
		{
			if(m_frameNum == 19)
			{
				m_location.Y = m_startPoint.Y;
				m_frameNum = 0;
				m_frameCount = 0;
				
				m_waiting = true;
			}
		}
		
		//static char buf[256];
		//sprintf(buf, "%d", g_frameMap[m_frameNum]);
		//fprintf(stderr, buf);
	}
}

void CFxLeak::UpdateHBlank()
{
}

void CFxLeak::SetLocation(int xStart, int yStart, int xEnd, int yEnd)
{
	m_location.X = m_startPoint.X = xStart;
	m_location.Y = m_startPoint.Y = yStart;
	m_endPoint.X = xEnd;
	m_endPoint.Y = yEnd;
	
	m_frameRate = ceil((yEnd - yStart) / 16.0);
}
