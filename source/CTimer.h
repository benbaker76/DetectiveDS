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
	CTimer(int hours, int minutes, int seconds, int milliSeconds);
	~CTimer();
	
	void Start();
	void Start(int hours, int minutes, int seconds, int milliSeconds);
	void Stop();
	void Update();
	void Reverse();

	CTime* pCurrentTime() const { return m_pCurrentTime; }
	
	void ToString();
	
private:
	CTime* m_pCurrentTime;
};

#endif
