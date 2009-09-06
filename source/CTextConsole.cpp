#include <nds.h>
#include <stdio.h>
#include "Text.h"
#include "CTextConsole.h"

CTextConsole::CTextConsole(CCursor* pCursor)
{
	m_pCursor = pCursor;
	m_charPos = NULL;
	m_textPos = 0;
	
	for(int i=0; i<MAX_TEXT_CONSOLE; i++)
		m_textArray[i] = NULL;
	
	ClearText();
}

CTextConsole::~CTextConsole()
{
}

void CTextConsole::ClearText()
{
	m_x = CONSOLE_X;
	m_y = CONSOLE_Y;
	m_pCursor->SetPosition(m_x, m_y);
	
	for(int i=0; i<MAX_TEXT_CONSOLE; i++)
	{
		char buf[256];
		sprintf(buf, "%*s", CONSOLE_WIDTH, "");
		DrawText(buf, CONSOLE_X, CONSOLE_Y + i, false);
	}
}

bool CTextConsole::AddText(const char* text)
{
	for(int i=m_textPos; i<MAX_TEXT_CONSOLE; i++)
	{
		if(m_textArray[i] == NULL)
		{
			m_textArray[i] = text;
			return true;
		}
	}
	
	for(int i=0; i<MAX_TEXT_CONSOLE; i++)
	{
		if(m_textArray[i] == NULL)
		{
			m_textArray[i] = text;
			return true;
		}
	}
	
	return false;
}

void CTextConsole::Update(int elapsedTime)
{
	m_lastUpdate += elapsedTime;
	
	if(m_charPos == NULL)
	{
		for(int i=m_textPos; i<MAX_TEXT_CONSOLE; i++)
		{
			if(m_textArray[i] != NULL)
			{
				ClearText();
				m_charPos = m_textArray[i];
				
				if(*m_charPos == '\0')
				{
					m_textArray[i] = NULL;
					m_charPos = NULL;
					
					if(++m_textPos == MAX_TEXT_CONSOLE)
						m_textPos = 0;
				}
				
				break;
			}
		}
	}

	if(m_charPos != NULL)
	{
		DrawChar(123 + CURSOR_FRAMES, m_x, m_y, false);
		
		switch(*m_charPos)
		{
		case '\e':		// Clear Console
			m_charPos++;
			ClearText();
			break;
		case '\n':		// New line
			m_charPos++;
			m_x = CONSOLE_X;
			m_y++;
			m_pCursor->SetPosition(m_x, m_y);
			
			if(m_y == CONSOLE_Y + CONSOLE_HEIGHT)
				ClearText();
			break;
		case '\0':		// NULL Character (end of text)
			m_x = CONSOLE_X;
			m_y++;
			m_pCursor->SetPosition(m_x, m_y);
			m_charPos = NULL;
			m_textArray[m_textPos] = NULL;

			if(++m_textPos == MAX_TEXT_CONSOLE)
				m_textPos = 0;
			break;
		default:
			DrawChar(*m_charPos, m_x, m_y, false);
		
			m_x++;
			m_charPos++;
			m_pCursor->SetPosition(m_x, m_y);
			
			if(m_x >= CONSOLE_X + CONSOLE_WIDTH)
			{
				m_x = CONSOLE_X;
				m_y++;
				m_pCursor->SetPosition(m_x, m_y);
				
				if(m_y == CONSOLE_Y + CONSOLE_HEIGHT)
					ClearText();
			}
			break;
		}
	}
}
