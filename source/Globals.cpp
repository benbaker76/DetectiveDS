#include <stdio.h>
#include "TDG.h"

bool IsRectEmpty(Rect* pRect)
{
	if(pRect == NULL)
		return true;
	
	return ((pRect->X == 0) && (pRect->Y == 0) && (pRect->Width == 0) && (pRect->Height == 0));
}

bool IntersectRect(Rect* pRectA, Rect* pRectB)
{
	if(pRectA == NULL || pRectB == NULL)
		return false;

	return ((pRectA->X < pRectB->X + pRectB->Width) && (pRectA->X + pRectA->Width > pRectB->X) && (pRectA->Y < pRectB->Y + pRectB->Height) && (pRectA->Y + pRectA->Height > pRectB->Y));
}

void PrintRect(Rect* pRect)
{
	if(pRect == NULL)
		return;
	
	static char buf[256];
	sprintf(buf, "X:%d, Y:%d, Width:%d, Height:%d", pRect->X, pRect->Y, pRect->Width, pRect->Height);
	fprintf(stderr, buf);
}

const u32 g_snideHeadFrames[] = { FRAME_WAITING | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK | FRAME_DOWN, FRAME_RIGHT, FRAME_UP, FRAME_LEFT, FRAME_DEAD, FRAME_BOMB, FRAME_GREEN_SPEAK, FRAME_GREEN_SPEAK, FRAME_GREEN_SPEAK, FRAME_GREEN_SPEAK | FRAME_GREEN_DOWN, FRAME_GREEN_RIGHT, FRAME_GREEN_UP, FRAME_GREEN_LEFT };
const u32 g_snideBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_DOWN | FRAME_GREEN_DOWN, FRAME_DOWN | FRAME_GREEN_DOWN, FRAME_DOWN | FRAME_GREEN_DOWN, FRAME_DOWN | FRAME_GREEN_DOWN, FRAME_RIGHT | FRAME_GREEN_RIGHT, FRAME_RIGHT | FRAME_GREEN_RIGHT, FRAME_RIGHT | FRAME_GREEN_RIGHT, FRAME_RIGHT | FRAME_GREEN_RIGHT, FRAME_UP | FRAME_GREEN_UP, FRAME_UP | FRAME_GREEN_UP, FRAME_UP | FRAME_GREEN_UP, FRAME_UP | FRAME_GREEN_UP, FRAME_LEFT | FRAME_GREEN_LEFT, FRAME_LEFT | FRAME_GREEN_LEFT, FRAME_LEFT | FRAME_GREEN_LEFT, FRAME_LEFT | FRAME_GREEN_LEFT, FRAME_DEAD, FRAME_BOMB };
const u32 g_reverendHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const u32 g_reverendBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const u32 g_bentleyHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const u32 g_bentleyBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const u32 g_cookHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const u32 g_cookBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const u32 g_gabrielHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_gabrielBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_cynthiaHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_cynthiaBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_professorHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_professorBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_doctorHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_doctorBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_majorHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const u32 g_majorBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const u32 g_dingleHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK | FRAME_ATTACK | FRAME_SURRENDER, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_dingleBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD, FRAME_ATTACK, FRAME_SURRENDER };
const u32 g_angusHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const u32 g_angusBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const u32 g_questionFrames[] = { FRAME_QUESTION, FRAME_QUESTION, FRAME_QUESTION, FRAME_QUESTION, FRAME_QUESTION, FRAME_QUESTION, FRAME_QUESTION, FRAME_QUESTION };

