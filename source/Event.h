#ifndef __CEVENT_H__
#define __CEVENT_H__

#include "TDG.h"

#define MAX_EVENTS			32

enum EventType
{
	EVENT_SHOW_ROOM,
	EVENT_GET_SHOT
};

class CEvent
{
public:
	CEvent(EventType eventType, CTime* pEventTime);
	~CEvent();
	
	bool Update(CTime* pCurrentTime);

private:
	EventType m_eventType;
	CTime* m_pEventTime;
};

#endif
