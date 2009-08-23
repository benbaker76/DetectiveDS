#include <nds.h>
#include <stdio.h>
#include "TDG.h"
#include "Game.h"
#include <maxmod9.h>

#include "soundbank_bin.h"
#include "soundbank.h"

CGame m_game(GAMETYPE_NORMAL);
CTimer m_timer(9, 10, 0, 0);

u8 m_elapsedTime;
u8 m_lastUpdate;

void InterruptHandlerVBlank()
{
}

void InterruptHandlerHBlank()
{
}

void InterruptHandlerTimer1()
{
}

void InterruptHandlerTimer2()
{
	m_timer.Update();
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
	mmLoad(MOD_KEYG_SUBTONAL);
	mmLoadEffect(SFX_AMBULANCE);
	mmLoadEffect(SFX_BOOM);
	mmStart(MOD_KEYG_SUBTONAL, MM_PLAY_LOOP);
	
	consoleDebugInit(DebugDevice_NOCASH);
	
	m_timer.Start();
	m_game.Initialize();

	while(1)
	{
		m_elapsedTime = m_timer.pCurrentTime()->MilliSeconds - m_lastUpdate;
		m_lastUpdate = m_timer.pCurrentTime()->MilliSeconds;
		
		m_game.Update(m_elapsedTime, m_timer.pCurrentTime());

		swiWaitForVBlank();
	}

	return 0;
}
