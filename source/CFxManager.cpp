#include "TDG.h"
#include "Text.h"
#include "CFxFade.h"
#include "CFxTextScroller.h"
#include "CFxParticles.h"
#include "CFxC64.h"

CFxManager::CFxManager()
{
	for(int i=0; i<MAX_FX; i++)
		m_fxArray[i] = NULL;
}

CFxManager::~CFxManager()
{
}

void CFxManager::Initialize()
{
	m_fxArray[FXTYPE_FADE] = new CFxFade(FXTYPE_FADE, this);
	m_fxArray[FXTYPE_FADE_RAMP] = new CFxFadeRamp(FXTYPE_FADE_RAMP, this);
	m_fxArray[FXTYPE_TEXT_SCROLLER] = new CFxTextScroller(FXTYPE_TEXT_SCROLLER, this);
	m_fxArray[FXTYPE_COLOUR] = new CFxColourPulse(FXTYPE_COLOUR, this);
	m_fxArray[FXTYPE_PARTICLES] = new CFxParticles(FXTYPE_PARTICLES, this);
	m_fxArray[FXTYPE_C64] = new CFxC64(FXTYPE_C64, this);
}

void CFxManager::FxOff()
{
	for(int i=0; i<MAX_FX; i++)
		if(m_fxArray[i] != NULL)
			m_fxArray[i]->SetEnabled(m_fxArray[i]->GetFxMode(), false);
}

void CFxManager::UpdateVBlank()
{
	for(int i=0; i<MAX_FX; i++)
		if(m_fxArray[i] != NULL)
			if(m_fxArray[i]->Enabled())
				m_fxArray[i]->UpdateVBlank();
}

void CFxManager::UpdateHBlank()
{
	for(int i=0; i<MAX_FX; i++)
		if(m_fxArray[i] != NULL)
			if(m_fxArray[i]->Enabled())
				m_fxArray[i]->UpdateHBlank();
}
