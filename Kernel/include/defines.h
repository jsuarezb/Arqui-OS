#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <stdint.h>

#define FALSE	0
#define TRUE	!FALSE

// Video driver
#define VIDEO_START		0xB8000
#define VIDEO_WIDTH		80
#define VIDEO_HEIGHT	25

#define DEFAULT_CONSOLE_FORMAT	0x0F
#define ERROR_CONSOLE_FORMAT	0xCF

// Keyboard driver
#define ASCII_ESCAPE	27
#define ASCII_CTRL		29
#define ASCII_SHIFT		20
#define ASCII_PRTSC		15
#define ASCII_ALT		27
#define ASCII_CAPS		27
#define ASCII_F1		27
#define ASCII_F2		27
#define ASCII_F3		27
#define ASCII_F4		27
#define ASCII_F5		27
#define ASCII_F6		27
#define ASCII_F7		27
#define ASCII_F8		27
#define ASCII_F9		27
#define ASCII_F10		27
#define ASCII_NUMLOCK	27
#define ASCII_SCROLLLOCK	27
#define ASCII_DELETE	127
#define SYS_REQ			27

#define LSHIFT_PRESSED	42
#define LSHIFT_RELEASED LSHIFT_PRESSED | 0x80
#define RSHIFT_PRESSED	54
#define RSHIFT_RELEASED RSHIFT_PRESSED | 0x80
#define CAPS_PRESSED	58
#define CAPS_RELEASED	CAPS_PRESSED | 0x80
#define CTRL_PRESSED	29
#define CTRL_RELEASED	29 | 0x80

#define RELEASE_FLAG	0x80

#define LOWERCASE	0
#define UPPERCASE	1

// IDT
/*
 * IDTR and IDT entry structure taken from
 * http://wiki.osdev.org/Interrupt_Descriptor_Table#IDT_in_IA-32e_Mode_.2864-bit_IDT.29
 */
#define IDT_OFFSET	0x20 // Pure64 interruptions offset
#define TIMER_TICK	0x00

/*
 * Register that points to the IDT
 * 0..15	size of the IDT
 * 16..63	memory offset of the IDT
 */
struct IDTR {
	uint16_t limit;
	uint64_t offset;
};

/*
 * Structure of an IDT Descriptor
 * 0..15	offset low bits
 * 16..31	selector
 * 32..39	zeros
 * 40..47	type and attributes
 * 48..55	offset middle bits
 * 56..71	offset high bits
 * 72..95	zeros
 */
struct IDTEntry {
	uint16_t lowBits;
	uint16_t selector;
	uint8_t zero1;
	uint8_t typeAttr;
	uint16_t midBits;
	uint32_t highBits;
	uint32_t zero2;
};

struct KBD {
	int capsEnabled;
	int shiftEnabled;
	int altEnabled;
	int ctrlEnabled;
	int pollRead;
	int pollWrite;
	int pollBuffer[16];
};

struct KBDKey {
	int shown;
	unsigned char asciiCode;
	unsigned char keyCode;
};

#endif
