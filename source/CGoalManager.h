#ifndef __CGOALMANAGER_H__
#define __CGOALMANAGER_H__

#include <stdio.h>
#include "CRoom.h"
#include "CPathFinder.h"
#include "Text.h"

#define MAX_GOALS		64

enum GoalType
{
	GOAL_WAIT,
	GOAL_SPEAK,
	GOAL_JUMPROOM,
	GOAL_JUMPPOINT,
	GOAL_GOTOROOM,
	GOAL_GOTOPOINT,
	GOAL_GOTOGOAL
};

class CPathFinder;

class CGoal
{
public:
	CGoal(GoalType goalType, int waitTime)
	{
		m_goalType = goalType;
		m_string = NULL;
		m_goalPosition = 0;
		m_waitValue = 0;
		m_waitTime = waitTime;
	}
	
	CGoal(GoalType goalType, CGoal* pGoal, int waitTime)
	{
		m_goalType = goalType;
		m_string = NULL;
		m_goalPosition = 0;
		m_pGoal = pGoal;
		m_waitValue = 0;
		m_waitTime = waitTime;
	}
	
	CGoal(GoalType goalType, const char* string, int waitTime)
	{
		m_goalType = goalType;
		m_string = string;
		m_goalPosition = 0;
		m_waitTime = waitTime;
		m_waitValue = 0;
		m_spoken = false;
	}
	
	CGoal(GoalType goalType, CRoom* pRoomStart, CRoom* pRoomEnd, int waitTime)
	{
		m_goalType = goalType;
		m_string = NULL;
		m_goalPosition = 0;
		m_waitValue = 0;
		m_waitTime = waitTime;
		
		m_pathFinder = new CPathFinder();
		m_pathFinder->FindRoute(pRoomStart, pRoomEnd);
		
		for(int i=1; i<MAX_ROOMS; i++)
			m_roomArray[i - 1] = m_pathFinder->GetRoom(i);
	}
	
	CGoal(GoalType goalType, CRoom* pRoom)
	{
		m_goalType = goalType;
		m_string = NULL;
		m_goalPosition = 0;
		m_waitValue = 0;
		m_waitTime = 0;
	
		m_roomArray[0] = pRoom;
	}
	
	CGoal(GoalType goalType, Point* pPoint, int waitTime)
	{
		m_goalType = goalType;
		m_pPoint = pPoint;
		m_string = NULL;
		m_goalPosition = 0;
		m_waitValue = 0;
		m_waitTime = waitTime;
	}
	
	CGoal(GoalType goalType, Point* pPoint)
	{
		m_goalType = goalType;
		m_pPoint = pPoint;
		m_string = NULL;
		m_goalPosition = 0;
		m_waitValue = 0;
		m_waitTime = 0;
	}
	
	void Reset()
	{
		m_goalPosition = 0;
		m_waitValue = 0;
		m_spoken = false;
	}
	
	GoalType GetGoalType() const { return m_goalType; }
	
	CRoom* pRoom() const { return m_roomArray[m_goalPosition]; }
	Point* pPoint() const { return m_pPoint; }
	CGoal* pGoal() const { return m_pGoal; }
	bool Waiting() { return (m_waitValue++ < m_waitTime); }
	bool TryGetSpeech(const char** string) { if(!m_spoken) { *string = m_string; m_spoken = true; return true; } else return false; }
	
	bool NextRoom() { return (m_roomArray[(m_goalPosition < MAX_ROOMS ? ++m_goalPosition : m_goalPosition)] != NULL); }

private:

	GoalType m_goalType;
	CPathFinder* m_pathFinder;
	CRoom* m_roomArray[MAX_ROOMS];
	Point* m_pPoint;
	CGoal* m_pGoal;
	
	bool m_spoken;
	
	const char* m_string;
	
	int m_goalPosition;
	int m_waitValue;
	int m_waitTime;
};

class CGoalManager
{
public:
	CGoalManager();
	~CGoalManager();
	
	void ClearGoals();
	bool AddGoal(CGoal* pGoal);
	bool InsertGoal(CGoal* pGoal);
	bool RemoveGoal(CGoal* pGoal);
	void ResetGoals();
	
	void SetGoalPosition(int value) { m_goalPosition = value; }
	
	CGoal* CurrentGoal() const { return m_goalArray[m_goalPosition]; }
	void NextGoal();
	
private:

	CGoal* m_goalArray[MAX_GOALS];
	int m_goalPosition;
};

#endif
