#include <stdint.h>
#include "include/defines.h"
#include "include/video.h"

unsigned char keysTable[1][85] = {
	{
		0, ASCII_ESCAPE, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
		'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
		ASCII_CTRL, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', ASCII_SHIFT,
		'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', ASCII_SHIFT, ASCII_PRTSC,
		ASCII_ALT, ' ', ASCII_CAPS, ASCII_F1, ASCII_F2, ASCII_F3, ASCII_F4, ASCII_F5, ASCII_F6,
		ASCII_F7, ASCII_F8, ASCII_F9, ASCII_F10, ASCII_NUMLOCK, ASCII_SCROLLLOCK, '7', '8', '9',
		'-', '4', '5', '6', '+', '1', '2', '3', '0', ASCII_DELETE, SYS_REQ
	}
};

/*
 * Sets the corresponding ascii code inside key
 */
void setKey(struct KBDKey * key, unsigned char code) {
	int state = 0;
	key->keyCode = code;
	key->asciiCode = keysTable[state][code];

	_vWrite(key->asciiCode);
}
