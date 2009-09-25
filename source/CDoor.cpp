#include <stdio.h>
#include "CDoor.h"

CDoor::CDoor(DoorType doorType, DoorState doorState, CRoom* pRoomIn, CRoom* pRoomOut)
{
	m_doorType = doorType;
	m_doorState = doorState;
	m_pRoomIn = pRoomIn;
	m_pRoomOut = pRoomOut;
	m_pDoorOut = NULL;
	m_hidden = (doorState == DOORSTATE_HIDDEN);
	
	memset(&m_rect, 0, sizeof(RECT));
	memset(&m_rectOpen, 0, sizeof(RECT));
	memset(&m_point, 0, sizeof(POINT));
	
	for(int i=0; i<MAX_DOOR_RECT; i++)
		memset(&m_rectArray[i], 0, sizeof(RECT));
	
	m_pRoomIn->GetColMapRect((CollisionType) m_doorType, &m_rect);
	
	m_topDoor = (m_rect.Width > 1 && m_rect.Height > 1);
	
	if(!IsRectEmpty(&m_rect))
	{
		m_point.X = ((m_rect.X + (m_rect.Width / 2)) - 1);
		m_point.Y = (m_rect.Y + m_rect.Height - 1);
		
		if(m_topDoor)
		{
			m_rectOpen.X = m_rect.X - m_rect.Width;
			m_rectOpen.Y = m_rect.Y;
			m_rectOpen.Width = m_rect.Width;
			m_rectOpen.Height = m_rect.Height;
		}
	}
	
	m_pRoomIn->GetColMapRect(COL_SRC_DOOR_CLOSED, &m_rectArray[DOORRECT_CLOSED]);
	m_pRoomIn->GetColMapRect(COL_SRC_DOOR_OPEN, &m_rectArray[DOORRECT_OPEN]);
	m_pRoomIn->GetColMapRect(COL_SRC_DOOR_HIDDEN, &m_rectArray[DOORRECT_HIDDEN]);
	m_pRoomIn->GetColMapRect(COL_SRC_DOOR_SMALL_CLOSED, &m_rectArray[DOORRECT_SMALL_CLOSED]);
	m_pRoomIn->GetColMapRect(COL_SRC_DOOR_SMALL_OPEN, &m_rectArray[DOORRECT_SMALL_OPEN]);
	m_pRoomIn->GetColMapRect(COL_SRC_DOOR_SMALL_HIDDEN, &m_rectArray[DOORRECT_SMALL_HIDDEN]);
}

CDoor::~CDoor()
{
}

bool CDoor::Initialize()
{
	for(int i=0; i < MAX_DOORS; i++)
	{
		CDoor* pDoorOut = m_pRoomOut->GetDoor(i);
	
		if(pDoorOut != NULL)
		{	
			if(m_pRoomIn == pDoorOut->pRoomOut())
			{
				m_pDoorOut = pDoorOut;
				return true;
			}
		}
	}
	
	//PrintRect(&m_rect);
	return false;
}

void CDoor::SetDoorState(DoorState doorState)
{
	m_doorState = doorState;
	
	if(m_pDoorOut != NULL)
	{
		if(m_pDoorOut->GetDoorState() != doorState)
			m_pDoorOut->SetDoorState(doorState);
	}
}

void CDoor::Draw()
{	
	switch(m_doorState)
	{
	case DOORSTATE_LOCKED:
	case DOORSTATE_CLOSED:
		if(m_topDoor)
			m_pRoomIn->MoveMap(&m_rectArray[DOORRECT_CLOSED], &m_rect);
		else
			m_pRoomIn->MoveMap(&m_rectArray[DOORRECT_SMALL_CLOSED], &m_rect);
		break;
	case DOORSTATE_OPEN:
		if(m_topDoor)
			m_pRoomIn->MoveMap(&m_rectArray[DOORRECT_OPEN], &m_rectOpen);
		else
			m_pRoomIn->MoveMap(&m_rectArray[DOORRECT_SMALL_OPEN], &m_rect);
		break;
	case DOORSTATE_HIDDEN:
		if(m_topDoor)
			m_pRoomIn->MoveMap(&m_rectArray[DOORRECT_HIDDEN], &m_rect);
		else
			m_pRoomIn->MoveMap(&m_rectArray[DOORRECT_SMALL_HIDDEN], &m_rect);
		break;
	}
}


