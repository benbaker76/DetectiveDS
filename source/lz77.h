#include <nds.h>

int getSize(uint8 * source, uint16 * dest, uint32 r2);
uint8 readByte(uint8 * source);
void decompressToVRAM(const void* source, void* dest);
