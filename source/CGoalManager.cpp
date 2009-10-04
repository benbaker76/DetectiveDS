#include "CGoalManager.h"
#include "CPathFinder.h"

CGoalManager::CGoalManager()
{
	ClearGoals();
}

CGoalManager::~CGoalManager()
{
}

void CGoalManager::ClearGoals()
{
	for(int i=0; i<MAX_GOALS; i++)
		m_goalArray[i] = NULL;
}

bool CGoalManager::AddGoal(CGoal* pGoal)
{
	for(int i=0; i<MAX_GOALS; i++)
	{
		if(m_goalArray[i] == NULL)
		{
			m_goalArray[i] = pGoal;
			
			return true;
		}
	}
	
	return false;
}
	
bool CGoalManager::RemoveGoal(CGoal* pGoal)
{
	for(int i=0; i<MAX_GOALS; i++)
	{
		if(m_goalArray[i] == pGoal)
		{	
			for(int j = i; j<MAX_GOALS-1; j++)
				m_goalArray[j] = m_goalArray[j + 1];
			
			m_goalArray[MAX_GOALS-1] = NULL;
			
			return true;
		}
	}
	
	return false;
}
