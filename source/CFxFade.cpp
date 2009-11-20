#include <nds.h>
#include <math.h>
#include "TDG.h"
#include "Gfx.h"
#include "CFxManager.h"
#include "CFxFade.h"
#include "Text.h"

void CFxFade::Initialize()
{
	//m_lightsEnabled = FxManager()->GetFx(FX_LIGHTS)->Enabled();
	
	//if(m_lightsEnabled)
	//	FxManager()->SetFx(FX_LIGHTS, false);
	
	m_fadeValue = 0;
	
	if(m_callback != NULL)
	{
		delete m_callback;
		m_callback = NULL;
	}
	
	int bgSrc = (m_bgSrc & BG0 ? BLEND_SRC_BG0 : 0) | (m_bgSrc & BG1 ? BLEND_SRC_BG1 : 0) | (m_bgSrc & BG2 ? BLEND_SRC_BG2 : 0) | (m_bgSrc & BG3 ? BLEND_SRC_BG3 : 0) | (m_bgSrc & SPRITE ? BLEND_SRC_SPRITE : 0);
	int bgDst = (m_bgDst & BG0 ? BLEND_DST_BG0 : 0) | (m_bgDst & BG1 ? BLEND_DST_BG1 : 0) | (m_bgDst & BG2 ? BLEND_DST_BG2 : 0) | (m_bgDst & BG3 ? BLEND_DST_BG3 : 0) | (m_bgDst & SPRITE ? BLEND_DST_SPRITE : 0);

	int bgSrcSub = (m_bgSrc & BG0_SUB ? BLEND_SRC_BG0 : 0) | (m_bgSrc & BG1_SUB ? BLEND_SRC_BG1 : 0) |  (m_bgSrc & BG2_SUB ? BLEND_SRC_BG2 : 0) | (m_bgSrc & BG3_SUB ? BLEND_SRC_BG3 : 0) | (m_bgSrc & SPRITE_SUB ? BLEND_SRC_SPRITE : 0);	
	int bgDstSub = (m_bgDst & BG0_SUB ? BLEND_DST_BG0 : 0) |  (m_bgDst & BG1_SUB ? BLEND_DST_BG1 : 0) | (m_bgDst & BG2_SUB ? BLEND_DST_BG2 : 0) | (m_bgDst & BG3_SUB ? BLEND_DST_BG3 : 0) | (m_bgDst & SPRITE_SUB ? BLEND_DST_SPRITE : 0);

	REG_BLDCNT = bgSrc | bgDst;
	REG_BLDCNT_SUB = bgSrcSub | bgDstSub;
	
	switch(CFx::GetFxMode())
	{
	case FXMODE_BLACK_IN:
		REG_BLDCNT |= BLEND_FADE_BLACK;
		REG_BLDCNT_SUB |= BLEND_FADE_BLACK;
		
		REG_BLDY = 0;
		REG_BLDY_SUB = 0;
		break;
	case FXMODE_BLACK_OUT:
		REG_BLDCNT |= BLEND_FADE_BLACK;
		REG_BLDCNT_SUB |= BLEND_FADE_BLACK;
		
		REG_BLDY = 17;
		REG_BLDY_SUB = 17;
		break;
	case FXMODE_WHITE_IN:
		REG_BLDCNT |= BLEND_FADE_WHITE;
		REG_BLDCNT_SUB |= BLEND_FADE_WHITE;
		
		REG_BLDY = 0;
		REG_BLDY_SUB = 0;
		break;
	case FXMODE_WHITE_OUT:
		REG_BLDCNT |= BLEND_FADE_WHITE;
		REG_BLDCNT_SUB |= BLEND_FADE_WHITE;
		
		REG_BLDY = 17;
		REG_BLDY_SUB = 17;
		break;
	case FXMODE_ALPHA_IN:
		REG_BLDCNT |= BLEND_ALPHA;
		REG_BLDCNT_SUB |= BLEND_ALPHA;
		
		REG_BLDALPHA = 0xF;
		REG_BLDALPHA_SUB = 0xF;
		break;
	case FXMODE_ALPHA_OUT:
		REG_BLDCNT |= BLEND_ALPHA;
		REG_BLDCNT_SUB |= BLEND_ALPHA;
		
		REG_BLDALPHA = (0xF << 8);
		REG_BLDALPHA_SUB = (0xF << 8);
	default:
		break;
	}
}

