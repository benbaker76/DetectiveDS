#ifndef __CCHARACTER_H__
#define __CCHARACTER_H__

#include "TDG.h"
#include "CItemCache.h"

#define MAX_CHARACTERS			11
#define MAX_ROOMS				37

#define CHARACTER_WIDTH			24
#define CHARACTER_HEIGHT		53

#define HEAD_HEIGHT				21

enum CharacterMode
{
	CHARMODE_NONE,
	CHARMODE_WAITING,
	CHARMODE_WALKING,
	CHARMODE_TALKING,
	CHARMODE_DEAD,
	CHARMODE_BOMB,
	CHARMODE_ATTACK,
	CHARMODE_SURRENDER
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
	CHARTYPE_ANGUS
};

class CRoom;
class CCharacter;

class CCharacter
{
public:
	CCharacter(CharacterType characterType, CSprite* pHeadSprite, CSprite* pBodySprite, int width, int height);
	~CCharacter();
	
	void SetPosition(float x, float y);
	void SetOamIndex(int index);
	void SetPriority(int priority);
	void Update();
	void SetVisible(CRoom* pRoom);
	void Show();
	void Hide();
	void Disable();
	void Draw();
	void Face(DirectionType directionType);
	void Move(DirectionType directionType);
	bool CheckCollision(DirectionType directionType, CollisionType* colNear, CollisionType* colFar);
	bool CheckCollision(DirectionType directionType, CCharacter* character, CharacterType* charNear, CharacterType* charFar);
	
	void SetCharacterMode(CharacterMode characterMode);
	
	void SetRoom(CRoom* pRoom) { m_pRoom = pRoom; }
	CRoom* GetRoom() const { return m_pRoom; }
	
	void SetX(float x) { SetPosition(x, m_y); }
	void SetY(float y) { SetPosition(y, m_y); }
	
	void SetPoint(int x, int y) { m_point.X = x; m_point.Y = y; }
	PPOINT pPoint() { SetPoint(m_x + (m_width / 2), m_y + (m_height - 8) + 4); return (PPOINT) &m_point; }
	
	void SetPath(int index, CRoom* pRoom) { m_path[index] = pRoom; }
	
	void SetAlpha(int alpha) { m_pHeadSprite->SetAlpha(alpha); m_pBodySprite->SetAlpha(alpha); }
	void SetGreen(bool value) { m_green = value; Face(m_facing); }
	void SetDeadSide(bool value) { m_deadSide = value; }
	
	float X() const { return m_x; }
	float Y() const { return m_y; }
	int AbsX();
	int SpriteX() const { return m_pHeadSprite->X(); }
	int SpriteY() const { return m_pHeadSprite->Y(); }
	int Width() const { return m_width; }
	int Height() const { return m_height; }
	DirectionType Facing() const { return m_facing; }
	bool Visible() const { return m_visible; }
	bool Dead() const { return m_dead; }
	
	int OamIndex() const { return m_pHeadSprite->OamIndex(); }
	int Priority() const { return m_pHeadSprite->Priority(); }
	CharacterType GetCharacterType() const { return m_characterType; }
	CharacterMode GetCharacterMode() const { return m_characterMode; }
	
	void RestoreLastCharacterMode() { m_characterMode = m_lastCharacterMode; }
	
	void AddItemCache() { m_itemCache = new CItemCache(ITEMLOCATION_CHARACTER, this); }
	void AddItemCache(CItem* itemArray[]) { m_itemCache = new CItemCache(ITEMLOCATION_CHARACTER, itemArray, this); }
	CItemCache* GetItemCache() const { return m_itemCache; }

private:
	CharacterType m_characterType;
	CharacterMode m_characterMode;
	CharacterMode m_lastCharacterMode;
	CSprite* m_pHeadSprite;
	CSprite* m_pBodySprite;
	
	CRoom* m_pRoom;
	
	CSprite* m_spriteCol1;
	CSprite* m_spriteCol2;
	
	DirectionType m_facing;
	
	CRoom* m_path[MAX_ROOMS];
	int m_pathPosition;
	
	bool m_visible;
	bool m_green;
	bool m_dead;
	bool m_deadSide;
	
	float m_x;
	float m_y;
	int m_width;
	int m_height;
	
	int m_waitingTime;
	
	POINT m_point;
	
	CItemCache* m_itemCache;
	
	void SetFrameType(FrameType frameType);
};

#endif
