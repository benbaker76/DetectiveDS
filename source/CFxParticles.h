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
	
	void AllocateGfx();
	void SetXOffset(int xOffset) { m_xOffset = xOffset; }
	void SetPosition(int x, int y) { m_position.X = x; m_position.Y = y; }

private:

	Particle m_particleArray[MAX_PARTICLES];
	
	Point m_position;
	
	int m_frameCount;
	int m_xOffset;
	
	int m_perspective;
	float m_ratio;
	
	float m_angleSpeed;
	
	bool m_pong;
};

#endif