#ifndef __CEVENT_H__
#define __CEVENT_H__

#include "TDG.h"

#define MAX_EVENTS			32

enum EventType
{
	EVENT_START_GAME,
	EVENT_MURDER_DINGLE,
	EVENT_MURDER_CYNTHIA,
	EVENT_MURDER_DOCTOR,
	EVENT_MURDER_GABRIEL,
	EVENT_GET_SHOT
};

enum EventFlag
{
	EVENTFLAG_NONE = 0,
	EVENTFLAG_GAME_OVER = BIT(0),
	EVENTFLAG_UPSTAIRS = BIT(1),
	EVENTFLAG_DOWNSTAIRS = BIT(2),
	EVENTFLAG_MURDER_DINGLE = BIT(3),
	EVENTFLAG_MURDER_CYNTHIA = BIT(4),
	EVENTFLAG_MURDER_DOCTOR = BIT(5),
	EVENTFLAG_MURDER_GABRIEL = BIT(6),
	EVENTFLAG_PLACE_KNIFE = BIT(7),
	EVENTFLAG_REMOVE_BULLETS = BIT(8)
};

class CEvent
{
public:
	CEvent(EventType eventType, CTime* pEventTime, int condition, int action);
	~CEvent();
	
	bool Update(CTime* pCurrentTime);

	bool Done() const { return m_done; }
	
	int Condition() const { return m_condition; }
	int Action() const { return m_action; }
	
	EventType GetEventType() const { return m_eventType; }
	
	void SetDone(bool value) { m_done = value; }

private:
	EventType m_eventType;
	CTime* m_pEventTime;
	
	int m_condition;
	int m_action;
	
	bool m_done;
};

#endif
