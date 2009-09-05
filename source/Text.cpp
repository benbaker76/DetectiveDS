#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TDG.h"
#include "lz77.h"

const char* g_snideText = "INSPECTOR SNIDE:\nSCOTLAND YARD\nDETECTIVE PLAYED BY\nYOURSELF.";
const char* g_reverandText = "REVERAND WRINKLEBUM:\nLOCAL VICAR WHOSE\nWIFE DISSAPEARED IN\nMYSTERIOUS\nCIRCUMSTANCES";
const char* g_bentleyText = "BENTLEY THE BUTLER:\nLIFELONG SERVANT TO\nTHE MCFUNGUS FAMILY.\nEXHIBITS SLIGHTLY\nHOSTILE BEHAVIOR..";
const char* g_cookText = "HILDA CRUMBLE:\nFAMILY COOK.\nNOTORIOUS FOR HER\nMACARONI  CHEESE.";
const char* g_gabrielText = "GABRIEL GASBAG:\nTHE MAID. OBEDIENT\nAND AGREEABLE, BUT\nNOT VERY BRIGHT.";
const char* g_cynthiaText = "CYNTHIA SLUDGEBUCKET:\nARROGANT AND SELF\nCENTRED DAUGHTER OF\nTHE MAJOR.";
const char* g_professorText = "PROFESSOR BULL:\nOLD FRIEND OF THE\nLATE MR. MCFUNGUS.\nSCATTERBRAINED AND\nCOMPLETELY MAD.";
const char* g_doctorText = "DOCTOR MORTEM:\nSHORTSIGHTED FAMILY\nDOCTOR.";
const char* g_majorText = "MAJOR SLUDGEBUCKET:\nRETIRED MAJOR.\nDISTURBED BUT\nHARMLESS.";
const char* g_dingleText = "MR DINGLE:\nFAMILY SOLICITOR.\nHERE TO READ THE\nWILL.";

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
	"NOTHING HERE",
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
	"STABBED DOCTOR!",
	"",
	"",
	"",
	"ANGUS MCFUNGUS' HEADSTONE",
	"A HEADSTONE"
};

const char* g_iconName[] =
{
	"NONE",
	"OPEN",
	"EXAMINE",
	"INVENTORY",
	"DROP",
	"SAVE",
	"LOAD",
	"SHOOT",
	"ACCUSE",
	"DOOR_OPEN",
	"DOOR_CLOSE",
	"USE_KEY",
	"QUESTION",
	"READ",
	"CONSUME",
	"USE",
	"TIME",
	"PLACE",
	"BAG"
};

const char* g_roomName[] =
{
	"YOU ARE IN\nYOUR ROOM.",
	"YOU ARE IN\nTHE REVEREND'S ROOM.",
	"YOU ARE IN\nBENTLEY'S ROOM.",
	"YOU ARE IN\nCOOK'S ROOM.",
	"YOU ARE IN\nGABRIEL'S ROOM.",
	"YOU ARE IN\nCYNTHIA'S ROOM.",
	"YOU ARE IN\nTHE PROFESSOR'S ROOM.",
	"YOU ARE IN\nTHE DOCTOR'S ROOM.",
	"YOU ARE IN\nTHE MAJOR'S ROOM.",
	"YOU ARE IN\nDINGLE'S ROOM.",
	"",										// Outside 1
	"",										// Outside 2
	"",										// Outside 3
	"",										// Outside 4
	"YOU ARE\nOUTSIDE",						// Passage 1
	"",										// Passage 2
	"",										// Passage 3
	"",										// Hall 1
	"",										// Hall 2
	"",										// Hall 3
	"",										// Hall 4
	"YOU ARE ON THE\nLANDING.",
	"YOU ARE IN\nTHE KITCHEN",
	"YOU ARE IN\nTHE HALL",
	"YOU ARE IN\nTHE STUDY",
	"",										// Clock
	"YOU ARE IN\nTHE CELLAR",
	"YOU ARE IN\nTHE DRAWING ROOM",
	"YOU ARE IN\nTHE LIBRARY",
	"YOU ARE IN\nTHE GARDEN",
	"YOU ARE IN\nTHE GRAVEYARD"
};

const char* g_KeyboardText[] =
{
	"    1 2 3 4 5 6 7 8 9 0 EXIT    ",
	"                                ",
	"    Q W E R T Y U I O P BKSP    ",
	"                                ",
	"     A S D F G H J K L ENTER    ",
	"                                ",
	"      Z X C V B N M  SPACE      "
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

void DrawChar(char c, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)) + (x + y * 32);
	
	*pMap = c - 0x20;
}

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

void DrawCharLarge(char c, int x, int y, bool sub)
{
	u16* pMap = (sub ? BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB) : BG_MAP_RAM(BG0_MAP_BASE)) + (x + y * 32);
	
	*pMap = 96 * 2 + g_largeTextMap[c - 0x20] * 2;
	*(pMap+32) = 96 * 2 + g_largeTextMap[c - 0x20] * 2 + 1;
}


