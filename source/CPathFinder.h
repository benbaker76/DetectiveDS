#ifndef __CPATHFINDER_H__
#define __CPATHFINDER_H__

#include "CRoom.h"

#define MAX_STEPS				54
#define MAX_ROOMS				38

class CRoomNode
{
public:
	CRoomNode(CRoom* pRoom)
	{
		Room = pRoom;
		
		for(int i=0; i<MAX_DOORS; i++)
			RoomConnections[i] = NULL;
	}
	
	CRoom* Room;
	CRoomNode* RoomConnections[MAX_DOORS];
	
private:
};

class CPathFinder
{
public:
	CPathFinder();
	~CPathFinder();
	
	static void Initialize(CRoom* pRoomArray[MAX_ROOMS]);
	void FindRoute(CRoom* pRoomStart, CRoom* pRoomEnd);
	CRoom* GetRoom(int index) const { return (m_returnArray[index] != NULL ? m_returnArray[index]->Room : NULL); }

private:
	static CRoomNode* g_pRoomNodeArray[MAX_ROOMS];
	CRoomNode* m_returnArray[MAX_ROOMS];

	CRoomNode* RoomToRoomNode(CRoom* pRoom);
	bool FindNextRoom(int count, CRoom* destination, CRoomNode* currNode);
	bool CanContinueSearch(CRoomNode* room);

};

#endif
