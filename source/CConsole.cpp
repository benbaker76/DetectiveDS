#include <nds.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "sprite_misc.h"
#include "Text.h"
#include "CConsole.h"

CConsole::CConsole(CCursor* pCursor)
{
	m_pCursor = pCursor;
	m_consoleMode = CONSOLEMODE_NORMAL;
	
	m_gfxArrowUp = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	m_gfxArrowDown = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	dmaCopy(sprite_miscTiles + 256 * 6, m_gfxArrowUp, 32 * 32);
	dmaCopy(sprite_miscTiles + 256 * 7, m_gfxArrowDown, 32 * 32);
	
	for(int i=0; i<CONSOLE_MAX_TEXT; i++)
		strcpy(m_textArray[i], "");

	for(int i=0; i<CONSOLE_MENU_MAX_TEXT; i++)
		m_menuArray[i] = NULL;
	
	Clear();
}

CConsole::~CConsole()
{
}

void CConsole::Clear()
{
	m_frameCount = 0;
	m_lineCount = 0;
	m_linePos = 0;
	m_lineOffset = 0;
		
	ClearText();
	
	m_pCursor->SetPosition(CONSOLE_MAP_X, CONSOLE_MAP_Y);
	
	HideArrows();
}

void CConsole::ClearText()
{
	for(int i=0; i<CONSOLE_MAX_VISIBLE_TEXT; i++)
	{
		static char buf[CONSOLE_MAP_WIDTH+2];
		sprintf(buf, "%*s", CONSOLE_MAP_WIDTH, "");
		DrawString(buf, CONSOLE_MAP_X, CONSOLE_MAP_Y + i, false);
	}
}

bool CConsole::AddText(const char* text)
{
	m_consoleMode = CONSOLEMODE_NORMAL;
	
	Clear();
	
	if(text == NULL)
		return false;
	
	m_lineCount = WordWrap(text);
	
	if(m_lineCount > CONSOLE_MAX_VISIBLE_TEXT)
	{
		ShowArrows();
		
		return true;
	}
	
	return false;
}

void CConsole::DrawText()
{
	for(int i=0; i<CONSOLE_MAX_VISIBLE_TEXT && m_lineOffset + i < m_lineCount; i++)
		DrawString(m_textArray[m_lineOffset + i], CONSOLE_MAP_X, CONSOLE_MAP_Y + i, false);
}

void CConsole::Update()
{
	m_frameCount++;
	
	if(m_frameCount > 3)
	{
		m_frameCount = 0;
		
		if(m_linePos < m_lineCount && m_linePos < CONSOLE_MAX_VISIBLE_TEXT)
		{	
			DrawString(m_textArray[m_linePos], CONSOLE_MAP_X, CONSOLE_MAP_Y + m_linePos, false);
			m_linePos++;
			
			m_pCursor->SetPosition(CONSOLE_MAP_X, CONSOLE_MAP_Y + m_linePos);
		}
	}
}

void CConsole::Move(DirectionType directionType)
{
	switch(directionType)
	{
		case DIRECTION_UP:
			if(m_lineOffset > 0)
				m_lineOffset--;
			break;
		case DIRECTION_DOWN:
			if(m_lineOffset + CONSOLE_MAX_VISIBLE_TEXT < m_lineCount)
				m_lineOffset++;
			break;
		case DIRECTION_LEFT:
		case DIRECTION_RIGHT:
			break;
	}
	
	ClearText();
	DrawText();
}

bool CConsole::CheckTouch(int x, int y)
{
	if(x > 140 && x < 140 + 20 && y > 120 && y < 120 + 12)
	{
		Move(DIRECTION_UP);
		return true;
	}
	
	if(x > 140 && x < 140 + 20 && y > 176 && y < 176 + 12)
	{
		Move(DIRECTION_DOWN);
		return true;
	}
	
	return false;
}

void CConsole::ClearMenu()
{
	m_menuCount = 0;
	m_menuPos = 0;
	m_menuOffset = 0;
	
	for(int i=0; i<CONSOLE_MENU_MAX_TEXT; i++)
		m_menuArray[i] = NULL;
	
	ClearMenuText();
	HideArrows();
}

void CConsole::ClearMenuText()
{
	for(int i=0; i<CONSOLE_MENU_VISIBLE_TEXT; i++)
	{
		static char buf[CONSOLE_MENU_MAP_WIDTH+2];
		sprintf(buf, "%*s", CONSOLE_MENU_MAP_WIDTH, "");
		DrawString(buf, CONSOLE_MENU_MAP_X, CONSOLE_MENU_MAP_Y + i, false);
	}
}

