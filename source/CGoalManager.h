#ifndef __CGOALMANAGER_H__
#define __CGOALMANAGER_H__

#include <stdio.h>
#include "CRoom.h"
#include "CGoal.h"
#include "Text.h"

#define MAX_GOALS		96

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
	void GotoGoal();
	
	int GetGoalPosition() const { return m_goalPosition; }
	void SetGoalPosition(int value) { m_goalPosition = value; }
	
	CGoal* GetGoal(int index) const { return m_goalArray[index]; }
	
	CGoal* CurrentGoal() const { return m_goalArray[m_goalPosition]; }
	void NextGoal();
	
	void Save(CSave* pSave);
	void Load(CSave* pSave);
	
private:

	CGoal* m_goalArray[MAX_GOALS];
	int m_goalPosition;
};

#endif
