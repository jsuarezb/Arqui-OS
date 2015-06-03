#include <stdint.h>
#include "include/keyboard.h"

signed int read(unsigned int fd, char * buf, int count)
{
	signed int bytes = 0;

	if (fd == STDIN) {
		int i;
		for (i = 0; i < count && !isBufferEmpty(); i++) {
			buf[i] = getKey();
			bytes++;
		}
	}

	return bytes;
}

signed int write(unsigned int fd, const char * buf, int count)
{
	signed int bytes = 0;

	if (fd == STDOUT) {
		while (count) {
			_vWrite(buf[bytes]);
			bytes++;
			count--;
		}
	}

	return bytes;
}

int getRTC(int content)
{
	// TODO
	return 0;
}

int setRTC(int content, int value)
{
	// TODO
	return 0;
}
