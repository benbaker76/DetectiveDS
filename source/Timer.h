#ifndef __CTIMER_H__
#define __CTIMER_H__

#include <nds.h>

class CTime
{
public:
	CTime(int hours, int minutes, int seconds, int milliSeconds)
	{
		Hours = hours;
		Minutes = minutes;
		Seconds = seconds;
		MilliSeconds = milliSeconds;
	};
	
	int Hours;
	int Minutes;
	int Seconds;
	int MilliSeconds;
};

class CTimer
{
public:
	CTimer();
	~CTimer();
	
	void Start();
	void Stop();
	void Update();

	CTime* pCurrentTime() const { return m_pCurrentTime; }
	
private:
	CTime* m_pCurrentTime;
};

#endif
