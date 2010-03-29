#include <nds.h>
#include <math.h>
#include <stdio.h>
#include "TDG.h"
#include "CGame.h"
#include "efs_lib.h"
#include <maxmod9.h>
#include "FileIo.h"
//#include "soundbank_bin.h"
#include "soundbank.h"
#include "fat.h"
#include "Text.h"

CGame m_game;
u8* pSoundBankBuffer = NULL;

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
	return m_game.MusicEventHandler(msg, param);
}

int main(void)
{
	int retVal = 0;
	//irqInit();

	irqSet(IRQ_VBLANK, InterruptHandlerVBlank);
	irqSet(IRQ_HBLANK, InterruptHandlerHBlank);
	irqSet(IRQ_TIMER1, InterruptHandlerTimer1);
	irqSet(IRQ_TIMER2, InterruptHandlerTimer2);
	
	irqEnable(IRQ_VBLANK | IRQ_HBLANK | IRQ_TIMER1 | IRQ_TIMER2);
	
	m_game.InitLoading();
	
#if (EFS == 1)
	retVal = EFS_Init(EFS_AND_FAT | EFS_DEFAULT_DEVICE, NULL);	// Init EFS
#else
	retVal = fatInitDefault();							// Init FAT
#endif

	if(retVal)
	{
		int soundBankSize = readFileSize("/Data/TDG/Audio/soundbank.bin");

		if(soundBankSize != 0)
		{
			pSoundBankBuffer = (u8*) malloc(soundBankSize);
			
			if(pSoundBankBuffer != NULL)
			{
				readFileBuffer("/Data/TDG/Audio/soundbank.bin", (char*) pSoundBankBuffer);
				
				mmInitDefaultMem((mm_addr)pSoundBankBuffer);
				
				//mmInitDefault((char*) "/TDG/Audio/soundbank.bin");
				//mmSelectMode(MM_MODE_B);
				mmSetEventHandler(mmEventHandler);
				mmLoad(MOD_DETECTIVE);
				mmLoad(MOD_WEATHER);
				mmLoadEffect(SFX_FOOTSTEP01);
				mmLoadEffect(SFX_FOOTSTEP02);
				mmLoadEffect(SFX_FOOTSTEP03);
				mmLoadEffect(SFX_FOOTSTEP04);
				mmLoadEffect(SFX_FOOTSTEP05);
				mmLoadEffect(SFX_FOOTSTEP06);
				mmLoadEffect(SFX_FOOTSTEP07);
				mmLoadEffect(SFX_FOOTSTEP08);
				mmLoadEffect(SFX_FOOTSTEP09);
				mmLoadEffect(SFX_FOOTSTEP10);
				mmLoadEffect(SFX_OPENDOOR);
				mmLoadEffect(SFX_CLOSEDOOR);
				mmLoadEffect(SFX_SECRETDOOR);
				mmLoadEffect(SFX_DRAIN);
				mmLoadEffect(SFX_GATE);
				mmLoadEffect(SFX_UNLOCK);
				mmLoadEffect(SFX_KEYDROP);
				mmLoadEffect(SFX_CLICK);
				mmLoadEffect(SFX_BEEP);
				mmLoadEffect(SFX_GHOSTLY);
				mmLoadEffect(SFX_HOWLING);
				mmLoadEffect(SFX_TIMEWARP);
				mmLoadEffect(SFX_MAGIC);
				mmLoadEffect(SFX_CLOCK_TICK);
				mmLoadEffect(SFX_CLOCK_CHIME);
				mmLoadEffect(SFX_FIREPLACE);
				mmLoadEffect(SFX_VACUUM);
				mmLoadEffect(SFX_BOMB);
				mmLoadEffect(SFX_GUNSHOT);
				mmLoadEffect(SFX_WATERDRIP);
				mmLoadEffect(SFX_GLASS);
				mmJingle(MOD_WEATHER);
				mmSetJingleVolume(0);
			}
		}
	}
	
	consoleDebugInit(DebugDevice_NOCASH);
	
	m_game.Initialize();

	while(1)
	{
		swiWaitForVBlank();
		
		m_game.Update();
	}

	return 0;
}
