#include <stdio.h>
#include "CDoor.h"
#include "CSave.h"

CDoor::CDoor(DoorType doorType, DoorState doorState, CRoom* pRoomIn, CRoom* pRoomOut, ItemType keyItemType)
{
	m_doorId = (doorType | (pRoomIn->GetRoomType() << 8) | (pRoomOut->GetRoomType() << 16));
	m_doorType = doorType;
	m_defaultDoorState = m_doorState = doorState;
	m_pRoomIn = pRoomIn;
	m_pRoomOut = pRoomOut;
	m_pDoorOut = NULL;
	m_keyItemType = keyItemType;
	m_hidden = (m_doorState == DOORSTATE_HIDDEN);
	
	m_rect = NULL;
	m_rectOpen = NULL;
	m_point = NULL;
	
	for(int i=0; i<MAX_DOOR_RECT; i++)
		m_rectArray[i] = NULL;
	
	m_pRoomIn->GetColMapRect((CollisionType) m_doorType, &m_rect);
	
	if(m_rect != NULL)
	{
		m_pRoomIn->GetColMapRect(COL_SRC_DOOR_CLOSED, &m_rectArray[DOORRECT_CLOSED]);
		m_pRoomIn->GetColMapRect(COL_SRC_DOOR_OPEN, &m_rectArray[DOORRECT_OPEN]);
		m_pRoomIn->GetColMapRect(COL_SRC_DOOR_HIDDEN, &m_rectArray[DOORRECT_HIDDEN]);
		m_pRoomIn->GetColMapRect(COL_SRC_DOOR_SMALL_CLOSED, &m_rectArray[DOORRECT_SMALL_CLOSED]);
		m_pRoomIn->GetColMapRect(COL_SRC_DOOR_SMALL_OPEN, &m_rectArray[DOORRECT_SMALL_OPEN]);
		m_pRoomIn->GetColMapRect(COL_SRC_DOOR_SMALL_HIDDEN, &m_rectArray[DOORRECT_SMALL_HIDDEN]);
	
		m_topDoor = (m_rect->Width > 1 && m_rect->Height > 1);
	
		m_point = new Point(m_rect->X + (m_rect->Width / 2) - 1, m_rect->Y + m_rect->Height);
		
		if(m_topDoor && m_rectArray[DOORRECT_OPEN] != NULL)
			m_rectOpen = new Rect(m_rect->X - m_rect->Width, m_rect->Y, m_rect->Width, m_rect->Height);
	}
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
			m_pRoomIn->MoveMap(m_rectArray[DOORRECT_CLOSED], m_rect);
		else
			m_pRoomIn->MoveMap(m_rectArray[DOORRECT_SMALL_CLOSED], m_rect);
		break;
	case DOORSTATE_OPEN:
		if(m_topDoor)
			m_pRoomIn->MoveMap(m_rectArray[DOORRECT_OPEN], m_rectOpen);
		else
			m_pRoomIn->MoveMap(m_rectArray[DOORRECT_SMALL_OPEN], m_rect);
		break;
	case DOORSTATE_HIDDEN:
		if(m_topDoor)
			m_pRoomIn->MoveMap(m_rectArray[DOORRECT_HIDDEN], m_rect);
		else
			m_pRoomIn->MoveMap(m_rectArray[DOORRECT_SMALL_HIDDEN], m_rect);
		break;
	}
}

void CDoor::Draw(CRoom* pCurrentRoom)
{
	if(pCurrentRoom != NULL)
	{
		if(m_pRoomIn != NULL)
		{
			if(m_pRoomIn == pCurrentRoom)
				m_pRoomIn->Draw();
		}
		
		if(m_pRoomOut != NULL)
		{
			if(m_pRoomOut == pCurrentRoom)
				m_pRoomOut->Draw();
		}
	}
}

void CDoor::Save(CSave* pSave)
{
	pSave->WriteByte(m_doorState);
}

void CDoor::Load(CSave* pSave)
{
	pSave->ReadByte((byte*)&m_doorState);
}

