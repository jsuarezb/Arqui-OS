#include <stdint.h>
#include "include/keyboard.h"

/*
 * Reads from `fd`, `count` amount of chars and
 * stores it into `buf`
 */
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

/*
 * Writes `count` amount of bytes from `buf` into `fd`
 */
signed int write(unsigned int fd, const char * buf, int count)
{
	signed int bytes = 0;

	if (fd == STDOUT) {
		while (count--) {
			_vWrite(buf[bytes]);
			bytes++;
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