Map* g_angus_landingMap = new Map(320, 256, map_angus_landingTiles, map_angus_landingTilesLen, map_angus_landingMap, map_angus_landingMapLen, map_angus_landingPal, map_angus_landingPalLen);
Map* g_angus_room1Map = new Map(320, 256, map_angus_room1Tiles, map_angus_room1TilesLen, map_angus_room1Map, map_angus_room1MapLen, map_angus_room1Pal, map_angus_room1PalLen);
Map* g_angus_room2Map = new Map(320, 256, map_angus_room2Tiles, map_angus_room2TilesLen, map_angus_room2Map, map_angus_room2MapLen, map_angus_room2Pal, map_angus_room2PalLen);
Map* g_angus_secretMap = new Map(256, 256, map_angus_secretTiles, map_angus_secretTilesLen, map_angus_secretMap, map_angus_secretMapLen, map_angus_secretPal, map_angus_secretPalLen);
Map* g_angus_stairsMap = new Map(256, 256, map_angus_stairsTiles, map_angus_stairsTilesLen, map_angus_stairsMap, map_angus_stairsMapLen, map_angus_stairsPal, map_angus_stairsPalLen);
Map* g_cellarMap = new Map(400, 256, map_cellarTiles, map_cellarTilesLen, map_cellarMap, map_cellarMapLen, map_cellarPal, map_cellarPalLen);
Map* g_clockMap = new Map(304, 256, map_clockTiles, map_clockTilesLen, map_clockMap, map_clockMapLen, map_clockPal, map_clockPalLen);
Map* g_courtyardMap = new Map(552, 256, map_courtyardTiles, map_courtyardTilesLen, map_courtyardMap, map_courtyardMapLen, map_courtyardPal, map_courtyardPalLen);
Map* g_diningMap = new Map(352, 192, map_diningTiles, map_diningTilesLen, map_diningMap, map_diningMapLen, map_diningPal, map_diningPalLen);
Map* g_drawingMap = new Map(640, 256, map_drawingTiles, map_drawingTilesLen, map_drawingMap, map_drawingMapLen, map_drawingPal, map_drawingPalLen);
Map* g_gardenMap = new Map(304, 256, map_gardenTiles, map_gardenTilesLen, map_gardenMap, map_gardenMapLen, map_gardenPal, map_gardenPalLen);
Map* g_graveyardMap = new Map(304, 256, map_graveyardTiles, map_graveyardTilesLen, map_graveyardMap, map_graveyardMapLen, map_graveyardPal, map_graveyardPalLen);
Map* g_hall1Map = new Map(832, 256, map_hall1Tiles, map_hall1TilesLen, map_hall1Map, map_hall1MapLen, map_hall1Pal, map_hall1PalLen);
Map* g_hall2Map = new Map(832, 256, map_hall2Tiles, map_hall2TilesLen, map_hall2Map, map_hall2MapLen, map_hall2Pal, map_hall2PalLen);
Map* g_hall3Map = new Map(832, 256, map_hall3Tiles, map_hall3TilesLen, map_hall3Map, map_hall3MapLen, map_hall3Pal, map_hall3PalLen);
Map* g_hall4Map = new Map(544, 256, map_hall4Tiles, map_hall4TilesLen, map_hall4Map, map_hall4MapLen, map_hall4Pal, map_hall4PalLen);
Map* g_kitchenMap = new Map(536, 256, map_kitchenTiles, map_kitchenTilesLen, map_kitchenMap, map_kitchenMapLen, map_kitchenPal, map_kitchenPalLen);
Map* g_landingMap = new Map(400, 256, map_landingTiles, map_landingTilesLen, map_landingMap, map_landingMapLen, map_landingPal, map_landingPalLen);
Map* g_libraryMap = new Map(416, 256, map_libraryTiles, map_libraryTilesLen, map_libraryMap, map_libraryMapLen, map_libraryPal, map_libraryPalLen);
Map* g_outside1Map = new Map(400, 256, map_outside1Tiles, map_outside1TilesLen, map_outside1Map, map_outside1MapLen, map_outside1Pal, map_outside1PalLen);
Map* g_outside2Map = new Map(544, 256, map_outside2Tiles, map_outside2TilesLen, map_outside2Map, map_outside2MapLen, map_outside2Pal, map_outside2PalLen);
Map* g_passage1Map = new Map(256, 256, map_passage1Tiles, map_passage1TilesLen, map_passage1Map, map_passage1MapLen, map_passage1Pal, map_passage1PalLen);
Map* g_passage2Map = new Map(256, 256, map_passage2Tiles, map_passage2TilesLen, map_passage2Map, map_passage2MapLen, map_passage2Pal, map_passage2PalLen);

