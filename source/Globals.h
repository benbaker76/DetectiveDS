#include "TDG.h"
#include <maxmod9.h>

#include "soundbank_bin.h"
#include "soundbank.h"

#ifndef __GLOBALS_H__
#define __GLOBALS_H__
typedef struct
{
	int Width;
	int Height;
	const u32* pTiles;
	u32 TilesLen;
	const u16* pMap;
	u32 MapLen;
	const u16* pPalette;
	u32 PaletteLen;	
} MAP, *PMAP;

typedef struct
{
	int X;
	int Y;
	int Width;
	int Height;
} RECT, *PRECT;

typedef struct
{
	int X;
	int Y;
} POINT, *PPOINT;

enum DirectionType
{
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
};

#endif

bool IsRectEmpty(PRECT pRect);
bool IntersectRect(PRECT pRectA, PRECT pRectB);
void PrintRect(PRECT pRect);

extern const u32 g_snideHeadFrames[];
extern const u32 g_snideBodyFrames[];
extern const u32 g_reverendHeadFrames[];
extern const u32 g_reverendBodyFrames[];
extern const u32 g_bentleyHeadFrames[];
extern const u32 g_bentleyBodyFrames[];
extern const u32 g_cookHeadFrames[];
extern const u32 g_cookBodyFrames[];
extern const u32 g_gabrielHeadFrames[];
extern const u32 g_gabrielBodyFrames[];
extern const u32 g_cynthiaHeadFrames[];
extern const u32 g_cynthiaBodyFrames[];
extern const u32 g_professorHeadFrames[];
extern const u32 g_professorBodyFrames[];
extern const u32 g_doctorHeadFrames[];
extern const u32 g_doctorBodyFrames[];
extern const u32 g_majorHeadFrames[];
extern const u32 g_majorBodyFrames[];
extern const u32 g_dingleHeadFrames[];
extern const u32 g_dingleBodyFrames[];
extern const u32 g_angusHeadFrames[];
extern const u32 g_angusBodyFrames[];

extern MAP g_cellarMap;
extern MAP g_clockMap;
extern MAP g_drawingMap;
extern MAP g_hall1Map;
extern MAP g_hall2Map;
extern MAP g_hall3Map;
extern MAP g_hall4Map;
extern MAP g_kitchenMap;
extern MAP g_landingMap;
extern MAP g_libraryMap;
extern MAP g_outside1Map;
extern MAP g_outside2Map;
extern MAP g_passage1Map;
extern MAP g_passage2Map;
extern MAP g_room1Map;
extern MAP g_room2Map;
extern MAP g_stairsMap;
extern MAP g_studyMap;
extern MAP g_gardenMap;
extern MAP g_graveyardMap;

extern MAP g_landing_front1Map;
extern MAP g_landing_front2Map;
extern MAP g_outside2_frontMap;
extern MAP g_stairs_frontMap;
extern MAP g_garden_frontMap;
extern MAP g_graveyard_frontMap;

extern mm_sound_effect g_sfx_footsteps;
extern mm_sound_effect g_sfx_opendoor;
extern mm_sound_effect g_sfx_closedoor;
