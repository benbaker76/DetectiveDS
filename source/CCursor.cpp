#include <nds.h>
#include "Text.h"
#include "CCursor.h"
#include "sprite_cursor.h"

CCursor::CCursor()
{
	m_anim = new CAnimation(ANIMTYPE_PINGPONG, 0, 4, CURSOR_FRAMES);
	
	m_gfx = oamAllocateGfx(&oamMain, SpriteSize_8x8, SpriteColorFormat_256Color);
	
	dmaCopy(sprite_cursorTiles, m_gfx, 8 * 8);
}

CCursor::~CCursor()
{
}

void CCursor::Update()
{
	m_anim->Update();
}

void CCursor::Hide()
{
	oamSet(&oamMain, 120, m_x, m_y, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, m_gfx, 0, false, true, false, false, false);
}

void CCursor::Show()
{
	dmaCopy(sprite_cursorTiles + 16 * m_anim->FrameNum(), m_gfx, 8 * 8);
	
	oamSet(&oamMain, 120, m_x * 8, m_y * 8, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, m_gfx, 0, false, false, false, false, false);
}
