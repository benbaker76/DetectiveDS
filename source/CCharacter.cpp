#include <stdio.h>
#include <math.h>
#include "CCharacter.h"
#include "Text.h"

CCharacter::CCharacter(CharacterType characterType, CSprite* pHeadSprite, CSprite* pBodySprite, CharacterSex characterSex, int width, int height)
{
	m_characterType = characterType;
	m_characterMode = CHARMODE_NONE;
	m_pHeadSprite = pHeadSprite;
	m_pBodySprite = pBodySprite;
	m_width = width;
	m_height = height;
	m_characterSex = characterSex;
	
	m_origSize.Width = width;
	m_origSize.Height = height;
	
	m_deadSide = false;
	
	m_point = new Point();
	m_rect = new Rect();
	
	m_itemCache = new CItemCache(ITEMLOCATION_CHARACTER, this);
	m_goalManager = new CGoalManager();
	
	Reset();
	
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
		m_pHeadSprite->SetPosition(ScreenX() - 16 + 32 , m_y + 32);
		m_pBodySprite->SetPosition(ScreenX() - 16, m_y + 32);
	}
	else
	{
		m_pHeadSprite->SetPosition(ScreenX(), m_y);
		m_pBodySprite->SetPosition(ScreenX(), m_y + HEAD_HEIGHT);
	}
}

