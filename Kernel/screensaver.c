#include <stdint.h>
#include "include/video.h"
#include "include/defines.h"
#include "include/screensaver.h"

static void (*frameDrawers[FRAMES])(void);
static int currentFrame = 0;
static char counter = 0;

/*
 * Draw the first frame of the screensaver
 */
void initScreensaver()
{
	frameDrawers[0] = &drawFrame0;
	frameDrawers[1] = &drawFrame1;
	frameDrawers[2] = &drawFrame2;
	currentFrame = 0;
	counter = 0;

	_vClear();
	draw();
}

/*
 * Go to the next frame and draw it
 */
void nextFrame()
{
	currentFrame = (currentFrame + 1) % FRAMES;	
	draw();
}

/*
 * Fill the screen with the corresponding frame
 */
void draw()
{
	// (*frameDrawers[currentFrame])();
	int i;

	counter = (counter == 0) ? 0xFF : 0x00;
	for (i = 0; i < VIDEO_WIDTH; i++)
		_vWriteFormat(' ', counter);

}

// In case I want to draw every frame by hand
// it can be done using an array
// of functions that draw the corresponding frame; another
// way is to define an array containing each screen for 
// every frame. This'd be hard to do by hand, so
// I'm sticking with a simple drawing function

void drawFrame0()
{
	int x, y;
	_vClear();

	for (y = 0; y < VIDEO_HEIGHT; y++) {
		for (x = 0; x < VIDEO_WIDTH; x++) {
			if (x == 4 && y == 6)
				_vWriteFormat(' ', WHITE_BG | WHITE_FG);
			else
				_vWriteFormat(' ', BLACK_BG | WHITE_FG);
		}
	}
}

void drawFrame1()
{
	int x, y;
	_vClear();

	for (y = 0; y < VIDEO_HEIGHT; y++) {
		for (x = 0; x < VIDEO_WIDTH; x++) {
			_vWriteFormat(' ', BLACK_BG | WHITE_FG);
		}
	}
}

void drawFrame2()
{
	int x, y;
	_vClear();

	for (y = 0; y < VIDEO_HEIGHT; y++) {
		for (x = 0; x < VIDEO_WIDTH; x++) {
			if (x == 4 && y == 6)
				_vWriteFormat(' ', BLACK_BG | WHITE_FG);
			else
				_vWriteFormat(' ', WHITE_BG | WHITE_FG);
		}
	}
}
