#ifndef __CCHARACTER_H__
#define __CCHARACTER_H__

#include "TDG.h"

#define MAX_CHARACTERS			11
#define MAX_ROOMS				31

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
	CHARTYPE_SNIDE,
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

class CCharacter
{
public:
	CCharacter(CharacterType characterType, CSprite* pHeadSprite, CSprite* pBodySprite, int width, int height);
	~CCharacter();
	
	void SetPosition(float x, float y);
	void UpdatePosition();
	void SetOamIndex(int index);
	void SetPriority(int priority);
	void Animate(int elapsedTime);
	void Show();
	void Hide();
	void Disable();
	void Draw();
	void Face(DirectionType directionType);
	void Move(DirectionType directionType);
	CollisionType CheckCollision(DirectionType directionType);
	
	void SetCharacterMode(CharacterMode characterMode);
	
	void SetRoom(CRoom* pRoom) { m_pRoom = pRoom; }
	CRoom* GetRoom() const { return m_pRoom; }
	
	void SetX(float x) { m_x = x; SetPosition(m_x, m_y); }
	void SetY(float y) { m_y = y; SetPosition(m_x, m_y); }
	
	void SetPoint(int x, int y) { m_point.X = x; m_point.Y = y; }
	PPOINT pPoint() { SetPoint(m_x + (m_width / 2) - 8, m_y + (m_height - 8)); return (PPOINT) &m_point; }
	
	void SetPath(int index, CRoom* pRoom) { m_path[index] = pRoom; }
	
	void SetAlpha(int alpha) { m_pHeadSprite->SetAlpha(alpha); m_pBodySprite->SetAlpha(alpha); }
	void SetGreen(bool value) { m_green = value; }
	
	float X() const { return m_x; }
	float Y() const { return m_y; }
	float SpriteX() const { return m_pHeadSprite->X(); }
	float SpriteY() const { return m_pHeadSprite->Y(); }
	float Width() const { return m_width; }
	float Height() const { return m_height; }
	DirectionType Facing() const { return m_facing; }
	bool Visible() const { return m_visible; }
	
	int OamIndex() const { return m_pHeadSprite->OamIndex(); }
	int Priority() const { return m_pHeadSprite->Priority(); }

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