void CCharacter::SetPosition(float x)
{
	SetPosition(x, CentreY());
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

void CCharacter::Reset()
{
	m_x = 0;
	m_y = 0;
	
	m_width = m_origSize.Width;
	m_height = m_origSize.Height;
	
	m_visible = false;
	m_green = false;
	m_dead = false;
	
	m_pRoom = NULL;
	m_pLastDoor = NULL;
	
	m_point->X = 0;
	m_point->Y = 0;
	
	m_string = NULL;
	
	m_goalMode = false;
	
	m_goalManager->ResetGoals();
	m_goalManager->SetGoalPosition(0);
	
	m_pHeadSprite->Reset();
	m_pBodySprite->Reset();
	
	SetHFlip(false);
}

void CCharacter::ResetAnimation()
{
	m_pHeadSprite->ResetAnimation();
	m_pBodySprite->ResetAnimation();
}

uint64 CCharacter::Update(CRoom* pCurrentRoom, uint64 eventFlags)
{
	switch(m_characterMode)
	{
	case CHARMODE_NONE:
		break;
	case CHARMODE_WAITING:
		if(m_goalMode)
		{
			m_frameCount++;
			
			if(m_frameCount > 800)
			{
				m_frameCount = 0;
				
				m_characterMode = CHARMODE_GOAL;
			}
		}
		break;
	case CHARMODE_TALKING:
		if(m_goalMode)
		{
			m_frameCount++;
			
			if(m_frameCount > 500)
			{
				m_frameCount = 0;
				
				m_characterMode = CHARMODE_GOAL;
			}
		}
		break;
	case CHARMODE_DEAD:
	case CHARMODE_BOMB:
	case CHARMODE_ATTACK:
	case CHARMODE_SURRENDER:
	case CHARMODE_QUESTION:
		break;
	case CHARMODE_GOAL:
		{
			CGoal* pGoal = m_goalManager->CurrentGoal();
			
			if(pGoal != NULL)
			{
				switch(pGoal->GetGoalType())
				{
				case GOAL_JUMPROOM:
					m_pRoom = pGoal->pRoom();
					m_goalManager->NextGoal();
					break;
				case GOAL_JUMPPOINT:
					{
						Point* pPoint = pGoal->pPoint();
						
						SetPosition(pPoint->X);
						
						m_goalManager->NextGoal();
					}
					break;
				case GOAL_WAIT:
					{
						SetFrameType(FRAME_WAITING);
						
						if(!pGoal->Waiting())
							m_goalManager->NextGoal();
					}
					break;
				case GOAL_SPEAK:
					if((pGoal->EventFlags() & eventFlags) == pGoal->EventFlags())
					{
						if(pGoal->TryGetSpeech(&m_string))
						{
							SetFrameType(FRAME_SPEAK);
						}
						else
						{
							if(!pGoal->Waiting())
								m_goalManager->NextGoal();
						}
					}
					else
					{
						if(!pGoal->Waiting())
							m_goalManager->NextGoal();
					}
					break;
				case GOAL_WAITEVENT:
					if((pGoal->EventFlags() & eventFlags) == pGoal->EventFlags())
					{
						if(pGoal->Waiting())
							SetFrameType(FRAME_NONE);
						else
							m_goalManager->NextGoal();
						
						break;
					}
					else
					{
						if(!pGoal->TimeOut())
							SetFrameType(FRAME_NONE);
						else
							m_goalManager->NextGoal();
						
						break;
					}
					break;
				case GOAL_SETEVENT:
					eventFlags |= pGoal->EventFlags();
					
					if(pGoal->Waiting())
						SetFrameType(FRAME_NONE);
					else
						m_goalManager->NextGoal();
					break;
				case GOAL_LOCKDOOR:
					if(m_pLastDoor != NULL)
					{
						if(m_pLastDoor->GetDoorState() != DOORSTATE_LOCKED)
						{
							m_pLastDoor->SetDoorState(DOORSTATE_LOCKED);
						
							m_pLastDoor->Draw(pCurrentRoom);
						}
					}
					
					if(pGoal->Waiting())
						SetFrameType(FRAME_NONE);
					else
						m_goalManager->NextGoal();
					break;
				case GOAL_GOTOGOAL:
					{					
						if(pGoal->Loop() && ((pGoal->EventFlags() & eventFlags) == pGoal->EventFlags()))
						{
							int loopValue = pGoal->GetLoopValue();
							
							m_goalManager->GotoGoal();
							
							pGoal->SetLoopValue(loopValue);
						}
						else
							m_goalManager->NextGoal();
					}
					break;
				case GOAL_GOTOROOM:
				case GOAL_GOTOCHAR:
					{
						if(pGoal->GetGoalType() == GOAL_GOTOCHAR)
						{
							if(!pGoal->PathFound())
								pGoal->CalculateCharacterPath(m_pRoom);
				
							if(pGoal->pCharacter()->GetRoom() == m_pRoom)
							{
								if(pGoal->Waiting())
									SetFrameType(FRAME_NONE);
								else
									m_goalManager->NextGoal();
								
								break;
							}
						}
						else
						{
							if(!pGoal->PathFound())
								pGoal->CalculateRoomPath(m_pRoom);
						}
						
						CRoom* pRoom = pGoal->pRoom();
						
						if(pRoom != NULL)
						{
							CDoor* pDoor = m_pRoom->GetRoomDoor(pRoom);
							Point point(pDoor->pPoint()->X, pDoor->pPoint()->Y);
							point.X *= 8;
							point.Y *= 8;
							
							if(MoveTo(&point))
							{
								DoorState doorState = pDoor->GetDoorState();
								
								if(pDoor->GetKeyItemType() != ITEM_NONE)
								{
									if(m_keyItemType == pDoor->GetKeyItemType())
									{							
										if(doorState == DOORSTATE_LOCKED || doorState == DOORSTATE_CLOSED)
											pDoor->SetDoorState(DOORSTATE_OPEN);
									}
									else
									{
										if(doorState == DOORSTATE_LOCKED)
										{
											if(pGoal->GotoId() != 0)
												m_goalManager->GotoGoal();
												
											SetFrameType(FRAME_NONE);
												
											break;
										}
										else
											pDoor->SetDoorState(DOORSTATE_OPEN);
									}
								}
								else
									pDoor->SetDoorState(DOORSTATE_OPEN);
								
								pDoor->Draw(pCurrentRoom);
								m_pLastDoor = pDoor;
								
								m_pRoom = pRoom;
								
								int xDoor = pDoor->pDoorOut()->pPoint()->X;
								int yDoor = pDoor->pDoorOut()->pPoint()->Y;

								m_x = xDoor * 8;
								m_y = yDoor * 8 - m_height - (yDoor == 24 ? 8 : 0);
								
								pGoal->NextRoom();
							}
						}
						else
						{
							if(pGoal->Waiting())
								SetFrameType(FRAME_NONE);
							else
								m_goalManager->NextGoal();
						}
					}
					break;
				case GOAL_GOTOPOINT:
					{					
						if(MoveTo(pGoal->pPoint()))
						{						
							if(pGoal->Waiting())
								SetFrameType(FRAME_NONE);
							else
								m_goalManager->NextGoal();
						}
					}
					break;
				default:
					break;
				}
			}
			else
				SetCharacterMode(CHARMODE_WAITING);
		}
		break;
	}
	
	SetPosition(m_x, m_y);

	m_pHeadSprite->Update();
	m_pBodySprite->Update();
	
	return eventFlags;
}

bool CCharacter::MoveTo(Point* pDest)
{
	int xPos = pPoint()->X;
	int yPos = pPoint()->Y;
	int xEnd = pDest->X;
	int yEnd = pDest->Y;	
	int xDist = xEnd - xPos;
	int yDist = yEnd - yPos;
	
	float angle = atan2(yDist, xDist);
	float degrees = angle * (180 / PI) + 180;
	
	if(abs(xDist) < 8 && abs(yDist) < 8)
		return true;
	
	if(abs(xDist) > 32 && yPos != m_pRoom->CentreY())
	{
		if(yPos < m_pRoom->CentreY())
		{
			SetFrameType(FRAME_LEFT);
			SetHFlip(false);
			m_x -= 0.6f;
			m_y += 0.3f;
		}
		else
		{
			SetFrameType(FRAME_RIGHT);
			SetHFlip(false);
			m_x += 0.6f;
			m_y -= 0.3f;
		}
		
		return false;
	}
	
	if(degrees > 315) // Left
	{
		SetFrameType(FRAME_LEFT);
		SetHFlip(false);
	}
	else if(degrees > 225) // Down
	{
		SetFrameType(FRAME_LEFT);
		SetHFlip(false);
	}
	else if(degrees > 135) // Right
	{
		SetFrameType(FRAME_LEFT);
		SetHFlip(true);
	}
	else if(degrees > 45) // Up
	{
		SetFrameType(FRAME_RIGHT);
		SetHFlip(false);
	}
	else // Left
	{
		SetFrameType(FRAME_LEFT);
		SetHFlip(false);
	}

	m_x += cos(angle) * 0.6f;
	
	if(abs(xDist) < 32)
		m_y += sin(angle) * 0.3f;
	
	return false;
}

bool CCharacter::IsVisible(CRoom* pRoom)
{
	if(m_pRoom == pRoom && ScreenX() + m_width > 0 && ScreenX() < 256)
		return true;

	return false;
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
	Rect rectMe(m_x, m_y + m_height - 8, m_width, 8);
	Rect rectYou(character->X(), character->Y() + character->Height() - 8, character->Width(), 8);
	
	*charNear = CHARTYPE_NONE;
	*charFar = CHARTYPE_NONE;
	
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
	m_characterMode = characterMode;

	switch(characterMode)
	{
	case CHARMODE_NONE:
		SetFrameType(FRAME_NONE);
		SetHFlip(false);
		break;
	case CHARMODE_WAITING:
		SetFrameType(FRAME_WAITING);
		m_pHeadSprite->GetNextFrame();
		m_pBodySprite->GetNextFrame();
		SetHFlip(false);
		m_frameCount = 0;
		break;
	case CHARMODE_GOAL:
		Face(m_facing);
		m_pHeadSprite->GetNextFrame();
		m_pBodySprite->GetNextFrame();
		SetHFlip(false);
		break;
	case CHARMODE_TALKING:
		(m_green ? SetFrameType(FRAME_GREEN_SPEAK) : SetFrameType(FRAME_SPEAK));
		m_pHeadSprite->GetNextFrame();
		m_pBodySprite->GetNextFrame();
		m_frameCount = 0;
		break;
	case CHARMODE_DEAD:
		m_dead = true;
		SetFrameType(FRAME_DEAD);
		m_pHeadSprite->GetNextFrame();
		m_pBodySprite->GetNextFrame();
		SetHFlip(false);
		
		if(m_deadSide)
		{
			m_width = 64;
			m_height = 18 + 32;
		}
		else
		{
			m_height = HEAD_HEIGHT;
		}
		break;
	case CHARMODE_BOMB:
		SetFrameType(FRAME_BOMB);
		m_pHeadSprite->GetNextFrame();
		m_pBodySprite->GetNextFrame();
		SetHFlip(false);
		break;
	case CHARMODE_ATTACK:
		SetFrameType(FRAME_ATTACK);
		m_pHeadSprite->GetNextFrame();
		m_pBodySprite->GetNextFrame();
		SetHFlip(true);
		break;
	case CHARMODE_SURRENDER:
		SetFrameType(FRAME_SURRENDER);
		m_pHeadSprite->GetNextFrame();
		m_pBodySprite->GetNextFrame();
		SetHFlip(false);
		break;
	case CHARMODE_QUESTION:
		SetFrameType(FRAME_QUESTION);
		SetHFlip(false);
		break;
	}
}

int CCharacter::ScreenX()
{
	return m_x - (m_pRoom == NULL ? 0 : m_pRoom->X());
}
