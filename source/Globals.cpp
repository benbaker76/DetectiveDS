#include <stdio.h>
#include "TDG.h"

bool IsRectEmpty(PRECT pRect)
{
	return (pRect->X == 0 && pRect->Y == 0 && pRect->Width == 0 && pRect->Height == 0);
}

bool IntersectRect(PRECT pRectA, PRECT pRectB)
{
	return (pRectA->X < pRectB->X + pRectB->Width && pRectA->X + pRectA->Width > pRectB->X && pRectA->Y < pRectB->Y + pRectB->Height && pRectA->Y + pRectA->Height > pRectB->Y);
}

void PrintRect(PRECT pRect)
{
	char buf[256];
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
const u32 g_cynthiaHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const u32 g_cynthiaBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const u32 g_professorHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_professorBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_doctorHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_doctorBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_majorHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT };
const u32 g_majorBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT };
const u32 g_dingleHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_dingleBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_angusHeadFrames[] = { FRAME_WAITING | FRAME_LEFT | FRAME_DOWN | FRAME_SPEAK, FRAME_SPEAK, FRAME_SPEAK, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };
const u32 g_angusBodyFrames[] = { FRAME_WAITING | FRAME_SPEAK | FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_LEFT | FRAME_DOWN, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_UP | FRAME_RIGHT, FRAME_DEAD };

MAP g_angus_landingMap = { 320, 248, map_angus_landingTiles, map_angus_landingTilesLen, map_angus_landingMap, map_angus_landingMapLen, map_angus_landingPal, map_angus_landingPalLen };
MAP g_angus_room1Map = { 320, 248, map_angus_room1Tiles, map_angus_room1TilesLen, map_angus_room1Map, map_angus_room1MapLen, map_angus_room1Pal, map_angus_room1PalLen };
MAP g_angus_room2Map = { 320, 248, map_angus_room2Tiles, map_angus_room2TilesLen, map_angus_room2Map, map_angus_room2MapLen, map_angus_room2Pal, map_angus_room2PalLen };
MAP g_angus_secretMap = { 256, 248, map_angus_secretTiles, map_angus_secretTilesLen, map_angus_secretMap, map_angus_secretMapLen, map_angus_secretPal, map_angus_secretPalLen };
MAP g_angus_stairsMap = { 256, 248, map_angus_stairsTiles, map_angus_stairsTilesLen, map_angus_stairsMap, map_angus_stairsMapLen, map_angus_stairsPal, map_angus_stairsPalLen };
MAP g_cellarMap = { 400, 248, map_cellarTiles, map_cellarTilesLen, map_cellarMap, map_cellarMapLen, map_cellarPal, map_cellarPalLen };
MAP g_clockMap = { 304, 248, map_clockTiles, map_clockTilesLen, map_clockMap, map_clockMapLen, map_clockPal, map_clockPalLen };
MAP g_courtyardMap = { 552, 248, map_courtyardTiles, map_courtyardTilesLen, map_courtyardMap, map_courtyardMapLen, map_courtyardPal, map_courtyardPalLen };
MAP g_drawingMap = { 640, 248, map_drawingTiles, map_drawingTilesLen, map_drawingMap, map_drawingMapLen, map_drawingPal, map_drawingPalLen };
MAP g_gardenMap = { 304, 248, map_gardenTiles, map_gardenTilesLen, map_gardenMap, map_gardenMapLen, map_gardenPal, map_gardenPalLen };
MAP g_graveyardMap = { 304, 248, map_graveyardTiles, map_graveyardTilesLen, map_graveyardMap, map_graveyardMapLen, map_graveyardPal, map_graveyardPalLen };
MAP g_hall1Map = { 832, 248, map_hall1Tiles, map_hall1TilesLen, map_hall1Map, map_hall1MapLen, map_hall1Pal, map_hall1PalLen };
MAP g_hall2Map = { 832, 248, map_hall2Tiles, map_hall2TilesLen, map_hall2Map, map_hall2MapLen, map_hall2Pal, map_hall2PalLen };
MAP g_hall3Map = { 832, 248, map_hall3Tiles, map_hall3TilesLen, map_hall3Map, map_hall3MapLen, map_hall3Pal, map_hall3PalLen };
MAP g_hall4Map = { 544, 248, map_hall4Tiles, map_hall4TilesLen, map_hall4Map, map_hall4MapLen, map_hall4Pal, map_hall4PalLen };
MAP g_kitchenMap = { 536, 248, map_kitchenTiles, map_kitchenTilesLen, map_kitchenMap, map_kitchenMapLen, map_kitchenPal, map_kitchenPalLen };
MAP g_landingMap = { 400, 248, map_landingTiles, map_landingTilesLen, map_landingMap, map_landingMapLen, map_landingPal, map_landingPalLen };
MAP g_libraryMap = { 416, 248, map_libraryTiles, map_libraryTilesLen, map_libraryMap, map_libraryMapLen, map_libraryPal, map_libraryPalLen };
MAP g_outside1Map = { 400, 248, map_outside1Tiles, map_outside1TilesLen, map_outside1Map, map_outside1MapLen, map_outside1Pal, map_outside1PalLen };
MAP g_outside2Map = { 544, 248, map_outside2Tiles, map_outside2TilesLen, map_outside2Map, map_outside2MapLen, map_outside2Pal, map_outside2PalLen };
MAP g_passage1Map = { 256, 248, map_passage1Tiles, map_passage1TilesLen, map_passage1Map, map_passage1MapLen, map_passage1Pal, map_passage1PalLen };
MAP g_passage2Map = { 256, 248, map_passage2Tiles, map_passage2TilesLen, map_passage2Map, map_passage2MapLen, map_passage2Pal, map_passage2PalLen };
MAP g_room1Map = { 400, 248, map_room1Tiles, map_room1TilesLen, map_room1Map, map_room1MapLen, map_room1Pal, map_room1PalLen };
MAP g_room2Map = { 344, 248, map_room2Tiles, map_room2TilesLen, map_room2Map, map_room2MapLen, map_room2Pal, map_room2PalLen };
MAP g_stairsMap = { 416, 248, map_stairsTiles, map_stairsTilesLen, map_stairsMap, map_stairsMapLen, map_stairsPal, map_stairsPalLen };
MAP g_studyMap = { 320, 248, map_studyTiles, map_studyTilesLen, map_studyMap, map_studyMapLen, map_studyPal, map_studyPalLen };
MAP g_utilityMap = { 280, 248, map_utilityTiles, map_utilityTilesLen, map_utilityMap, map_utilityMapLen, map_utilityPal, map_utilityPalLen };

