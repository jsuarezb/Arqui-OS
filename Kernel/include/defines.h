#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <stdint.h>

// Video driver
#define VIDEO_START		0xB8000
#define VIDEO_WIDTH		80
#define VIDEO_HEIGHT	25

#define DEFAULT_CONSOLE_FORMAT	0x0F
#define ERROR_CONSOLE_FORMAT	0xCF

// Keyboard driver
#define ASCII_ESCAPE	27
#define ASCII_CTRL		29
#define ASCII_SHIFT		42
#define ASCII_PRTSC		55
#define ASCII_ALT		56
#define ASCII_CAPS		58
#define ASCII_F1		59
#define ASCII_F2		60
#define ASCII_F3		61
#define ASCII_F4		62
#define ASCII_F5		63
#define ASCII_F6		64
#define ASCII_F7		65
#define ASCII_F8		66
#define ASCII_F9		67
#define ASCII_F10		68
#define ASCII_NUMLOCK	69
#define ASCII_SCROLLLOCK	70
#define ASCII_DELETE	127
#define SYS_REQ			84

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
	int capsPressed;
	int shiftPressed;
	int altPressed;
	int ctrlPressed;
	int pollRead;
	int pollWrite;
	int pollBuffer[32];
};

struct KBDKey {
	unsigned char asciiCode;
	unsigned char keyCode;
};

#endif
