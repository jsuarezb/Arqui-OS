#include <stdint.h>
#include "include/video.h"
#include "include/keyboard.h"
#include "include/api.h"

static int i = 0;

void timertickHandler()
{

}

void keyboardHandler(unsigned char c)
{
	struct KBDKey key;
	setKey(&key, c);
}

void syscallHandler(int code, int arg1, int arg2, int arg3)
{
	switch (code) {
		case SYS_READ:
			read(arg1, arg2, arg3);
			break;
		case SYS_WRITE:
			write(arg1, arg2, arg3);
			break;
		case SYS_TIME:
			return getRTC(arg1);
		case SYS_STIME:
			return setRTC(arg1, arg2);
		default:
			break;
	}
}
