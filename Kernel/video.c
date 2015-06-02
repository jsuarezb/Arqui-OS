/*
 * Video driver
 */

#include "include/defines.h"
#include "include/video.h"
#define VIDEO_SIZE width * height

static char * const video = (char*) VIDEO_START;
static int vOffset = 0;
static const int width = VIDEO_WIDTH;
static const int height = VIDEO_HEIGHT;

void _vClear() {
	int x;

	vOffset = 0;
	for (x = 0; x < VIDEO_SIZE; x++)
		_vWrite(' ');

	vOffset = 0;
}

void _vWrite(char c) {
	_vWriteFormat(c, DEFAULT_CONSOLE_FORMAT);
}

void _vWriteError(char c) {
	_vWriteFormat(c, ERROR_CONSOLE_FORMAT);
}

void _vWriteFormat(char c, char format) {
	// Filter special characters
	switch (c) {
		case '\n':
			_vNewLine();
			break;
		case '\b':
			_vDelete();
			break;
		default:
			video[vOffset] = c;
			video[vOffset + 1] = format;
			vOffset += 2;
			break;
	}

	if (vOffset >= 2 * VIDEO_SIZE)
		_vMoveUp();
	
}

void _vPrint(char* c) {
	while(*c) _vWrite(*c++);
}

void _vPrintError(char* c) {
	while(*c) _vWriteError(*c++);
}

void _vDelete() {
	if (vOffset > 0) {
		vOffset -= 2;
		video[vOffset] = ' ';
		video[vOffset + 1] = DEFAULT_CONSOLE_FORMAT;
	}
}

void _vMoveUp() {
	int i;

	for (i = 0; i < 2 * (VIDEO_SIZE - width); i++)
		video[i] = video[i + 2 * width];

	for (; i < 2 * VIDEO_SIZE; i++)
		video[i] = i % 2 == 0 ? ' ' : DEFAULT_CONSOLE_FORMAT;

	vOffset -= 2 * width;
}

void _vNewLine() {
	// Fill line with spaces till the end
	do {
		_vWrite(' ');
	} while ((vOffset / 2) % width > 0);

}
