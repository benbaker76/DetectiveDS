#include <maxmod9.h>

//#include "soundbank_bin.h"
#include "soundbank.h"

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

struct Map
{
	Map(int width, int height, const u32* ptiles, u32 tilesLen, const u16* pmap, u32 mapLen, const u16* ppalette, u32 paletteLen) : Width(width), Height(height), pTiles(ptiles), TilesLen(tilesLen), pMap(pmap), MapLen(mapLen), pPalette(ppalette), PaletteLen(paletteLen) {}
	Map(int width, int height, const u32* ptiles, u32 tilesLen, const u16* pmap, u32 mapLen) : Width(width), Height(height), pTiles(ptiles), TilesLen(tilesLen), pMap(pmap), MapLen(mapLen) {}
	int Width;
	int Height;
	const u32* pTiles;
	u32 TilesLen;
	const u16* pMap;
	u32 MapLen;
	const u16* pPalette;
	u32 PaletteLen;	
};

struct Rect
{
	Rect() : X(0), Y(0), Width(0), Height(0) {}
	Rect(int x, int y, int width, int height) : X(x), Y(y), Width(width), Height(height) {}
	int X;
	int Y;
	int Width;
	int Height;
};

struct Point
{
	Point() : X(0), Y(0) {}
	Point(int x, int y) : X(x), Y(y) {}
	int X;
	int Y;
};

struct PointF
{
	PointF() : X(0), Y(0) {}
	PointF(int x, int y) : X(x), Y(y) {}
	float X;
	float Y;
};

struct Size
{
	Size() : Width(0), Height(0) {}
	Size(int width, int height) : Width(width), Height(height) {}
	int Width;
	int Height;
};

enum DirectionType
{
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
};

#endif

bool IsRectEmpty(Rect* pRect);
bool IntersectRect(Rect* pRectA, Rect* pRectB);
void PrintRect(Rect* pRect);
float RandomFloat(float min, float max);
int RandomInt(int min, int max);
DirectionType GetDirection(Point* startPoint, Point* endPoint);
void PrintDirection(DirectionType directionType);

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
extern const u32 g_questionFrames[];

extern Map* g_angus_landingMap;
extern Map* g_angus_room1Map;
extern Map* g_angus_room2Map;
extern Map* g_angus_secretMap;
extern Map* g_angus_stairsMap;
extern Map* g_cellarMap;
extern Map* g_clockMap;
extern Map* g_courtyardMap;
extern Map* g_diningMap;
extern Map* g_drawingMap;
extern Map* g_gardenMap;
extern Map* g_graveyardMap;
extern Map* g_hall1Map;
extern Map* g_hall2Map;
extern Map* g_hall3Map;
extern Map* g_hall4Map;
extern Map* g_kitchenMap;
extern Map* g_landingMap;
extern Map* g_libraryMap;
extern Map* g_outside1Map;
extern Map* g_outside2Map;
extern Map* g_passage1Map;
extern Map* g_passage2Map;
extern Map* g_bentleyMap;
extern Map* g_cookMap;
extern Map* g_cynthiaMap;
extern Map* g_dingleMap;
extern Map* g_doctorMap;
extern Map* g_gabrielMap;
extern Map* g_majorMap;
extern Map* g_professorMap;
extern Map* g_reverendMap;
extern Map* g_snideMap;
extern Map* g_stairsMap;
extern Map* g_studyMap;
extern Map* g_laundryMap;
extern Map* g_sewersMap;

extern Map* g_angus_landing_frontMap;
extern Map* g_angus_room_frontMap;
extern Map* g_angus_secret_frontMap;
extern Map* g_courtyard_frontMap;
extern Map* g_dining_frontMap;
extern Map* g_garden_frontMap;
extern Map* g_graveyard_frontMap;
extern Map* g_landing_front1Map;
extern Map* g_landing_front2Map;
extern Map* g_outside2_frontMap;
extern Map* g_stairs_frontMap;

extern mm_sound_effect g_sfx_footsteps[];
extern mm_sound_effect g_sfx_opendoor;
extern mm_sound_effect g_sfx_closedoor;
extern mm_sound_effect g_sfx_secretdoor;
extern mm_sound_effect g_sfx_drain;
extern mm_sound_effect g_sfx_gate;
extern mm_sound_effect g_sfx_unlock;
extern mm_sound_effect g_sfx_keydrop;
extern mm_sound_effect g_sfx_click;
extern mm_sound_effect g_sfx_beep;
extern mm_sound_effect g_sfx_ghostly;
extern mm_sound_effect g_sfx_howling;
extern mm_sound_effect g_sfx_timewarp;
extern mm_sound_effect g_sfx_magic;
extern mm_sound_effect g_sfx_clock_tick;
extern mm_sound_effect g_sfx_clock_chime;
extern mm_sound_effect g_sfx_fireplace;
extern mm_sound_effect g_sfx_vacuum;
extern mm_sound_effect g_sfx_bomb;
extern mm_sound_effect g_sfx_gunshot;
extern mm_sound_effect g_sfx_waterdrip;
extern mm_sound_effect g_sfx_glass;

extern u16 g_lightningBgPal[];
extern u16 g_lightningSpritePal[];
extern u16 g_c64Pal[];