MAP g_angus_landing_frontMap = { 320, 192, map_angus_landing_frontTiles, map_angus_landing_frontTilesLen, map_angus_landing_frontMap, map_angus_landing_frontMapLen };
MAP g_angus_room_frontMap = { 320, 192, map_angus_room_frontTiles, map_angus_room_frontTilesLen, map_angus_room_frontMap, map_angus_room_frontMapLen };
MAP g_angus_secret_frontMap = { 256, 192, map_angus_secret_frontTiles, map_angus_secret_frontTilesLen, map_angus_secret_frontMap, map_angus_secret_frontMapLen };
MAP g_courtyard_frontMap = { 552, 192, map_courtyard_frontTiles, map_courtyard_frontTilesLen, map_courtyard_frontMap, map_courtyard_frontMapLen };
MAP g_garden_frontMap = { 304, 192, map_garden_frontTiles, map_garden_frontTilesLen, map_garden_frontMap, map_garden_frontMapLen };
MAP g_graveyard_frontMap = { 304, 192, map_graveyard_frontTiles, map_graveyard_frontTilesLen, map_graveyard_frontMap, map_graveyard_frontMapLen };
MAP g_landing_front1Map = { 400, 192, map_landing_front1Tiles, map_landing_front1TilesLen, map_landing_front1Map, map_landing_front1MapLen };
MAP g_landing_front2Map = { 400, 192, map_landing_front2Tiles, map_landing_front2TilesLen, map_landing_front2Map, map_landing_front2MapLen };
MAP g_outside2_frontMap = { 544, 192, map_outside2_frontTiles, map_outside2_frontTilesLen, map_outside2_frontMap, map_outside2_frontMapLen };
MAP g_stairs_frontMap = { 416, 192, map_stairs_frontTiles, map_stairs_frontTilesLen, map_stairs_frontMap, map_stairs_frontMapLen };

mm_sound_effect g_sfx_footsteps = { { SFX_FOOTSTEPS } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_opendoor = { { SFX_OPENDOOR } , (int)(1.0f * (1<<10)), 0, 255, 127 };
mm_sound_effect g_sfx_closedoor = { { SFX_CLOSEDOOR } , (int)(1.0f * (1<<10)), 0, 255, 127 };

u16 g_lightningPal[] = {
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

