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
	m_dead = false;
	m_deadSide = false;
	
	m_pathPosition = 0;
	
	m_itemCache = new CItemCache(ITEMLOCATION_CHARACTER, this);
	
	//m_spriteCol1 = new CSprite(SPRITE_COL1, sprite_colTiles + 256 * 0, sprite_colTilesLen, sprite_colPal, sprite_colPalLen, NULL, 0);
	//m_spriteCol2 = new CSprite(SPRITE_COL2, sprite_colTiles + 256 * 1, sprite_colTilesLen, sprite_colPal, sprite_colPalLen, NULL, 0);
	
	//m_spriteCol1 = new CSprite(SPRITE_COL1, sprite_colBitmap, NULL, 0);
	//m_spriteCol2 = new CSprite(SPRITE_COL2, sprite_colBitmap, NULL, 0);
	
	//m_spriteCol1->SetOamIndex(122);
	//m_spriteCol2->SetOamIndex(123);
}

CCharacter::~CCharacter()
{
}

void CCharacter::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
	
	if(m_dead && m_deadSide)
	{
		m_pHeadSprite->SetPosition(AbsX() - 16 + 32 , m_y + 32);
		m_pBodySprite->SetPosition(AbsX() - 16, m_y + 32);
	}
	else
	{
		m_pHeadSprite->SetPosition(AbsX(), m_y);
		m_pBodySprite->SetPosition(AbsX(), m_y + HEAD_HEIGHT);
	}
}

void CCharacter::SetOamIndex(int index)
{
	m_pHeadSprite->SetOamIndex(index);
	m_pBodySprite->SetOamIndex(index + 1);
}

void CCharacter::SetPriority(int priority)
{
	m_pHeadSprite->SetPriority(priority);
	m_pBodySprite->SetPriority(priority);
}

