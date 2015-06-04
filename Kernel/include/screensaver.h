#ifndef _SCREENSAVER_H_
#define _SCREENSAVER_H

#define TICKS_TO_SECONDS		18
#define TICKS_PER_FRAME 		1 * TICKS_TO_SECONDS
#define SCREENSAVER_WAIT_TIME	2 * TICKS_TO_SECONDS

void initScreensaver();

void tick();

void draw();

void drawFrame0();

void drawFrame1();

void drawFrame2();

#endif
