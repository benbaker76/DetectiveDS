#include <nds.h>
#include <stdio.h>
#include "TDG.h"
#include "CGame.h"
#include <maxmod9.h>

#include "soundbank_bin.h"
#include "soundbank.h"

#include "Text.h"

CVideo m_video;
CGame m_game(GAMETYPE_NORMAL);

void InterruptHandlerVBlank()
{
	m_game.UpdateVBlank();
}

void InterruptHandlerHBlank()
{
	m_game.UpdateHBlank();
}

void InterruptHandlerTimer1()
{
	m_game.UpdateTimer1();
}

void InterruptHandlerTimer2()
{
	m_game.UpdateTimer2();
}

mm_word mmEventHandler(mm_word msg, mm_word param)
{
	switch( msg )
	{

	case MMCB_SONGMESSAGE:
        break;
	case MMCB_SONGFINISHED:
		break;
    }
	
	return 0;
}

int main(void)
{
	//irqInit();

	irqSet(IRQ_VBLANK, InterruptHandlerVBlank);
	irqSet(IRQ_HBLANK, InterruptHandlerHBlank);
	irqSet(IRQ_TIMER1, InterruptHandlerTimer1);
	irqSet(IRQ_TIMER2, InterruptHandlerTimer2);
	
	irqEnable(IRQ_VBLANK | IRQ_HBLANK | IRQ_TIMER1 | IRQ_TIMER2);
	
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmSetEventHandler(mmEventHandler);
	mmLoad(MOD_DETECTIVE);
	mmLoadEffect(SFX_FOOTSTEPS);
	mmLoadEffect(SFX_OPENDOOR);
	mmLoadEffect(SFX_CLOSEDOOR);
	mmStart(MOD_DETECTIVE, MM_PLAY_ONCE);
	//mmPosition(1);
	
	consoleDebugInit(DebugDevice_NOCASH);
	
	m_video.Initialize();
	//m_video.InitializeTitleScreen();

	m_game.Initialize();

	while(1)
	{
		swiWaitForVBlank();
		
		m_game.Update();
	}

	return 0;
}
