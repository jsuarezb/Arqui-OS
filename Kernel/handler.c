#include <stdint.h>
#include "include/video.h"
#include "include/keyboard.h"

static int i = 0;

void timerTick()
{

}

void keyboardHandler(unsigned char c)
{
	struct KBDKey key;
	setKey(&key, c);
}
