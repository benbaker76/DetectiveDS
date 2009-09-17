#ifndef __CGAME_H__
#define __CGAME_H__

#include "TDG.h"
#include <maxmod9.h>

#include "soundbank_bin.h"
#include "soundbank.h"

enum GameMode
{
	GAMEMODE_RUNNING,
	GAMEMODE_PAUSED
};

enum DisplayMode
{
	DISPLAYMODE_GAME,
	DISPLAYMODE_MENU,
	DISPLAYMODE_CONSOLE,
	DISPLAYMODE_KEYBOARD
};

enum GameType
{
	GAMETYPE_NORMAL
};

class CGame
{
public:
	CGame(GameType gameType);
	~CGame();
	
	void Initialize();
	void Update();
	void UpdateSnideMovement(int keys_held);
	void SetMenuIcons(CollisionType colNear, CollisionType colFar);
	bool TryGetDoor(CollisionType colNear, CollisionType colFar, CDoor** pDoor);
	void ProcessMenu(int x, int y);
	void PostProcessMenu();
	
	void InitRoom();
	void UpdateFx();

	void InitializeDoors();
	void SortSprites();
	void UpdateCharacters(int elapsedTime);
	
	mm_word MusicEventHandler(mm_word msg, mm_word param);
	void UpdateVBlank();
	void UpdateHBlank();
	void UpdateTimer1();
	void UpdateTimer2();

private:
	GameType m_gameType;
	GameMode m_gameMode;
	
	CFxManager m_fxManager;
	CMenu* m_menu;
	CCursor* m_cursor;
	CPointer* m_pointer;
	CConsole* m_console;
	CKeyboard* m_keyboard;
	
	CCharacter* m_characterArray[MAX_CHARACTERS];
	CSprite* m_spriteArray[MAX_SPRITES];
	CRoom* m_roomArray[MAX_ROOMS];
	CItem* m_itemArray[MAX_ITEMS];
	CEvent* m_eventArray[MAX_EVENTS];

	CRoom* m_currentRoom;
	CCharacter* m_snide;
	CWatch* m_watch;
	CTimer* m_timer;
	
	IconType m_lastIconType;
	
	DisplayMode m_displayMode;
	
	int m_bg2MainVScroll;
};

#endif
