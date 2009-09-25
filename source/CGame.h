#ifndef __CGAME_H__
#define __CGAME_H__

#include "TDG.h"
#include <maxmod9.h>

#include "soundbank_bin.h"
#include "soundbank.h"

#define MAKEITEMARRAY(a,b,c,d,e)	{ itemArray[0] = a; itemArray[1] = b; itemArray[2] = c; itemArray[3] = d; itemArray[4] = e; }

enum GameMode
{
	GAMEMODE_RUNNING,
	GAMEMODE_PAUSED,
	GAMEMODE_GAMEOVER
};

enum DisplayMode
{
	DISPLAYMODE_GAME,
	DISPLAYMODE_MENU,
	DISPLAYMODE_CONSOLE,
	DISPLAYMODE_CONSOLE_MENU,
	DISPLAYMODE_KEYBOARD
};

enum GameType
{
	GAMETYPE_NORMAL
};

enum QuestionMode
{
	QUESTIONMODE_NONE,
	QUESTIONMODE_WAITING,
	QUESTIONMODE_ASKABOUT,
	QUESTIONMODE_REPLY
};

enum QuestionType
{
	QUESTIONTYPE_MRMCFUNGUS,
	QUESTIONTYPE_ANOBJECT,
	QUESTIONTYPE_ANOTHERGUEST
};

enum UseMode
{
	USEMODE_USE,
	USEMODE_TO,
	USEMODE_WITH
};

enum OpenMode
{
	OPENMODE_ROOM,
	OPENMODE_ITEM
};

enum KeyboardMode
{
	KEYBOARDMODE_BOOK1,
	KEYBOARDMODE_BOOK2,
	KEYBOARDMODE_SAFE
};

class CGame
{
public:
	CGame(GameType gameType);
	~CGame();
	
	void Initialize();
	void Update();
	
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
	
	bool m_charactersInRoom[MAX_CHARACTERS];
	bool m_someoneInRoom;
	
	QuestionMode m_questionMode;
	QuestionType m_questionType;
	
	UseMode m_useMode;
	UseType m_useType;
	
	OpenMode m_openMode;
	
	KeyboardMode m_keyboardMode;
	
	CItem* m_useItem;
	CItem* m_withItem;
	CItem* m_placeItem;
	CItem* m_inItem;
	CCharacter* m_questionCharacter;
	
	char m_buffer[2048];

	CRoom* m_currentRoom;
	CCharacter* m_snide;
	CWatch* m_watch;
	CTimer* m_timer;
	
	IconType m_lastIconType;
	
	DisplayMode m_displayMode;
	
	int m_bg2MainVScroll;
	
	void InitializeGame();
	void InitializeDoors();
	void SortSprites();
	void UpdateCharacters();
	bool CheckCharacterCollision(DirectionType directionType, CharacterType* charNear, CharacterType* charFar);
	void UpdateDisplayMode(touchPosition touch, int keys_held, int keys_pressed, int keys_released);
	void UpdateSnideMovement(int keys_held);
	void SetMenuIcons(MenuMode menuMode, CItem* pItem);
	bool TryGetDoor(CollisionType colNear, CollisionType colFar, CDoor** pDoor);
	bool TryGetRoomCache(CRoom* pRoom, CollisionType colType, CItemCache** pItemCache);
	int ShowItemMenu(const char* text, CItemCache* pItemCache, CItem* pItemExclude);
	void ShowVisibleCharactersMenu();
	void ShowCharacterMenu(const char* text);
	void ProcessMenu(int x, int y);
	void PostProcessMenu();
	
	void InitRoom();
	void UpdateFx();
	
	void InitGameOver(bool win);
};

#endif
