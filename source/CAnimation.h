#ifndef __CANIMATION_H__
#define __CANIMATION_H__

enum AnimationType
{
	ANIMTYPE_FORWARD,
	ANIMTYPE_BACKWARD,
	ANIMTYPE_PINGPONG,
	ANIMTYPE_RANDOM,
	ANIMTYPE_MANUAL
};

enum AnimationState
{
	ANIMSTATE_PLAY,
	ANIMSTATE_STOP
};

enum AnimationMode
{
	ANIMMODE_START,
	ANIMMODE_RUNNING
};

class CAnimation
{
public:
	CAnimation(AnimationType animType, int startDelay, int frameRate, int frameTotal);
	~CAnimation();
	
	void Reset();
	bool Update();
	
	void SetType(AnimationType type) { m_animType = type; }
	void SetState(AnimationState state) { m_animState = state; }
	AnimationState GetState() const { return m_animState; }
	void SetFrame(int frameNum) { m_frameNum = frameNum; }
	int FrameNum() const { return m_frameNum; }

private:

	AnimationType m_animType;
	AnimationState m_animState;
	AnimationMode m_animMode;
	
	int m_startDelay;
	int m_frameNum;
	int m_frameCount;
	int m_frameTotal;
	int m_frameRate;
	
	bool m_ping;

};

#endif