void CFxFade::Shutdown()
{
	REG_BLDCNT = 0;
	REG_BLDCNT_SUB = 0;
}

void CFxFade::Reset()
{
}

void CFxFade::UpdateVBlank()
{
	switch(CFx::GetFxMode())
	{
	case FXMODE_BLACK_IN:
	case FXMODE_WHITE_IN:
		REG_BLDY = m_fadeValue;
		REG_BLDY_SUB = m_fadeValue;
		break;
	case FXMODE_BLACK_OUT:
	case FXMODE_WHITE_OUT:
		REG_BLDY = 17 - m_fadeValue;
		REG_BLDY_SUB = 17 - m_fadeValue;
		break;
	case FXMODE_ALPHA_IN:
		REG_BLDALPHA = (m_fadeValue << 8) | (0xF - m_fadeValue);
		REG_BLDALPHA_SUB = (m_fadeValue << 8) | (0xF - m_fadeValue);
		break;
	case FXMODE_ALPHA_OUT:
		REG_BLDALPHA = ((0xF - m_fadeValue) << 8) | m_fadeValue;
		REG_BLDALPHA_SUB = ((0xF - m_fadeValue) << 8) | m_fadeValue;
		break;
	default:
		break;
	}
	
	switch(CFx::GetFxMode())
	{
		case FXMODE_BLACK_IN:
		case FXMODE_WHITE_IN:
		case FXMODE_BLACK_OUT:
		case FXMODE_WHITE_OUT:
			if(m_fadeValue < 17)
				m_fadeValue++;
			else
			{
				SetEnabled(CFx::GetFxMode(), false);
				
				if(m_callback != NULL)
					(*m_callback)(0);
			}
			break;
	case FXMODE_ALPHA_IN:
	case FXMODE_ALPHA_OUT:
			if(m_fadeValue < 0xF)
				m_fadeValue++;
			else
			{
				SetEnabled(CFx::GetFxMode(), false);
				
				if(m_callback != NULL)
					(*m_callback)(0);
			}
		break;
	}
}

void CFxFade::UpdateHBlank()
{
}

// ------------------------------------------------

void CFxFadeRamp::Initialize()
{
	Reset();
	
	switch(CFx::GetFxMode())
	{
	case FXMODE_BLACK_IN:
		REG_BLDCNT_SUB = BLEND_FADE_BLACK | BLEND_ALPHA | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE | BLEND_DST_BG2 | BLEND_DST_BG3;
		REG_BLDCNT_SUB &= ~BLEND_FADE_WHITE;
		REG_BLDCNT_SUB |= BLEND_FADE_BLACK;
		REG_BLDY_SUB = 0;
		break;
	case FXMODE_BLACK_OUT:
		REG_BLDCNT_SUB = BLEND_FADE_BLACK | BLEND_ALPHA | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE | BLEND_DST_BG2 | BLEND_DST_BG3;
		REG_BLDCNT_SUB &= ~BLEND_FADE_WHITE;
		REG_BLDCNT_SUB |= BLEND_FADE_BLACK;
		REG_BLDY_SUB = 17;
		break;
	case FXMODE_WHITE_IN:
		REG_BLDCNT_SUB = BLEND_FADE_WHITE | BLEND_ALPHA | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE | BLEND_DST_BG2 | BLEND_DST_BG3;
		REG_BLDCNT_SUB &= ~BLEND_FADE_BLACK;
		REG_BLDCNT_SUB |= BLEND_FADE_WHITE;
		REG_BLDY_SUB = 0;
		break;
	case FXMODE_WHITE_OUT:
		REG_BLDCNT_SUB = BLEND_FADE_WHITE | BLEND_ALPHA | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE | BLEND_DST_BG2 | BLEND_DST_BG3;
		REG_BLDCNT_SUB &= ~BLEND_FADE_BLACK;
		REG_BLDCNT_SUB |= BLEND_FADE_WHITE;
		REG_BLDY_SUB = 17;
		break;
	default:
		break;
	}
}

