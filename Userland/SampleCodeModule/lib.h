#ifndef _LIB_H
#define _LIB_H

/*
 * Writes a single character on screen
 */
void putChar(char c);

/*
 * Gets a character from keyboard buffer
 */
char getChar();

/*
 * Prints a formatted string
 */
void printf(char * fmt, ...);

/*
 * Scans from std input specified fmt
 */
int scanf(const char * fmt, ...);

/*
 * Stores the extracted values from `src` formatted as `fmt`
 */
int sscanf(const char * src, const char * fmt, ...);

/*
 * Writes an int in its string representation on `to`
 */
void to_s(int f, char * to);

/*
 * Concats two strings and writes the concatenation on `to`
 */
void concat(char * first, char * second, char * to);

/*
 * Compares two string until first difference
 * 0 if both are equal
 * not 0 if they differ
 */
int strcmp(const char * str1, const char * str2);

/*
 * Seeks for a char inside `str`
 * If found, returns the index of `c` inside `str`
 * If not found, returns -1
 */
int cindex(char c, const char * str);

void printf_v ( char* s, ... );
int int_length ( int i );
int strlen ( char* s );
void to_c (int i, char* to );
void to_hex( int i, char* to);

#endif