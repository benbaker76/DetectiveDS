#include <stdio.h>
#include "Event.h"

CEvent::CEvent(EventType eventType, CTime* pEventTime)
{
	m_eventType = eventType;
	m_pEventTime = pEventTime;
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
		return true;
		
	return false;
}
