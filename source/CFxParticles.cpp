#include <nds.h>
#include <math.h>
#include "TDG.h"
#include "Gfx.h"
#include "CFxManager.h"
#include "CFxParticles.h"
#include "Text.h"

void CFxParticles::Initialize()
{
	m_frameCount = 0;
	m_xOffset = 0;
	m_perspective = 300;
	m_position.X = 0;
	m_position.Y = 0;
	m_ratio = 0;
	m_angleSpeed = PI / 24;
	
	m_pong = true;
	
	switch(CFx::GetFxMode())
	{
	case FXMODE_RAIN:
		for(int i=0; i<MAX_PARTICLES; i++)
			dmaCopy(sprite_fx_rainTiles, m_particleArray[i].Gfx,  16 * 16);
		break;
	case FXMODE_SKULL:
		for(int i=0; i<MAX_PARTICLES; i++)
			dmaCopy(sprite_fx_skullTiles, m_particleArray[i].Gfx,  16 * 16);
		break;
	case FXMODE_HOURGLASS:
		for(int i=0; i<MAX_PARTICLES; i++)
			dmaCopy(sprite_fx_hourglassTiles, m_particleArray[i].Gfx,  16 * 16);
		break;
	default:
		break;
	}
	
	Reset();
}

void CFxParticles::Shutdown()
{
	for(int i=0; i<MAX_PARTICLES; i++)
		oamSet(&oamSub, PARTICLE_START + i, 0, 0, 0, 0, SpriteSize_16x16, SpriteColorFormat_256Color, m_particleArray[i].Gfx, -1, false, true, false, false, false);
}

void CFxParticles::Reset()
{
	switch(CFx::GetFxMode())
	{
	case FXMODE_RAIN:
		for(int i=0; i<MAX_PARTICLES; i++)
		{
			m_particleArray[i].X = rand() % 256;
			m_particleArray[i].Y = rand() % 192;
			m_particleArray[i].Speed = (rand() % 4) + 2;
			m_particleArray[i].Lifetime = 0;
			
			oamSet(&oamSub, PARTICLE_START + i, 0, 0, 1, 0, SpriteSize_16x16, SpriteColorFormat_256Color, m_particleArray[i].Gfx, -1, false, true, false, false, false);
		}
		break;
	case FXMODE_SKULL:
	case FXMODE_HOURGLASS:
		for(int i=0; i<MAX_PARTICLES; i++)
		{
			m_particleArray[i].StartY = rand() % 96;
			m_particleArray[i].Angle = rand() % 360;
			m_particleArray[i].Radius = (int) (m_particleArray[i].StartY / 2);
			m_particleArray[i].Lifetime = 0;
			
			oamSet(&oamSub, PARTICLE_START + i, 0, 0, 1, 0, SpriteSize_16x16, SpriteColorFormat_256Color, m_particleArray[i].Gfx, -1, false, true, false, false, false);
		}
		break;
	default:
		break;
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
						dmaCopy(sprite_fx_rainTiles + (m_particleArray[i].Lifetime * 64), m_particleArray[i].Gfx, 16 * 16);
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
							
							dmaCopy(sprite_fx_rainTiles, m_particleArray[i].Gfx, 16 * 16);
						}
						else
						{
							dmaCopy(sprite_fx_rainTiles + (m_particleArray[i].Lifetime * 64), m_particleArray[i].Gfx, 16 * 16);
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
			
			oamSet(&oamSub, PARTICLE_START + i, (m_particleArray[i].X - m_xOffset) & 0xFF, m_particleArray[i].Y, 1, 0, SpriteSize_16x16, SpriteColorFormat_256Color, m_particleArray[i].Gfx, -1, false, false, false, false, false);
		}
		break;
	case FXMODE_SKULL:
	case FXMODE_HOURGLASS:
		for(int i=0; i<32; i++)
		{
			m_particleArray[i].Angle += m_angleSpeed;

			if (m_pong)
			{
				if (m_ratio < 1)
					m_ratio += 0.0001F;
				else
					m_pong = false;
			}
			else
			{
				if (m_ratio > 0)
					m_ratio -= 0.0001F;
				else
				{
					SetEnabled(CFx::GetFxMode(), false);
					break;
				}
				//else
				//	m_pong = true;
			}

			float a = (float) sin(m_particleArray[i].Angle) * m_particleArray[i].Radius;
			float b = (float) cos(m_particleArray[i].Angle) * m_particleArray[i].Radius;
			float scalar = m_perspective / (b + m_perspective);
			
			m_particleArray[i].X = (int) (m_ratio * a * scalar + m_position.X);
			m_particleArray[i].Y = (int) (m_position.Y - (m_ratio * (b * scalar / 4 + m_particleArray[i].StartY)));
			
			if(CFx::GetFxMode() == FXMODE_SKULL)
				m_particleArray[i].Lifetime = (int) (m_pong ? m_ratio * 7 : ((1 - m_ratio) * 7) + 8);
			else
				m_particleArray[i].Lifetime = (int) (m_ratio * 7);
			
			dmaCopy((CFx::GetFxMode() == FXMODE_SKULL ? sprite_fx_skullTiles : sprite_fx_hourglassTiles) + (m_particleArray[i].Lifetime * 64), m_particleArray[i].Gfx, 16 * 16);
			
			oamSet(&oamSub, PARTICLE_START + i, (m_particleArray[i].X - m_xOffset), m_particleArray[i].Y, 0, 0, SpriteSize_16x16, SpriteColorFormat_256Color, m_particleArray[i].Gfx, -1, false, false, false, false, false);
		}
		break;
	default:
		break;
	}
}

void CFxParticles::UpdateHBlank()
{
}

void CFxParticles::AllocateGfx()
{
	for(int i=0; i<MAX_PARTICLES; i++)
		m_particleArray[i].Gfx = oamAllocateGfx(&oamSub, SpriteSize_16x16, SpriteColorFormat_256Color);
}

