#include <nds.h>
#include "Text.h"
#include "CCursor.h"

CCursor::CCursor()
{
	m_anim = new CAnimation(ANIMTYPE_PINGPONG, 0, 4, CURSOR_FRAMES);
}

CCursor::~CCursor()
{
}

void CCursor::Update()
{
	m_anim->Update();
}

void CCursor::Show()
{
	DrawChar(123 + m_anim->FrameNum(), m_x, m_y, false);
}
