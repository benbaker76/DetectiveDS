#ifndef __CGAME_H__
#define __CGAME_H__

#include "TDG.h"
#include "CSave.h"
#include <maxmod9.h>

//#include "soundbank_bin.h"
#include "soundbank.h"

#define MAX_POINTS	4
#define MAX_TEXT_BUFFER		1024

#define MAKEITEMARRAY(a,b,c,d,e)	{ itemArray[0] = a; itemArray[1] = b; itemArray[2] = c; itemArray[3] = d; itemArray[4] = e; }

enum GameMode
{
	GAMEMODE_INTRO,
	GAMEMODE_TITLESCREEN,
	GAMEMODE_PAUSED,
	GAMEMODE_FREEZE,
	GAMEMODE_RUNNING,
	GAMEMODE_DYING,
	GAMEMODE_REVERSETIME,
	GAMEMODE_ENDING,
	GAMEMODE_GAMEOVER
};

enum GameOverMode
{
	GAMEOVERMODE_WIN,
	GAMEOVERMODE_LOSE,
	GAMEOVERMODE_END,
	GAMEOVERMODE_NOTHING
};

enum EndingMode
{
	ENDINGMODE_NONE,
	ENDINGMODE_SHOT,
	ENDINGMODE_LEDATGUNPOINT,
	ENDINGMODE_DINGLESPEAKS,
	ENDINGMODE_PULLTRIGGER,
	ENDINGMODE_ESCAPE,
	ENDINGMODE_ESCAPING,
	ENDINGMODE_ESCAPED,
	ENDINGMODE_ARREST,
	ENDINGMODE_GAMEOVER_WIN,
	ENDINGMODE_GAMEOVER_LOSE,
	ENDINGMODE_GAMEOVER_END
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

enum MurderType
{
	MURDERTYPE_DINGLE,
	MURDERTYPE_CYNTHIA,
	MURDERTYPE_DOCTOR,
	MURDERTYPE_GABRIEL
};

enum SongType
{
	SONGTYPE_TITLESCREEN,
	SONGTYPE_MURDER,
	SONGTYPE_TENSION,
	SONGTYPE_INGAME
};

class CGame
{
public:
	CGame();
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
	
	CCharacter* m_question;
	
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
	CCharacter* m_speakCharacter;
	
	bool m_gargoyleActive[3];

	CRoom* m_currentRoom;
	CCharacter* m_snide;
	CWatch* m_watch;
	CTimer* m_timer;
	
	GameOverMode m_gameOverMode;
	EndingMode m_endingMode;
	
	int m_frameCount;
	
	int m_dieFrameCount;
	int m_reverseTimeFrameCount;
	int m_freezeFrameCount;
	
	int m_introIndex;
	
	int m_characterIndex;
	
	uint64 m_eventFlags;
	
	Point* m_ratPoints[MAX_POINTS];
	
	mm_sfxhand m_footsteps;
	mm_sfxhand m_clock;
	mm_sfxhand m_fireplace;
	//mm_sfxhand m_waterdrip;
	
	IconType m_lastIconType;
	
	DisplayMode m_displayMode;
	
	SongType m_songType;
	
	CSave* m_save;
	
	int m_bg2MainVScroll;
	
	void InitData(int param);
	void InitDoors();
	void ResetRooms();
	void SortSprites();
	uint64 GetCharactersInRoom(CRoom* pRoom);
	void UpdateCharacters();
	void CharacterSpeak(CCharacter* pCharacter, const char* string);
	void HideCharacters();
	bool CheckCharacterCollision(DirectionType directionType, CharacterType* charNear, CharacterType* charFar);
	void UpdateDisplayMode(touchPosition touch, int keys_held, int keys_pressed, int keys_released);
	void UpdateSnideMovement(int keys_held);
	void SetMenuIcons(MenuMode menuMode, CItem* pItem);
	bool TryGetDoor(CollisionType colNear, CollisionType colFar, CDoor** pDoor);
	bool TryGetRoomCache(CRoom* pRoom, CollisionType colType, CItemCache** pItemCache);
	int ShowItemMenu(const char* text, CItemCache* pItemCache, CItem* pItemExclude);
	bool ShowVisibleCharactersMenu();
	void ShowCharacterMenu(const char* text, CCharacter* pCharacterExclude);
	void ProcessMenu(int x, int y);
	void PostProcessMenu();
	
	void InitRoom();
	void InitMurder(MurderType murderType);
	void UpdateFx();
	
	void InitVideoIntro();
	void InitVideoMain();
	void InitIntro1();
	void InitIntro2(int param);
	void InitIntro3(int param);
	void UpdateIntro();
	void InitGame(GameType gameType);
	void UpdateGame(touchPosition touch, int keys_held, int keys_pressed, int keys_released);
	void UpdateEvents();
	void UpdateEventFlags();
	void InitGameOver(GameOverMode gameOverMode);
	void UpdateGameOver();
	void InitEnding(EndingMode endingMode);
	void UpdateEnding(touchPosition touch, int keys_held, int keys_pressed, int keys_released);
	void InitTitleScreen();
	void UpdateTitleScreen();
	void SoundOff();
	void FxOff();
	void PlaySong(SongType songType);
	void StopSong();
	
	void Save();
	bool Load();
};

#endif
