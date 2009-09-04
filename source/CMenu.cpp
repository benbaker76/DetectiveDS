#include <nds.h>
#include "CMenu.h"

CMenu::CMenu()
{
}

CMenu::~CMenu()
{
}

void CMenu::DrawIcon(IconType iconType, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB) : BG_MAP_RAM(BG1_MAP_BASE)) + (x + y * 32);
	
	for(u32 y=0; y<2; y++)
		for(u32 x=0; x<3; x++)
			*(pMap+x+y*32) = iconType * 6 + x + y * 3;
}
