#include "CGoal.h"
#include "CCharacter.h"

CGoal::CGoal(int id, GoalType goalType, int waitTime)
{
	m_id = id;
	m_goalType = goalType;
	m_string = NULL;
	m_goalPosition = 0;
	m_waitValue = 0;
	m_waitTime = waitTime;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
}

CGoal::CGoal(int id, GoalType goalType, CCharacter* character, int waitTime)
{
	m_id = id;
	m_goalType = goalType;
	m_string = NULL;
	m_goalPosition = 0;
	m_waitValue = 0;
	m_character = character;
	m_waitTime = waitTime;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
}

CGoal::CGoal(int id, GoalType goalType, uint64 eventFlags, int waitTime)
{
	m_id = id;
	m_goalType = goalType;
	m_string = NULL;
	m_goalPosition = 0;
	m_waitValue = 0;
	m_eventFlags = eventFlags;
	m_waitTime = waitTime;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
}

CGoal::CGoal(int id, GoalType goalType, uint64 eventFlags, int waitTime, int timeOut)
{
	m_id = id;
	m_goalType = goalType;
	m_string = NULL;
	m_goalPosition = 0;
	m_waitValue = 0;
	m_eventFlags = eventFlags;
	m_waitTime = waitTime;
	m_timeOut = timeOut;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
}

CGoal::CGoal(int id, GoalType goalType, int gotoId, uint64 eventFlags, int waitTime, int loopCount)
{
	m_id = id;
	m_goalType = goalType;
	m_string = NULL;
	m_goalPosition = 0;
	m_gotoId = gotoId;
	m_eventFlags = eventFlags;
	m_waitValue = 0;
	m_waitTime = waitTime;
	m_loopCount = loopCount;
	m_timeValue = 0;
	m_loopValue = 0;
	m_pathFound = false;
}

CGoal::CGoal(int id, GoalType goalType, const char* string, int waitTime)
{
	m_id = id;
	m_goalType = goalType;
	m_string = string;
	m_goalPosition = 0;
	m_waitTime = waitTime;
	m_waitValue = 0;
	m_spoken = false;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
}

CGoal::CGoal(int id, GoalType goalType, CRoom* pRoomEnd, int waitTime)
{
	m_id = id;
	m_goalType = goalType;
	m_string = NULL;
	m_goalPosition = 0;
	m_roomEnd = pRoomEnd;
	m_waitValue = 0;
	m_waitTime = waitTime;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
}

CGoal::CGoal(int id, GoalType goalType, CRoom* pRoomStart, CRoom* pRoomEnd, int waitTime)
{
	m_id = id;
	m_goalType = goalType;
	m_string = NULL;
	m_goalPosition = 0;
	m_roomEnd = pRoomEnd;
	m_waitValue = 0;
	m_waitTime = waitTime;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
	
	CalculatePath(pRoomStart, pRoomEnd);
}

CGoal::CGoal(int id, GoalType goalType, CRoom* pRoomStart, CRoom* pRoomEnd, int gotoId, int waitTime)
{
	m_id = id;
	m_goalType = goalType;
	m_string = NULL;
	m_goalPosition = 0;
	m_roomEnd = pRoomEnd;
	m_gotoId = gotoId;
	m_waitValue = 0;
	m_waitTime = waitTime;
	m_timeValue = 0;
	m_loopValue = 0;
	m_pathFound = false;
	
	CalculatePath(pRoomStart, pRoomEnd);
}

CGoal::CGoal(int id, GoalType goalType, CRoom* pRoom)
{
	m_id = id;
	m_goalType = goalType;
	m_string = NULL;
	m_goalPosition = 0;
	m_waitValue = 0;
	m_waitTime = 0;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;

	m_roomArray[0] = pRoom;
}

CGoal::CGoal(int id, GoalType goalType, Point* pPoint, int waitTime)
{
	m_id = id;
	m_goalType = goalType;
	m_pPoint = pPoint;
	m_string = NULL;
	m_goalPosition = 0;
	m_waitValue = 0;
	m_waitTime = waitTime;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
}

CGoal::CGoal(int id, GoalType goalType, Point* pPoint)
{
	m_id = id;
	m_goalType = goalType;
	m_pPoint = pPoint;
	m_string = NULL;
	m_goalPosition = 0;
	m_waitValue = 0;
	m_waitTime = 0;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
}

void CGoal::Reset()
{
	m_goalPosition = 0;
	m_waitValue = 0;
	m_timeValue = 0;
	m_loopValue = 0;
	m_spoken = false;
	m_pathFound = false;
}

void CGoal::CalculateCharacterPath(CRoom* pRoomStart)
{
	if(m_character->GetRoom() == NULL)
		return;
		
	CalculatePath(pRoomStart, m_character->GetRoom());
}

void CGoal::CalculateRoomPath(CRoom* pRoomStart)
{	
	CalculatePath(pRoomStart, m_roomEnd);
}

void CGoal::CalculatePath(CRoom* pRoomStart, CRoom* pRoomEnd)
{
	if(m_pathFound)
		return;

	static CPathFinder pathFinder;
	pathFinder.FindRoute(pRoomStart, pRoomEnd);
	
	for(int i=1; i<MAX_ROOMS; i++)
		m_roomArray[i - 1] = pathFinder.GetRoom(i);
	
	m_pathFound = true;
}
