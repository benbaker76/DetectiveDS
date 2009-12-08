#include <stdio.h>
#include "CEvent.h"
#include "CSave.h"

CEvent::CEvent(EventType eventType, CTime* pEventTime, uint64 condition, uint64 action)
{
	m_eventType = eventType;
	m_pEventTime = pEventTime;
	m_condition = condition;
	m_action = action;
	
	m_done = false;
}

CEvent::~CEvent()
{
}

bool CEvent::Update(CTime* pCurrentTime)
{
	if(pCurrentTime->Hours >= m_pEventTime->Hours &&
		pCurrentTime->Minutes >= m_pEventTime->Minutes &&
		pCurrentTime->Seconds >= m_pEventTime->Seconds &&
		pCurrentTime->MilliSeconds >= m_pEventTime->MilliSeconds)
	{
		return true;
	}
	
	return false;
}

void CEvent::Save(CSave* pSave)
{
	m_pEventTime->Save(pSave);
	
	pSave->WriteBool(m_done);
}

void CEvent::Load(CSave* pSave)
{
	m_pEventTime->Load(pSave);
	
	pSave->ReadBool(&m_done);
}

