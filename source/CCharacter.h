#ifndef __CCHARACTER_H__
#define __CCHARACTER_H__

#include "TDG.h"

#define MAX_CHARACTERS			11

#define CHARACTER_WIDTH			24
#define CHARACTER_HEIGHT		53

#define HEAD_HEIGHT				21

enum CharacterType
{
	CHARACTER_SNIDE,
	CHARACTER_REVEREND,
	CHARACTER_BENTLEY,
	CHARACTER_COOK,
	CHARACTER_GABRIEL,
	CHARACTER_CYNTHIA,
	CHARACTER_PROFESSOR,
	CHARACTER_DOCTOR,
	CHARACTER_MAJOR,
	CHARACTER_DINGLE,
	CHARACTER_ANGUS
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
	
	void SetFrameType(FrameType frameType);
	
	void SetRoom(CRoom* pRoom) { m_pRoom = pRoom; }
	void SetRoom(CRoom* pRoom, CDoor* pDoor);
	CRoom* GetRoom() const { return m_pRoom; }
	
	void SetX(float x) { m_x = x; SetPosition(m_x, m_y); }
	void SetY(float y) { m_y = y; SetPosition(m_x, m_y); }
	
	void SetAlpha(int alpha) { m_pHeadSprite->SetAlpha(alpha); m_pBodySprite->SetAlpha(alpha); }
	
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
	CSprite* m_pHeadSprite;
	CSprite* m_pBodySprite;
	
	CRoom* m_pRoom;
	
	CSprite* m_spriteCol1;
	CSprite* m_spriteCol2;
	
	DirectionType m_facing;
	
	bool m_visible;
	
	float m_x;
	float m_y;
	int m_width;
	int m_height;
};

#endif
