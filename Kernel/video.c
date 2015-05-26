/*
 * Video driver
 */

#include <video.h>
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
			video[vOffset + 1] = DEFAULT_CONSOLE_FORMAT;
			vOffset += 2;
			break;
	}

	if (vOffset > 2 * VIDEO_SIZE)
		_vClearLine();
	
}

void _vDelete() {
	if (vOffset > 0) {
		vOffset -= 2;
		video[vOffset] = ' ';
		video[vOffset + 1] = DEFAULT_CONSOLE_FORMAT;
	}
}

void _vClearLine() {
	int x;

	for (x = 0; x < 2 * (VIDEO_SIZE - width); x++) // copy char and format
		video[x] = video[x + width];

	for (; x < 2 * VIDEO_SIZE; x++)
		video[x] = (x % 2 == 0) ? ' ' : DEFAULT_CONSOLE_FORMAT;

	vOffset -= 2 * width;
}

void _vNewLine() {
	// Fill line with spaces till the end
	do {
		_vWrite(' ');
	} while ((vOffset / 2) % width > 0);

}
