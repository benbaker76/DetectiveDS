#ifndef __CTIMER_H__
#define __CTIMER_H__

#include <nds.h>

class CSave;

class CTime
{
public:
	CTime() : Hours(0), Minutes(0), Seconds(0), MilliSeconds(0) {}
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
	
	void Save(CSave* pSave);
	void Load(CSave* pSave);
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
	void SetTime(CTime* time) { m_pCurrentTime->Hours = time->Hours; m_pCurrentTime->Minutes = time->Minutes; m_pCurrentTime->Seconds = time->Seconds; m_pCurrentTime->MilliSeconds = time->MilliSeconds; }
	
	void ToString();
	
	void Save(CSave* pSave);
	void Load(CSave* pSave);
	
private:
	CTime* m_pCurrentTime;
};

#endif
