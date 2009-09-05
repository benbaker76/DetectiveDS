#include <nds.h>
#include <stdio.h>
#include "TDG.h"
#include "Text.h"
#include "CKeyboard.h"

CKeyboard::CKeyboard()
{
}

CKeyboard::~CKeyboard()
{
}

void CKeyboard::Initialize()
{
	m_textEntry[0] = NULL;
	m_charPos = 0;

	dmaCopy(keyboardTiles, BG_TILE_RAM(BG3_TILE_BASE), keyboardTilesLen);
	dmaCopy(keyboardMap, BG_MAP_RAM(BG3_MAP_BASE), keyboardMapLen);
	
	for(int i=0; i<7; i++)
		DrawText(g_KeyboardText[i], 0, 16 + i, false);
}

void CKeyboard::Shutdown()
{
	dmaCopy(menu_bottomTiles, BG_TILE_RAM(BG3_TILE_BASE), menu_bottomTilesLen);
	dmaCopy(menu_bottomMap, BG_MAP_RAM(BG3_MAP_BASE), menu_bottomMapLen);
}

void CKeyboard::CheckKeyTouch(int touchX, int touchY)
{
	int mapX = touchX / 8;
	int mapY = touchY / 8;
	
	if(mapY < 16)
		return;
		
	if(m_charPos < MAX_TEXT_ENTRY)
	{
		char c = g_KeyboardText[mapY - 16][mapX];
		
		if(c != ' ')
		{
			m_textEntry[m_charPos] = c;
			m_textEntry[m_charPos+1] = NULL;
			
			DrawText(m_textEntry, 1, 11, false);
			
			m_charPos++;
		}
	}
}
