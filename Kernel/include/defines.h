#ifndef _DEFINES_
#define _DEFINES_

/*
 * IDTR and IDT entry structure taken from
 * http://wiki.osdev.org/Interrupt_Descriptor_Table#IDT_in_IA-32e_Mode_.2864-bit_IDT.29
 */

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

#endif
