#include <nds.h>
#include <stdio.h>
#include "CTimer.h"

CTimer::CTimer()
{
	m_pCurrentTime = new CTime(0, 0, 0, 0);
}

CTimer::CTimer(int hours, int minutes, int seconds, int milliSeconds)
{
	m_pCurrentTime = new CTime(hours, minutes, seconds, milliSeconds);
}

CTimer::~CTimer()
{
}

void CTimer::Start()
{
	TIMER2_DATA = (u16) TIMER_FREQ(1000);	
	TIMER2_CR = (TIMER_ENABLE | TIMER_IRQ_REQ | TIMER_DIV_1);
}

void CTimer::Stop()
{
	TIMER2_CR &= ~TIMER_ENABLE;
}

void CTimer::Update()
{
	m_pCurrentTime->MilliSeconds++;
	
	if(m_pCurrentTime->MilliSeconds == 1000)
	{
		m_pCurrentTime->MilliSeconds = 0;
		m_pCurrentTime->Seconds++;
		
		if(m_pCurrentTime->Seconds == 60)
		{		
			m_pCurrentTime->Seconds = 0;
			m_pCurrentTime->Minutes++;
			
			if(m_pCurrentTime->Minutes == 60)
			{
				m_pCurrentTime->Minutes = 0;
				m_pCurrentTime->Hours++;
			}
		}
	}
}
