#include <nds.h>
#include "CMenu.h"

CMenu::CMenu()
{
	m_gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	dmaCopy(sprite_miscTiles + 256 * 2, m_gfx, 32 * 32);
}

CMenu::~CMenu()
{
}

void CMenu::ClearIcons()
{
	for(int i=0; i<MAX_ICONS; i++)
		m_iconArray[i] = ICON_NONE;
}

void CMenu::AddIconSet(IconSet iconSet)
{
	switch(iconSet)
	{
	case ICONSET_NOTHING:
		break;
	case ICONSET_GENERAL:
		AddIcon(ICON_OPEN);
		AddIcon(ICON_EXAMINE);
		AddIcon(ICON_TIME);
		AddIcon(ICON_INVENTORY);
		AddIcon(ICON_USE);
		AddIcon(ICON_ACCUSE);
		break;
	case ICONSET_DOOR_OPEN:
		AddIcon(ICON_DOOR_OPEN);
		AddIcon(ICON_INVENTORY);
		break;
	case ICONSET_DOOR_CLOSE:
		AddIcon(ICON_DOOR_CLOSE);
		AddIcon(ICON_INVENTORY);
		break;
	case ICONSET_ITEM:
		AddIcon(ICON_EXAMINE);
		AddIcon(ICON_PLACE);
		AddIcon(ICON_OPEN);
		break;
	}
}

bool CMenu::AddIcon(IconType iconType)
{
	bool retVal = false;
	
	for(int i=0; i<MAX_ICONS; i++)
	{
		if(m_iconArray[i] == ICON_NONE)
		{
			m_iconArray[i] = iconType;
			retVal = true;
			break;
		}
	}
	
	return retVal;
}
	
void CMenu::Show(MenuMode menuMode)
{
	m_menuMode = menuMode;
			
	Draw();
}

void CMenu::Draw()
{
	for(int y=0; y<3; y++)
		for(int x=0; x<3; x++)
			DrawIcon(m_iconArray[x + y * ICON_WIDTH], 21 + x * ICON_WIDTH, 16 + y * ICON_HEIGHT, false);
}

void CMenu::Hide()
{
	ClearIcons();
	HideBox();
	Draw();
}

void CMenu::DrawIcon(IconType iconType, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB) : BG_MAP_RAM(BG1_MAP_BASE)) + (x + y * 32);
	
	for(u32 y=0; y<2; y++)
		for(u32 x=0; x<3; x++)
			*(pMap+x+y*32) = iconType * 6 + x + y * ICON_WIDTH;
}

void CMenu::HideBox()
{
	oamSet(&oamMain, 122, 0, 0, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfx, 0, false, true, false, false, false);
}

void CMenu::DrawBox(int x, int y)
{
	int mapX = x / 8;
	int mapY = y / 8;
	
	if(mapX < 21 || mapX > 30 || mapY < 16 || mapY > 22)
		return;
	
	for(int y=0; y<3; y++)
		for(int x=0; x<3; x++)
			if((mapX >= (MENU_X / 8) + (x * ICON_WIDTH)) && (mapX < (MENU_X / 8) + (x * ICON_WIDTH) + ICON_WIDTH) && (mapY >= (MENU_Y / 8) + (y * ICON_HEIGHT)) && (mapY < (MENU_Y / 8) + (y * ICON_HEIGHT) + ICON_HEIGHT))
				if(m_iconArray[x + y * ICON_WIDTH] != NULL)
				{
					oamSet(&oamMain, 122, MENU_X + (x * ICON_WIDTH * 8) - 2, MENU_Y + (y * ICON_HEIGHT * 8) - 2, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, m_gfx, 0, false, false, false, false, false);
					return;
				}
				
	HideBox();
}

IconType CMenu::CheckIconHit(int x, int y)
{
	int mapX = x / 8;
	int mapY = y / 8;
	
	if(mapX < 21 || mapX > 30 || mapY < 16 || mapY > 22)
		return ICON_NONE;
	
	for(int y=0; y<3; y++)
		for(int x=0; x<3; x++)
			if((mapX >= (MENU_X / 8) + (x * ICON_WIDTH)) && (mapX < (MENU_X / 8) + (x * ICON_WIDTH) + ICON_WIDTH) && (mapY >= (MENU_Y / 8) + (y * ICON_HEIGHT)) && (mapY < (MENU_Y / 8) + (y * ICON_HEIGHT) + ICON_HEIGHT))
				if(m_iconArray[x + y * ICON_WIDTH] != NULL)
					return m_iconArray[x + y * ICON_WIDTH];
	
	return ICON_NONE;
}
