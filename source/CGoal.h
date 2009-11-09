#ifndef __CGOAL_H__
#define __CGOAL_H__

#include "CPathFinder.h"

#define LOOP_INFINITE	-1

enum GoalType
{
	GOAL_WAIT,
	GOAL_SPEAK,
	GOAL_JUMPROOM,
	GOAL_JUMPPOINT,
	GOAL_GOTOROOM,
	GOAL_GOTOPOINT,
	GOAL_GOTOGOAL,
	GOAL_GOTOCHAR,
	GOAL_WAITCHAR,
	GOAL_STOP
};

class CPathFinder;

class CGoal
{
public:
	CGoal(int id, GoalType goalType, int waitTime)
	{
		m_id = id;
		m_goalType = goalType;
		m_string = NULL;
		m_goalPosition = 0;
		m_waitValue = 0;
		m_waitTime = waitTime;
		m_timeValue = 0;
		m_loopValue = 0;
	}
	
	CGoal(int id, GoalType goalType, int waitTime, int timeOut)
	{
		m_id = id;
		m_goalType = goalType;
		m_string = NULL;
		m_goalPosition = 0;
		m_waitValue = 0;
		m_waitTime = waitTime;
		m_timeOut = timeOut;
		m_timeValue = 0;
		m_loopValue = 0;
	}
	
	CGoal(int id, GoalType goalType, int gotoId, int waitTime, int loopCount)
	{
		m_id = id;
		m_goalType = goalType;
		m_string = NULL;
		m_goalPosition = 0;
		m_gotoId = gotoId;
		m_waitValue = 0;
		m_waitTime = waitTime;
		m_loopCount = loopCount;
		m_timeValue = 0;
		m_loopValue = 0;
	}
	
	CGoal(int id, GoalType goalType, const char* string, int waitTime)
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
	}
	
	CGoal(int id, GoalType goalType, CRoom* pRoomStart, CRoom* pRoomEnd, int waitTime)
	{
		m_id = id;
		m_goalType = goalType;
		m_string = NULL;
		m_goalPosition = 0;
		m_waitValue = 0;
		m_waitTime = waitTime;
		m_timeValue = 0;
		m_loopValue = 0;
		
		m_pathFinder = new CPathFinder();
		m_pathFinder->FindRoute(pRoomStart, pRoomEnd);
		
		for(int i=1; i<MAX_ROOMS; i++)
			m_roomArray[i - 1] = m_pathFinder->GetRoom(i);
	}
	
	CGoal(int id, GoalType goalType, CRoom* pRoom)
	{
		m_id = id;
		m_goalType = goalType;
		m_string = NULL;
		m_goalPosition = 0;
		m_waitValue = 0;
		m_waitTime = 0;
		m_timeValue = 0;
		m_loopValue = 0;
	
		m_roomArray[0] = pRoom;
	}
	
	CGoal(int id, GoalType goalType, Point* pPoint, int waitTime)
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
	}
	
	CGoal(int id, GoalType goalType, Point* pPoint)
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
	}
	
	void Reset()
	{
		m_goalPosition = 0;
		m_waitValue = 0;
		m_timeValue = 0;
		m_loopValue = 0;
		m_spoken = false;
	}
	
	void CalculatePath(CRoom* pRoomStart, CRoom* pRoomEnd)
	{
		m_pathFinder = new CPathFinder();
		m_pathFinder->FindRoute(pRoomStart, pRoomEnd);
		
		for(int i=1; i<MAX_ROOMS; i++)
			m_roomArray[i - 1] = m_pathFinder->GetRoom(i);
	}
	
	GoalType GetGoalType() const { return m_goalType; }
	
	CRoom* pRoom() const { return m_roomArray[m_goalPosition]; }
	Point* pPoint() const { return m_pPoint; }
	int Id() const { return m_id; }
	int GotoId() const { return m_gotoId; }
	bool Waiting() { return (m_waitValue++ < m_waitTime); }
	bool TryGetSpeech(const char** string) { if(!m_spoken) { *string = m_string; m_spoken = true; return true; } else return false; }
	
	bool NextRoom() { return (m_roomArray[(m_goalPosition < MAX_ROOMS ? ++m_goalPosition : m_goalPosition)] != NULL); }
	bool Loop() { return (m_loopCount == -1  || m_loopValue++ < m_loopCount); }

private:
	
	int m_id;
	GoalType m_goalType;
	CPathFinder* m_pathFinder;
	CRoom* m_roomArray[MAX_ROOMS];
	Point* m_pPoint;
	int m_gotoId;
	
	bool m_spoken;
	
	const char* m_string;
	
	int m_goalPosition;
	
	int m_waitValue;
	int m_waitTime;
	
	int m_timeOut;
	int m_timeValue;
	
	int m_loopValue;
	int m_loopCount;
};

#endif
