#ifndef __CGOAL_H__
#define __CGOAL_H__

#include <stdio.h>
#include "CPathFinder.h"
#include "Text.h"

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
	GOAL_WAITEVENT,
	GOAL_SETEVENT,
	GOAL_LOCKDOOR,
	GOAL_STOP
};

class CCharacter;
class CSave;

class CGoal
{
public:

	CGoal(int id, GoalType goalType, int waitTime);
	CGoal(int id, GoalType goalType, CCharacter* character, int waitTime);
	CGoal(int id, GoalType goalType, uint64 eventFlags, int waitTime);
	CGoal(int id, GoalType goalType, uint64 eventFlags, int waitTime, int timeOut);
	CGoal(int id, GoalType goalType, int gotoId, uint64 eventFlags, int waitTime, int loopCount);
	CGoal(int id, GoalType goalType, const char* string, int waitTime);
	CGoal(int id, GoalType goalType, const char* string, uint64 eventFlags,int waitTime);
	CGoal(int id, GoalType goalType, CRoom* pRoomEnd, int waitTime);
	CGoal(int id, GoalType goalType, CRoom* pRoomStart, CRoom* pRoomEnd, int waitTime);
	CGoal(int id, GoalType goalType, CRoom* pRoomStart, CRoom* pRoomEnd, int gotoId, int waitTime);
	CGoal(int id, GoalType goalType, CRoom* pRoom);
	CGoal(int id, GoalType goalType, Point* pPoint, int waitTime);
	CGoal(int id, GoalType goalType, Point* pPoint);
	void Reset();
	void CalculateCharacterPath(CRoom* pRoomStart);
	void CalculateRoomPath(CRoom* pRoomEnd);

	GoalType GetGoalType() const { return m_goalType; }
	
	CRoom* pRoom() const { return m_roomArray[m_goalPosition]; }
	Point* pPoint() const { return m_pPoint; }
	int Id() const { return m_id; }
	int GotoId() const { return m_gotoId; }
	bool PathFound() const { return m_pathFound; }
	bool Waiting() { return (m_waitValue++ < m_waitTime); }
	bool TimeOut() { return (m_timeValue++ < m_timeOut); }
	bool TryGetSpeech(const char** string) { if(!m_spoken) { *string = m_string; m_spoken = true; return true; } else return false; }
	
	bool NextRoom() { return (m_roomArray[(m_goalPosition < MAX_ROOMS ? ++m_goalPosition : m_goalPosition)] != NULL); }
	bool Loop() { return (m_loopCount == -1  || m_loopValue++ < m_loopCount); }
	//bool Loop() { static char buf[256]; sprintf(buf, "%d:%d", m_loopValue, m_loopCount); fprintf(stderr, buf); return (m_loopCount == -1  || m_loopValue++ < m_loopCount); }
	
	void PrintRooms() { for(int i=0; i<MAX_ROOMS; i++) if(m_roomArray[i] != NULL) fprintf(stderr, g_roomName[m_roomArray[i]->GetRoomType()]); }
	
	bool GetGoalPosition() const { return m_goalPosition; }
	void SetGoalPosition(int goalPosition) { m_goalPosition = goalPosition; }
	
	CCharacter* pCharacter() const { return m_character; }
	
	CRoom* pRoomEnd() const { return m_roomEnd; }
	
	int GetLoopValue() const { return m_loopValue; }
	void SetLoopValue(int loopValue) { m_loopValue = loopValue; }
	
	uint64 EventFlags() const { return m_eventFlags; }
	
	void Save(CSave* pSave);
	void Load(CSave* pSave);

private:
	
	int m_id;
	GoalType m_goalType;
	CRoom* m_roomArray[MAX_ROOMS];
	CCharacter* m_character;
	CRoom* m_roomEnd;
	Point* m_pPoint;
	int m_gotoId;
	
	bool m_spoken;
	bool m_pathFound;
	
	const char* m_string;
	
	int m_goalPosition;
	
	int m_waitValue;
	int m_waitTime;
	
	int m_timeOut;
	int m_timeValue;
	
	int m_loopValue;
	int m_loopCount;
	
	uint64 m_eventFlags;
	
	void CalculatePath(CRoom* pRoomStart, CRoom* pRoomEnd);
};

#endif
