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

enum DirectionType
{
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
};

#endif

extern const int g_snideHeadFrames[];
extern const int g_snideBodyFrames[];
extern const int g_reverendHeadFrames[];
extern const int g_reverendBodyFrames[];
extern const int g_bentleyHeadFrames[];
extern const int g_bentleyBodyFrames[];
extern const int g_cookHeadFrames[];
extern const int g_cookBodyFrames[];
extern const int g_gabrielHeadFrames[];
extern const int g_gabrielBodyFrames[];
extern const int g_cynthiaHeadFrames[];
extern const int g_cynthiaBodyFrames[];
extern const int g_professorHeadFrames[];
extern const int g_professorBodyFrames[];
extern const int g_doctorHeadFrames[];
extern const int g_doctorBodyFrames[];
extern const int g_majorHeadFrames[];
extern const int g_majorBodyFrames[];
extern const int g_dingleHeadFrames[];
extern const int g_dingleBodyFrames[];
extern const int g_angusHeadFrames[];
extern const int g_angusBodyFrames[];

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
