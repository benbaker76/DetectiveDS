#ifndef __CCONSOLE_H__
#define __CCONSOLE_H__

#include <nds.h>
#include "Globals.h"
#include "CCursor.h"
#include "CSelector.h"

#define CONSOLE_X				8
#define CONSOLE_Y				120
#define CONSOLE_WIDTH			144
#define CONSOLE_HEIGHT			64

#define CONSOLE_MAP_X			(CONSOLE_X / 8)
#define CONSOLE_MAP_Y			(CONSOLE_Y / 8)
#define CONSOLE_MAP_WIDTH		(CONSOLE_WIDTH / 8)
#define CONSOLE_MAP_HEIGHT		(CONSOLE_HEIGHT / 8)

#define CONSOLE_MENU_X			8
#define CONSOLE_MENU_Y			144
#define CONSOLE_MENU_WIDTH		144
#define CONSOLE_MENU_HEIGHT		40

#define CONSOLE_MENU_VISIBLE_TEXT	5
#define CONSOLE_MENU_MAX_TEXT		16

#define CONSOLE_MENU_MAP_X		(CONSOLE_MENU_X / 8)
#define CONSOLE_MENU_MAP_Y		(CONSOLE_MENU_Y / 8)
#define CONSOLE_MENU_MAP_WIDTH	(CONSOLE_MENU_WIDTH / 8)
#define CONSOLE_MENU_MAP_HEIGHT	(CONSOLE_MENU_HEIGHT / 8)

#define CONSOLE_MAX_TEXT		8

class CConsole
{
public:
	CConsole(CCursor* pCursor);
	~CConsole();
	
	void ClearText();
	void ClearMenu();
	void CreateMenu(const char* menuArray[], int menuCount);
	void DrawMenu();
	void HideMenu();
	bool AddText(const char* text);
	void Update();

	void MoveSelectorBar(DirectionType directionType);
	void DrawSelectorBar();
	void HideSelectorBar();
	void HideArrow();
	void ShowArrow();
	
	int MenuItem() const { return (m_menuOffset + m_menuPos); }
	
private:
	CCursor* m_pCursor;
	CSelector m_selector;
	
	int m_menuPos;
	int m_menuOffset;
	int m_menuCount;
	
	int m_x;
	int m_y;
	
	u16* m_gfxArrow;

	int m_lastUpdate;
	
	const char* m_charPos;
	u32 m_textPos;
	const char* m_textArray[CONSOLE_MAX_TEXT];
	const char* m_menuArray[CONSOLE_MENU_MAX_TEXT];
};

#endif
