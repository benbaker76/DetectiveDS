#include <nds.h>

enum CollisionType
{
	COL_NOTHING_HERE = 0,
	COL_DOOR1 = 1,
	COL_DOOR2 = 2,
	COL_DOOR3 = 3,
	COL_DOOR4 = 4,
	COL_DOOR5 = 5,
	COL_DOOR6 = 6,
	COL_DOOR7 = 7,
	COL_DOOR8 = 8,
	COL_WALL = 9,
	COL_DUMMY = 10,
	COL_FOUR_POSTER_BED = 11,
	COL_CHEST_OF_DRAWERS = 12,
	COL_FIREPLACE = 13,
	COL_COAL_BUCKET = 14,
	COL_PAINTING = 15,
	COL_WOODEN_BOX = 16,
	COL_MICROWAVE = 17,
	COL_SIDEBOARD = 18,
	COL_CUPBOARD1 = 19,
	COL_CUPBOARD2 = 20,
	COL_CUPBOARD3 = 21,
	COL_CUPBOARD4 = 22,
	COL_SINK = 23,
	COL_STAIRCASE = 24,
	COL_BOOKCASE1 = 25,
	COL_BOOKCASE2 = 26,
	COL_BOXES1 = 27,
	COL_BOXES2 = 28,
	COL_BOXES3 = 29,
	COL_BED = 30,
	COL_CLOTHES_CUPBOARD = 31,
	COL_CLOCK = 32,
	COL_WINDOW = 33,
	COL_DESK = 34,
	COL_SHELVES = 35,
	COL_LOCKED_WALL_SAFE = 36,
	COL_OPEN_WALL_SAFE = 37,
	COL_DINGLES_BODY = 38,
	COL_PIANO_AND_A_SQUASHED_CYNTHIA_SLUDGEBUCKET = 39,
	COL_GABRIELS_BODY = 40,
	COL_STABBED_DOCTOR = 41,
	COL_TORCH_ANIM1 = 42,
	COL_TORCH_ANIM2 = 43,
	COL_TORCH_ANIM3 = 44,
	COL_HEADSTONE1 = 45,
	COL_HEADSTONE2 = 46,
	COL_CLOCK_FACE = 47,
	COL_FIREPLACE_ANIM = 48,
	COL_FOUNTAIN = 49,
	COL_GARGOYLE1 = 50,
	COL_GARGOYLE2 = 51,
	COL_GARGOYLE3 = 52,
	
	// ------- Hidden objects
	
	COL_DOOR_CLOSED = 64,
	COL_DOOR_OPEN = 65,
	COL_DOOR_SMALL_CLOSED = 66,
	COL_DOOR_SMALL_OPEN = 67,
	COL_DOOR_SMALL_HIDDEN = 68,
	COL_TORCH1 = 69,
	COL_TORCH2 = 70,
	COL_FIREPLACE1 = 71,
	COL_FIREPLACE2 = 72,
	COL_FIREPLACE3 = 73
};

extern const unsigned char col_angus_landing[];
extern const unsigned char col_angus_room1[];
extern const unsigned char col_angus_room2[];
extern const unsigned char col_angus_secret[];
extern const unsigned char col_angus_stairs[];
extern const unsigned char col_cellar[];
extern const unsigned char col_clock[];
extern const unsigned char col_courtyard[];
extern const unsigned char col_drawing[];
extern const unsigned char col_garden[];
extern const unsigned char col_graveyard[];
extern const unsigned char col_hall1[];
extern const unsigned char col_hall2[];
extern const unsigned char col_hall3[];
extern const unsigned char col_hall4[];
extern const unsigned char col_kitchen[];
extern const unsigned char col_landing[];
extern const unsigned char col_library[];
extern const unsigned char col_outside1[];
extern const unsigned char col_outside2[];
extern const unsigned char col_outside3[];
extern const unsigned char col_passage1[];
extern const unsigned char col_passage2[];
extern const unsigned char col_room1[];
extern const unsigned char col_room2[];
extern const unsigned char col_room3[];
extern const unsigned char col_stairs[];
extern const unsigned char col_stairs_front[];
extern const unsigned char col_study[];
extern const unsigned char col_utility[];
