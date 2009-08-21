#include <nds.h>
#include <stdio.h>
#include "TDG.h"

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

void DrawText(const char* string, int x, int y, bool sub)
{
	u16* pMap = BG_MAP_RAM(BG0_MAP_BASE) + (x + y * 32);
	
	for(int i=0; i<strlen(string); i++)
		*pMap++ = string[i] - 0x20;
}

void DrawTextLarge(const char* string, int x, int y, bool sub)
{
	u16* pMap = BG_MAP_RAM(BG0_MAP_BASE) + (x + y * 32);
	
	for(int i=0; i<strlen(string); i++)
	{
		*pMap = string[i] * 2 - 0x20 + 96;
		*(pMap+32) = string[i] * 2 - 0x20 + 96 + 1;
		pMap++;
	}
}


