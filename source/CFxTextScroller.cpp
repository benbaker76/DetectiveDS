#include <nds.h>
#include <stdio.h>
#include <math.h>
#include "Gfx.h"
#include "CFxManager.h"
#include "CFxTextScroller.h"
#include "Text.h"

void CFxTextScroller::Initialize()
{
	m_scrollPos = 0;
	m_textPos = 0;
	m_charPos = NULL;
	
	BACKGROUND.scroll[0].x = 0;
	
	ClearText();
}

void CFxTextScroller::Shutdown()
{
	BACKGROUND.scroll[0].x = 0;
	static char buf[34];
	sprintf(buf, "%*s", 32, "");
	DrawStringLarge(buf, 0, 11, false);
}

void CFxTextScroller::UpdateVBlank()
{
	if((m_scrollPos++ & 0x7) == 0)
	{
		if(m_charPos == NULL)
		{
			for(int i=m_textPos; i<MAX_TEXT_SCROLLER; i++)
			{
				if(m_textArray[i] != NULL)
				{
					m_charPos = m_textArray[i];
					break;
				}
			}
		
			//DrawCharLarge(' ', (((m_scrollPos - 8) >> 3) & 0x1F), (((((m_scrollPos - 8) >> 3) >> 5) & 1) << 5) + 11, false);
			DrawCharLarge(' ', m_scrollPos >> 3, 11, false);
		}
		else
		{
			//DrawCharLarge(*m_charPos, (((m_scrollPos - 8) >> 3) & 0x1F), (((((m_scrollPos - 8) >> 3) >> 5) & 1) << 5) + 11, false);
			DrawCharLarge(*m_charPos, m_scrollPos >> 3, 11, false);
			
			if(*(++m_charPos) == '\0')
			{
				m_charPos = NULL;
				
				if(!m_loop)
				{
					m_textArray[m_textPos] = NULL;

					if(++m_textPos == MAX_TEXT_SCROLLER)
						m_textPos = 0;
				}
			}
		}
	}
}

void CFxTextScroller::UpdateHBlank()
{
	if(REG_VCOUNT > 80 && REG_VCOUNT < 104)
		BACKGROUND.scroll[0].x = m_scrollPos;
	else if(REG_VCOUNT > 104)
		BACKGROUND.scroll[0].x = 0;
}

void CFxTextScroller::ClearText()
{
	m_charPos = 0;

	for(int i=0; i<MAX_TEXT_SCROLLER; i++)
		m_textArray[i] = NULL;
}

bool CFxTextScroller::AddText(const char* text)
{
	for(int i=m_textPos; i<MAX_TEXT_SCROLLER; i++)
	{
		if(m_textArray[i] == NULL)
		{
			strcpy(m_textBuffer[i], text);
			
			m_textArray[i] = m_textBuffer[i];
			return true;
		}
	}
	
	for(int i=0; i<MAX_TEXT_SCROLLER; i++)
	{
		if(m_textArray[i] == NULL)
		{
			strcpy(m_textBuffer[i], text);
			
			m_textArray[i] = m_textBuffer[i];
			return true;
		}
	}
	
	return false;
}
