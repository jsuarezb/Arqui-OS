#include <stdint.h>
#include "include/video.h"
#include "include/keyboard.h"
#include "include/api.h"
#include "include/screensaver.h"
#include "include/handler.h"

extern unsigned int tickCount;
extern unsigned int showingScreensaver;
extern unsigned int timerLimit;
extern unsigned int timer;

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
	timer = timerLimit;
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
			getRTC(arg1);
			break;
		case SYS_STIME:
			setRTC(arg1);
			break;
		case SYS_SCREENSAVER:
			setScreensaverTime(arg1);
		default:
			break;
	}
}