void CFxFadeRamp::Shutdown()
{
	REG_BLDCNT_SUB = 0;
	dmaTransfer(1, NULL, NULL, 0, 0);
}

void CFxFadeRamp::Reset()
{
	for(int i=0; i<SCREEN_HEIGHT; i++)
		m_map_ramp[i] = (i < 40 ? 17 : (17 - (abs(i - 40) * ((96.0f / SCREEN_HEIGHT)))));
	
	dmaTransfer(1, NULL, NULL, 0, 0);
	m_fadeValue = 0;
}

void CFxFadeRamp::UpdateVBlank()
{
	switch(CFx::GetFxMode())
	{
	case FXMODE_BLACK_IN:
	case FXMODE_WHITE_IN:
		for(int i=0; i<SCREEN_HEIGHT; i++)
			m_map_mix[i] = (u16) fmin(m_map_ramp[i] + m_fadeValue, 17);
			
		dmaTransfer(1, m_map_mix, (void*) &REG_BLDY_SUB, 1, DMA_ENABLE | DMA_REPEAT | DMA_START_HBL | DMA_DST_RESET);
		break;
	case FXMODE_BLACK_OUT:
	case FXMODE_WHITE_OUT:
		for(int i=0; i<SCREEN_HEIGHT; i++)
			m_map_mix[i] = (u16) fmin(m_map_ramp[i] + (17 - m_fadeValue), 17);
			
		dmaTransfer(1, m_map_mix, (void*) &REG_BLDY_SUB, 1, DMA_ENABLE | DMA_REPEAT | DMA_START_HBL | DMA_DST_RESET);
		break;
	default:
		break;
	}
	
	if(m_fadeValue < 17)
		m_fadeValue++;
	else
	{
		//Reset();
		//SetEnabled(false);
		
		//REG_BLDCNT_SUB = BLEND_FADE_BLACK | BLEND_ALPHA | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE | BLEND_DST_BG2 | BLEND_DST_BG3;
	}
}

void CFxFadeRamp::UpdateHBlank()
{
	/* if(REG_VCOUNT < 64)
	{
		REG_BLDCNT_SUB &= ~BLEND_FADE_WHITE;
		REG_BLDCNT_SUB |= BLEND_FADE_BLACK;
	}
	else
	{
		if(GetFxMode() == FXMODE_WHITE_OUT)
		{
			REG_BLDCNT_SUB &= ~BLEND_FADE_BLACK;
			REG_BLDCNT_SUB |= BLEND_FADE_WHITE;
		}
		else
		{
			REG_BLDCNT_SUB &= ~BLEND_FADE_WHITE;
			REG_BLDCNT_SUB |= BLEND_FADE_BLACK;	
		}
	} */
}

// ------------------------------------------------

void CFxColourPulse::Initialize()
{
	m_ping = true;
	m_fadeValue = false;
}

void CFxColourPulse::Shutdown()
{
	*(SPRITE_PALETTE + 47)  = 0xFFF;
	dmaTransfer(1, NULL, NULL, 0, 0);
}

void CFxColourPulse::Reset()
{
}

void CFxColourPulse::UpdateVBlank()
{
	*(SPRITE_PALETTE + 47) = (m_fadeValue << 10) | (m_fadeValue << 5) | m_fadeValue;

	if(m_ping)
	{
		if(++m_fadeValue >= 0x1F-1)
			m_ping = !m_ping;
	}
	else
	{
		if(--m_fadeValue <= 8)
			m_ping = !m_ping;
	}
}

void CFxColourPulse::UpdateHBlank()
{
}
