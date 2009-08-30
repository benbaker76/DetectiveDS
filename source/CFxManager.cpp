#include "TDG.h"
#include "Text.h"
#include "CFxFade.h"

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
	m_fxArray[FX_FADE_BLACK_IN] = new CFxFade(FX_FADE_BLACK_IN, this);
	m_fxArray[FX_FADE_BLACK_OUT] = new CFxFade(FX_FADE_BLACK_OUT, this);
	m_fxArray[FX_FADE_WHITE_IN] = new CFxFade(FX_FADE_WHITE_IN, this);
	m_fxArray[FX_FADE_WHITE_OUT] = new CFxFade(FX_FADE_WHITE_OUT, this);
	m_fxArray[FX_LIGHTS_BLACK] = new CFxLights(FX_LIGHTS_BLACK, this);
	m_fxArray[FX_LIGHTS_BLACK_IN] = new CFxLights(FX_LIGHTS_BLACK_IN, this);
	m_fxArray[FX_LIGHTS_BLACK_OUT] = new CFxLights(FX_LIGHTS_BLACK_OUT, this);
	m_fxArray[FX_LIGHTS_WHITE] = new CFxLights(FX_LIGHTS_WHITE, this);
	m_fxArray[FX_LIGHTS_WHITE_IN] = new CFxLights(FX_LIGHTS_WHITE_IN, this);
	m_fxArray[FX_LIGHTS_WHITE_OUT] = new CFxLights(FX_LIGHTS_WHITE_OUT, this);
}

void CFxManager::FxOff()
{
		for(int i=0; i<MAX_FX; i++)
		if(m_fxArray[i] != NULL)
			m_fxArray[i]->SetEnabled(false);
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
