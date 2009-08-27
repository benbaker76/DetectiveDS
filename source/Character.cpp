#include <stdio.h>
#include "Character.h"
#include "Text.h"

CCharacter::CCharacter(CharacterType characterType, CSprite* pHeadSprite, CSprite* pBodySprite)
{
	m_characterType = characterType;
	m_pHeadSprite = pHeadSprite;
	m_pBodySprite = pBodySprite;
	m_x = 0;
	m_y = 0;

	m_spriteCol1 = new CSprite(SPRITE_COL1, sprite_col1Tiles, sprite_col1TilesLen, sprite_col1Pal, sprite_col1PalLen, NULL, 0);
	m_spriteCol2 = new CSprite(SPRITE_COL2, sprite_col2Tiles, sprite_col2TilesLen, sprite_col2Pal, sprite_col2PalLen, NULL, 0);
	
	m_spriteCol1->SetOamIndex(0);
	m_spriteCol2->SetOamIndex(1);
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

void CCharacter::Face(DirectionType directionType)
{
	switch(directionType)
	{
		case DIRECTION_UP:
			SetFrameType(FRAME_UP);
			break;
		case DIRECTION_DOWN:
			SetFrameType(FRAME_DOWN);
			break;
		case DIRECTION_LEFT:
			SetFrameType(FRAME_LEFT);
			break;
		case DIRECTION_RIGHT:
			SetFrameType(FRAME_RIGHT);
			break;
	}
}

void CCharacter::Move(DirectionType directionType)
{
	switch(directionType)
	{
		case DIRECTION_UP:
			SetFrameType(FRAME_UP);
			SetPosition(m_x + 1, m_y - 1);
			break;
		case DIRECTION_DOWN:
			SetFrameType(FRAME_DOWN);
			SetPosition(m_x - 1, m_y + 1);
			break;
		case DIRECTION_LEFT:
			SetFrameType(FRAME_LEFT);
			SetPosition(m_x - 1, m_y);
			break;
		case DIRECTION_RIGHT:
			SetFrameType(FRAME_RIGHT);
			SetPosition(m_x + 1, m_y);
			break;
	}
}

CollisionType CCharacter::CheckCollision(DirectionType directionType, CRoom* pRoom)
{
	CollisionType retType = COL_PATH;
	int x = ((pRoom->X() + m_x) + CHARACTER_WIDTH / 2) / 8;
	int y = ((pRoom->Y() + m_y) + CHARACTER_HEIGHT-8) / 8;
	int x2 = ((m_x + CHARACTER_WIDTH / 2) / 8);
	int y2 = ((m_y + CHARACTER_HEIGHT-8) / 8);
	
	m_spriteCol1->SetPosition(x2 * 8, y2 * 8);
	m_spriteCol1->Draw();
	
	switch(directionType)
	{
		case DIRECTION_UP:
			retType = (CollisionType) pRoom->ColMap(x, y-1);
			
			m_spriteCol2->SetPosition(x2 * 8, (y2-1) * 8);
			m_spriteCol2->Draw();
			break;
		case DIRECTION_DOWN:
			retType = (CollisionType) pRoom->ColMap(x, y+1);
			
			m_spriteCol2->SetPosition(x2 * 8, (y2+1) * 8);
			m_spriteCol2->Draw();
			break;
		case DIRECTION_LEFT:
			retType = (CollisionType) pRoom->ColMap(x-2, y);
			
			m_spriteCol2->SetPosition((x2-2) * 8, y2 * 8);
			m_spriteCol2->Draw();
			break;
		case DIRECTION_RIGHT:
			retType = (CollisionType) pRoom->ColMap(x+2, y);
			
			m_spriteCol2->SetPosition((x2+2) * 8, y2 * 8);
			m_spriteCol2->Draw();
			break;
	}
	
	DrawText("                                ", 0, 0, false);
	DrawText(g_colName[(int) retType], 0, 0, false);
	
	return retType;
}

void CCharacter::SetFrameType(FrameType frameType)
{
	m_pHeadSprite->SetFrameType(frameType);
	m_pBodySprite->SetFrameType(frameType);
}
