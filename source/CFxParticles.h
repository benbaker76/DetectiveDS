#ifndef __CFXPARTICLES_H__
#define __CFXPARTICLES_H__

#include "CFx.h"

#define MAX_PARTICLES	80
#define PARTICLE_START	32

struct Particle
{
	u16* Gfx;
	int X;
	int Y;
	float Angle;
	float Speed;
	int Lifetime;
	int Radius;
	int StartY;
};

class CFxParticles : public CFx
{
public:

	CFxParticles(FxType fxType, CFxManager* fxManager) : CFx(fxType, fxManager)
	{
		for(int i=0; i<MAX_PARTICLES; i++)
			m_particleArray[i].Gfx = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);
	}
	~CFxParticles()
	{
		for(int i=0; i<MAX_PARTICLES; i++)
			oamFreeGfx(&oamSub, m_particleArray[i].Gfx);
	}

	void Initialize();
	void Shutdown();
	void Reset();
	void UpdateVBlank();
	void UpdateHBlank();
	
	void SetXOffset(int xOffset) { m_xOffset = xOffset; }

private:

	Particle m_particleArray[MAX_PARTICLES];
	
	int m_frameCount;
	int m_xOffset;
	
	int m_perspective;
	int m_centreX;
	float m_ratio;
	
	float m_angleSpeed;
	
	bool m_pong;
};

#endif