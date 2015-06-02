
#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

void setupIDTentry(int index, uint16_t selector, uint64_t offset, uint8_t access);


#endif