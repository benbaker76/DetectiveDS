#ifndef __CGAME_H__
#define __CGAME_H__

#include "TDG.h"

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
	void Update(int elapsedTime, CTime* pTime);
	void SortSprites();

private:
	GameType m_gameType;
	CVideo m_video;
	
	CCharacter* m_characterArray[MAX_CHARACTERS];
	CMap* m_mapArray[MAX_MAPS];
	CSprite* m_spriteArray[MAX_SPRITES];
	CRoom* m_roomArray[MAX_ROOMS];
	CItem* m_itemArray[MAX_ITEMS];
	CEvent* m_eventArray[MAX_EVENTS];
};

#endif
