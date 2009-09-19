#ifndef __CCHARACTER_H__
#define __CCHARACTER_H__

#include "TDG.h"

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
	CHARMOND_DEAD
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
	void UpdatePosition();
	void SetOamIndex(int index);
	void SetPriority(int priority);
	void Animate();
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
	void SetGreen(bool value) { m_green = value; }
	
	float X() const { return m_x; }
	float Y() const { return m_y; }
	int AbsX(); // const { return m_x - m_pRoom->X(); }
	int SpriteX() const { return m_pHeadSprite->X(); }
	int SpriteY() const { return m_pHeadSprite->Y(); }
	int Width() const { return m_width; }
	int Height() const { return m_height; }
	DirectionType Facing() const { return m_facing; }
	bool Visible() const { return m_visible; }
	
	int OamIndex() const { return m_pHeadSprite->OamIndex(); }
	int Priority() const { return m_pHeadSprite->Priority(); }
	CharacterType GetCharacterType() const { return m_characterType; }
	CharacterMode GetCharacterMode() const { return m_characterMode; }

private:
	CharacterType m_characterType;
	CharacterMode m_characterMode;
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
	
	float m_x;
	float m_y;
	int m_width;
	int m_height;
	
	POINT m_point;
	
	void SetFrameType(FrameType frameType);
};

#endif
