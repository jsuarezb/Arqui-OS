#include <stdint.h>
#include "include/video.h"

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
	int i;
	
	_vPrint(" Hello ");
	_vPrintError("World");
}
