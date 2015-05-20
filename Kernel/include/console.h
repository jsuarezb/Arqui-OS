#define VIDEO_START 0xB8000
#define VIDEO_WIDTH 80
#define VIDEO_HEIGHT 25
#define VIDEO_SIZE VIDEO_WIDTH * VIDEO_HEIGHT

#define DEFAULT_CONSOLE_FORMAT 0x0F

#include <stdint.h>

// _ → kernel

void _clear();

void _writeChar(char c);

void _write(char* str);

void _clearLine();

void _newLine();
