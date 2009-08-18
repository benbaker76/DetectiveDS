#include "Character.h"

CCharacter::CCharacter(CharacterType characterType, CSprite* pHeadSprite, CSprite* pBodySprite)
{
	m_characterType = characterType;
	m_pHeadSprite = pHeadSprite;
	m_pBodySprite = pBodySprite;
	
	m_x = 128;
	m_y = 64;
}

CCharacter::~CCharacter()
{
}

void CCharacter::Draw(int elapsedTime)
{
	m_pHeadSprite->Draw(elapsedTime, m_x, m_y);
	m_pBodySprite->Draw(elapsedTime, m_x, m_y + 21);
}

void CCharacter::Move(DirectionType directionType)
{
	switch(directionType)
	{
		case DIRECTION_UP:
			SetFrameType(FRAME_UP);
			m_x+=2;
			m_y--;
			break;
		case DIRECTION_DOWN:
			SetFrameType(FRAME_DOWN);
			m_x-=2;
			m_y++;
			break;
		case DIRECTION_LEFT:
			SetFrameType(FRAME_LEFT);
			m_x-=2;
			break;
		case DIRECTION_RIGHT:
			SetFrameType(FRAME_RIGHT);
			m_x+=2;
			break;
	}
}

void CCharacter::SetFrameType(FrameType frameType)
{
	m_pHeadSprite->SetFrameType(frameType);
	m_pBodySprite->SetFrameType(frameType);
}
