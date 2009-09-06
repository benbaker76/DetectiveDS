#include <nds.h>
#include "Text.h"
#include "CCursor.h"

CCursor::CCursor()
{
	m_ping = true;
	m_lastUpdate = 0;
}

CCursor::~CCursor()
{
}

void CCursor::Update(int elapsedTime)
{
	m_lastUpdate += elapsedTime;
	
	if(m_lastUpdate > 50)
	{
		m_lastUpdate = 0;
		
		if(m_ping)
		{
			if(++m_frameNum >= CURSOR_FRAMES-1)
				m_ping = !m_ping;
		}
		else
		{
			if(--m_frameNum <= 0)
				m_ping = !m_ping;
		}
	}
}

void CCursor::Draw()
{
	DrawChar(123 + m_frameNum, m_x, m_y, false);
}
