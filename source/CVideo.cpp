#include <nds.h>
#include "CVideo.h"
#include "TDG.h"
#include "windows.h"
#include "Text.h"
#include "lz77.h"

CVideo::CVideo()
{
}

CVideo::~CVideo()
{
}

void CVideo::Initialize()
{
	videoSetMode(MODE_0_2D | DISPLAY_WIN0_ON | DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE);
	videoSetModeSub(MODE_0_2D | DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE);
	
	vramSetMainBanks(VRAM_A_MAIN_BG_0x06000000, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG_0x06200000, VRAM_D_SUB_SPRITE);
	
	bgInit(0, BgType_Text4bpp, BgSize_T_256x256, BG0_MAP_BASE, BG0_TILE_BASE);
	bgInit(1, BgType_Text8bpp, BgSize_T_256x256, BG1_MAP_BASE, BG1_TILE_BASE);
	bgInit(2, BgType_Text8bpp, BgSize_T_256x256, BG2_MAP_BASE, BG2_TILE_BASE);
	bgInit(3, BgType_Text8bpp, BgSize_T_256x256, BG3_MAP_BASE, BG3_TILE_BASE);
	
	bgInitSub(0, BgType_Text4bpp, BgSize_T_256x256, BG0_MAP_BASE_SUB, BG0_TILE_BASE_SUB);
	bgInitSub(1, BgType_Text8bpp, BgSize_T_256x256, BG1_MAP_BASE_SUB, BG1_TILE_BASE_SUB);
	int bg2Sub = bgInitSub(2, BgType_Text8bpp, BgSize_T_512x256, BG2_MAP_BASE_SUB, BG2_TILE_BASE_SUB);
	int bg3Sub = bgInitSub(3, BgType_Text8bpp, BgSize_T_512x256, BG3_MAP_BASE_SUB, BG3_TILE_BASE_SUB);
	
	bgSetControlBits(bg2Sub, BG_PRIORITY_0);
	bgSetControlBits(bg3Sub, BG_PRIORITY_2);
	
	lcdMainOnBottom();
	
	dmaCopy(sprite_snide_bodyPal, SPRITE_PALETTE_SUB, sprite_snide_bodyPalLen);
	
	dmaCopy(watchTiles, BG_TILE_RAM_SUB(BG1_TILE_BASE_SUB), watchTilesLen);
	dmaCopy(watchMap, BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB), watchMapLen);
	
	dmaCopy(fontTiles, BG_TILE_RAM(BG0_TILE_BASE), fontTilesLen);
	//dmaCopy(fontPal, BG_PALETTE, fontPalLen);
	
	dmaCopy(font_largeTiles, BG_TILE_RAM(BG0_TILE_BASE) + fontTilesLen, font_largeTilesLen);
	
	//dmaCopy(title_bg1Tiles, BG_TILE_RAM(BG1_TILE_BASE), title_bg1TilesLen);
	//dmaCopy(title_bg1Map, BG_MAP_RAM(BG1_MAP_BASE), title_bg1MapLen);
	
	dmaCopy(title_bg2Tiles, BG_TILE_RAM(BG2_TILE_BASE), title_bg2TilesLen);
	dmaCopy(title_bg2Map, BG_MAP_RAM(BG2_MAP_BASE), title_bg2MapLen);
	
	dmaCopy(menu_bottomTiles, BG_TILE_RAM(BG3_TILE_BASE), menu_bottomTilesLen);
	dmaCopy(menu_bottomMap, BG_MAP_RAM(BG3_MAP_BASE), menu_bottomMapLen);
	dmaCopy(menu_bottomPal, BG_PALETTE, menu_bottomPalLen);
	
	//dmaCopy(title_bg3Tiles, BG_TILE_RAM(BG3_TILE_BASE), title_bg3TilesLen);
	//dmaCopy(title_bg3Map, BG_MAP_RAM(BG3_MAP_BASE), title_bg3MapLen);
	
	WIN_IN = WIN0_BG0 | WIN0_BG1 | WIN0_BG2 | WIN0_BG3 | WIN0_SPRITES | WIN0_BLENDS;
	WIN_OUT = WIN0_BG0 | WIN0_BG1 | WIN0_BG3 | WIN0_SPRITES | WIN0_BLENDS;
	WIN0_Y0 = 0;
	WIN0_Y1 = 80;
	WIN0_X0	= 0;
	WIN0_X1 = 255;
	
	//DrawText("@2009 HEADSOFT", 9, 1, false);
	DrawText("INTRODUCING", 4, 17, false);
	DrawText("THE CAST..", 5, 18, false);
	
	DrawTextLarge("\"GRENADE!\" SHOUTS THE MAJOR.", 0, 11, false);
	
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	oamInit(&oamSub, SpriteMapping_1D_32, false);
}
