#ifndef __CPATH_H__
#define __CPATH_H__

#include "CRoom.h"

#define MAX_STEPS				54
#define MAX_ROOMS				37

class CRoomNode
{
public:
	CRoomNode(CRoom* pRoom)
	{
		Room = pRoom;
	}
	
	CRoom* Room;
	CRoomNode* RoomConnections[MAX_DOORS];
	
private:
};

class CPath
{
public:
	CPath(CRoom* pRoomArray[MAX_ROOMS]);
	~CPath();
	
	void FindRoute(CRoom* pRoomStart, CRoom* pRoomEnd);
	CRoom* GetRoom(int index) const { return (m_returnArray[index] != NULL ? m_returnArray[index]->Room : NULL); }

private:
	CRoomNode* m_pRoomNodeArray[MAX_ROOMS];
	CRoomNode* m_returnArray[MAX_ROOMS];

	CRoomNode* RoomToRoomNode(CRoom* pRoom);
	bool FindNextRoom(int count, CRoom* destination, CRoomNode* currNode);
	bool CanContinueSearch(CRoomNode* room);

};

#endif
