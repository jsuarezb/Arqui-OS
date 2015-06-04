#ifndef _KEYBOARD_H_
#define _KEYBOARD_H

#include "defines.h"

void setKey(unsigned char code);
void KBDinitialize();
int addKey(unsigned char c);
unsigned char getKey();
int isLetter(unsigned char c);
int isBufferEmpty();

#endif
