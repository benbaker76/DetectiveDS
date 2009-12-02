#include <nds.h>
#include <math.h>
#include "CAnimation.h"
#include "CSave.h"

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
	m_animState = (m_animType == ANIMTYPE_MANUAL ? ANIMSTATE_STOP : ANIMSTATE_PLAY);
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
				case ANIMTYPE_MANUAL:
					break;
			}
			
			return true;
		}
	}
	
	return false;
}

void CAnimation::Save(CSave* pSave)
{
	pSave->WriteByte(m_animType);
	pSave->WriteByte(m_animState);
	pSave->WriteByte(m_animMode);
	
	pSave->WriteUInt32(m_startDelay);
	pSave->WriteUInt32(m_frameNum);
	pSave->WriteUInt32(m_frameCount);
	pSave->WriteUInt32(m_frameTotal);
	pSave->WriteUInt32(m_frameRate);
	
	pSave->WriteBool(m_ping);
}

void CAnimation::Load(CSave* pSave)
{
	pSave->ReadByte((byte*)&m_animType);
	pSave->ReadByte((byte*)&m_animState);
	pSave->ReadByte((byte*)&m_animMode);
	
	pSave->ReadUInt32((u32*)&m_startDelay);
	pSave->ReadUInt32((u32*)&m_frameNum);
	pSave->ReadUInt32((u32*)&m_frameCount);
	pSave->ReadUInt32((u32*)&m_frameTotal);
	pSave->ReadUInt32((u32*)&m_frameRate);
	
	pSave->ReadBool(&m_ping);
}
