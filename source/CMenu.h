#ifndef __CMENU_H__
#define __CMENU_H__

#include "TDG.h"

#define MENU_X				168
#define MENU_Y				128
#define MENU_WIDTH			72
#define MENU_HEIGHT			48
#define MENU_PADDING		8

#define ICON_WIDTH			3
#define ICON_HEIGHT			2

#define ITEM_WIDTH			3
#define ITEM_HEIGHT			2

#define MAX_ICONS			9

enum IconType
{
	ICON_NONE,
	ICON_OPEN,
	ICON_EXAMINE,
	ICON_INVENTORY,
	ICON_DROP,
	ICON_SAVE,
	ICON_LOAD,
	ICON_SHOOT,
	ICON_ACCUSE,
	ICON_DOOR_OPEN,
	ICON_DOOR_CLOSE,
	ICON_USE_KEY,
	ICON_QUESTION,
	ICON_READ,
	ICON_CONSUME,
	ICON_USE,
	ICON_TIME,
	ICON_PLACE,
	ICON_BAG
};

enum IconSet
{
	ICONSET_NOTHING,
	ICONSET_GENERAL,
	ICONSET_DOOR_OPEN,
	ICONSET_DOOR_CLOSE,
	ICONSET_ITEM
};

enum MenuMode
{
	MENUMODE_GENERAL,
	MENUMODE_ITEM
};

class CMenu
{
public:
	CMenu();
	~CMenu();
	
	void ClearIcons();
	void AddIconSet(IconSet iconSet);
	bool AddIcon(IconType iconType);
	void Show(MenuMode menuMode);
	void Draw();
	void Hide();
	void Reset();
	void DrawIcon(IconType iconType, int x, int y, bool sub);
	void DrawItem(ItemType itemType, int x, int y, bool sub);
	void DrawBox(int x, int y);
	IconType CheckIconHit(int x, int y);
	
	MenuMode GetMenuMode() const { return m_menuMode; }

private:
	IconType m_iconArray[MAX_ICONS];
	MenuMode m_menuMode;
	
	u16* m_gfxBox;
	
	void HideBox();
};

#endif