Map* g_cynthiaMap = new Map(400, 256, map_cynthiaTiles, map_cynthiaTilesLen, map_cynthiaMap, map_cynthiaMapLen, map_cynthiaPal, map_cynthiaPalLen);
Map* g_dingleMap = new Map(400, 256, map_dingleTiles, map_dingleTilesLen, map_dingleMap, map_dingleMapLen, map_dinglePal, map_dinglePalLen);
Map* g_doctorMap = new Map(400, 256, map_doctorTiles, map_doctorTilesLen, map_doctorMap, map_doctorMapLen, map_doctorPal, map_doctorPalLen);
Map* g_majorMap = new Map(400, 256, map_majorTiles, map_majorTilesLen, map_majorMap, map_majorMapLen, map_majorPal, map_majorPalLen);
Map* g_professorMap = new Map(400, 256, map_professorTiles, map_professorTilesLen, map_professorMap, map_professorMapLen, map_professorPal, map_professorPalLen);
Map* g_reverendMap = new Map(400, 256, map_reverendTiles, map_reverendTilesLen, map_reverendMap, map_reverendMapLen, map_reverendPal, map_reverendPalLen);
Map* g_snideMap = new Map(400, 256, map_snideTiles, map_snideTilesLen, map_snideMap, map_snideMapLen, map_snidePal, map_snidePalLen);
Map* g_bentleyMap = new Map(344, 256, map_bentleyTiles, map_bentleyTilesLen, map_bentleyMap, map_bentleyMapLen, map_bentleyPal, map_bentleyPalLen);
Map* g_cookMap = new Map(344, 256, map_cookTiles, map_cookTilesLen, map_cookMap, map_cookMapLen, map_cookPal, map_cookPalLen);
Map* g_gabrielMap = new Map(344, 256, map_gabrielTiles, map_gabrielTilesLen, map_gabrielMap, map_gabrielMapLen, map_gabrielPal, map_gabrielPalLen);

Map* g_stairsMap = new Map(416, 256, map_stairsTiles, map_stairsTilesLen, map_stairsMap, map_stairsMapLen, map_stairsPal, map_stairsPalLen);
Map* g_studyMap = new Map(320, 256, map_studyTiles, map_studyTilesLen, map_studyMap, map_studyMapLen, map_studyPal, map_studyPalLen);
Map* g_utilityMap = new Map(296, 256, map_utilityTiles, map_utilityTilesLen, map_utilityMap, map_utilityMapLen, map_utilityPal, map_utilityPalLen);

Map* g_angus_landing_frontMap = new Map(320, 192, map_angus_landing_frontTiles, map_angus_landing_frontTilesLen, map_angus_landing_frontMap, map_angus_landing_frontMapLen);
Map* g_angus_room_frontMap = new Map(320, 192, map_angus_room_frontTiles, map_angus_room_frontTilesLen, map_angus_room_frontMap, map_angus_room_frontMapLen);
Map* g_angus_secret_frontMap = new Map(256, 192, map_angus_secret_frontTiles, map_angus_secret_frontTilesLen, map_angus_secret_frontMap, map_angus_secret_frontMapLen);
Map* g_courtyard_frontMap = new Map(552, 192, map_courtyard_frontTiles, map_courtyard_frontTilesLen, map_courtyard_frontMap, map_courtyard_frontMapLen);
Map* g_dining_frontMap = new Map(352, 192, map_dining_frontTiles, map_dining_frontTilesLen, map_dining_frontMap, map_dining_frontMapLen);
Map* g_garden_frontMap = new Map(304, 192, map_garden_frontTiles, map_garden_frontTilesLen, map_garden_frontMap, map_garden_frontMapLen);
Map* g_graveyard_frontMap = new Map(304, 192, map_graveyard_frontTiles, map_graveyard_frontTilesLen, map_graveyard_frontMap, map_graveyard_frontMapLen);
Map* g_landing_front1Map = new Map(400, 192, map_landing_front1Tiles, map_landing_front1TilesLen, map_landing_front1Map, map_landing_front1MapLen);
Map* g_landing_front2Map = new Map(400, 192, map_landing_front2Tiles, map_landing_front2TilesLen, map_landing_front2Map, map_landing_front2MapLen);
Map* g_outside2_frontMap = new Map(544, 192, map_outside2_frontTiles, map_outside2_frontTilesLen, map_outside2_frontMap, map_outside2_frontMapLen);
Map* g_stairs_frontMap = new Map(416, 192, map_stairs_frontTiles, map_stairs_frontTilesLen, map_stairs_frontMap, map_stairs_frontMapLen);

