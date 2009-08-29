#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TDG.h"
#include "lz77.h"

void DrawPixel(int x, int y, int colorIndex)
{
	u16 tileId = *(BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB) + (x / 8) + (y / 8) * 32);
	u16* pTile = BG_TILE_RAM_SUB(BG1_TILE_BASE_SUB) + tileId * 32 + ((x % 8) / 2) + (y % 8) * 4;
	*pTile = ((x % 2) == 0 ? ((*pTile &~ 0xF) | colorIndex) : ((*pTile &~ 0x0F00) | (colorIndex << 8)));
}

void DrawPixelDouble(int x, int y, int colorIndex)
{
	u16 tileId = *(BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB) + (x / 8) + (y / 8) * 32);
	u16* pTile = BG_TILE_RAM_SUB(BG1_TILE_BASE_SUB) + tileId * 32 + ((x % 8) / 2) + (y % 8) * 4;
	*pTile = (colorIndex | colorIndex << 8);
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

void DrawTime(CTime* pTime)
{
	dmaCopy(watchTiles, BG_TILE_RAM_SUB(BG1_TILE_BASE_SUB), watchTilesLen);
	dmaCopy(watchMap, BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB), watchMapLen);
	//dmaCopy(watchPal, BG_PALETTE_SUB, watchPalLen);

	float radians;
	int x, y;
	
	int secondHandRotation = (pTime->Seconds * 6) - 90;
	radians = secondHandRotation * (PI / 180);
	x = 112 + cos(radians) * 8;
	y = 20 + sin(radians) * 8;
	DrawLine(112, 20, x, y, 3);
	
	int minuteHandRotation = (pTime->Minutes * 6) - 90;
	radians = minuteHandRotation * (PI / 180);
	x = 112 + cos(radians) * 8;
	y = 20 + sin(radians) * 8;
	DrawLine(112, 20, x, y, 3);
	
	int hourHandRotation = (pTime->Hours * 30) + (pTime->Minutes * 0.5) - 90;
	radians = hourHandRotation * (PI / 180);
	x = 112 + cos(radians) * 8;
	y = 20 + sin(radians) * 8;
	DrawLine(112, 20, x, y, 3);
}
