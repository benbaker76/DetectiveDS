#ifndef __COLMAP_H__
#define __COLMAP_H__

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
	COL_HEADSTONE1 = 42,
	COL_HEADSTONE2 = 43,
	COL_FOUNTAIN_WITH_RUNNING_WATER = 44,
	COL_FOUNTAIN_DRAINED_OF_WATER = 45,
	COL_GARGOYLE1 = 46,
	COL_GARGOYLE2 = 47,
	COL_GARGOYLE3 = 48,
	COL_GOAT_LIKE_PAINTING = 49,
	COL_DESK_WITH_A_STATUE = 50,
	COL_A_TROPHY = 51,
	COL_ANGUS_BOOKCASE = 52,
	COL_KNIGHT = 53,
	COL_COUCH = 54,
	COL_HOURGLASS = 55,
	COL_GOLDEN_SKULL = 56,
	COL_TABLE = 57,
	COL_BROOM = 58,
	COL_WASHING_MACHINE = 59,
	COL_WASHING_BASKET = 60,
	COL_CUPBOARD = 61,
	COL_CABINET = 62,
	
	// ------- Source Animation Objects
	
	COL_SRC_DOOR_CLOSED = 128,
	COL_SRC_DOOR_OPEN = 129,
	COL_SRC_DOOR_SMALL_CLOSED = 130,
	COL_SRC_DOOR_SMALL_OPEN = 131,
	COL_SRC_DOOR_SMALL_HIDDEN = 132,
	COL_SRC_TORCH1 = 133,
	COL_SRC_TORCH2 = 134,
	COL_SRC_FIREPLACE1 = 135,
	COL_SRC_FIREPLACE2 = 136,
	COL_SRC_FIREPLACE3 = 137,
	COL_SRC_FIREPLACE4 = 138,
	COL_SRC_FIREPLACE5 = 139,
	COL_SRC_SAFE1 = 140,
	COL_SRC_SAFE2 = 141,
	COL_SRC_SAFE3 = 142,
	COL_SRC_LIGHT1 = 143,
	COL_SRC_LIGHT2 = 144,
	COL_SRC_LIGHT3 = 145,
	COL_SRC_LIGHT4 = 146,
	COL_SRC_EYES1 = 147,
	COL_SRC_EYES2 = 148,
	COL_SRC_EYES3 = 149,
	COL_SRC_EYES4 = 150,
	COL_SRC_EYES5 = 151,
	COL_SRC_EYES6 = 152,
	COL_SRC_STATUE = 153,
	COL_SRC_TROPHY = 154,
	COL_SRC_SWORD = 155,
	COL_SRC_BALL_ON_CHAIN = 156,
	COL_SRC_BOOKCASE1 = 157,
	COL_SRC_BOOKCASE2 = 158,
	COL_SRC_PENDULUM1 = 159,
	COL_SRC_PENDULUM2 = 160,
	COL_SRC_PENDULUM3 = 161,
	COL_SRC_WATERFALL1 = 162,
	COL_SRC_WATERFALL2 = 163,
	COL_SRC_WATERFALL3 = 164,
	COL_SRC_CABINET1 = 165,
	COL_SRC_CABINET2 = 166,
	COL_SRC_FAUCET1 = 167,
	COL_SRC_FAUCET2 = 168,
	COL_SRC_FAUCET3 = 169,
	COL_SRC_FAUCET4 = 170,
	COL_SRC_LEAK1 = 171,
	COL_SRC_LEAK2 = 172,
	COL_SRC_LEAK3 = 173,
	COL_SRC_LEAK4 = 174,
	COL_SRC_LEAK5 = 175,
	COL_SRC_LEAK6 = 176,
	COL_SRC_LEAK7 = 177,
	COL_SRC_LEAK8 = 178,
	COL_SRC_BULB1 = 179,
	COL_SRC_BULB2 = 180,
	
	// ------- Destination Animation Objects
	
	COL_DST_TORCH1 = 192,
	COL_DST_TORCH2 = 193,
	COL_DST_TORCH3 = 194,
	COL_DST_CLOCK = 195,
	COL_DST_FIREPLACE = 196,
	COL_DST_SAFE = 197,
	COL_DST_LIGHT1 = 198,
	COL_DST_LIGHT2 = 199,
	COL_DST_EYES = 200,
	COL_DST_STATUE = 201,
	COL_DST_TROPHY = 202,
	COL_DST_SWORD = 203,
	COL_DST_BALL_ON_CHAIN = 204,
	COL_DST_BOOKCASE1 = 205,
	COL_DST_BOOKCASE2 = 206,
	COL_DST_PENDULUM = 207,
	COL_DST_WATERFALL = 208,
	COL_DST_CABINET = 209,
	COL_DST_FAUCET = 210,
	COL_DST_LEAK = 211,
	COL_DST_BULB = 212
};

#endif

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
