#ifndef __CGAME_H__
#define __CGAME_H__

#include "TDG.h"
#include <maxmod9.h>

#include "soundbank_bin.h"
#include "soundbank.h"

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
	void SortSprites();
	void InitializeDoors();
	
	void UpdateVBlank();
	void UpdateHBlank();
	void UpdateTimer1();
	void UpdateTimer2();

private:
	GameType m_gameType;
	CVideo m_video;
	CFxManager m_fxManager;
	
	CCharacter* m_characterArray[MAX_CHARACTERS];
	CMap* m_mapArray[MAX_MAPS];
	CSprite* m_spriteArray[MAX_SPRITES];
	CRoom* m_roomArray[MAX_ROOMS];
	CItem* m_itemArray[MAX_ITEMS];
	CEvent* m_eventArray[MAX_EVENTS];

	CRoom* m_currentRoom;
	CCharacter* m_snide;
	CWatch* m_watch;
	CTimer* m_timer;
	
	u8 m_elapsedTime;
	u8 m_lastUpdate;
	
	int m_bg2MainVScroll;
};

#endif
