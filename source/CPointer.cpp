#include "TDG.h"
#include "CPointer.h"

CPointer::CPointer()
{
	m_point = new Point(0, 0);
	m_rect = new Rect(0, 0, 256, 192);

	m_gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	dmaCopy(sprite_miscTiles + 256 * 1, m_gfx, 32 * 32);
}

CPointer::~CPointer()
{
}

void CPointer::Move(int keys_held)
{
	if(keys_held & KEY_UP)
	{
		m_y -= m_speed[DIRECTION_UP];
		m_speed[DIRECTION_UP] += POINTER_SPEED;
	}
	else
	{
		m_speed[DIRECTION_UP] = 0;
	}
	
	if(keys_held & KEY_DOWN)
	{
		m_y += m_speed[DIRECTION_DOWN];
		m_speed[DIRECTION_DOWN] += POINTER_SPEED;
	}
	else
	{
		m_speed[DIRECTION_DOWN] = 0;
	}
	
	if(keys_held & KEY_LEFT)
	{
		m_x -= m_speed[DIRECTION_LEFT];
		m_speed[DIRECTION_LEFT] += POINTER_SPEED;
	}
	else
	{
		m_speed[DIRECTION_LEFT] = 0;
	}
	
	if(keys_held & KEY_RIGHT)
	{
		m_x += m_speed[DIRECTION_RIGHT];
		m_speed[DIRECTION_RIGHT] += POINTER_SPEED;
	}
	else
	{
		m_speed[DIRECTION_RIGHT] = 0;
	}
	
	if(m_x < m_rect->X - POINTER_X)
		m_x = m_rect->X - POINTER_X;
	if(m_x > m_rect->X + m_rect->Width - POINTER_X)
		m_x = m_rect->X + m_rect->Width - POINTER_X;
	if(m_y < m_rect->Y)
		m_y = m_rect->Y;
	if(m_y > m_rect->Y + m_rect->Height)
		m_y = m_rect->Y + m_rect->Height;
}

void CPointer::Hide()
{
	oamSet(&oamMain, 121, m_x, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfx, 0, false, true, false, false, false);
}

void CPointer::Update()
{
	oamSet(&oamMain, 121, m_x, m_y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfx, 0, false, false, false, false,	 false);
}