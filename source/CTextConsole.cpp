#include <nds.h>
#include <stdio.h>
#include "Text.h"
#include "CTextConsole.h"

CTextConsole::CTextConsole()
{
	m_cursorPing = true;
	m_lastUpdate = 0;
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
	m_cursorX = CONSOLE_X;
	m_cursorY = CONSOLE_Y;
	
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
		DrawChar(123 + CURSOR_FRAMES, m_cursorX, m_cursorY, false);
		
		switch(*m_charPos)
		{
		case '\E':		// Clear Console
			m_charPos++;
			ClearText();
			break;
		case '\n':		// New line
			m_charPos++;
			m_cursorX = CONSOLE_X;
			m_cursorY++;
			
			if(m_cursorY == CONSOLE_Y + CONSOLE_HEIGHT)
				ClearText();
			break;
		case '\0':		// NULL Character (end of text)
			m_cursorX = CONSOLE_X;
			m_cursorY++;
			m_charPos = NULL;
			m_textArray[m_textPos] = NULL;

			if(++m_textPos == MAX_TEXT_CONSOLE)
				m_textPos = 0;
			break;
		default:
			DrawChar(*m_charPos, m_cursorX, m_cursorY, false);
		
			m_cursorX++;
			m_charPos++;
			
			if(m_cursorX >= CONSOLE_X + CONSOLE_WIDTH)
			{
				m_cursorX = CONSOLE_X;
				m_cursorY++;
				
				if(m_cursorY == CONSOLE_Y + CONSOLE_HEIGHT)
					ClearText();
			}
			break;
		}
	}
	
	if(m_lastUpdate > 50)
	{
		m_lastUpdate = 0;
		
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
