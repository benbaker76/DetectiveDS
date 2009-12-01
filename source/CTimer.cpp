#include <nds.h>
#include <stdio.h>
#include "CTimer.h"
#include "CSave.h"

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

void CTimer::Start(int hours, int minutes, int seconds, int milliSeconds)
{
	m_pCurrentTime->Hours = hours;
	m_pCurrentTime->Minutes = minutes;
	m_pCurrentTime->Seconds = seconds;
	m_pCurrentTime->MilliSeconds = milliSeconds;
	
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
	
	if(m_pCurrentTime->MilliSeconds >= 1000)
	{
		m_pCurrentTime->MilliSeconds = 0;
		m_pCurrentTime->Seconds++;
		
		if(m_pCurrentTime->Seconds >= 60)
		{		
			m_pCurrentTime->Seconds = 0;
			m_pCurrentTime->Minutes++;
			
			if(m_pCurrentTime->Minutes >= 60)
			{
				m_pCurrentTime->Minutes = 0;
				m_pCurrentTime->Hours++;
			}
		}
	}
}

void CTimer::Reverse()
{
	m_pCurrentTime->MilliSeconds = 0;
	
	m_pCurrentTime->Seconds -= 5;
	
	if(m_pCurrentTime->Seconds < 0)
	{		
		m_pCurrentTime->Seconds = 59;
		m_pCurrentTime->Minutes--;
		
		if(m_pCurrentTime->Minutes < 0)
		{
			m_pCurrentTime->Minutes = 59;
			m_pCurrentTime->Hours--;
		}
	}
}

void CTimer::ToString()
{
	static char buf[256];
	
	sprintf(buf, "%02d:%02d:%02d:%02d", m_pCurrentTime->Hours, m_pCurrentTime->Minutes, m_pCurrentTime->Seconds, m_pCurrentTime->MilliSeconds);
	fprintf(stderr, buf);
}

void CTimer::Save(CSave* pSave)
{
	pSave->WriteUInt32(m_pCurrentTime->Hours);
	pSave->WriteUInt32(m_pCurrentTime->Minutes);
	pSave->WriteUInt32(m_pCurrentTime->Seconds);
	pSave->WriteUInt32(m_pCurrentTime->MilliSeconds);
}

void CTimer::Load(CSave* pSave)
{
	pSave->ReadUInt32((u32*)&m_pCurrentTime->Hours);
	pSave->ReadUInt32((u32*)&m_pCurrentTime->Minutes);
	pSave->ReadUInt32((u32*)&m_pCurrentTime->Seconds);
	pSave->ReadUInt32((u32*)&m_pCurrentTime->MilliSeconds);
}


