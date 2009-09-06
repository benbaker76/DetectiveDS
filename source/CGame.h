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
	void InitializeDoors();
	void SortSprites();
	void AnimateCharacters(int elapsedTime);
	void DrawCharacters();
	
	void UpdateVBlank();
	void UpdateHBlank();
	void UpdateTimer1();
	void UpdateTimer2();

private:
	GameType m_gameType;
	GameMode m_gameMode;
	
	CFxManager m_fxManager;
	CMenu m_menu;
	CCursor m_cursor;
	CTextConsole* m_textConsole;
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
	
	int m_bg2MainVScroll;
};

#endif
