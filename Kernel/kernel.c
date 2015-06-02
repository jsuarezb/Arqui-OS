#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <video.h>
#include "include/defines.h"
#include "include/idt.h"
#include "include/video.h"
#include "include/keyboard.h"

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

// IDT 

static struct IDTEntry* idt = (struct IDTEntry*) 0x0000;
static struct IDTR idtr;
struct KBD keyboard;

typedef int (*EntryPoint)();

void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	ncPrint("[x64BareBones]");
	ncNewline();
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}

int main()
{	
	ncPrint("[Kernel Main]");
	ncNewline();
	ncPrint("  Sample code module at 0x");
	ncPrintHex((uint64_t)sampleCodeModuleAddress);
	ncNewline();
	ncPrint("  Calling the sample code module returned: ");
	ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	ncNewline();
	ncNewline();

	ncPrint("  Sample data module at 0x");
	ncPrintHex((uint64_t)sampleDataModuleAddress);
	ncNewline();
	ncPrint("  Sample data module contents: ");
	ncPrint((char*)sampleDataModuleAddress);
	ncNewline();

	ncPrint("[Finished]");
	
	_vClear();

	int x;
	for (x = 0; x < 80; x++)
		_vWrite('#');
	
	KBDinitialize();

	IDTinitialize();

	while(1) {
		while (!canRead());

		unsigned char c = getKey();
		_vWrite(c);
	}

	return 0;
}

void IDTinitialize()
{
	setupIDTentry(0x20, 0x08, &_irq00handler, 0x8E);
	setupIDTentry(0x21, 0x08, &_irq01handler, 0x8E);

	picMasterMask(0xFE); 
	picSlaveMask(0xFF);

	_sti();
}


void setupIDTentry(int index, uint16_t selector, uint64_t offset, uint8_t access)
{
	idt[index].lowBits = offset & 0xFFFF;
	idt[index].midBits = (offset >> 16) & 0xFFFF;
	idt[index].highBits = (offset >> 32) & 0xFFFFFFFF;

	idt[index].selector = selector;
	idt[index].typeAttr = access;

	idt[index].zero1 = 0;
	idt[index].zero2 = 0;
}
