#include <stdio.h>
#include <math.h>
#include "CCharacter.h"
#include "Text.h"

CCharacter::CCharacter(CharacterType characterType, CSprite* pHeadSprite, CSprite* pBodySprite, int width, int height)
{
	m_characterType = characterType;
	m_characterMode = CHARMODE_NONE;
	m_pHeadSprite = pHeadSprite;
	m_pBodySprite = pBodySprite;
	m_x = 0;
	m_y = 0;
	m_width = width;
	m_height = height;
	
	m_visible = false;
	m_green = false;
	
	m_pathPosition = 0;
	
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
	
	m_pHeadSprite->SetPosition(AbsX(), m_y);
	m_pBodySprite->SetPosition(AbsX(), m_y+HEAD_HEIGHT);
}

void CCharacter::UpdatePosition()
{
	if(m_characterMode == CHARMODE_WALKING)
	{
		CRoom* pRoom = m_path[m_pathPosition];
		
		if(pRoom != NULL)
		{
			CDoor* pDoor = m_pRoom->GetRoomDoor(pRoom);
			int xPos = pPoint()->X;
			int yPos = pPoint()->Y;
			int xEnd = pDoor->pPoint()->X * 8;
			int yEnd = pDoor->pPoint()->Y * 8;
			int xDist = xEnd - xPos;
			int yDist = yEnd - yPos;
				
			if(abs(xDist) > 8 || abs(yDist) > 8)
			{						
				if(abs(xDist) < 32)	 		// Near the door
				{			
					if(xDist < 0)			// Move directly towards it
						m_x -= 0.6f;		// left
					else
						m_x += 0.6f;		// right						
						
					if(yDist < 0)			// Move directly towards it
						m_y -= 0.3f;		// up
					else
						m_y += 0.3f;		// down						
				}
				else
				{
					if(yPos > m_pRoom->CentreY())			// Below centre of room so move up diagonally
					{
						SetFrameType(FRAME_RIGHT);
						m_x += 0.6f;
						m_y -= 0.3f;
					}
					else if(yPos < m_pRoom->CentreY()) 	// Above centre of room so move down diagonally
					{
						SetFrameType(FRAME_LEFT);
						m_x -= 0.6f;
						m_y += 0.3f;
					}
					else
					{
						if(xDist < 0)
							SetFrameType(FRAME_LEFT);
						else
							SetFrameType(FRAME_RIGHT);
					
						float direction = atan2(yDist, xDist);
						// Move directly towards door
						m_x += cos(direction) * 0.6f;
						//m_y += sin(direction) * 0.3f;
					}
				}
			}
			else
			{
				m_pathPosition++;
				m_pRoom = pRoom;
				
				pDoor->SetDoorState(DOORSTATE_OPEN);
				
				int xDoor = pDoor->pDoorOut()->pPoint()->X;
				int yDoor = pDoor->pDoorOut()->pPoint()->Y;
				m_x = xDoor * 8;
				m_y = yDoor * 8 - m_height;
			}
		}
		else
			SetCharacterMode(CHARMODE_WAITING);
	}
	
	SetPosition(m_x, m_y);
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

void CCharacter::SetVisible(CRoom* pRoom)
{
	if(m_pRoom == pRoom && AbsX() + m_width > 0 && AbsX() < 256)
		Show();
	else
		Hide();
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
	m_facing = directionType;
	
	switch(directionType)
	{
		case DIRECTION_UP:
			(m_green ? SetFrameType(FRAME_GREEN_UP) : SetFrameType(FRAME_UP));
			break;
		case DIRECTION_DOWN:
			(m_green ? SetFrameType(FRAME_GREEN_DOWN) : SetFrameType(FRAME_DOWN));
			break;
		case DIRECTION_LEFT:
			(m_green ? SetFrameType(FRAME_GREEN_LEFT) : SetFrameType(FRAME_LEFT));
			break;
		case DIRECTION_RIGHT:
			(m_green ? SetFrameType(FRAME_GREEN_RIGHT) : SetFrameType(FRAME_RIGHT));
			break;
	}
}

void CCharacter::Move(DirectionType directionType)
{
	m_facing = directionType;
	
	switch(directionType)
	{
		case DIRECTION_UP:
			(m_green ? SetFrameType(FRAME_GREEN_UP) : SetFrameType(FRAME_UP));
			SetPosition(m_x + 1.33, m_y - 0.66);
			break;
		case DIRECTION_DOWN:
			(m_green ? SetFrameType(FRAME_GREEN_DOWN) : SetFrameType(FRAME_DOWN));
			SetPosition(m_x - 1.33, m_y + 0.66);
			break;
		case DIRECTION_LEFT:
			(m_green ? SetFrameType(FRAME_GREEN_LEFT) : SetFrameType(FRAME_LEFT));
			SetPosition(m_x - 1, m_y);
			break;
		case DIRECTION_RIGHT:
			(m_green ? SetFrameType(FRAME_GREEN_RIGHT) : SetFrameType(FRAME_RIGHT));
			SetPosition(m_x + 1, m_y);
			break;
	}
}

void CCharacter::CheckCollision(DirectionType directionType, CollisionType* colNear, CollisionType* colFar)
{
	*colNear = COL_NOTHING_HERE;
	*colFar = COL_NOTHING_HERE;
	int x = pPoint()->X / 8;
	int y = pPoint()->Y / 8;
	
	switch(directionType)
	{
		case DIRECTION_UP:
			*colNear = (CollisionType) m_pRoom->ColMap(x + 1, y - 1);
			*colFar = (CollisionType) m_pRoom->ColMap(x + 1, y - 2);
			
			//m_spriteCol1->SetPosition((x + 1) * 8 - m_pRoom->X(), (y - 1) * 8);
			//m_spriteCol2->SetPosition((x + 1) * 8 - m_pRoom->X(), (y - 2) * 8);
			//m_spriteCol1->Draw();
			//m_spriteCol2->Draw();
			break;
		case DIRECTION_DOWN:
			*colNear = (CollisionType) m_pRoom->ColMap(x - 1, y + 1);
			*colFar = (CollisionType) m_pRoom->ColMap(x - 1, y + 2);
			
			//m_spriteCol1->SetPosition((x - 1) * 8 - m_pRoom->X(), (y + 1) * 8);
			//m_spriteCol2->SetPosition((x - 1) * 8 - m_pRoom->X(), (y + 2) * 8);
			//m_spriteCol1->Draw();
			//m_spriteCol2->Draw();
			break;
		case DIRECTION_LEFT:
			*colNear = (CollisionType) m_pRoom->ColMap(x - 1, y);
			*colFar = (CollisionType) m_pRoom->ColMap(x - 2, y);
			
			//m_spriteCol1->SetPosition((x - 1) * 8 - m_pRoom->X(), y * 8);
			//m_spriteCol2->SetPosition((x - 2) * 8 - m_pRoom->X(), y * 8);
			//m_spriteCol1->Draw();
			//m_spriteCol2->Draw();
			break;
		case DIRECTION_RIGHT:
			*colNear = (CollisionType) m_pRoom->ColMap(x + 1, y);
			*colFar = (CollisionType) m_pRoom->ColMap(x + 2, y);
			
			//m_spriteCol1->SetPosition((x + 1) * 8 - m_pRoom->X(), y * 8);
			//m_spriteCol2->SetPosition((x + 2) * 8 - m_pRoom->X(), y * 8);
			//m_spriteCol1->Draw();
			//m_spriteCol2->Draw();
			break;
	}
}

void CCharacter::SetFrameType(FrameType frameType)
{
	m_pHeadSprite->SetFrameType(frameType);
	m_pBodySprite->SetFrameType(frameType);
}

void CCharacter::SetCharacterMode(CharacterMode characterMode)
{	
	m_characterMode = characterMode;

	switch(characterMode)
	{
	case CHARMODE_NONE:
		SetFrameType(FRAME_NONE);
		break;
	case CHARMODE_WAITING:
		SetFrameType(FRAME_WAITING);
		break;
	case CHARMODE_WALKING:
		Face(m_facing);
		break;
	case CHARMODE_TALKING:
		(m_green ? SetFrameType(FRAME_GREEN_SPEAK) : SetFrameType(FRAME_SPEAK));
		break;
	case CHARMOND_DEAD:
		break;
	}
}

int CCharacter::AbsX()
{
	return m_x - m_pRoom->X();
}
