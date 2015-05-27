#include <stdint.h>
#include "include/video.h"


static int timer = 0;

void irqDispatcher(uint64_t irq)
{
	switch(irq) {
		case 0:
			timerTick();
			break;
	}
	return;
}

void timerTick()
{
	timer ++;
	_vWrite('_');
}