bool CConsole::AddMenuItem(const char* text, void* object)
{
	for(int i=0; i<CONSOLE_MENU_MAX_TEXT; i++)
	{
		if(m_menuArray[i] == NULL)
		{
			m_menuArray[i] = text;
			m_objectArray[i] = object;
			
			m_menuCount++;
			
			return true;
		}
	}
	
	return false;
}

void CConsole::ShowMenu()
{
	m_consoleMode = CONSOLEMODE_MENU;
	
	for(int i=0; i<CONSOLE_MENU_VISIBLE_TEXT && m_menuOffset + i < m_menuCount; i++)
		DrawString(m_menuArray[m_menuOffset + i], CONSOLE_MENU_MAP_X, CONSOLE_MENU_MAP_Y + i, CONSOLE_MENU_MAP_WIDTH, false);
	
	if(m_menuCount > CONSOLE_MENU_VISIBLE_TEXT)
		ShowArrows();
}

void CConsole::HideMenu()
{
	HideSelectorBar();
	HideArrows();
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
			if(m_menuPos < CONSOLE_MENU_VISIBLE_TEXT-1 && m_menuPos < m_menuCount-1)
				m_menuPos++;
			else if(m_menuPos + m_menuOffset < m_menuCount-1)
				m_menuOffset++;
			break;
		case DIRECTION_LEFT:
		case DIRECTION_RIGHT:
			break;
	}
	
	ClearMenuText();
	ShowMenu();
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

void CConsole::HideArrows()
{
	oamSet(&oamMain, 119, 140, (m_consoleMode == CONSOLEMODE_NORMAL ? 120 : 144), 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxArrowUp, 0, false, true, false, false, false);
	oamSet(&oamMain, 120, 140, 176, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxArrowDown, 0, false, true, false, false, false);
}

void CConsole::ShowArrows()
{
	oamSet(&oamMain, 119, 140, (m_consoleMode == CONSOLEMODE_NORMAL ? 120 : 144), 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxArrowUp, 0, false, false, false, false, false);
	oamSet(&oamMain, 120, 140, 176, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxArrowDown, 0,	false, false, false, false, false);
}

bool CConsole::CheckMenuTouch(int x, int y)
{
	int mapX = x / 8;
	int mapY = y / 8;
	
	if(mapX < 1 || mapX > 19 || mapY < 18 || mapY > 23)
		return false;
		
	if(x > 140 && x < 140 + 20 && y > 144 && y < 144 + 12)
	{
		//MoveSelectorBar(DIRECTION_UP);
		
		if(m_menuOffset > 0)
			m_menuOffset--;
			
		ClearMenuText();
		ShowMenu();
		
		return false;
	}
	
	if(x > 140 && x < 140 + 20 && y > 176 && y < 176 + 12)
	{
		//MoveSelectorBar(DIRECTION_DOWN);
		
		if(m_menuOffset + CONSOLE_MENU_VISIBLE_TEXT < m_menuCount)
			m_menuOffset++;
			
		ClearMenuText();
		ShowMenu();
		
		return false;
	}

	m_menuPos = mapY - 18;
	
	return true;
}

int CConsole::WordWrap(const char* text)
{
	char c = '\0';
	static char line[CONSOLE_MAP_WIDTH+2], word[CONSOLE_MAX_WORD+2];
	int newline = 0, line_pos = 0, word_pos = 0, line_count = 0;

	while(1)
	{
        c = *text++;

        if (c == '\0')
		{
            if (line_pos > 0)
			{
                line[line_pos] = '\0';
				strcpy(m_textArray[line_count++], line);
            }

            return line_count;
        }
		
        if (c == '\n')
			newline = 1;

        line[line_pos++] = word[word_pos++] = c;

        if (isspace(c))
            word_pos = 0;

        if (word_pos > CONSOLE_MAX_WORD)
		{
            word[word_pos] = '\0';
            return line_count;
        }

        if (newline || line_pos > CONSOLE_MAP_WIDTH)
		{
            newline = 0;
            line_pos -= word_pos;

            while(isspace(line[--line_pos]));

            line[line_pos+1] = '\0';
            strcpy(m_textArray[line_count++], line);
            strncpy(line, word, word_pos);
            line_pos = word_pos;
        }
    }

	return line_count;
}
