#ifndef __CFXPARTICLES_H__
#define __CFXPARTICLES_H__

#include "CFx.h"

#define MAX_PARTICLES	80
#define PARTICLE_START	32

typedef struct
{
	u16* Gfx;
	int X;
	int Y;
	int Speed;
	int Lifetime;
} PARTICLE, *PPARTICLE;

class CFxParticles : public CFx
{
public:

	CFxParticles(FxType fxType, CFxManager* fxManager) : CFx(fxType, fxManager)
	{
		for(int i=0; i<MAX_PARTICLES; i++)
			m_particleArray[i].Gfx = oamAllocateGfx(&oamSub, SpriteSize_8x8, SpriteColorFormat_256Color);
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

	PARTICLE m_particleArray[MAX_PARTICLES];
	
	int m_frameCount;
	int m_xOffset;
};

#endif