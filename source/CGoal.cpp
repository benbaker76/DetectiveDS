#include "CGoal.h"
#include "CCharacter.h"
#include "CSave.h"

CGoal::CGoal(int id, GoalType goalType, int waitTime)
{
	m_id = id;
	m_goalType = goalType;
	m_string = NULL;
	m_goalPosition = 0;
	m_waitValue = 0;
	m_character = NULL;
	m_roomEnd = NULL;
	m_pPoint = NULL;
	m_waitTime = waitTime;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
	
	for(int i=0; i<MAX_ROOMS; i++)
		m_roomArray[i] = NULL;
}

CGoal::CGoal(int id, GoalType goalType, CCharacter* character, int waitTime)
{
	m_id = id;
	m_goalType = goalType;
	m_string = NULL;
	m_goalPosition = 0;
	m_waitValue = 0;
	m_character = character;
	m_roomEnd = NULL;
	m_pPoint = NULL;
	m_waitTime = waitTime;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
	
	for(int i=0; i<MAX_ROOMS; i++)
		m_roomArray[i] = NULL;
}

CGoal::CGoal(int id, GoalType goalType, uint64 eventFlags, int waitTime)
{
	m_id = id;
	m_goalType = goalType;
	m_string = NULL;
	m_goalPosition = 0;
	m_waitValue = 0;
	m_eventFlags = eventFlags;
	m_character = NULL;
	m_roomEnd = NULL;
	m_pPoint = NULL;
	m_waitTime = waitTime;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
	
	for(int i=0; i<MAX_ROOMS; i++)
		m_roomArray[i] = NULL;
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
	m_character = NULL;
	m_roomEnd = NULL;
	m_pPoint = NULL;
	m_timeOut = timeOut;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
	
	for(int i=0; i<MAX_ROOMS; i++)
		m_roomArray[i] = NULL;
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
	m_character = NULL;
	m_roomEnd = NULL;
	m_pPoint = NULL;
	m_loopCount = loopCount;
	m_timeValue = 0;
	m_loopValue = 0;
	m_pathFound = false;
	
	for(int i=0; i<MAX_ROOMS; i++)
		m_roomArray[i] = NULL;
}

CGoal::CGoal(int id, GoalType goalType, const char* string, int waitTime)
{
	m_id = id;
	m_goalType = goalType;
	m_string = string;
	m_eventFlags = 0;
	m_goalPosition = 0;
	m_waitTime = waitTime;
	m_character = NULL;
	m_roomEnd = NULL;
	m_pPoint = NULL;
	m_waitValue = 0;
	m_spoken = false;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
	
	for(int i=0; i<MAX_ROOMS; i++)
		m_roomArray[i] = NULL;
}

CGoal::CGoal(int id, GoalType goalType, const char* string, uint64 eventFlags, int waitTime)
{
	m_id = id;
	m_goalType = goalType;
	m_string = string;
	m_eventFlags = eventFlags;
	m_goalPosition = 0;
	m_waitTime = waitTime;
	m_character = NULL;
	m_roomEnd = NULL;
	m_pPoint = NULL;
	m_waitValue = 0;
	m_spoken = false;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
	
	for(int i=0; i<MAX_ROOMS; i++)
		m_roomArray[i] = NULL;
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
	m_character = NULL;
	m_pPoint = NULL;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
	
	for(int i=0; i<MAX_ROOMS; i++)
		m_roomArray[i] = NULL;
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
	m_character = NULL;
	m_pPoint = NULL;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
	
	for(int i=0; i<MAX_ROOMS; i++)
		m_roomArray[i] = NULL;
	
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
	m_character = NULL;
	m_pPoint = NULL;
	m_timeValue = 0;
	m_loopValue = 0;
	m_pathFound = false;
	
	for(int i=0; i<MAX_ROOMS; i++)
		m_roomArray[i] = NULL;
	
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
	m_character = NULL;
	m_roomEnd = NULL;
	m_pPoint = NULL;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
	
	for(int i=0; i<MAX_ROOMS; i++)
		m_roomArray[i] = NULL;

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
	m_character = NULL;
	m_roomEnd = NULL;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
	
	for(int i=0; i<MAX_ROOMS; i++)
		m_roomArray[i] = NULL;
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
	m_character = NULL;
	m_roomEnd = NULL;
	m_timeValue = 0;
	m_loopValue = 0;
	m_gotoId = 0;
	m_pathFound = false;
	
	for(int i=0; i<MAX_ROOMS; i++)
		m_roomArray[i] = NULL;
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

void CGoal::Save(CSave* pSave)
{
	pSave->WriteUInt32(m_id);
	pSave->WriteByte(m_goalType);
	
	for(int i=0; i<MAX_ROOMS; i++)
		pSave->WriteRoom(m_roomArray[i]);
	
	pSave->WriteCharacter(m_character);
	pSave->WriteRoom(m_roomEnd);
	pSave->WritePoint(m_pPoint);
	pSave->WriteUInt32(m_gotoId);
	
	pSave->WriteBool(m_spoken);
	pSave->WriteBool(m_pathFound);
	
	//pSave->WriteUInt32((u32)m_string);

	pSave->WriteUInt32(m_goalPosition);
	
	pSave->WriteUInt32(m_waitValue);
	pSave->WriteUInt32(m_waitTime);
	
	pSave->WriteUInt32(m_timeOut);
	pSave->WriteUInt32(m_timeValue);
	
	pSave->WriteUInt32(m_loopValue);
	pSave->WriteUInt32(m_loopCount);
	
	pSave->WriteUInt64(m_eventFlags);
}

void CGoal::Load(CSave* pSave)
{
	pSave->ReadUInt32((u32*)&m_id);
	pSave->ReadByte((byte*)&m_goalType);
	
	for(int i=0; i<MAX_ROOMS; i++)
		pSave->ReadRoom(&m_roomArray[i]);
	
	pSave->ReadCharacter(&m_character);
	pSave->ReadRoom(&m_roomEnd);
	pSave->ReadPoint(m_pPoint);
	pSave->ReadUInt32((u32*)&m_gotoId);
	
	pSave->ReadBool(&m_spoken);
	pSave->ReadBool(&m_pathFound);
	
	//pSave->ReadUInt32((u32*)m_string);

	pSave->ReadUInt32((u32*)&m_goalPosition);
	
	pSave->ReadUInt32((u32*)&m_waitValue);
	pSave->ReadUInt32((u32*)&m_waitTime);
	
	pSave->ReadUInt32((u32*)&m_timeOut);
	pSave->ReadUInt32((u32*)&m_timeValue);
	
	pSave->ReadUInt32((u32*)&m_loopValue);
	pSave->ReadUInt32((u32*)&m_loopCount);
	
	pSave->ReadUInt64((u64*)&m_eventFlags);
}


