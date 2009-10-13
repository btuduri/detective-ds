#include <nds.h>
#include <stdio.h>
#include "TDG.h"
#include "CGame.h"
#include <maxmod9.h>

#include "soundbank_bin.h"
#include "soundbank.h"

#include "Text.h"

CGame m_game;

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
	//irqInit();

	irqSet(IRQ_VBLANK, InterruptHandlerVBlank);
	irqSet(IRQ_HBLANK, InterruptHandlerHBlank);
	irqSet(IRQ_TIMER1, InterruptHandlerTimer1);
	irqSet(IRQ_TIMER2, InterruptHandlerTimer2);
	
	irqEnable(IRQ_VBLANK | IRQ_HBLANK | IRQ_TIMER1 | IRQ_TIMER2);
	
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmSetEventHandler(mmEventHandler);
	mmLoad(MOD_DETECTIVE);
	mmLoad(MOD_WEATHER);
	mmLoadEffect(SFX_FOOTSTEPS);
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
	//mmStart(MOD_WEATHER, MM_PLAY_LOOP);
	mmJingle(MOD_WEATHER);
	mmSetJingleVolume(0);
	
	consoleDebugInit(DebugDevice_NOCASH);
	
	m_game.Initialize();

	while(1)
	{
		swiWaitForVBlank();
		
		m_game.Update();
	}

	return 0;
}
