#include <stdint.h>
#include "include/video.h"
#include "include/keyboard.h"
#include "include/api.h"
#include "include/screensaver.h"
#include "include/handler.h"

static unsigned int timer = SCREENSAVER_WAIT_TIME;
static unsigned int tickCount = TICKS_PER_FRAME;
static unsigned int showingScreensaver = FALSE;

/*
 * Function to run on timer tick interruption
 */
void timertickHandler()
{
	if (timer == 0) { // Screensaver state
		if (!showingScreensaver) { 
			// If it's not showing the screensaver yet
			startScreensaver();
		} else { 
			// If it's already showing it
			tickScreensaver();
		}
	} else {
		timer--;
	}
}

/*
 * Function to run on keyboard interruption
 */
void keyboardHandler(unsigned char c)
{
	timer = SCREENSAVER_WAIT_TIME;
	if (showingScreensaver) {
		stopScreensaver();			
	}	

	setKey(c);
}

/*
 * Function to run on software interruption (int 80h)
 */
void syscallHandler(uint64_t code, uint64_t arg1, uint64_t arg2, uint64_t arg3)
{
	switch (code) {
		case SYS_READ:
			read(arg1, arg2, arg3);
			break;
		case SYS_WRITE:
			write(arg1, arg2, arg3);
			break;
		case SYS_TIME:
			return getRTC(arg1);
		case SYS_STIME:
			return setRTC(arg1, arg2);
		default:
			break;
	}
}

/*
 * Saves the current screen and shows the screensaver
 */
void startScreensaver()
{
	showingScreensaver = TRUE;
	_vBackupScreen();
	initScreensaver();
}

/*
 * Stops the screensaver and resumes activity
 */
void stopScreensaver()
{
	_vRestoreScreen();
	showingScreensaver = FALSE;
}

/*
 * Frame manager for the screensaver
 */
void tickScreensaver()
{
	if (tickCount == 0) {
		nextFrame();
		tickCount = TICKS_PER_FRAME;
	} else {
		tickCount--;
	}
}
