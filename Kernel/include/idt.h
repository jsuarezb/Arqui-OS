#ifndef _IDT_H_
#define _IDT_H_

#include "defines.h"
#include <stdint.h>

void _cli(void);
void _sti(void);

void _irq00handler();
void _irq01handler();
void _int80handler();
void picMasterMask(uint16_t); 
void picSlaveMask(uint16_t);

#endif
