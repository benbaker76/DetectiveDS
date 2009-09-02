#include <stdio.h>
#include <math.h>
#include "CCharacter.h"
#include "Text.h"

CCharacter::CCharacter(CharacterType characterType, CSprite* pHeadSprite, CSprite* pBodySprite, int width, int height)
{
	m_characterType = characterType;
	m_pHeadSprite = pHeadSprite;
	m_pBodySprite = pBodySprite;
	m_x = 0;
	m_y = 0;
	m_width = width;
	m_height = height;

	//m_spriteCol1 = new CSprite(SPRITE_COL1, sprite_col1Tiles, sprite_col1TilesLen, sprite_col1Pal, sprite_col1PalLen, NULL, 0);
	//m_spriteCol2 = new CSprite(SPRITE_COL2, sprite_col2Tiles, sprite_col2TilesLen, sprite_col2Pal, sprite_col2PalLen, NULL, 0);
	
	m_spriteCol1 = new CSprite(SPRITE_COL1, sprite_col1Bitmap, NULL, 0);
	m_spriteCol2 = new CSprite(SPRITE_COL2, sprite_col2Bitmap, NULL, 0);
	
	m_spriteCol1->SetOamIndex(122);
	m_spriteCol2->SetOamIndex(123);
}

CCharacter::~CCharacter()
{
}

void CCharacter::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
	m_pHeadSprite->SetPosition(x, y);
	m_pBodySprite->SetPosition(x, y+HEAD_HEIGHT);
}

void CCharacter::SetOamIndex(int index)
{
	m_pHeadSprite->SetOamIndex(index);
	m_pBodySprite->SetOamIndex(index+1);
}

void CCharacter::SetPriority(int priority)
{
	m_pHeadSprite->SetPriority(priority);
	m_pBodySprite->SetPriority(priority);
}

void CCharacter::Animate(int elapsedTime)
{
	m_pHeadSprite->Animate(elapsedTime);
	m_pBodySprite->Animate(elapsedTime);
}

void CCharacter::Show()
{
	m_visible = true;
}

void CCharacter::Hide()
{
	m_visible = false;
}

void CCharacter::Disable()
{
	m_pHeadSprite->Hide();
	m_pBodySprite->Hide();
}

void CCharacter::Draw()
{
	if(!m_visible)
		return;
	
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
			SetPosition(m_x + 1.33, m_y - 0.66);
			break;
		case DIRECTION_DOWN:
			SetFrameType(FRAME_DOWN);
			SetPosition(m_x - 1.33, m_y + 0.66);
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
	CollisionType retType = COL_NOTHING_HERE;
	float x = (pRoom->X() + m_x) + (m_width / 2) - 8;
	float y = (pRoom->Y() + m_y) + (m_height - 8);
	//float x2 = m_x + (m_width / 2) - 8 + 4;
	//float y2 = m_y + (m_height - 8) + 4;
	
	//m_spriteCol1->SetPosition(x2, y2);
	//m_spriteCol1->Draw();
	
	switch(directionType)
	{
		case DIRECTION_UP:
			retType = (CollisionType) pRoom->ColMap(ceil((x + 8) / 8), ceil((y - 8) / 8));
					
			//m_spriteCol2->SetPosition(ceil(x2 + 8), ceil(y2 - 8));
			//m_spriteCol2->Draw();
			break;
		case DIRECTION_DOWN:
			retType = (CollisionType) pRoom->ColMap(round((x - 8) / 8), round((y + 8) / 8));
			
			//m_spriteCol2->SetPosition(round(x2 - 8), round(y2 + 8));
			//m_spriteCol2->Draw();
			break;
		case DIRECTION_LEFT:
			retType = (CollisionType) pRoom->ColMap(round((x - 8) / 8), round(y / 8));
			
			//m_spriteCol2->SetPosition(round(x2 - 8), round(y2));
			//m_spriteCol2->Draw();
			break;
		case DIRECTION_RIGHT:
			retType = (CollisionType) pRoom->ColMap(round((x + 8) / 8), round(y / 8));
			
			//m_spriteCol2->SetPosition(round(x2 + 8), round(y2));
			//m_spriteCol2->Draw();
			break;
	}
	
	//DrawText("                                ", 0, 0, false);
	//DrawText(g_colName[(int) retType], 0, 0, false);
	
	return retType;
}

void CCharacter::SetFrameType(FrameType frameType)
{
	m_pHeadSprite->SetFrameType(frameType);
	m_pBodySprite->SetFrameType(frameType);
}
