#ifndef IDT_H
#define IDT_H

#include "defines.h"
#include <stdint.h>

void _lidt (struct IDTR * idtr);

void _irq00handler (uint64_t irq);

#endif
