#include "Globals.h"
#include "CTimer.h"

void SaveTiles(PRECT pRect, u16* pDest);
void RestoreTiles(PRECT pRect, u16* pSrc);
void DrawPixel(int x, int y, int colorIndex);
void DrawLine(int x0, int y0, int x1, int y1, int colorIndex);
void DrawTime(CTime* pTime, int x, int y);
void dmaTransfer(uint8 channel, const void* src, void* dest, uint32 size, uint32 mode);
void ClearBG(int bg, bool sub);
	