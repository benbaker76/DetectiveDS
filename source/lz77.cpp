#include <nds.h>

int getSize(uint8 * source, uint16 * dest, uint32 r2)
{
   u32 size = *((u32*)source) >> 8;
   return (size<<8) | 0x10;
}

uint8 readByte(uint8 * source)
{
   return *source++;
}

void decompressToVRAM(const void* source, void* dest)
{ 
   TDecompressionStream decStream;
   decStream.getSize = getSize;
   decStream.getResult = NULL;
   decStream.readByte = readByte;
   swiDecompressLZSSVram((void*)source, dest, 0, &decStream);
}
