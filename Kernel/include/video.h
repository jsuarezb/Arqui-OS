#define VIDEO_START 0xB8000
#define VIDEO_WIDTH 80
#define VIDEO_HEIGHT 25

#define DEFAULT_CONSOLE_FORMAT 0x0F

// _ → kernel

void _vClear();

void _vWrite(char c);

void _vDelete();

void _vClearLine();

void _vNewLine();
