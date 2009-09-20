#include <nds.h>
#include <stdio.h>
#include "sprite_misc.h"
#include "Text.h"
#include "CConsole.h"

CConsole::CConsole(CCursor* pCursor)
{
	m_pCursor = pCursor;
	m_charPos = NULL;
	m_textPos = 0;
	m_menuPos = 0;
	m_menuOffset = 0;
	m_menuCount = 0;
	
	m_gfxArrow = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	dmaCopy(sprite_miscTiles + 256 * 6, m_gfxArrow, 32 * 32);
	
	for(int i=0; i<CONSOLE_MAX_TEXT; i++)
		m_textArray[i] = NULL;
		
	for(int i=0; i<CONSOLE_MENU_MAX_TEXT; i++)
		m_menuArray[i] = NULL;
	
	ClearText();
}

CConsole::~CConsole()
{
}

void CConsole::ClearText()
{
	m_x = CONSOLE_MAP_X;
	m_y = CONSOLE_MAP_Y;
	
	m_pCursor->SetPosition(m_x, m_y);
	
	for(int i=0; i<CONSOLE_MAX_TEXT; i++)
	{
		char buf[256];
		sprintf(buf, "%*s", CONSOLE_MAP_WIDTH, "");
		DrawText(buf, CONSOLE_MAP_X, CONSOLE_MAP_Y + i, false);
	}
}

void CConsole::ClearMenu()
{
	for(int i=0; i<CONSOLE_MENU_VISIBLE_TEXT; i++)
	{
		char buf[256];
		sprintf(buf, "%*s", CONSOLE_MENU_MAP_WIDTH, "");
		DrawText(buf, CONSOLE_MENU_MAP_X, CONSOLE_MENU_MAP_Y + i, false);
	}
}

void CConsole::CreateMenu(const char* menuArray[], int menuCount)
{
	m_menuCount = menuCount;
	m_menuPos = 0;
	m_menuOffset = 0;
	
	for(int i=0; i<CONSOLE_MENU_MAX_TEXT; i++)
		m_menuArray[i] = NULL;
	
	ClearMenu();
	
	for(int i=0; i<menuCount; i++)
		m_menuArray[i] = menuArray[i];
		
	DrawMenu();
}

void CConsole::DrawMenu()
{
	for(int i=0; i<CONSOLE_MENU_VISIBLE_TEXT; i++)
		DrawText(m_menuArray[m_menuOffset + i], CONSOLE_MENU_MAP_X, CONSOLE_MENU_MAP_Y + i, CONSOLE_MENU_MAP_WIDTH, false);
	
	if(m_menuCount > CONSOLE_MENU_VISIBLE_TEXT)
		ShowArrow();
}

void CConsole::HideMenu()
{
	HideSelectorBar();
	HideArrow();
}

bool CConsole::AddText(const char* text)
{
	for(int i=m_textPos; i<CONSOLE_MAX_TEXT; i++)
	{
		if(m_textArray[i] == NULL)
		{
			m_textArray[i] = text;
			
			Update();
			return true;
		}
	}
	
	for(int i=0; i<CONSOLE_MAX_TEXT; i++)
	{
		if(m_textArray[i] == NULL)
		{
			m_textArray[i] = text;
			
			Update();
			return true;
		}
	}
	
	return false;
}

void CConsole::Update()
{
	if(m_charPos == NULL)
	{
		for(int i=m_textPos; i<CONSOLE_MAX_TEXT; i++)
		{
			if(m_textArray[i] != NULL)
			{
				ClearText();
				m_charPos = m_textArray[i];
				
				if(*m_charPos == '\0')
				{
					m_textArray[i] = NULL;
					m_charPos = NULL;
					
					if(++m_textPos == CONSOLE_MAX_TEXT)
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
			m_x = CONSOLE_MAP_X;
			m_y++;
			m_pCursor->SetPosition(m_x, m_y);
			
			if(m_y == CONSOLE_MAP_Y + CONSOLE_MAP_HEIGHT)
				ClearText();
			break;
		case '\0':		// NULL Character (end of text)
			m_x = CONSOLE_MAP_X;
			m_y++;
			m_pCursor->SetPosition(m_x, m_y);
			m_charPos = NULL;
			m_textArray[m_textPos] = NULL;

			if(++m_textPos == CONSOLE_MAX_TEXT)
				m_textPos = 0;
			break;
		default:
			DrawChar(*m_charPos, m_x, m_y, false);
		
			m_x++;
			m_charPos++;
			m_pCursor->SetPosition(m_x, m_y);
			
			if(m_x >= CONSOLE_MAP_X + CONSOLE_MAP_WIDTH)
			{
				m_x = CONSOLE_MAP_X;
				m_y++;
				m_pCursor->SetPosition(m_x, m_y);
				
				if(m_y == CONSOLE_MAP_Y + CONSOLE_MAP_HEIGHT)
					ClearText();
			}
			break;
		}
	}
}

void CConsole::MoveSelectorBar(DirectionType directionType)
{
	switch(directionType)
	{
		case DIRECTION_UP:
			if(m_menuPos > 0)
				m_menuPos--;
			else if(m_menuOffset > 0)
				m_menuOffset--;
			break;
		case DIRECTION_DOWN:
			if(m_menuPos < CONSOLE_MENU_VISIBLE_TEXT-1)
				m_menuPos++;
			else if(m_menuPos + m_menuOffset < m_menuCount-1)
				m_menuOffset++;
			break;
		case DIRECTION_LEFT:
		case DIRECTION_RIGHT:
			break;
	}
	
	ClearMenu();
	DrawMenu();
}

void CConsole::DrawSelectorBar()
{
	m_selector.SetPosition(CONSOLE_MENU_X - 1, CONSOLE_MENU_Y + m_menuPos * 8 - 1);
	m_selector.Draw();
}

void CConsole::HideSelectorBar()
{
	m_selector.Hide();
}

void CConsole::HideArrow()
{
	oamSet(&oamMain, 120, 140, 176, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxArrow, 0, false, true, false, false, false);
}

void CConsole::ShowArrow()
{
	oamSet(&oamMain, 120, 140, 176, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxArrow,	0,	false, false, false, false,	 false);
}


