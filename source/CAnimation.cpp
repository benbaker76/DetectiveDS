#include <nds.h>
#include <math.h>
#include "CAnimation.h"

CAnimation::CAnimation(AnimationType animType, int startDelay, int frameRate, int frameTotal)
{
	m_animType = animType;
	m_startDelay = startDelay;
	m_frameRate = frameRate;
	m_frameTotal = frameTotal;
	
	Reset();
}

CAnimation::~CAnimation()
{
}

void CAnimation::Reset()
{
	m_animMode = ANIMMODE_START;
	m_frameNum = 0;
	m_frameCount = 0;
	m_ping = true;
}

bool CAnimation::Update()
{
	m_frameCount++;
	
	if(m_animMode == ANIMMODE_START)
	{
		if(m_frameCount > m_startDelay)
		{
			m_frameCount = 0;
			
			m_animMode = ANIMMODE_RUNNING;
		}
	}
	else
	{
		if(m_frameCount > m_frameRate)
		{
			m_frameCount = 0;
			
			if(m_animState == ANIMSTATE_STOP)
				return false;
			
			switch(m_animType)
			{
				case ANIMTYPE_FORWARD:
					if(++m_frameNum > m_frameTotal-1)
					{
						m_frameNum = 0;
						m_animMode = ANIMMODE_START;
					}
					break;
				case ANIMTYPE_BACKWARD:
					if(--m_frameNum <= 0)
					{
						m_frameNum = m_frameTotal-1;
						m_animMode = ANIMMODE_START;
					}
					break;
				case ANIMTYPE_PINGPONG:
					if(m_ping)
					{
						if(++m_frameNum >= m_frameTotal-1)
							m_ping = !m_ping;
					}
					else
					{
						if(--m_frameNum <= 0)
						{
							m_ping = !m_ping;
							m_animMode = ANIMMODE_START;
						}
					}
					break;
				case ANIMTYPE_RANDOM:
					m_frameNum = rand() % m_frameTotal;
					break;
			}
			
			return true;
		}
	}
	
	return false;
}
