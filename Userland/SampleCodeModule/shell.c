#include <stdint.h>
#include "define.h"
#include "lib.h"
#include "shell.h"

#define COMMAND_LINE_SIZE	76

char shellBuffer[COMMAND_LINE_SIZE] = {0};
int bufferIndex = 0;

void startShell()
{
	char c;

	printLineStart();
	// Main loop
	while (1) {
		// Keep waiting till there's a key to read
		c = getChar();
		switch (c) {
			case '\n':
				putChar(c);
				parseCommand(shellBuffer);
				printLineStart();
				break;
			case '\b':
				if (bufferIndex > 0) {
					shellBuffer[bufferIndex--] = 0;
					putChar(c);
				}
				break;
			case -1:
				break;
			default:
				if (bufferIndex == COMMAND_LINE_SIZE) {
					putChar('\b');
					bufferIndex--;
				}

				shellBuffer[bufferIndex++] = c;
				putChar(c);
				break;
		}
	}
}

void printLineStart()
{
	printf("#> ");
}

void parseCommand(const char * line)
{
	char command[80] = {0};
	char args[80] = {0};

	// We need at least the command to be scanned
	int hasCommand = sscanf(line, "%s %s", command, args);
	if (hasCommand == 0)
		return;

	if (strcmp(command, HELP_COMMAND) == 0) {
		help();
	} else if (strcmp(command, SET_TIME_COMMAND) == 0) {

	} else if (strcmp(command, GET_TIME_COMMAND) == 0) {

	} else if (strcmp(command, SET_SCREENSAVER_COMMAND) == 0) {
		int seconds = 0;
		if (sscanf(args, "%d", &seconds) > 0 && seconds > 0)
			setScreensaver(seconds);

	} else {
		printf("Command not found.\n");
	}

	clearBuffer();
}

static void clearBuffer(void)
{
	int i;
	for (i = 0; i < 76; i++)
		shellBuffer[i] = 0;

	bufferIndex = 0;
}

/*
 * Shell functions
 */
static void help()
{
	printf("Hi, I'm help, available commands:\n");
	printf("help, time, stime, ss\n");
}

static void setTime()
{
	// TODO
}

static void getTime()
{
	// TODO
}

static void setScreensaver(int seconds)
{
	execSysCall(SYS_SCREENSAVER, seconds, 0, 0);
}
