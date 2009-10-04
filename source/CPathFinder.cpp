#include <nds.h>
#include <stdio.h>
#include "CPathFinder.h"
#include "CDoor.h"
#include "Text.h"

CRoomNode* CPathFinder::g_pRoomNodeArray[MAX_ROOMS];

CPathFinder::CPathFinder()
{
}

CPathFinder::~CPathFinder()
{
}

void CPathFinder::Initialize(CRoom* pRoomArray[MAX_ROOMS])
{
	for(int i=0; i<MAX_ROOMS; i++)
		g_pRoomNodeArray[i] = new CRoomNode(pRoomArray[i]);	
}

CRoomNode* CPathFinder::RoomToRoomNode(CRoom* pRoom)
{
	for(int i=0; i<MAX_ROOMS; i++)
	{
		if(g_pRoomNodeArray[i]->Room == pRoom)
			return g_pRoomNodeArray[i];
	}
	
	return NULL;
}

void CPathFinder::FindRoute(CRoom* pRoomStart, CRoom* pRoomEnd)
{
	CRoomNode* pRoomNodeStart = RoomToRoomNode(pRoomStart);
	
	for(int i=0; i<MAX_ROOMS; i++)
	{
		for(int j=0; j<MAX_DOORS; j++)
		{
			CDoor* pDoor = g_pRoomNodeArray[i]->Room->GetDoor(j);
			
			if(!pDoor->Hidden())
				g_pRoomNodeArray[i]->RoomConnections[j] = RoomToRoomNode(pDoor->pRoomOut());
		}
		
		m_returnArray[i] = NULL;
	}
	
	m_returnArray[0] = pRoomNodeStart;
	FindNextRoom(1, pRoomEnd, pRoomNodeStart);
}

bool CPathFinder::FindNextRoom(int count, CRoom* destination, CRoomNode* currNode)
{
	if(currNode == NULL)
		return false;
	
	for(int i=0; i<MAX_DOORS; i++)
	{
		if(CanContinueSearch(currNode->RoomConnections[i]))
		{
			m_returnArray[count] = currNode->RoomConnections[i];
			
			if(currNode->RoomConnections[i]->Room == destination)
				return true;
			else
			{		
				if(count < MAX_DOORS - 1)
				{
					if(FindNextRoom(count + 1, destination, currNode->RoomConnections[i]))
						return true;
					else
						m_returnArray[count + 1] = NULL;
				}
			}
		}
	}
	
	return false;
}

bool CPathFinder::CanContinueSearch(CRoomNode* room)
{
	for(int i=0; i<MAX_DOORS; i++)
	{
		if(m_returnArray[i] != NULL)
		{
			if(m_returnArray[i] == room)
				return false;
		}
	}
	
	return true;
}