void CCharacter::Update()
{
	switch(m_characterMode)
	{
	case CHARMODE_NONE:
		break;
	case CHARMODE_WAITING:
		m_waitingTime++;
		
		if(m_waitingTime > 500)
			m_characterMode = CHARMODE_WALKING;
		break;
	case CHARMODE_WALKING:
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
						{
							SetFrameType(FRAME_RIGHT);
							SetHFlip(false);
							
							m_y -= 0.3f;		// up
						}
						else
						{
							SetFrameType(FRAME_LEFT);
							SetHFlip(false);
							
							m_y += 0.3f;		// down
						}
					}
					else
					{			
						if(yPos > m_pRoom->CentreY())			// Below centre of room so move up diagonally
						{
							SetFrameType(FRAME_RIGHT);
							SetHFlip(false);
							
							m_x += 0.6f;
							m_y -= 0.3f;
						}
						else if(yPos < m_pRoom->CentreY()) 	// Above centre of room so move down diagonally
						{
							SetFrameType(FRAME_LEFT);
							SetHFlip(false);
							
							m_x -= 0.6f;
							m_y += 0.3f;
						}
						else
						{						
							if(xDist < 0)
							{
								SetFrameType(FRAME_LEFT);
								SetHFlip(false);
							}
							else
							{
								SetFrameType(FRAME_LEFT);
								SetHFlip(true);
							}
						
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
		break;
	case CHARMODE_TALKING:
		break;
	case CHARMODE_DEAD:
	case CHARMODE_BOMB:
	case CHARMODE_ATTACK:
	case CHARMODE_SURRENDER:
	case CHARMODE_QUESTION:
		break;
	}
	
	SetPosition(m_x, m_y);

	m_pHeadSprite->Update();
	m_pBodySprite->Update();
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

void CCharacter::SetHFlip(bool hflip)
{
	m_pHeadSprite->SetHFlip(hflip);
	m_pBodySprite->SetHFlip(hflip);
}

void CCharacter::Draw()
{
	if(!m_visible)
		return;
	
	m_pHeadSprite->Draw();
	m_pBodySprite->Draw();
}

void CCharacter::SetSub(bool sub)
{
	m_pHeadSprite->SetSub(sub);
	m_pBodySprite->SetSub(sub);
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

bool CCharacter::CheckCollision(DirectionType directionType, CollisionType* colNear, CollisionType* colFar)
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
	
	if(*colNear != COL_NOTHING_HERE || *colFar != COL_NOTHING_HERE)
		return true;
	
	return false;
}

bool CCharacter::CheckCollision(DirectionType directionType, CCharacter* character, CharacterType* charNear, CharacterType* charFar)
{
	RECT rectMe, rectYou;
	
	*charNear = CHARTYPE_NONE;
	*charFar = CHARTYPE_NONE;
	
	rectMe.X = m_x;
	rectMe.Y = m_y + m_height - 8;
	rectMe.Width = m_width;
	rectMe.Height = 8;
	
	rectYou.X = character->X();
	rectYou.Y = character->Y() + character->Height() - 8;
	rectYou.Width = character->Width();
	rectYou.Height = 8;
	
	switch(directionType)
	{
		case DIRECTION_UP:
			if(IntersectRect(&rectMe, &rectYou))
				*charNear = character->GetCharacterType();
			
			rectMe.X += 8;
			rectMe.Y -= 8;
			
			if(IntersectRect(&rectMe, &rectYou))
				*charFar = character->GetCharacterType();
			break;
		case DIRECTION_DOWN:
			if(IntersectRect(&rectMe, &rectYou))
				*charNear = character->GetCharacterType();
			
			rectMe.X -= 8;
			rectMe.Y += 8;
			
			if(IntersectRect(&rectMe, &rectYou))
				*charFar = character->GetCharacterType();
			break;
		case DIRECTION_LEFT:
			if(IntersectRect(&rectMe, &rectYou))
				*charNear = character->GetCharacterType();
			
			rectMe.X -= 16;
			
			if(IntersectRect(&rectMe, &rectYou))
				*charFar = character->GetCharacterType();
			break;
		case DIRECTION_RIGHT:
			if(IntersectRect(&rectMe, &rectYou))
				*charNear = character->GetCharacterType();
			
			rectMe.X += 16;
			
			if(IntersectRect(&rectMe, &rectYou))
				*charFar = character->GetCharacterType();
			break;
	}
	
	if(*charNear != CHARTYPE_NONE || *charFar != CHARTYPE_NONE)
		return true;
	
	return false;
}

void CCharacter::SetFrameType(FrameType frameType)
{
	m_pHeadSprite->SetFrameType(frameType);
	m_pBodySprite->SetFrameType(frameType);
}

void CCharacter::SetCharacterMode(CharacterMode characterMode)
{
	m_lastCharacterMode = m_characterMode;
	m_characterMode = characterMode;

	switch(characterMode)
	{
	case CHARMODE_NONE:
		SetFrameType(FRAME_NONE);
		break;
	case CHARMODE_WAITING:
		SetFrameType(FRAME_WAITING);
		m_pHeadSprite->GetNextFrame();
		m_pBodySprite->GetNextFrame();
		m_waitingTime = 0;
		break;
	case CHARMODE_WALKING:
		Face(m_facing);
		break;
	case CHARMODE_TALKING:
		(m_green ? SetFrameType(FRAME_GREEN_SPEAK) : SetFrameType(FRAME_SPEAK));
		break;
	case CHARMODE_DEAD:
		m_dead = true;
		SetFrameType(FRAME_DEAD);
		m_pHeadSprite->GetNextFrame();
		m_pBodySprite->GetNextFrame();
		break;
	case CHARMODE_BOMB:
		SetFrameType(FRAME_BOMB);
		m_pHeadSprite->GetNextFrame();
		m_pBodySprite->GetNextFrame();
		break;
	case CHARMODE_ATTACK:
		SetFrameType(FRAME_ATTACK);
		m_pHeadSprite->GetNextFrame();
		m_pBodySprite->GetNextFrame();
		break;
	case CHARMODE_SURRENDER:
		SetFrameType(FRAME_SURRENDER);
		m_pHeadSprite->GetNextFrame();
		m_pBodySprite->GetNextFrame();
		break;
	case CHARMODE_QUESTION:
		SetFrameType(FRAME_QUESTION);
		break;
	}
}

int CCharacter::AbsX()
{
	return m_x - m_pRoom->X();
}
