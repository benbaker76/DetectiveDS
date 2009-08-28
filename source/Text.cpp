#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TDG.h"
#include "lz77.h"

const char* g_snideText[] =
{
	"INSPECTOR SNIDE:      ",
	"SCOTLAND YARD         ",
	"DETECTIVE PLAYED BY   ",
	"YOURSELF.             ",
	"                      "
};

const char* g_reverandText[] =
{
	"REVERAND WRINKLEBUM:  ",
	"LOCAL VICAR WHOSE     ",
	"WIFE DISSAPEARED IN   ",
	"MYSTERIOUS            ",
	"CIRCUMSTANCES         "
};

const char* g_bentleyText[] =
{
	"BENTLEY THE BUTLER:   ",
	"LIFELONG SERVANT TO   ",
	"THE MCFUNGUS FAMILY.  ",
	"EXHIBITS SLIGHTLY     ",
	"HOSTILE BEHAVIOR..    "
};

const char* g_cookText[] =
{
	"HILDA CRUMBLE:        ",
	"FAMILY COOK.          ",
	"NOTORIOUS FOR HER     ",
	"MACARONI  CHEESE.     ",
	"                      "
};



const char* g_gabrielText[] =
{
	"GABRIEL GASBAG:       ",
	"THE MAID. OBEDIENT    ",
	"AND AGREEABLE, BUT    ",
	"NOT VERY BRIGHT.      ",
	"                      "
};

const char* g_cynthiaText[] =
{
	"CYNTHIA SLUDGEBUCKET: ",
	"ARROGANT AND SELF     ",
	"CENTRED DAUGHTER OF   ",
	"THE MAJOR.            ",
	"                      "
};

const char* g_professorText[] =
{
	"PROFESSOR BULL:       ",
	"OLD FRIEND OF THE     ",
	"LATE MR. MCFUNGUS.    ",
	"SCATTERBRAINED AND    ",
	"COMPLETELY MAD.       "
};

const char* g_doctorText[] =
{
	"DOCTOR MORTEM:        ",
	"SHORTSIGHTED FAMILY   ",
	"DOCTOR.               ",
	"                      ",
	"                      "
};

const char* g_majorText[] =
{
	"MAJOR SLUDGEBUCKET:   ",
	"RETIRED MAJOR.        ",
	"DISTURBED BUT         ",
	"HARMLESS.             ",
	"                      "
};

const char* g_dingleText[] =
{
	"MR DINGLE:            ",
	"FAMILY SOLICITOR.     ",
	"HERE TO READ THE      ",
	"WILL.                 ",
	"                      "
};

const char* g_itemName[] =
{
	"NOTHING HERE",
	"A HOT WATER BOTTLE",
	"BLANK BULLETS",
	"A CANDLESTICK",
	"THE WILL;",
	"A KNIFE;",
	"NEWSPAPER CUTTING",
	"A NOTE;",
	"A SMALL BOTTLE",
	"A CRAVATE;",
	"A SOGGY ENVELOPE",
	"A LETTER",
	"SCALPELS",
	"A SYRINGE;",
	"A BOTTLE OF PILLS",
	"A HAMMER",
	"A BUNCH OF KEYS",
	"A BIG IRON KEY",
	"A SILVER TRAY",
	"A BOTTLE OF WINE",
	"A COMB",
	"A HARDBACK BOOK",
	"A FOLDED DOCUMENT;",
	"AN ELEPHANT GUN",
	"A DIARY",
	"A BLACK BAG",
	"COLOGNE",
	"A SMALL BOOK",
	"DIRTY PLATES",
	"A PICTURE",
	"A WAD OF NOTES",
	"A LOCKET",
	"A SCREWDRIVER",
	"AN OPEN LOCKET",
	"BROKEN PLATES",
	"BROKEN GLASS",
	"SHREDDED PAPER",
	"BOOKS",
	"BOOKS",
	"A LETTER OPENER",
	"A JACKET",
	"NOTEBOOKS",
	"PLANS",
	"A MIRROR",
	"CUTLERY",
	"A PIECE OF CARD",
	"A BRIEFCASE",
	"A FOLDER",
	"A PAPERWEIGHT",
	"PADDED ENVELOPES",
	"A BOMB!",
	"A SMALL KEY",
	"BULLETS"
};

const char* g_colName[] =
{
	"PATH",
	"DOOR1",
	"DOOR2",
	"DOOR3",
	"DOOR4",
	"DOOR5",
	"DOOR6",
	"DOOR7",
	"SECRET PASSAGE",
	"WALL",
	"DUMMY",
	"FOUR POSTER BED",
	"CHEST OF DRAWERS",
	"FIREPLACE",
	"COAL BUCKET",
	"PAINTING",
	"WOODEN BOX",
	"MICROWAVE",
	"SIDEBOARD",
	"CUPBOARD",
	"CUPBOARD",
	"CUPBOARD",
	"CUPBOARD",
	"SINK",
	"STAIRCASE",
	"BOOKCASE",
	"BOOKCASE",
	"BOXES",
	"BOXES",
	"BOXES",
	"BED",
	"CLOTHES CUPBOARD",
	"CLOCK",
	"WINDOW",
	"DESK",
	"SHELVES",
	"LOCKED WALL SAFE",
	"OPEN WALL SAFE",
	"DINGLE'S BODY!",
	"PIANO AND A SQUASHED CYNTHIA SLUDGEBUCKET!",
	"GABRIEL'S BODY!",
	"STABBED DOCTOR!"
};

const int g_largeTextMap[] =
{
	0x00,0x20,0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1F,0x1B,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1D,0x1E,0x00,0x00,0x00,0x00,
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

void DrawText(const char* string, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)) + (x + y * 32);
	
	for(u32 i=0; i<strlen(string); i++)
		*pMap++ = string[i] - 0x20;
}

void DrawTextLarge(const char* string, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)) + (x + y * 32);
	
	for(u32 i=0; i<strlen(string); i++)
	{	
		*pMap = 96 * 2 + g_largeTextMap[string[i] - 0x20] * 2;
		*(pMap+32) = 96 * 2 + g_largeTextMap[string[i] - 0x20] * 2 + 1;
		pMap++;
	}
}

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
	dmaCopy(watchPal, BG_PALETTE_SUB, watchPalLen);

	float radians;
	int x, y;
	
	int secondHandRotation = (pTime->Seconds * 6) - 90;
	radians = secondHandRotation * (PI / 180);
	x = 112 + cos(radians) * 8;
	y = 20 + sin(radians) * 8;
	DrawLine(112, 20, x, y, 15);
	
	int minuteHandRotation = (pTime->Minutes * 6) - 90;
	radians = minuteHandRotation * (PI / 180);
	x = 112 + cos(radians) * 8;
	y = 20 + sin(radians) * 8;
	DrawLine(112, 20, x, y, 15);
	
	int hourHandRotation = (pTime->Hours * 30) + (pTime->Minutes * 0.5) - 90;
	radians = hourHandRotation * (PI / 180);
	x = 112 + cos(radians) * 8;
	y = 20 + sin(radians) * 8;
	DrawLine(112, 20, x, y, 15);
}

