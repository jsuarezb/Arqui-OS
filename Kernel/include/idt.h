#ifndef _IDT_H_
#define _IDT_H_

#include "defines.h"
#include <stdint.h>

void fooBar(void);
void _cli(void);
void _sti(void);
void _irq00handler (uint64_t irq);
void picMasterMask(uint16_t); 
void picSlaveMask(uint16_t);


#endif
