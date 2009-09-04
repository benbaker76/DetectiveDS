#include <nds.h>
#include "CMenu.h"

CMenu::CMenu()
{
	ClearIcons();
		
	AddIcon(ICON_OPEN);
	AddIcon(ICON_EXAMINE);
	AddIcon(ICON_TIME);
	AddIcon(ICON_INVENTORY);
	AddIcon(ICON_USE);
	AddIcon(ICON_ACCUSE);
}

CMenu::~CMenu()
{
}

void CMenu::ClearIcons()
{
	for(int i=0; i<MAX_ICONS; i++)
		m_iconArray[i] = ICON_NONE;
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
	
bool CMenu::RemoveIcon(IconType iconType)
{
	bool retVal = false;
	
	for(int i=0; i<MAX_ICONS; i++)
	{
		if(m_iconArray[i] == iconType)
		{
			m_iconArray[i] = ICON_NONE;
			retVal = true;
			break;
		}
	}
	
	return retVal;
}

void CMenu::DrawMenu()
{
	for(int y=0; y<2; y++)
		for(int x=0; x<3; x++)
			DrawIcon(m_iconArray[x + y * 3], 21 + x * 3, 16 + y * 2, false);
}

void CMenu::DrawIcon(IconType iconType, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB) : BG_MAP_RAM(BG1_MAP_BASE)) + (x + y * 32);
	
	for(u32 y=0; y<2; y++)
		for(u32 x=0; x<3; x++)
			*(pMap+x+y*32) = iconType * 6 + x + y * 3;
}

IconType CMenu::CheckIconClick(int touchX, int touchY)
{
	int mapX = touchX / 8;
	int mapY = touchY / 8;
	
	if(mapX < 21 || mapX > 30 || mapY < 16 || mapY > 22)
		return ICON_NONE;
	
	for(int y=0; y<3; y++)
		for(int x=0; x<3; x++)
			if((mapX >= 21 + (x * 3)) && (mapX < 21 + (x * 3) + 3) && (mapY >= 16 + (y * 2)) && (mapY < 16 + (y * 2) + 2))
				return m_iconArray[x + y * 3];
	
	return ICON_NONE;
}
