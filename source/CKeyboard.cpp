#include <nds.h>
#include <stdio.h>
#include "TDG.h"
#include "Text.h"
#include "CKeyboard.h"
#include "Gfx.h"

CKeyboard::CKeyboard(CCursor* pCursor)
{
	m_pCursor = pCursor;
	
	m_gfxBox = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	m_gfxBoxLeft = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	m_gfxBoxRight = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	dmaCopy(sprite_miscTiles + 256 * 8, m_gfxBox, 32 * 32);
	dmaCopy(sprite_miscTiles + 256 * 9, m_gfxBoxLeft, 32 * 32);
	dmaCopy(sprite_miscTiles + 256 * 10, m_gfxBoxRight, 32 * 32);
}

CKeyboard::~CKeyboard()
{
}

void CKeyboard::Show(const char* string)
{
	m_textEntry[0] = NULL;
	m_charPos = 0;
	m_x = KEYBOARD_LEFT;
	m_y = KEYBOARD_TOP;

	dmaCopy(keyboardTiles, BG_TILE_RAM(BG3_TILE_BASE), keyboardTilesLen);
	dmaCopy(keyboardMap, BG_MAP_RAM(BG3_MAP_BASE), keyboardMapLen);
	
	DrawString(string, 1, 11, false);
	
	for(int i=0; i<7; i++)
		DrawString(g_keyboardText[i], 0, 16 + i, false);
		
	m_pCursor->SetPosition(m_charPos + 1, 12);
	DrawBox();
}

void CKeyboard::Hide()
{
	dmaCopy(menu_bottomTiles, BG_TILE_RAM(BG3_TILE_BASE), menu_bottomTilesLen);
	dmaCopy(menu_bottomMap, BG_MAP_RAM(BG3_MAP_BASE), menu_bottomMapLen);
	ClearBG(0, false);
	HideBox();
}

void CKeyboard::HideBox()
{
	oamSet(&oamMain, 122, 0, 0, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxBox, 0, false, true, false, false, false);
	oamSet(&oamMain, 123, 0, 0, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxBoxLeft, 0, false, true, false, false, false);
	oamSet(&oamMain, 124, 0, 0, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxBoxRight, 0, false, true, false, false, false);
}

void CKeyboard::DrawBox()
{
	HideBox();
	
	char c = g_keyboardHit[m_y - KEYBOARD_TOP][m_x];

	switch(c)
	{
	case '\e':
		oamSet(&oamMain, 123, 24 * 8 - 3, m_y * 8 - 3, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxBoxLeft, 0, false, false, false, false, false);
		oamSet(&oamMain, 124, 24 * 8 - 3 + 6, m_y * 8 - 3, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxBoxRight, 0, false, false, false, false, false);
		break;
	case '\b':
		oamSet(&oamMain, 123, 24 * 8 - 3, m_y * 8 - 3, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxBoxLeft, 0, false, false, false, false, false);
		oamSet(&oamMain, 124, 24 * 8 - 3 + 6, m_y * 8 - 3, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxBoxRight, 0, false, false, false, false, false);
		break;
	case '\n':
		oamSet(&oamMain, 123, 23 * 8 - 3, m_y * 8 - 3, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxBoxLeft, 0, false, false, false, false, false);
		oamSet(&oamMain, 124, 23 * 8 - 3 + 14, m_y * 8 - 3, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxBoxRight, 0, false, false, false, false, false);
		break;
	case ' ':
		oamSet(&oamMain, 123, 20 * 8 - 3, m_y * 8 - 3, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxBoxLeft, 0, false, false, false, false, false);
		oamSet(&oamMain, 124, 20 * 8 - 3 + 30, m_y * 8 - 3, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxBoxRight, 0, false, false, false, false, false);
		break;
	default:
		oamSet(&oamMain, 122, m_x * 8 - 3, m_y * 8 - 3, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfxBox, 0, false, false, false, false, false);
		break;
	}
}

char CKeyboard::CheckKeyPress(int keys_released)
{
	char c = '\0';
	
	if(keys_released & KEY_UP)
	{
		if(m_y - 2 >= KEYBOARD_TOP)
		{
			m_y -= 2;
			
			if(m_y >= 18)
				m_x -= 1;
		}
	}
	
	if(keys_released & KEY_DOWN)
	{
		if(m_y + 2 <= KEYBOARD_BOTTOM)
		{
			m_y += 2;
			
			if(m_y >= 20 && m_x < 27)
				m_x += 1;
			
			if(m_x == 27 && m_y == 20)
				m_x -= 1;
				
			if(m_x == 27 && m_y == 22)
				m_x -= 1;
		}
	}
	
	if(keys_released & KEY_LEFT)
	{
		if(m_x - 2 >= KEYBOARD_LEFT)
		{
			m_x -= 2;
			
			if(m_x == 4 && m_y == 22)
				m_x += 2;
				
			if(m_x >= 24 && (m_y == 16 || m_y == 18))
				m_x = 22;
				
			if(m_x >= 23 && m_y == 20)
				m_x = 21;
				
			if(m_x >= 20 && m_y == 22)
				m_x = 18;
		}
	}
	
	if(keys_released & KEY_RIGHT)
	{
		if(m_x + 2 <= KEYBOARD_RIGHT)
		{
			m_x += 2;
		}
	}
	
	if(keys_released & KEY_A)
		c = ProcessKey(m_x, m_y);
	
	DrawBox();
	
	m_pCursor->Show();
	
	return c;
}

char CKeyboard::CheckKeyTouch(int x, int y)
{
	int mapX = x / 8;
	int mapY = y / 8;
	
	if(mapY < KEYBOARD_TOP)
		return '\0';
	
	char c = ProcessKey(mapX, mapY);
	
	if(c != '\0')
	{
		m_x = mapX;
		m_y = mapY;
		
		DrawBox();
	}
	
	m_pCursor->Show();
	
	return c;
}

char CKeyboard::ProcessKey(int x, int y)
{
	char c = g_keyboardHit[y - KEYBOARD_TOP][x];
	
	switch(c)
	{
	case '\e':
		break;
	case '\b':
		if(m_charPos > 0)
		{
			DrawString("  ", m_charPos, 12, false);
			m_textEntry[--m_charPos] = '\0';
			
			DrawString(m_textEntry, 1, 12, false);
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
			
			DrawString(m_textEntry, 1, 12, false);
			m_pCursor->SetPosition(m_charPos + 1, 12);
		}
		break;
	}
	
	return c;
}
