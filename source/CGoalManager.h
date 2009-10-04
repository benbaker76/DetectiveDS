#ifndef __CGOALMANAGER_H__
#define __CGOALMANAGER_H__

#include "CRoom.h"
#include "CPathFinder.h"

#define MAX_GOALS		32
#define MAX_POINTS		8

enum GoalType
{
	GOAL_GOTOROOM,
	GOAL_GOTOPOINT
};

class CPathFinder;

class CGoal
{
public:
	CGoal(GoalType goalType, CRoom* pRoomStart, CRoom* pRoomEnd)
	{
		m_goalType = goalType;
		m_goalPosition = 0;
		
		m_pathFinder = new CPathFinder();
		m_pathFinder->FindRoute(pRoomStart, pRoomEnd);
		
		for(int i=1; i<MAX_ROOMS; i++)
			m_roomArray[i - 1] = m_pathFinder->GetRoom(i);
	}
	
	CGoal(GoalType goalType, Point* pPoint[MAX_POINTS])
	{
		m_goalType = goalType;
		m_goalPosition = 0;
		
		for(int i=0; i<MAX_POINTS; i++)
			m_pointArray[i] = pPoint[i];
	}
	
	GoalType GetGoalType() const { return m_goalType; }
	
	CRoom* pRoom() const { return m_roomArray[m_goalPosition]; }
	Point* pPoint() const { return m_pointArray[m_goalPosition]; }
	
	bool NextRoom() { return (m_roomArray[++m_goalPosition] != NULL); }
	bool NextPoint() { return (m_pointArray[++m_goalPosition] != NULL); }

private:

	GoalType m_goalType;
	CPathFinder* m_pathFinder;
	CRoom* m_roomArray[MAX_ROOMS];
	Point* m_pointArray[MAX_POINTS];
	
	int m_goalPosition;
};

class CGoalManager
{
public:
	CGoalManager();
	~CGoalManager();
	
	void ClearGoals();
	bool AddGoal(CGoal* pGoal);
	bool RemoveGoal(CGoal* pGoal);
	
	CGoal* CurrentGoal() const { return m_goalArray[0]; }
	void NextGoal() { RemoveGoal(m_goalArray[0]); }
	
private:

	CGoal* m_goalArray[MAX_GOALS];
};

#endif
