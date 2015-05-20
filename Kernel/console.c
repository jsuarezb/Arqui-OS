#include <console.h>

static uint8_t * const video = (uint8_t*) VIDEO_START;
static uint8_t * currVideo = (uint8_t*) VIDEO_START;
static const uint32_t width = VIDEO_WIDTH;
static const uint32_t height = VIDEO_HEIGHT;

void _clear() {
	int x;

	for (x = 0; x < VIDEO_WIDTH * VIDEO_HEIGHT; x++) {
		*(video + 2 * x) = ' ';
		*(video + 2 * x + 1) = DEFAULT_CONSOLE_FORMAT;
	}

	currVideo = video;
}

void _writeChar(char c) {
	*(currVideo) = c;
	currVideo += 2;

	if (currVideo - video > 2 * VIDEO_SIZE)
		_clearLine();
	
}

void _write(char* str) {
	while (*str) {
		_writeChar(*str);
		str++;
	}
}

void _clearLine() {
	int x;

	for (x = 0; x < 2 * (VIDEO_SIZE - VIDEO_WIDTH); x++) // copy char and format
		*(video + x) = *(video + x + VIDEO_WIDTH);

	for (; x < 2 * VIDEO_SIZE; x++)
		*(video + x) = (x % 2 == 0) ? ' ' : DEFAULT_CONSOLE_FORMAT;

	currVideo -= 2 * VIDEO_WIDTH;
}

void _newLine() {
	currVideo += (80 - (currVideo - video) % 80);

	if (currVideo > video + VIDEO_SIZE)
		_clearLine();

}