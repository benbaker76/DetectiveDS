#include <nds.h>
#include "Gfx.h"
#include "CFxManager.h"
#include "CFxFade.h"
#include "Text.h"

void CFxFade::Initialize()
{
	m_lightsEnabled = FxManager()->GetFx(FX_LIGHTS)->Enabled();
	
	if(m_lightsEnabled)
		FxManager()->SetFx(FX_LIGHTS, false);
	
	switch(CFx::GetFxType())
	{
	case FX_FADE_BLACK_IN:
		REG_BLDCNT_SUB = BLEND_FADE_BLACK | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE;
		REG_BLDY_SUB = 0;
		REG_BLDALPHA_SUB = 0xF;
		break;
	case FX_FADE_BLACK_OUT:
		REG_BLDCNT_SUB = BLEND_FADE_BLACK | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE;
		REG_BLDY_SUB = 0xF;
		REG_BLDALPHA_SUB = (0xF << 8);
		break;
	case FX_FADE_WHITE_IN:
		REG_BLDCNT_SUB = BLEND_FADE_WHITE | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE;
		REG_BLDY_SUB = 0;
		REG_BLDALPHA_SUB = 0xF;
		break;
	case FX_FADE_WHITE_OUT:
		REG_BLDCNT_SUB = BLEND_FADE_WHITE | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE;
		REG_BLDY_SUB = 0xF;
		REG_BLDALPHA_SUB = (0xF << 8);
		break;
	default:
		break;
	}
	
	m_fadeValue = 0;
}

void CFxFade::Shutdown()
{
	REG_BLDCNT_SUB = 0;
}

void CFxFade::UpdateVBlank()
{
	switch(CFx::GetFxType())
	{
	case FX_FADE_BLACK_IN:
	case FX_FADE_WHITE_IN:
		REG_BLDY_SUB = m_fadeValue;
		REG_BLDALPHA_SUB = 0xF;
		break;
	case FX_FADE_BLACK_OUT:
	case FX_FADE_WHITE_OUT:
		REG_BLDY_SUB = 0xF - m_fadeValue;
		REG_BLDALPHA_SUB = ((0xF - m_fadeValue) << 8) | m_fadeValue;
		break;
	default:
		break;
	}
	
	if(m_fadeValue < 0xF)
		m_fadeValue++;
	else
	{
		SetEnabled(false);
		
		if(m_lightsEnabled)
			FxManager()->SetFx(FX_LIGHTS, true);
			
		return;
	}
}

void CFxFade::UpdateHBlank()
{
}

// ------------------------------------------------

void CFxLights::Initialize()
{
	for(int i=0; i<SCREEN_HEIGHT; i++)
		m_map_light[i] = 16 - (abs(i - 40) * ((32.0f / SCREEN_HEIGHT)));
		
	REG_BLDCNT_SUB = BLEND_FADE_BLACK | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE;
}

void CFxLights::Shutdown()
{
	REG_BLDCNT_SUB = 0;
	dmaTransfer(1, NULL, NULL, 0, 0);
}

void CFxLights::UpdateVBlank()
{
	dmaTransfer(1, &m_map_light[1], (void*) &REG_BLDY_SUB, 1, DMA_ENABLE | DMA_REPEAT | DMA_START_HBL | DMA_DST_RESET);
}

void CFxLights::UpdateHBlank()
{
}
