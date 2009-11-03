#include "CGoalManager.h"
#include "CPathFinder.h"

CGoalManager::CGoalManager()
{
	m_goalPosition = 0;
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

bool CGoalManager::InsertGoal(CGoal* pGoal)
{
	for(int i=MAX_GOALS - 1; i>=0; i--)
		m_goalArray[i + 1] = m_goalArray[i];
	
	m_goalArray[0] = pGoal;
			
	return true;
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

void CGoalManager::ResetGoals()
{
	for(int i=0; i<MAX_GOALS; i++)
	{
		CGoal* pGoal = m_goalArray[i];
		
		if(pGoal != NULL)
			pGoal->Reset();
	}
}

void CGoalManager::NextGoal()
{
	if(m_goalPosition < MAX_GOALS)
		m_goalPosition++;
		
	CGoal* pGoal = m_goalArray[m_goalPosition];
	
	if(pGoal != NULL)
	{
		if(pGoal->GetGoalType() == GOAL_GOTOGOAL)
		{
			for(int i=0; i<MAX_GOALS; i++)
			{
				if(m_goalArray[i]->Id() == pGoal->GotoId())
				{
					m_goalPosition = i;
					
					ResetGoals();
					
					break;
				}
			}
		}
	}
}
