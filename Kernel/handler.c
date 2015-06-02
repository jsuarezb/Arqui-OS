#include <stdint.h>
#include "include/keyboard.h"

void timerTick()
{

}

void keyboardHandler(unsigned char c)
{
	struct KBDKey * key;
	setKey(key, c);	
}
