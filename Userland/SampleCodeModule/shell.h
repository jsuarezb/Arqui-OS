#ifndef	_SHELL_H_
#define	_SHELL_H_

/*
 * Starts the shell
 */
void startShell();

/*
 * Prints shell line header
 */
void printLineStart();

/*
 *
 */
void parseCommand(const char * line);

/*
 * Clears the shell buffer
 */
static void clearBuffer();

/*
 * Help function
 */
static void help();

/*
 * Sets the system time
 */
static void setTime();

/*
 * Prints system time
 */
static void getTime();

/*
 * Set screensaver wait time
 */
static void setScreensaver(int seconds);

#endif