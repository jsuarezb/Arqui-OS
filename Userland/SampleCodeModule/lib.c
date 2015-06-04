/*
	sysCallHandler -> int 80
	Hacer sys call
		rdi - rci - rdx - rbx

*/
#include "lib.h"
#include "define.h"
#include "libasm.h"

void putChar( char c ) 
{
	execSysCall(SYS_WRITE, STDOUT, &c, 1);
}

void printf( char* s )
{
	int i = 0;
	for ( i = 0; s[i] != '\0'; i++) {
		putChar( s[i] );
	}
}

// to = placeHolder
void to_s ( int f, char* to )
{
	int aux = f;

	do {
		to++;
		aux = aux / 10;
	} while ( aux != 0 );
	
	*to = '\0';
	to--;
	int digit = f;
	
	do {
		digit = f % 10;
		f /= 10;
		*to = digit;
		to--;
	} while ( f != 0 );
}

void concat (char* first, char* second, char* to) 
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

// printf( "gilada %d%d\n", 2, 3 )

void getChar ( char c )
{
	execSysCall( SYS_READ, STDIN, c, 1 );
}

void scanf ( char* s)
{
	int i = 0;
	for ( i = 0; s[i] != '\0'; i++) {
		getChar( s[i] );
	}
}

