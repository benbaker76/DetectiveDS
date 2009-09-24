#include <nds.h>
#include <stdio.h>
#include "TDG.h"
#include "Text.h"
#include "CKeyboard.h"
#include "Gfx.h"

CKeyboard::CKeyboard(CCursor* pCursor)
{
	m_pCursor = pCursor;
}

CKeyboard::~CKeyboard()
{
}

void CKeyboard::Show(const char* string)
{
	m_textEntry[0] = NULL;
	m_charPos = 0;

	dmaCopy(keyboardTiles, BG_TILE_RAM(BG3_TILE_BASE), keyboardTilesLen);
	dmaCopy(keyboardMap, BG_MAP_RAM(BG3_MAP_BASE), keyboardMapLen);
	
	DrawText(string, 1, 11, false);
	
	for(int i=0; i<7; i++)
		DrawText(g_KeyboardText[i], 0, 16 + i, false);
		
	m_pCursor->SetPosition(m_charPos + 1, 12);
}

void CKeyboard::Hide()
{
	dmaCopy(menu_bottomTiles, BG_TILE_RAM(BG3_TILE_BASE), menu_bottomTilesLen);
	dmaCopy(menu_bottomMap, BG_MAP_RAM(BG3_MAP_BASE), menu_bottomMapLen);
	ClearBG(0, false);
}

char CKeyboard::CheckKeyTouch(int x, int y)
{
	int mapX = x / 8;
	int mapY = y / 8;
	
	if(mapY < 16)
		return '\0';
		
	char c = g_KeyboardHit[mapY - 16][mapX];
	
	switch(c)
	{
	case '\e':
		break;
	case '\b':
		if(m_charPos > 0)
		{
			DrawText("  ", m_charPos, 12, false);
			m_textEntry[--m_charPos] = '\0';
			
			DrawText(m_textEntry, 1, 12, false);
			m_pCursor->SetPosition(m_charPos + 1, 12);
		}
		break;
	case '\0':
		break;
	case '\n':
		break;
	default:
		if(m_charPos < MAX_TEXT_ENTRY)
		{
			m_textEntry[m_charPos++] = c;
			m_textEntry[m_charPos] = '\0';
			
			DrawText(m_textEntry, 1, 12, false);
			m_pCursor->SetPosition(m_charPos + 1, 12);
		}
		break;
	}
	
	m_pCursor->Show();
	
	return c;
}
