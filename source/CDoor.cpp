#include <stdio.h>
#include "CDoor.h"

CDoor::CDoor(DoorType doorType, DoorState doorState, CRoom* pRoomIn, CRoom* pRoomOut)
{
	m_doorType = doorType;
	m_doorState = doorState;
	m_pRoomIn = pRoomIn;
	m_pRoomOut = pRoomOut;
	m_pDoorOut = NULL;
	
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;
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
	
	GetPosition();
}

void CDoor::GetPosition()
{
	bool doorFound = false;
	
	for(int y=0; y < m_pRoomIn->Height() / 8; y++)
	{
		for(int x=0; x < m_pRoomIn->Width() / 8; x++)
		{	
			if(m_pRoomIn->ColMap(x, y) == m_doorType)
			{
				if(!doorFound)
				{
					doorFound = true;			
					m_x = x * 8;
					m_y = y * 8;
				}
				
				m_width = (x * 8 - m_x);
				m_height = (y * 8 - m_y);
			}
		}
	}
	
	//char buf[256];
	//sprintf(buf, "x:%d, y:%d, width:%d, height:%d", m_x, m_y, m_width, m_height);
	//fprintf(stderr, buf);
}
