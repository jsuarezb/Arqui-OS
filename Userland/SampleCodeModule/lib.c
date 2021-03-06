/*
	sysCallHandler -> int 80
	Hacer sys call
		rdi - rci - rdx - rbx

*/
#include <stdarg.h>
#include "lib.h"
#include "define.h"
#include "libasm.h"

#include <stdarg.h>

static void vprintf(char* s, va_list vl);
static int vsscanf(const char * s, const char * f, va_list vl);

void putChar(char c)
{
	execSysCall(SYS_WRITE, STDOUT, (uint64_t) &c, 1);
}

char getChar()
{
	char c = -1;
	while(c == -1)
		execSysCall(SYS_READ, STDIN, (uint64_t) &c, 1);

	return c;
}

void putString(char * str)
{
	while (*str != '\0')
		putChar(*str++);
}

void printf(char * s, ...)
{
	va_list vl;
	va_start(vl, s);

	vprintf(s, vl);

	va_end(vl);
}

static void vprintf(char* s, va_list vl) {
	char nextChar, cAux;
	char * sAux;
   	int i, iAux;

   	for (i = 0; s[i] != '\0'; i++) {
   		if(s[i] == '%'){
   			nextChar = s[i+1];
   			if (nextChar == '\0') {
   				putChar('%');
   				break;
   			} else if (nextChar == 'd') {
				iAux = va_arg(vl, int);
				char istring[int_length(iAux)];
				itos(iAux, 10, istring);
				putString(istring);
				i++;
   			} else if (nextChar == 'c') {
				cAux = (char) va_arg(vl, int);
				putChar(cAux);
				i++;
   			} else if (nextChar == 's') {
				sAux = va_arg(vl, char *);
				putString(sAux);
				i++;
   			} else if (nextChar == 'x') {
   				iAux = va_arg(vl, int);
   				char hex[int_length(i)];
   				itos(iAux, 16, hex);
   				putString(hex);
   				i++;
   			} else {
   				putChar('%');
   			}
		} else {
			putChar(s[i]);

		}
	}
}

int scanf(const char * format, ...)
{
	char buffer[81];
	char c;
	int count, readIndex = 0;
	va_list vl;
	va_start(vl, format);

	// We want to write every scanned character
	while ((c = getChar()) != '\n') {
		if (c == '\b') {
			if (readIndex - 1 >= 0) {
				buffer[readIndex] = '\0';
				putChar(c);
				readIndex--;
			}
		} else {
			buffer[readIndex] = c;

			if (readIndex + 1 > 80)
				putChar('\b');
			else
				readIndex++;

			putChar(c);
		}
	}
	putChar('\n');
	count = vsscanf(buffer, format, vl);
	va_end(vl);
	return count;
}

int sscanf(const char * source, const char * format, ...)
{
	int count;
	va_list vl;

	va_start(vl, format);
	count = vsscanf(source, format, vl);
	va_end(vl);
	return count;
}

static int vsscanf(const char * s, const char * f, va_list vl)
{
	int i, count = 0;
	char * strBuffer;
	char intBuffer[25]; // We can read numbers only 25 digits long

	while (*s != '\0' && *f != '\0') {
		// Read till first non space character
		while (*f == ' ')
			f++;

		if (*f == '%') { // Maybe found a format specifier
			f++;

			if (*f == 's') { // String format
				f++;
				// Read till first non space character found
				while (*s == ' ')
					s++;

				// Ready to copy till the first space or end of string
				strBuffer = va_arg(vl, char *);
				i = 0;
				while (*s != ' ' && *s != '\0') {
					strBuffer[i] = *s;
					s++;
					i++;
				}

				count++;
			} else if (*f == 'd') { // Number format
				f++;

				while (*s == ' ')
					s++;

				// Check if we have a number
				if (cindex(*s, "0123456789") >= 0) {
					i = 0;
					// Being careful with intBuffer size; it's 25 chars long,
					// so we have to write 24 chars max, so there's space for \0
					while (*s != ' ' && *s != '\0' && cindex(*s, "0123456789") >= 0 && i < 24) {
						intBuffer[i] = *s;
						s++;
						i++;
					}
					intBuffer[i] = '\0';
					*(va_arg(vl, int *)) = stoi(intBuffer);

					count++;
				} else {
					return count;
				}
			} else {
				while (*s == ' ')
					s++;

				if (*s != '%')
					return count;
				s++;
				if (*s != *f)
					return count;
			}

		} else { // Normal character
			// Read until first non space character
			while (*s == ' ')
				s++;

			// At the first non equal set of characters, end function
			if (*s != *f) {
				return count;
			} else {
				s++;
				f++;
			}
		}
	}

	return count;
}

void concat(char * first, char * second, char * to)
{
	int i = 0;
	int j = 0;

	for ( i = 0; first[i] != '\0'; i++ ) {
		to[i] = first[i];
	}
	for ( j = 0; second[i] != '\0'; i++, j++ ) {
		to[i] = second[j];
	}
	to[i] = '\0';
}

// to = placeHolder
void itos (int i, int base, char * to)
{
	char const digits[] = "0123456789ABCDEF";
	int aux = i;

	do {
		aux /= base;
		to++;
	} while (aux > 0);

	*to = '\0';

	do {
		to--;
		*to = digits[i % base];
		i /= base;
	} while (i > 0);
}

/*
 * Returns the index of the char in str, -1 if not in str
 */
int cindex(char c, const char * str)
{
	int i = 0, found = 0;

	while (*str != '\0') {
		if (*str == c) {
			found = 1;
			break;
		}

		str++;
		i++;
	}

	return (found > 0) ? i : -1;
}

/*
 * String representation of an int to int (base 10)
 */
int stoi(const char * str)
{
	int i = 0;
	while (*str != '\0') {
		i = i * 10 + *str - '0';
		str++;
	}

	return i;
}

int int_length ( int i ) {
	int aux = 0;
	do {
		i = i / 10;
		aux ++;
	} while ( i != 0 );
	return aux;
}

int strlen ( char * s ) {
	int i = 0;
	while (s[i] != '\0')
		i++;
	return i;
}

int strcmp(const char * str1, const char * str2)
{
	while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0') {
		str1++;
		str2++;
	}

	return *str1 - *str2;
}

int isDigit ( int n )
{
	return (n - '0' >= 0 && n - '0' <= 9);
}
