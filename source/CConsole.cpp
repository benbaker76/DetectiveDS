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
	
	m_gfxArrowUp = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	m_gfxArrowDown = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	dmaCopy(sprite_miscTiles + 256 * 6, m_gfxArrowUp, 32 * 32);
	dmaCopy(sprite_miscTiles + 256 * 7, m_gfxArrowDown, 32 * 32);
		
	for(int i=0; i<CONSOLE_MENU_MAX_TEXT; i++)
		m_menuArray[i] = NULL;
	
	ClearText();
}

CConsole::~CConsole()
{
}

void CConsole::ClearText()
{
	m_pCursor->SetPosition(CONSOLE_MAP_X, CONSOLE_MAP_Y);
	//HideArrows();
	
	m_lineCount = 0;
	m_linePos = 0;
	m_lineOffset = 0;
	
	for(int i=0; i<CONSOLE_MAX_TEXT; i++)
	{
		char buf[256];
		sprintf(buf, "%*s", CONSOLE_MAP_WIDTH, "");
		DrawText(buf, CONSOLE_MAP_X, CONSOLE_MAP_Y + i, false);
	}
}

void CConsole::AddText(const char* text)
{
	ClearText();
	
	m_lineCount = WordWrap(text);
	
	//if(m_lineCount > CONSOLE_MAX_VISIBLE_TEXT)
	//	ShowArrows();
}

void CConsole::Update()
{
	m_frameCount++;
	
	if(m_frameCount > 4)
	{
		m_frameCount = 0;
		
		if(m_linePos < m_lineCount && m_linePos < CONSOLE_MAX_VISIBLE_TEXT)
		{
			DrawChar(' ', CONSOLE_MAP_X, CONSOLE_MAP_Y + m_linePos, false);
			DrawText(m_textArray[m_linePos], CONSOLE_MAP_X, CONSOLE_MAP_Y + m_linePos, false);
			m_linePos++;
			
			m_pCursor->SetPosition(CONSOLE_MAP_X, CONSOLE_MAP_Y + m_linePos);
		}
	}
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
		char buf[256];
		sprintf(buf, "%*s", CONSOLE_MENU_MAP_WIDTH, "");
		DrawText(buf, CONSOLE_MENU_MAP_X, CONSOLE_MENU_MAP_Y + i, false);
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
	for(int i=0; i<CONSOLE_MENU_VISIBLE_TEXT; i++)
		DrawText(m_menuArray[m_menuOffset + i], CONSOLE_MENU_MAP_X, CONSOLE_MENU_MAP_Y + i, CONSOLE_MENU_MAP_WIDTH, false);
	
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
	oamSet(&oamMain, 119, 140, 144, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxArrowUp, 0, false, true, false, false, false);
	oamSet(&oamMain, 120, 140, 176, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxArrowDown, 0, false, true, false, false, false);
}

void CConsole::ShowArrows()
{
	oamSet(&oamMain, 119, 140, 144, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxArrowUp, 0, false, false, false, false, false);
	oamSet(&oamMain, 120, 140, 176, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxArrowDown, 0,	false, false, false, false, false);
}

int CConsole::WordWrap(const char* text)
{
	char c = '\0', line[CONSOLE_MAP_WIDTH+2], word[CONSOLE_MAX_WORD+2];
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