mm_sound_effect g_sfx_footsteps = { { SFX_FOOTSTEPS } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_opendoor = { { SFX_OPENDOOR } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_closedoor = { { SFX_CLOSEDOOR } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_secretdoor = { { SFX_SECRETDOOR } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_drain = { { SFX_DRAIN } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_gate = { { SFX_GATE } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_unlock = { { SFX_UNLOCK } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_keydrop = { { SFX_KEYDROP } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_click = { { SFX_CLICK } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_beep = { { SFX_BEEP } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_ghostly = { { SFX_GHOSTLY } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_howling = { { SFX_HOWLING } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_timewarp = { { SFX_TIMEWARP } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_magic = { { SFX_MAGIC } , (int)(1.0f * (1<<10)), 0, 255, 127 };

u16 g_lightningBgPal[] =
{
	0x7c1f,0x5efb,0x7fff,0x140f,0x1c15,0x307f,0x51df,0x7fff,
	0x7fff,0x7fff,0x7fff,0x7fff,0x5e7f,0x7fff,0x7fff,0x7fff,
	0x7fff,0x7fff,0x7fff,0x5e76,0x6f1a,0x7fff,0x3d2c,0x7fff,
	0x7fff,0x7fff,0x7b9d,0x7fff,0x72fa,0x4129,0x7fff,0x7bbd,
	0x6a95,0x7fff,0x7fff,0x59ce,0x7fff,0x7fff,0x5104,0x7fff,
	0x7fff,0x7fff,0x7b9c,0x7270,0x7fff,0x7fff,0x6ab4,0x7fff,
	0x7bdd,0x7fff,0x7fff,0x622f,0x7359,0x7fff,0x7fff,0x7fff,
	0x7fff,0x7fff,0x7fff,0x7fff,0x2d48,0x7fff,0x3daa,0x7fff,
	0x7fff,0x5eb2,0x739b,0x7fff,0x2505,0x524e,0x7fff,0x6b37,
	0x7fff,0x7fff,0x7fff,0x7fff,0x7fff,0x7fff,0x739a,0x7fff,
	0x7fff,0x7fff,0x7fff,0x7fff,0x4e2c,0x7fff,0x7fff,0x734e,
	0x7fff,0x7bda,0x7fff,0x7fff,0x6f05,0x7fff,0x7fff,0x7fff,
	0x77b8,0x7fff,0x6f71,0x6b4a,0x7ffd,0x1f06,0x7fff,0x5bb6,
	0x7fff,0x11e4,0x374c,0x42f0,0x77fd,0x7fff,0x7fff,0x4b92,
	0x7fff,0x18e6,0x6b9a,0x7fff,0x7fff,0x7fff,0x7fff,0x1daa,
	0x7fff,0x77de,0x7fff,0x679b,0x7fff,0x4f37,0x7fff,0x7fff,
	0x32d1,0x7fff,0x7fff,0x7fff,0x6b9c,0x7fff,0x3bfe,0x7fff,
	0x67ff,0x7fff,0x7fff,0x7fff,0x6fff,0x52b5,0x7fff,0x7fff,
	0x7fff,0x7fff,0x7fff,0x431a,0x679d,0x7fff,0x2276,0x7fff,
	0x7fff,0x7fff,0x4f3b,0x7fff,0x7fff,0x7fff,0x7fff,0x2eb9,
	0x7fff,0x7fff,0x7fff,0x7fff,0x0e9d,0x7fff,0x7fff,0x7fff,
	0x7fff,0x7fff,0x7fff,0x6b9e,0x7fff,0x7fff,0x7fff,0x7fff,
	0x7fff,0x7fff,0x7fff,0x431f,0x7fff,0x7fff,0x7fff,0x46b9,
	0x7fff,0x7fff,0x3657,0x7fff,0x6bbf,0x7fff,0x150b,0x677c,
	0x73be,0x7fff,0x7fff,0x4298,0x21d3,0x7fff,0x7fff,0x7fff,
	0x5f3b,0x7fff,0x7fff,0x7fff,0x14af,0x2117,0x463a,0x5adc,
	0x7fff,0x6b5d,0x56bd,0x7fff,0x7fff,0x7fff,0x7fff,0x7fff,
	0x7fff,0x7fff,0x7fff,0x7fff,0x5adf,0x7fff,0x7fff,0x7fff,
	0x7fff,0x7fff,0x7fff,0x7fff,0x7fff,0x0000,0x318c,0x4210,
	0x5294,0x6318,0x739c,0x7fff,0x7fff,0x7fff,0x7fff,0x7fff,
	0x7fff,0x7fff,0x7fff,0x7fff,0x7fff,0x0000,0x7fff,0x7fff,
	0x7fff,0x7fff,0x7fff,0x7fff,0x7fff,0x7fff,0x7fff,0x7fff
};

u16 g_lightningSpritePal[] =
{
	0x7c1f,0x4638,0x7fff,0x100c,0x1811,0x241b,0x38bf,0x7fff,
	0x5e7f,0x77bf,0x7fff,0x7fff,0x453f,0x7fff,0x7fff,0x7fff,
	0x5efc,0x7fff,0x7fff,0x51b2,0x5e55,0x773b,0x30ea,0x7fff,
	0x7bbe,0x7fff,0x6e98,0x7fff,0x6615,0x34e7,0x7fff,0x6ad6,
	0x59cf,0x7fff,0x7fff,0x4d4a,0x7fff,0x7fff,0x40c3,0x7fff,
	0x7fff,0x7b9b,0x76b2,0x6da9,0x7fff,0x7fff,0x5e0d,0x7fff,
	0x6ed5,0x777a,0x7fff,0x5589,0x6672,0x7bbd,0x7fff,0x7fff,
	0x7358,0x7fff,0x7fff,0x7fff,0x2506,0x7fff,0x3168,0x7fff,
	0x6b38,0x4e4d,0x62f4,0x739b,0x1cc4,0x41eb,0x7fff,0x5a91,
	0x7fff,0x7fff,0x7fff,0x6b37,0x7ffe,0x779b,0x62f4,0x7fff,
	0x7fff,0x7bdd,0x7fff,0x7fff,0x3dc9,0x7fff,0x7fff,0x6f07,
	0x7fff,0x7770,0x7bdb,0x7fff,0x5a63,0x7fff,0x7fff,0x7fff,
	0x6f70,0x7bdb,0x674a,0x5ee6,0x7394,0x1665,0x7fff,0x3b6e,
	0x6bda,0x0d83,0x1f26,0x2e8b,0x5394,0x7fff,0x7fff,0x2f4b,
	0x7fff,0x14c5,0x4f33,0x6378,0x7fff,0x7fff,0x7fff,0x1568,
	0x7fff,0x5758,0x77de,0x4b36,0x7fff,0x36d2,0x7fff,0x6bbb,
	0x264e,0x7fff,0x7fff,0x6359,0x4b38,0x7fff,0x17fe,0x7fff,
	0x3bfe,0x63ff,0x7fff,0x7fff,0x43fe,0x4231,0x73ff,0x7fff,
	0x7fff,0x7fff,0x7fff,0x2ab8,0x473a,0x7fff,0x1a12,0x639d,
	0x7fff,0x7fff,0x32d9,0x5f7c,0x7fff,0x7fff,0x7fff,0x1e56,
	0x7fff,0x7fff,0x73be,0x7fff,0x0619,0x7fff,0x7fff,0x7fff,
	0x7fff,0x7fff,0x6fbf,0x3f1d,0x7fff,0x7fff,0x7fff,0x7fff,
	0x7fff,0x7fff,0x7fff,0x1e9f,0x6fbf,0x575f,0x635c,0x2e36,
	0x7fff,0x7fff,0x25f4,0x7fff,0x3f1f,0x73be,0x10e9,0x4ad9,
	0x56fa,0x7fff,0x7fff,0x2e15,0x1d6f,0x7fff,0x635b,0x7fff,
	0x4298,0x6f9d,0x7fff,0x77df,0x108c,0x1cf2,0x2957,0x3df9,
	0x5efb,0x4a5a,0x35bb,0x6b5c,0x7fff,0x5adc,0x6b5d,0x7fff,
	0x7fff,0x631d,0x7fff,0x7fff,0x319f,0x7fff,0x7fff,0x7fff,
	0x7fff,0x7fff,0x7fff,0x5eff,0x7fff,0x0000,0x294a,0x318c,
	0x4210,0x4e73,0x5ef7,0x6f7b,0x7bde,0x7fff,0x7fff,0x7fff,
	0x7fff,0x7fff,0x7fff,0x7fff,0x7fff,0x0000,0x7fff,0x7fff,
	0x6739,0x4e7f,0x4ff3,0x4fff,0x7e73,0x7fff,0x7ff3,0x7fff
};

u16 g_c64Pal[] =
{
	0x0000,0x3c85,0x5d6d,0x5ead,0x4373,0x1e4a,0x3737,0x00c7,
	0x0d2e,0x10cd,0x2993,0x7fff,0x4e73,0x35ad,0x2108,0x0000
};

