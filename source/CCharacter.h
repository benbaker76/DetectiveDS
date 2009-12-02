#ifndef __CCHARACTER_H__
#define __CCHARACTER_H__

#include "TDG.h"
#include "CItemCache.h"
#include "CGoalManager.h"

#define MAX_CHARACTERS			11
#define MAX_ROOMS				39

#define CHARACTER_WIDTH			24
#define CHARACTER_HEIGHT		53

#define HEAD_HEIGHT				21

#define CENTRE_Y				-1

enum CharacterMode
{
	CHARMODE_NONE,
	CHARMODE_WAITING,
	CHARMODE_TALKING,
	CHARMODE_DEAD,
	CHARMODE_BOMB,
	CHARMODE_ATTACK,
	CHARMODE_SURRENDER,
	CHARMODE_QUESTION,
	CHARMODE_GOAL
};

enum CharacterType
{
	CHARTYPE_NONE = -1,
	CHARTYPE_SNIDE = 0,
	CHARTYPE_REVEREND,
	CHARTYPE_BENTLEY,
	CHARTYPE_COOK,
	CHARTYPE_GABRIEL,
	CHARTYPE_CYNTHIA,
	CHARTYPE_PROFESSOR,
	CHARTYPE_DOCTOR,
	CHARTYPE_MAJOR,
	CHARTYPE_DINGLE,
	CHARTYPE_ANGUS,
	CHARTYPE_QUESTIONMARK
};

enum CharacterSex
{
	CHARSEX_NONE,
	CHARSEX_MALE,
	CHARSEX_FEMALE
};

class CRoom;
class CCharacter;
class CSave;

class CCharacter
{
public:
	CCharacter(CharacterType characterType, CSprite* pHeadSprite, CSprite* pBodySprite, CharacterSex characterSex, int width, int height);
	~CCharacter();
	
	void SetPosition(float x, float y);
	void SetPosition(float x);
	void SetOamIndex(int index);
	void SetPriority(int priority);
	void Reset();
	void ResetAnimation();
	uint64 Update(CRoom* pCurrentRoom, uint64 eventFlags);
	bool MoveTo(Point* pDest);
	bool IsVisible(CRoom* pRoom);
	void Show();
	void Hide();
	void Disable();
	void SetHFlip(bool hflip);
	void Draw();
	void SetSub(bool sub);
	void Face(DirectionType directionType);
	void Move(DirectionType directionType);
	bool CheckCollision(DirectionType directionType, CollisionType* colNear, CollisionType* colFar);
	bool CheckCollision(DirectionType directionType, CCharacter* character, CharacterType* charNear, CharacterType* charFar);
	
	void SetCharacterMode(CharacterMode characterMode);
	
	void SetRoom(CRoom* pRoom) { m_pRoom = pRoom; }
	CRoom* GetRoom() const { return m_pRoom; }
	
	void SetX(float x) { SetPosition(x, m_y); }
	void SetY(float y) { SetPosition(y, m_y); }
	
	void SetSize(int width, int height) { m_width = width; m_height = height; }
	
	void SetLoop(bool loop) { m_pHeadSprite->SetLoop(loop); m_pBodySprite->SetLoop(loop); }
	
	void SetPoint(int x, int y) { m_point->X = x; m_point->Y = y; }
	Point* pPoint() { SetPoint(m_x + (m_width / 2), m_y + (m_height - 8) + 4); return m_point; }
	
	void SetRect(int x, int y, int width, int height) { m_rect->X = x; m_rect->Y = y; m_rect->Width = width; m_rect->Height = height; }
	Rect* pRect() { SetRect(m_x, m_y, m_width, m_height); return m_rect; }
	
	void SetAlpha(int alpha) { m_pHeadSprite->SetAlpha(alpha); m_pBodySprite->SetAlpha(alpha); }
	void SetGreen(bool value) { m_green = value; Face(m_facing); }
	void SetDeadSide(bool value) { m_deadSide = value; }
	
	float X() const { return m_x; }
	float Y() const { return m_y; }
	int ScreenX();
	int SpriteX() const { return m_pHeadSprite->X(); }
	int SpriteY() const { return m_pHeadSprite->Y(); }
	int CentreY() const { return (m_pRoom == NULL ? m_y : m_pRoom->CentreY() - m_height); }
	int Width() const { return m_width; }
	int Height() const { return m_height; }
	DirectionType Facing() const { return m_facing; }
	bool Visible() const { return m_visible; }
	bool Dead() const { return m_dead; }
	
	int OamIndex() const { return m_pHeadSprite->OamIndex(); }
	int Priority() const { return m_pHeadSprite->Priority(); }
	CharacterType GetCharacterType() const { return m_characterType; }
	CharacterMode GetCharacterMode() const { return m_characterMode; }
	CharacterSex GetCharacterSex() const { return m_characterSex; }
	
	void AddItems(CItem* item1, CItem* item2, CItem* item3, CItem* item4, CItem* item5) { m_itemCache->AddItems(item1, item2, item3, item4, item5); }
	CItemCache* GetItemCache() const { return m_itemCache; }
	
	void AddGoal(CGoal* pGoal) { m_goalManager->AddGoal(pGoal); }
	void InsertGoal(CGoal* pGoal) { m_goalManager->InsertGoal(pGoal); }
	
	bool TryGetSpeech(const char** string) { if(m_string != NULL) { *string = m_string; m_string = NULL; return true; } else return false; }
	
	void SetGoalMode(bool value) { m_goalMode = value; }
	bool GetGoalMode() const { return m_goalMode; }
	
	void SetKeyItemType(ItemType keyItemType) { m_keyItemType = keyItemType; }
	
	void Save(CSave* pSave);
	void Load(CSave* pSave);

private:
	CharacterType m_characterType;
	CharacterMode m_characterMode;
	CharacterSex m_characterSex;
	
	CSprite* m_pHeadSprite;
	CSprite* m_pBodySprite;
	
	CRoom* m_pRoom;
	CDoor* m_pLastDoor;
	
	//CSprite* m_spriteCol1;
	//CSprite* m_spriteCol2;
	
	DirectionType m_facing;
	
	bool m_visible;
	bool m_green;
	bool m_dead;
	bool m_deadSide;
	
	Size m_origSize;
	float m_x;
	float m_y;
	int m_width;
	int m_height;
	
	int m_frameCount;
	
	bool m_goalMode;

	Point* m_point;
	Rect* m_rect;
	
	CItemCache* m_itemCache;
	CGoalManager* m_goalManager;
	
	const char* m_string;
	
	ItemType m_keyItemType;
	
	void SetFrameType(FrameType frameType);
};

#endif
