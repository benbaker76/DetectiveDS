#include <nds.h>
#include <math.h>
#include "TDG.h"
#include "Gfx.h"
#include "CFxManager.h"
#include "CFxParticles.h"
#include "Text.h"

void CFxParticles::Initialize()
{
	switch(CFx::GetFxMode())
	{
	case FXMODE_RAIN:
		for(int i=0; i<MAX_PARTICLES; i++)
			dmaCopy(sprite_fx_rainTiles, m_particleArray[i].Gfx,  8 * 8 * 2);
		break;
	default:
		break;
	}
	
	Reset();
}

void CFxParticles::Shutdown()
{
	for(int i=0; i<MAX_PARTICLES; i++)
		oamSet(&oamSub, PARTICLE_START + i, 0, 0, 0, 0, SpriteSize_8x8, SpriteColorFormat_256Color, m_particleArray[i].Gfx, 0, false, true, false, false, false);
}

void CFxParticles::Reset()
{
	for(int i=0; i<MAX_PARTICLES; i++)
	{
		m_particleArray[i].X = rand() % 256;
		m_particleArray[i].Y = rand() % 192;
		m_particleArray[i].Speed = (rand() % 4) + 2;
	}
}

void CFxParticles::UpdateVBlank()
{
	switch(CFx::GetFxMode())
	{
	case FXMODE_RAIN:
		for(int i=0; i<MAX_PARTICLES; i++)
		{
			if(m_particleArray[i].Y > 144)
			{
				if(m_particleArray[i].Lifetime == 0)
				{
					int num = rand() % 10;
					
					if(num == 0)
					{
						m_particleArray[i].Lifetime++;
						dmaCopy(sprite_fx_rainTiles + (m_particleArray[i].Lifetime * 16), m_particleArray[i].Gfx, 8 * 8 * 2);
					}
					else
					{
						m_particleArray[i].X -= m_particleArray[i].Speed;
						m_particleArray[i].Y += m_particleArray[i].Speed;
					}
				}
				else
				{
					m_frameCount++;
					
					if(m_frameCount > 3)
					{
						m_frameCount = 0;
						
						m_particleArray[i].Lifetime++;
						
						if(m_particleArray[i].Lifetime == 5)
						{
							m_particleArray[i].X = rand() % 256;
							m_particleArray[i].Y = rand() % 192;
							m_particleArray[i].Speed = (rand() % 4) + 2;
							m_particleArray[i].Lifetime = 0;
							
							dmaCopy(sprite_fx_rainTiles, m_particleArray[i].Gfx, 8 * 8 * 2);
						}
						else
						{
							dmaCopy(sprite_fx_rainTiles + (m_particleArray[i].Lifetime * 16), m_particleArray[i].Gfx, 8 * 8 * 2);
						}
					}
				}
			}
			else
			{
				m_particleArray[i].X -= m_particleArray[i].Speed;
				m_particleArray[i].Y += m_particleArray[i].Speed;
			}
			
			if(m_particleArray[i].X < 0)
				m_particleArray[i].X = 256;
				
			if(m_particleArray[i].Y > 192)
				m_particleArray[i].Y = 0;
			
			oamSet(&oamSub, PARTICLE_START + i, (m_xOffset + m_particleArray[i].X) & 0xFF, m_particleArray[i].Y, 1, 0, SpriteSize_8x8, SpriteColorFormat_256Color, m_particleArray[i].Gfx, 0, false, false, false, false, false);
		}
		break;
	default:
		break;
	}
}

void CFxParticles::UpdateHBlank()
{
}
