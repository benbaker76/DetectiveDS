#include <nds.h>
#include "Text.h"
#include "CTextConsole.h"

CTextConsole::CTextConsole()
{
	m_cursorX = CONSOLE_X;
	m_cursorY = CONSOLE_Y;
	m_cursorPing = true;
	
	ClearText();
}

CTextConsole::~CTextConsole()
{
}

void CTextConsole::ClearText()
{
	for(int i=0; i<MAX_TEXT_CONSOLE; i++)
	{
		m_textArray[i] = NULL;
		DrawText("                   ", CONSOLE_X, CONSOLE_Y + i, false);
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
	
	if(m_lastUpdate > 50)
	{
		m_lastUpdate = 0;
		
		if(m_charPos == NULL)
		{
			for(int i=m_textPos; i<MAX_TEXT_CONSOLE; i++)
			{
				if(m_textArray[i] != NULL)
				{
					m_charPos = m_textArray[i];
					break;
				}
			}
		}

		if(m_charPos != NULL)
		{
			DrawChar(*m_charPos, m_cursorX, m_cursorY, false);
			
			m_cursorX++;
			m_charPos++;
			
			if(m_cursorX >= CONSOLE_X + CONSOLE_WIDTH)
			{
				m_cursorX = CONSOLE_X;
				m_cursorY++;
				
				if(m_cursorY == CONSOLE_Y + CONSOLE_HEIGHT)
				{
					ClearText();
					m_cursorX = CONSOLE_X;
					m_cursorY = CONSOLE_Y;
				}
			}
			
			if(*m_charPos == '\n')
			{
				m_cursorX = CONSOLE_X;
				m_cursorY++;
				
				if(m_cursorY == CONSOLE_Y + CONSOLE_HEIGHT)
				{
					ClearText();
					m_cursorX = CONSOLE_X;
					m_cursorY = CONSOLE_Y;
				}
			}
			
			if(*m_charPos == '\0')
			{
				m_cursorX = CONSOLE_X;
				m_cursorY++;
				m_charPos = NULL;
				m_textArray[m_textPos] = NULL;

				if(++m_textPos == MAX_TEXT_CONSOLE)
					m_textPos = 0;
			}
		}
		
		DrawCursor();
	}
}

void CTextConsole::DrawCursor()
{
	DrawChar(123 + m_cursorFrame, m_cursorX, m_cursorY, false);
	
	if(m_cursorPing)
	{
		if(++m_cursorFrame >= CURSOR_FRAMES-1)
			m_cursorPing = !m_cursorPing;
	}
	else
	{
		if(--m_cursorFrame <= 0)
			m_cursorPing = !m_cursorPing;
	}
}
