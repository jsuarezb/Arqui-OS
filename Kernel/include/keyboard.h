#ifndef _KEYBOARD_H_
#define _KEYBOARD_H

#include "defines.h"

void setKey(struct KBDKey * key, unsigned char code);
void KBDinitialize();
int isLetter(unsigned char c);

#endif
