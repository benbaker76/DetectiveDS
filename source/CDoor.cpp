#include <stdio.h>
#include "CDoor.h"

CDoor::CDoor(DoorType doorType, DoorState doorState, CRoom* pRoomIn, CRoom* pRoomOut)
{
	m_doorType = doorType;
	m_doorState = doorState;
	m_pRoomIn = pRoomIn;
	m_pRoomOut = pRoomOut;
	m_pDoorOut = NULL;
	
	memset(&m_rect, 0, sizeof(RECT));
	
	for(int i=0; i<MAX_DOOR_RECT; i++)
		memset(&m_rectArray[i], 0, sizeof(RECT));
}

CDoor::~CDoor()
{
}

void CDoor::Initialize()
{
	for(int i=0; i < MAX_DOORS; i++)
	{
		CDoor* pDoor = m_pRoomOut->GetDoor(i);
	
		if(pDoor != NULL)
		{	
			if(m_pRoomIn == pDoor->pRoomOut())
				m_pDoorOut = pDoor;
		}
	}
	
	m_pRoomIn->GetColMapRect((CollisionType) m_doorType, &m_rect);
	
	m_pRoomIn->GetColMapRect(COL_DOOR_CLOSED, &m_rectArray[DOORRECT_CLOSED]);
	m_pRoomIn->GetColMapRect(COL_DOOR_OPEN, &m_rectArray[DOORRECT_OPEN]);
	m_pRoomIn->GetColMapRect(COL_DOOR_SMALL_CLOSED, &m_rectArray[DOORRECT_SMALL_CLOSED]);
	m_pRoomIn->GetColMapRect(COL_DOOR_SMALL_OPEN, &m_rectArray[DOORRECT_SMALL_OPEN]);
	m_pRoomIn->GetColMapRect(COL_DOOR_SMALL_HIDDEN, &m_rectArray[DOORRECT_SMALL_HIDDEN]);
	
	//char buf[256];
	//sprintf(buf, "X:%d, Y:%d, Width:%d, Height:%d", m_rect.X, m_rect.Y, m_rect.Width, m_rect.Height);
	//fprintf(stderr, buf);
}

void CDoor::SetDoorState(DoorState doorState)
{
	m_doorState = doorState;
	
	if(m_pDoorOut->GetDoorState() != doorState)
		m_pDoorOut->SetDoorState(doorState);
}

void CDoor::Draw()
{
	bool topDoor = (m_rect.Y < 23);
		
	switch(m_doorState)
	{
	case DOORSTATE_LOCKED:
	case DOORSTATE_CLOSED:
		if(topDoor)
			m_pRoomIn->MoveMap(&m_rectArray[DOORRECT_CLOSED], &m_rect);
		else
			m_pRoomIn->MoveMap(&m_rectArray[DOORRECT_SMALL_CLOSED], &m_rect);
		break;
	case DOORSTATE_OPEN:
		if(topDoor)
		{
			RECT destRect;
	
			destRect.X = m_rect.X - m_rect.Width;
			destRect.Y = m_rect.Y;
			destRect.Width = m_rect.Width;
			destRect.Height = m_rect.Height;
			
			m_pRoomIn->MoveMap(&m_rectArray[DOORRECT_OPEN], &destRect);
		}
		else
			m_pRoomIn->MoveMap(&m_rectArray[DOORRECT_SMALL_OPEN], &m_rect);
		break;
	case DOORSTATE_HIDDEN:
		if(topDoor)
			m_pRoomIn->MoveMap(&m_rectArray[DOORRECT_OPEN], &m_rect);
		else
			m_pRoomIn->MoveMap(&m_rectArray[DOORRECT_SMALL_HIDDEN], &m_rect);
		break;
	}
	
	//char buf[256];
	//sprintf(buf, "X:%d, Y:%d, Width:%d, Height:%d", m_rect.X, m_rect.Y, m_rect.Width, m_rect.Height);
	//fprintf(stderr, buf);
}


