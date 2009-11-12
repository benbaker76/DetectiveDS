#include <nds.h>
#include <math.h>
#include "TDG.h"
#include "Gfx.h"
#include "CFxManager.h"
#include "CFxRat.h"
#include "Text.h"

void CFxRat::Initialize()
{
	m_location.X = 0;
	m_location.Y = 0;
	m_xOffset = 0;
	m_frameNum = 0;
	m_frameCount = 0;
	m_direction = DIRECTION_LEFT;
	m_pointPos = 0;
	m_waiting = false;
	
	for(int i=0; i<MAX_POINTS; i++)
		m_pointArray[i] = NULL;
	
	m_gfx = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);
	
	dmaCopy(sprite_fx_ratTiles, m_gfx,  16 * 16);
}

void CFxRat::Shutdown()
{
	Reset();
}

void CFxRat::Reset()
{
	oamSet(&oamSub, 30, (int)m_location.X - m_xOffset, (int)m_location.Y, 1, 0, SpriteSize_16x16, SpriteColorFormat_256Color, m_gfx, -1, false, true, false, false, false);
}

void CFxRat::UpdateVBlank()
{
	bool hFlip = false;
	bool vFlip = false;
	
	if(m_waiting)
	{
		if(++m_frameCount == 500)
		{
			m_frameCount = 0;
			m_waiting = false;
		}
	}
	else
	{
		int xDist = m_pointArray[m_pointPos]->X - m_location.X;
		int yDist = m_pointArray[m_pointPos]->Y - m_location.Y;
		
		float radians = atan2(yDist, xDist);
		float degrees = radians * (180 / PI) + 180;
		
		m_location.X += cos(radians);
		m_location.Y += sin(radians);
		
		if(degrees > 315)
			m_direction = DIRECTION_LEFT;
		else if(degrees > 225)
			m_direction = DIRECTION_DOWN;
		else if(degrees > 135)
			m_direction = DIRECTION_RIGHT;
		else if(degrees > 45)
			m_direction = DIRECTION_UP;
		else
			m_direction = DIRECTION_LEFT;
		
		if (yDist > 0)
		{
			m_direction = DIRECTION_DOWN;
			vFlip = true;
		}
		else if(yDist < 0)
		{
			m_direction = DIRECTION_UP;
		}
		else if(xDist > 0)
		{
			m_direction = DIRECTION_RIGHT;
		}
		else
		{
			m_direction = DIRECTION_LEFT;
			hFlip = true;
		}
		
		if(xDist == 0 && yDist == 0)
		{
			m_location.X = m_pointArray[m_pointPos]->X;
			m_location.Y = m_pointArray[m_pointPos]->Y;
			
			m_pointPos = rand() % 4;
			
			m_waiting = true;
		}
		
		//static char buf[256];
		//sprintf(buf, "abs(xDist):%d abs(yDist):%d m_pointPos:%d", xDist, yDist, m_pointPos);
		//fprintf(stderr, buf);
		//PrintDirection(m_direction);
		
		dmaCopy(sprite_fx_ratTiles + (m_frameNum + (m_direction == DIRECTION_UP || m_direction == DIRECTION_DOWN ? 4 : 0 )) * 64, m_gfx, 16 * 16);
		
		if(++m_frameNum == 4)
			m_frameNum = 0;
	}
	
	oamSet(&oamSub, 30, (int) m_location.X - m_xOffset, (int)m_location.Y, 1, 0, SpriteSize_16x16, SpriteColorFormat_256Color, m_gfx, -1, false, false, hFlip, vFlip, false);
}

void CFxRat::UpdateHBlank()
{
}

void CFxRat::SetPoints(Point* p1, Point* p2, Point* p3, Point* p4)
{
	m_pointArray[0] = p1;
	m_pointArray[1] = p2;
	m_pointArray[2] = p3;
	m_pointArray[3] = p4;
	
	m_pointPos = rand() % 4;
	
	m_location.X = m_pointArray[m_pointPos]->X;
	m_location.Y = m_pointArray[m_pointPos]->Y;
}
