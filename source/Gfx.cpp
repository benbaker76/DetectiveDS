#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TDG.h"
#include "lz77.h"

void SaveTiles(Rect* pRect, u16* pDest)
{
	for(int y=pRect->Y; y < pRect->Y + pRect->Height; y++)
	{
		for(int x=pRect->X; x < pRect->X + pRect->Width; x++)
		{
			u16 tileId = *(BG_MAP_RAM_SUB(BG3_MAP_BASE_SUB) + x + y * 32);
			u16* pTile = BG_TILE_RAM_SUB(BG3_TILE_BASE_SUB) + tileId * 32;
			
			dmaCopy(pTile, pDest, 64);
			pDest += 32;
		}
	}
}

void RestoreTiles(Rect* pRect, u16* pSrc)
{
	for(int y=pRect->Y; y < pRect->Y + pRect->Height; y++)
	{
		for(int x=pRect->X; x < pRect->X + pRect->Width; x++)
		{
			u16 tileId = *(BG_MAP_RAM_SUB(BG3_MAP_BASE_SUB) + x + y * 32);
			u16* pTile = BG_TILE_RAM_SUB(BG3_TILE_BASE_SUB) + tileId * 32;
			
			dmaCopy(pSrc, pTile, 64);
			pSrc += 32;
		}
	}
}

void DrawPixel(int x, int y, int colorIndex)
{
	u16 tileId = *(BG_MAP_RAM_SUB(BG3_MAP_BASE_SUB) + (x / 8) + (y / 8) * 32);
	u16* pTile = BG_TILE_RAM_SUB(BG3_TILE_BASE_SUB) + tileId * 32 + ((x % 8) / 2) + (y % 8) * 4;
	*pTile = ((x % 2) == 0 ? ((*pTile &~ 0xFF) | colorIndex) : ((*pTile &~ 0xFF00) | (colorIndex << 8)));
}

void DrawLine(int x0, int y0, int x1, int y1, int colorIndex)
{
	int dy = y1 - y0;
	int dx = x1 - x0;
	int stepx, stepy;

	if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
	if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
	dy <<= 1;
	dx <<= 1;

	DrawPixel(x0, y0, colorIndex);
	
	if (dx > dy)
	{
		int fraction = dy - (dx >> 1);
		
		while (x0 != x1)
		{
			if (fraction >= 0)
			{
				y0 += stepy;
				fraction -= dx;
			}
			
			x0 += stepx;
			fraction += dy;
			DrawPixel(x0, y0, colorIndex);
		}
	}
	else
	{
		int fraction = dx - (dy >> 1);
		
		while (y0 != y1)
		{
			if (fraction >= 0)
			{
				x0 += stepx;
				fraction -= dy;
			}
			
			y0 += stepy;
			fraction += dx;
			DrawPixel(x0, y0, colorIndex);
		}
	}
}

void DrawTime(CTime* pTime, int x, int y)
{
	float radians;
	int x2, y2;
	
	//int secondHandRotation = (pTime->Seconds * 6) - 90;
	//radians = secondHandRotation * (PI / 180);
	//x2 = x + cos(radians) * 5;
	//y2 = y + sin(radians) * 5;
	//DrawLine(x, y, x2, y2, 3);
	
	int minuteHandRotation = (pTime->Minutes * 6) - 90;
	radians = minuteHandRotation * (PI / 180);
	x2 = x + cos(radians) * 5;
	y2 = y + sin(radians) * 5;
	DrawLine(x, y, x2, y2, 3);
	
	int hourHandRotation = (pTime->Hours * 30) + (pTime->Minutes * 0.5) - 90;
	radians = hourHandRotation * (PI / 180);
	x2 = x + cos(radians) * 4;
	y2 = y + sin(radians) * 4;
	DrawLine(x, y, x2, y2, 3);
}

void dmaTransfer(uint8 channel, const void* src, void* dest, uint32 size, uint32 mode)
{
	DMA_CR(channel) = 0;
	DMA_SRC(channel) = (uint32)src;
	DMA_DEST(channel) = (uint32)dest;
	DMA_CR(channel) = (size | mode);
};

void ClearBG(int bg, bool sub)
{
	switch(bg)
	{
		case 0:
			dmaFillHalfWords(0, (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)), 2048);
			break;
		case 1:
			dmaFillHalfWords(0, (sub ? BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB) : BG_MAP_RAM(BG1_MAP_BASE)), 2048);
			break;
		case 2:
			dmaFillHalfWords(0, (sub ? BG_MAP_RAM_SUB(BG2_MAP_BASE_SUB) : BG_MAP_RAM(BG2_MAP_BASE)), 2048);
			break;
		case 3:
			dmaFillHalfWords(0, (sub ? BG_MAP_RAM_SUB(BG3_MAP_BASE_SUB) : BG_MAP_RAM(BG3_MAP_BASE)), 2048);
			break;
	}
}
