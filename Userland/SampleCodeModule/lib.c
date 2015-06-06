/*
	sysCallHandler -> int 80
	Hacer sys call
		rdi - rci - rdx - rbx

*/
#include "lib.h"
#include "define.h"
#include "libasm.h"

#include <stdarg.h>		

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
    char const digits[] = "0123456789";
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
		*to = digits[digit%10];
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

// Variable args

void printf_v( char* s, ... ) {
	
  	va_list ap;
   	int i;
   	va_start(ap, s);
	
   	for ( i = 0; s[i] != '\0'; i++) {
   		if( s[i] == '%' ){
			if ( s[i+1] = 'd' ) {
				int aux = va_arg(ap, int);
				char istring[ (int_length(aux)) ];
				to_s(aux, istring);
				printf( istring );
				i++;
			} else if ( s[i+1] = 'c' ) {
				char aux = va_arg(ap, char);
				char letter[2];
				to_c (aux, letter);
				printf(letter);
				i++;
			} else if ( s[i+1] = 's' ) {
				char* aux = va_arg(ap, char*);
				printf(aux);
				i++;
			} else
				putChar('%');
		} else 
			putChar( s[i] );
   	}
   	va_end(ap);
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

void to_c (int i, char* to ) {
	to[0] = (char) i;
	to[1] = '\0';
}