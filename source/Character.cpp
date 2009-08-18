#include "Character.h"

CCharacter::CCharacter(CharacterType characterType, CSprite* pHeadSprite, CSprite* pBodySprite)
{
	m_characterType = characterType;
	m_pHeadSprite = pHeadSprite;
	m_pBodySprite = pBodySprite;
	m_x = 0;
	m_y = 0;
}

CCharacter::~CCharacter()
{
}

void CCharacter::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
	m_pHeadSprite->SetPosition(x, y);
	m_pBodySprite->SetPosition(x, y+HEAD_HEIGHT);
}

void CCharacter::SetPriority(int index)
{
	m_pHeadSprite->SetOamIndex(index);
	m_pBodySprite->SetOamIndex(index+1);
}

void CCharacter::Animate(int elapsedTime)
{
	m_pHeadSprite->Animate(elapsedTime);
	m_pBodySprite->Animate(elapsedTime);
}

void CCharacter::Hide()
{
	m_pHeadSprite->Hide();
	m_pBodySprite->Hide();
}

void CCharacter::Draw()
{
	m_pHeadSprite->Draw();
	m_pBodySprite->Draw();
}

void CCharacter::Move(DirectionType directionType)
{
	switch(directionType)
	{
		case DIRECTION_UP:
			SetFrameType(FRAME_UP);
			SetPosition(m_x + 2, m_y - 1);
			break;
		case DIRECTION_DOWN:
			SetFrameType(FRAME_DOWN);
			SetPosition(m_x - 2, m_y + 1);
			break;
		case DIRECTION_LEFT:
			SetFrameType(FRAME_LEFT);
			SetPosition(m_x - 2, m_y);
			break;
		case DIRECTION_RIGHT:
			SetFrameType(FRAME_RIGHT);
			SetPosition(m_x + 2, m_y);
			break;
	}
}

void CCharacter::SetFrameType(FrameType frameType)
{
	m_pHeadSprite->SetFrameType(frameType);
	m_pBodySprite->SetFrameType(frameType);
}
