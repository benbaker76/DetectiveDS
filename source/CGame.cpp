#include <nds.h>
#include <stdio.h>
#include "TDG.h"
#include "CGame.h"
#include "Text.h"
#include "Gfx.h"
#include "CFxParticles.h"
#include "windows.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::Initialize()
{
	InitIntro();
}

void CGame::InitData()
{
	dmaFillHalfWords(0, BG_PALETTE_SUB, 512);
	dmaFillHalfWords(0, BG_PALETTE, 512);
	
	dmaFillHalfWords(0, BG_MAP_RAM_SUB(INTRO_BG0_MAP_BASE_SUB), 2048);
	dmaFillHalfWords(0, BG_MAP_RAM(INTRO_BG0_MAP_BASE), 2048);
	
	dmaFillHalfWords(0, BG_MAP_RAM_SUB(INTRO_BG1_MAP_BASE_SUB), 2048);
	dmaFillHalfWords(0, BG_MAP_RAM(INTRO_BG1_MAP_BASE), 2048);

	InitVideoMain();
	
	ClearBG(0, true);
	ClearBG(1, true);
	ClearBG(2, true);
	ClearBG(3, true);
	
	ClearBG(0, false);
	ClearBG(1, false);
	ClearBG(2, false);
	ClearBG(3, false);

	m_fxManager.Initialize();
	m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
	m_fxManager.SetFx(FXTYPE_TEXT_SCROLLER, FXMODE_NORMAL, true);
	m_fxManager.SetFx(FXTYPE_COLOUR, FXMODE_NORMAL, true);
	m_fxManager.SetFx(FXTYPE_C64, FXMODE_NORMAL, true);
		
	for(int i=0; i<MAX_CHARACTERS; i++)
		m_characterArray[i] = NULL;
		
	for(int i=0; i<MAX_SPRITES; i++)
		m_spriteArray[i] = NULL;
		
	for(int i=0; i<MAX_ROOMS; i++)
		m_roomArray[i] = NULL;
		
	for(int i=0; i<MAX_ITEMS; i++)
		m_itemArray[i] = NULL;
		
	for(int i=0; i<MAX_EVENTS; i++)
		m_eventArray[i] = NULL;
		
	m_itemArray[ITEM_NONE] = new CItem(ITEM_NONE, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_HOT_WATER_BOTTLE] = new CItem(ITEM_A_HOT_WATER_BOTTLE, ITEMATTRIB_OPEN);
	m_itemArray[ITEM_BLANK_BULLETS] = new CItem(ITEM_BLANK_BULLETS, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_CANDLESTICK] = new CItem(ITEM_A_CANDLESTICK, ITEMATTRIB_NONE);
	m_itemArray[ITEM_THE_WILL] = new CItem(ITEM_THE_WILL, ITEMATTRIB_EVIDENCE | ITEMATTRIB_READ);			// Clue #1
	m_itemArray[ITEM_A_KNIFE] = new CItem(ITEM_A_KNIFE, ITEMATTRIB_EVIDENCE);								// Clue #8
	m_itemArray[ITEM_NEWSPAPER_CUTTING] = new CItem(ITEM_NEWSPAPER_CUTTING, ITEMATTRIB_READ);
	m_itemArray[ITEM_A_NOTE] = new CItem(ITEM_A_NOTE, ITEMATTRIB_EVIDENCE | ITEMATTRIB_READ);				// Clue #4
	m_itemArray[ITEM_A_SMALL_BOTTLE] = new CItem(ITEM_A_SMALL_BOTTLE, ITEMATTRIB_EVIDENCE | ITEMATTRIB_CONSUME);		// Clue #6
	m_itemArray[ITEM_A_CRAVATE] = new CItem(ITEM_A_CRAVATE, ITEMATTRIB_EVIDENCE);							// Clue #3
	m_itemArray[ITEM_A_SOGGY_ENVELOPE] = new CItem(ITEM_A_SOGGY_ENVELOPE, ITEMATTRIB_OPEN);
	m_itemArray[ITEM_A_LETTER] = new CItem(ITEM_A_LETTER, ITEMATTRIB_READ);
	m_itemArray[ITEM_SCALPELS] = new CItem(ITEM_SCALPELS, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_SYRINGE] = new CItem(ITEM_A_SYRINGE, ITEMATTRIB_EVIDENCE);							// Clue #9
	m_itemArray[ITEM_A_BOTTLE_OF_PILLS] = new CItem(ITEM_A_BOTTLE_OF_PILLS, ITEMATTRIB_CONSUME);
	m_itemArray[ITEM_A_HAMMER] = new CItem(ITEM_A_HAMMER, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_BUNCH_OF_KEYS] = new CItem(ITEM_A_BUNCH_OF_KEYS, ITEMATTRIB_USE_KEY);
	m_itemArray[ITEM_A_BIG_IRON_KEY] = new CItem(ITEM_A_BIG_IRON_KEY, ITEMATTRIB_USE_KEY);
	m_itemArray[ITEM_A_SILVER_TRAY] = new CItem(ITEM_A_SILVER_TRAY, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_BOTTLE_OF_WINE] = new CItem(ITEM_A_BOTTLE_OF_WINE, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_COMB] = new CItem(ITEM_A_COMB, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_HARDBACK_BOOK] = new CItem(ITEM_A_HARDBACK_BOOK, ITEMATTRIB_OPEN | ITEMATTRIB_READ);
	m_itemArray[ITEM_A_FOLDED_DOCUMENT] = new CItem(ITEM_A_FOLDED_DOCUMENT, ITEMATTRIB_EVIDENCE | ITEMATTRIB_READ);	// Clue #2
	m_itemArray[ITEM_AN_ELEPHANT_GUN] = new CItem(ITEM_AN_ELEPHANT_GUN, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_DIARY] = new CItem(ITEM_A_DIARY, ITEMATTRIB_NONE | ITEMATTRIB_READ);
	m_itemArray[ITEM_A_BLACK_BAG] = new CItem(ITEM_A_BLACK_BAG, ITEMATTRIB_OPEN);
	m_itemArray[ITEM_COLOGNE] = new CItem(ITEM_COLOGNE, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_SMALL_BOOK] = new CItem(ITEM_A_SMALL_BOOK, ITEMATTRIB_NONE);
	m_itemArray[ITEM_DIRTY_PLATES] = new CItem(ITEM_DIRTY_PLATES, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_PICTURE] = new CItem(ITEM_A_PICTURE, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_WAD_OF_NOTES] = new CItem(ITEM_A_WAD_OF_NOTES, ITEMATTRIB_EVIDENCE);				// Clue #5
	m_itemArray[ITEM_A_LOCKET] = new CItem(ITEM_A_LOCKET, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_SCREWDRIVER] = new CItem(ITEM_A_SCREWDRIVER, ITEMATTRIB_NONE);
	m_itemArray[ITEM_AN_OPEN_LOCKET] = new CItem(ITEM_AN_OPEN_LOCKET, ITEMATTRIB_EVIDENCE);				// Clue #10
	m_itemArray[ITEM_BROKEN_PLATES] = new CItem(ITEM_BROKEN_PLATES, ITEMATTRIB_NONE);
	m_itemArray[ITEM_BROKEN_GLASS] = new CItem(ITEM_BROKEN_GLASS, ITEMATTRIB_NONE);
	m_itemArray[ITEM_SHREDDED_PAPER] = new CItem(ITEM_SHREDDED_PAPER, ITEMATTRIB_NONE);
	m_itemArray[ITEM_BOOKS1] = new CItem(ITEM_BOOKS1, ITEMATTRIB_NONE);
	m_itemArray[ITEM_BOOKS2] = new CItem(ITEM_BOOKS2, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_LETTER_OPENER] = new CItem(ITEM_A_LETTER_OPENER, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_JACKET] = new CItem(ITEM_A_JACKET, ITEMATTRIB_OPEN);
	m_itemArray[ITEM_NOTEBOOKS] = new CItem(ITEM_NOTEBOOKS, ITEMATTRIB_OPEN);
	m_itemArray[ITEM_PLANS] = new CItem(ITEM_PLANS, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_MIRROR] = new CItem(ITEM_A_MIRROR, ITEMATTRIB_NONE);
	m_itemArray[ITEM_CUTLERY] = new CItem(ITEM_CUTLERY, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_PIECE_OF_CARD] = new CItem(ITEM_A_PIECE_OF_CARD, ITEMATTRIB_READ);
	m_itemArray[ITEM_A_BRIEFCASE] = new CItem(ITEM_A_BRIEFCASE, ITEMATTRIB_OPEN);
	m_itemArray[ITEM_A_FOLDER] = new CItem(ITEM_A_FOLDER, ITEMATTRIB_OPEN);
	m_itemArray[ITEM_A_PAPERWEIGHT] = new CItem(ITEM_A_PAPERWEIGHT, ITEMATTRIB_NONE);
	m_itemArray[ITEM_PADDED_ENVELOPES] = new CItem(ITEM_PADDED_ENVELOPES, ITEMATTRIB_OPEN, 10);
	m_itemArray[ITEM_A_BOMB] = new CItem(ITEM_A_BOMB, ITEMATTRIB_EVIDENCE);								// Clue #7
	m_itemArray[ITEM_A_SMALL_KEY] = new CItem(ITEM_A_SMALL_KEY, ITEMATTRIB_USE_KEY);
	m_itemArray[ITEM_BULLETS] = new CItem(ITEM_BULLETS, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_SWORD] = new CItem(ITEM_A_SWORD, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_BALL_ON_CHAIN] = new CItem(ITEM_A_BALL_ON_CHAIN, ITEMATTRIB_NONE);
	m_itemArray[ITEM_AN_HOURGLASS] = new CItem(ITEM_AN_HOURGLASS, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_GOLDEN_SKULL] = new CItem(ITEM_A_GOLDEN_SKULL, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_RED_KEY] = new CItem(ITEM_A_RED_KEY, ITEMATTRIB_USE_KEY);
	m_itemArray[ITEM_A_FIREPLACE_BELLOW] = new CItem(ITEM_A_FIREPLACE_BELLOW, ITEMATTRIB_NONE);
	m_itemArray[ITEM_WASHING_POWDER] = new CItem(ITEM_WASHING_POWDER, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_DIRTY_SHIRT] = new CItem(ITEM_A_DIRTY_SHIRT, ITEMATTRIB_NONE);
	
	m_itemArray[ITEM_A_BRIEFCASE]->SetKeyItemType(ITEM_A_SMALL_KEY);
	
	m_spriteArray[SPRITE_SNIDE_HEAD] = new CSprite(SPRITE_SNIDE_HEAD, sprite_snide_headTiles, sprite_snide_headTilesLen, sprite_snide_headPal, sprite_snide_headPalLen, g_snideHeadFrames, 16);
	m_spriteArray[SPRITE_SNIDE_BODY] = new CSprite(SPRITE_SNIDE_BODY, sprite_snide_bodyTiles, sprite_snide_bodyTilesLen, sprite_snide_bodyPal, sprite_snide_bodyPalLen, g_snideBodyFrames, 17);
	m_spriteArray[SPRITE_REVEREND_HEAD] = new CSprite(SPRITE_REVEREND_HEAD, sprite_reverend_headTiles, sprite_reverend_headTilesLen, sprite_reverend_headPal, sprite_reverend_headPalLen, g_reverendHeadFrames, 4);
	m_spriteArray[SPRITE_REVEREND_BODY] = new CSprite(SPRITE_REVEREND_BODY, sprite_reverend_bodyTiles, sprite_reverend_bodyTilesLen, sprite_reverend_bodyPal, sprite_reverend_bodyPalLen, g_reverendBodyFrames, 6);
	m_spriteArray[SPRITE_BENTLEY_HEAD] = new CSprite(SPRITE_BENTLEY_HEAD, sprite_bentley_headTiles, sprite_bentley_headTilesLen, sprite_bentley_headPal, sprite_bentley_headPalLen, g_bentleyHeadFrames, 4);
	m_spriteArray[SPRITE_BENTLEY_BODY] = new CSprite(SPRITE_BENTLEY_BODY, sprite_bentley_bodyTiles, sprite_bentley_bodyTilesLen, sprite_bentley_bodyPal, sprite_bentley_bodyPalLen, g_bentleyBodyFrames, 6);
	m_spriteArray[SPRITE_COOK_HEAD] = new CSprite(SPRITE_COOK_HEAD, sprite_cook_headTiles, sprite_cook_headTilesLen, sprite_cook_headPal, sprite_cook_headPalLen, g_cookHeadFrames, 4);
	m_spriteArray[SPRITE_COOK_BODY] = new CSprite(SPRITE_COOK_BODY, sprite_cook_bodyTiles, sprite_cook_bodyTilesLen, sprite_cook_bodyPal, sprite_cook_bodyPalLen, g_cookBodyFrames, 6);
	m_spriteArray[SPRITE_GABRIEL_HEAD] = new CSprite(SPRITE_GABRIEL_HEAD, sprite_gabriel_headTiles, sprite_gabriel_headTilesLen, sprite_gabriel_headPal, sprite_gabriel_headPalLen, g_gabrielHeadFrames, 5);
	m_spriteArray[SPRITE_GABRIEL_BODY] = new CSprite(SPRITE_GABRIEL_BODY, sprite_gabriel_bodyTiles, sprite_gabriel_bodyTilesLen, sprite_gabriel_bodyPal, sprite_gabriel_bodyPalLen, g_gabrielBodyFrames, 7);
	m_spriteArray[SPRITE_CYNTHIA_HEAD] = new CSprite(SPRITE_CYNTHIA_HEAD, sprite_cynthia_headTiles, sprite_cynthia_headTilesLen, sprite_cynthia_headPal, sprite_cynthia_headPalLen, g_cynthiaHeadFrames, 5);
	m_spriteArray[SPRITE_CYNTHIA_BODY] = new CSprite(SPRITE_CYNTHIA_BODY, sprite_cynthia_bodyTiles, sprite_cynthia_bodyTilesLen, sprite_cynthia_bodyPal, sprite_cynthia_bodyPalLen, g_cynthiaBodyFrames, 7);
	m_spriteArray[SPRITE_PROFESSOR_HEAD] = new CSprite(SPRITE_PROFESSOR_HEAD, sprite_professor_headTiles, sprite_professor_headTilesLen, sprite_professor_headPal, sprite_professor_headPalLen, g_professorHeadFrames, 5);
	m_spriteArray[SPRITE_PROFESSOR_BODY] = new CSprite(SPRITE_PROFESSOR_BODY, sprite_professor_bodyTiles, sprite_professor_bodyTilesLen, sprite_professor_bodyPal, sprite_professor_bodyPalLen, g_professorBodyFrames, 7);
	m_spriteArray[SPRITE_DOCTOR_HEAD] = new CSprite(SPRITE_DOCTOR_HEAD, sprite_doctor_headTiles, sprite_doctor_headTilesLen, sprite_doctor_headPal, sprite_doctor_headPalLen, g_doctorHeadFrames, 5);
	m_spriteArray[SPRITE_DOCTOR_BODY] = new CSprite(SPRITE_DOCTOR_BODY, sprite_doctor_bodyTiles, sprite_doctor_bodyTilesLen, sprite_doctor_bodyPal, sprite_doctor_bodyPalLen, g_doctorBodyFrames, 7);
	m_spriteArray[SPRITE_MAJOR_HEAD] = new CSprite(SPRITE_MAJOR_HEAD, sprite_major_headTiles, sprite_major_headTilesLen, sprite_major_headPal, sprite_major_headPalLen, g_majorHeadFrames, 4);
	m_spriteArray[SPRITE_MAJOR_BODY] = new CSprite(SPRITE_MAJOR_BODY, sprite_major_bodyTiles, sprite_major_bodyTilesLen, sprite_major_bodyPal, sprite_major_bodyPalLen, g_majorBodyFrames, 6);		
	m_spriteArray[SPRITE_DINGLE_HEAD] = new CSprite(SPRITE_DINGLE_HEAD, sprite_dingle_headTiles, sprite_dingle_headTilesLen, sprite_dingle_headPal, sprite_dingle_headPalLen, g_dingleHeadFrames, 5);
	m_spriteArray[SPRITE_DINGLE_BODY] = new CSprite(SPRITE_DINGLE_BODY, sprite_dingle_bodyTiles, sprite_dingle_bodyTilesLen, sprite_dingle_bodyPal, sprite_dingle_bodyPalLen, g_dingleBodyFrames, 9);
	
	m_spriteArray[SPRITE_ANGUS_HEAD] = new CSprite(SPRITE_ANGUS_HEAD, sprite_angus_headBitmap, g_angusHeadFrames, 4);
	m_spriteArray[SPRITE_ANGUS_BODY] = new CSprite(SPRITE_ANGUS_BODY, sprite_angus_bodyBitmap, g_angusBodyFrames, 6);

	//m_spriteArray[SPRITE_ANGUS_HEAD] = new CSprite(SPRITE_ANGUS_HEAD, sprite_angus_headTiles, sprite_angus_headTilesLen, sprite_angus_headPal, sprite_angus_headPalLen, g_angusHeadFrames, 4);
	//m_spriteArray[SPRITE_ANGUS_BODY] = new CSprite(SPRITE_ANGUS_BODY, sprite_angus_bodyTiles, sprite_angus_bodyTilesLen, sprite_angus_bodyPal, sprite_angus_bodyPalLen, g_angusBodyFrames, 6);
	
	m_spriteArray[SPRITE_QUESTION_HEAD] = new CSprite(SPRITE_QUESTION_HEAD, sprite_question_headTiles, sprite_question_headTilesLen, sprite_question_headPal, sprite_question_headPalLen, g_questionFrames, 8);
	m_spriteArray[SPRITE_QUESTION_BODY] = new CSprite(SPRITE_QUESTION_BODY, sprite_question_bodyTiles, sprite_question_bodyTilesLen, sprite_question_bodyPal, sprite_question_bodyPalLen, g_questionFrames, 8);

	m_characterArray[CHARTYPE_SNIDE] = new CCharacter(CHARTYPE_SNIDE, m_spriteArray[SPRITE_SNIDE_HEAD], m_spriteArray[SPRITE_SNIDE_BODY], CHARSEX_MALE, 24, 53);
	m_characterArray[CHARTYPE_REVEREND] = new CCharacter(CHARTYPE_REVEREND, m_spriteArray[SPRITE_REVEREND_HEAD], m_spriteArray[SPRITE_REVEREND_BODY], CHARSEX_MALE, 24, 53);
	m_characterArray[CHARTYPE_BENTLEY] = new CCharacter(CHARTYPE_BENTLEY, m_spriteArray[SPRITE_BENTLEY_HEAD], m_spriteArray[SPRITE_BENTLEY_BODY], CHARSEX_MALE, 24, 53);
	m_characterArray[CHARTYPE_COOK] = new CCharacter(CHARTYPE_COOK, m_spriteArray[SPRITE_COOK_HEAD], m_spriteArray[SPRITE_COOK_BODY], CHARSEX_FEMALE, 24, 44);
	m_characterArray[CHARTYPE_GABRIEL] = new CCharacter(CHARTYPE_GABRIEL, m_spriteArray[SPRITE_GABRIEL_HEAD], m_spriteArray[SPRITE_GABRIEL_BODY], CHARSEX_FEMALE, 24, 48);
	m_characterArray[CHARTYPE_CYNTHIA] = new CCharacter(CHARTYPE_CYNTHIA, m_spriteArray[SPRITE_CYNTHIA_HEAD], m_spriteArray[SPRITE_CYNTHIA_BODY], CHARSEX_FEMALE, 24, 49);
	m_characterArray[CHARTYPE_PROFESSOR] = new CCharacter(CHARTYPE_PROFESSOR, m_spriteArray[SPRITE_PROFESSOR_HEAD], m_spriteArray[SPRITE_PROFESSOR_BODY], CHARSEX_MALE, 24, 48);
	m_characterArray[CHARTYPE_DOCTOR] = new CCharacter(CHARTYPE_DOCTOR, m_spriteArray[SPRITE_DOCTOR_HEAD], m_spriteArray[SPRITE_DOCTOR_BODY], CHARSEX_MALE, 24, 49);
	m_characterArray[CHARTYPE_MAJOR] = new CCharacter(CHARTYPE_MAJOR, m_spriteArray[SPRITE_MAJOR_HEAD], m_spriteArray[SPRITE_MAJOR_BODY], CHARSEX_MALE, 24, 46);
	m_characterArray[CHARTYPE_DINGLE] = new CCharacter(CHARTYPE_DINGLE, m_spriteArray[SPRITE_DINGLE_HEAD], m_spriteArray[SPRITE_DINGLE_BODY], CHARSEX_MALE, 24, 48);
	m_characterArray[CHARTYPE_ANGUS] = new CCharacter(CHARTYPE_ANGUS, m_spriteArray[SPRITE_ANGUS_HEAD], m_spriteArray[SPRITE_ANGUS_BODY], CHARSEX_MALE, 24, 48);
	
	m_question = new CCharacter(CHARTYPE_QUESTION, m_spriteArray[SPRITE_QUESTION_HEAD], m_spriteArray[SPRITE_QUESTION_BODY], CHARSEX_NONE, 24, 48);
	
	m_characterArray[CHARTYPE_SNIDE]->SetDeadSide(true);
	m_characterArray[CHARTYPE_DOCTOR]->SetDeadSide(true);
	
	m_roomArray[ROOM_SNIDE] = new CRoom(ROOM_SNIDE, g_snideMap, NULL, col_room1, 144);
	m_roomArray[ROOM_REVEREND] = new CRoom(ROOM_REVEREND, g_reverendMap, NULL, col_room1, 144);
	m_roomArray[ROOM_BENTLEY] = new CRoom(ROOM_BENTLEY, g_bentleyMap, NULL, col_room2, 168);
	m_roomArray[ROOM_COOK] = new CRoom(ROOM_COOK, g_cookMap, NULL, col_room2, 168);
	m_roomArray[ROOM_GABRIEL] = new CRoom(ROOM_GABRIEL, g_gabrielMap, NULL, col_room2, 168);
	m_roomArray[ROOM_CYNTHIA] = new CRoom(ROOM_CYNTHIA, g_cynthiaMap, NULL, col_room1, 144);
	m_roomArray[ROOM_PROFESSOR] = new CRoom(ROOM_PROFESSOR, g_professorMap, NULL, col_room1, 144);
	m_roomArray[ROOM_DOCTOR] = new CRoom(ROOM_DOCTOR, g_doctorMap, NULL, col_room1, 144);		
	m_roomArray[ROOM_MAJOR] = new CRoom(ROOM_MAJOR, g_majorMap, NULL, col_room1, 144);
	m_roomArray[ROOM_DINGLE] = new CRoom(ROOM_DINGLE, g_dingleMap, NULL, col_room1, 144);
	m_roomArray[ROOM_OUTSIDE1] = new CRoom(ROOM_OUTSIDE1, g_outside1Map, NULL, col_outside1, 160);
	m_roomArray[ROOM_OUTSIDE2] = new CRoom(ROOM_OUTSIDE2, g_outside2Map, g_outside2_frontMap, col_outside2, 152);
	m_roomArray[ROOM_OUTSIDE3] = new CRoom(ROOM_OUTSIDE3, g_outside1Map, NULL, col_outside1, 160);
	m_roomArray[ROOM_OUTSIDE4] = new CRoom(ROOM_OUTSIDE4, g_outside2Map, g_outside2_frontMap, col_outside2, 152);
	m_roomArray[ROOM_PASSAGE1] = new CRoom(ROOM_PASSAGE1, g_passage1Map, NULL, col_passage1, 152);
	m_roomArray[ROOM_PASSAGE2] = new CRoom(ROOM_PASSAGE2, g_passage2Map, NULL, col_passage2, 152);
	m_roomArray[ROOM_PASSAGE3] = new CRoom(ROOM_PASSAGE3, g_passage1Map, NULL, col_passage1, 152);
	m_roomArray[ROOM_HALL1] = new CRoom(ROOM_HALL1, g_hall1Map, NULL, col_hall1, 160);
	m_roomArray[ROOM_HALL2] = new CRoom(ROOM_HALL2, g_hall2Map, NULL, col_hall2, 160);
	m_roomArray[ROOM_HALL3] = new CRoom(ROOM_HALL3, g_hall3Map, NULL, col_hall3, 160);
	m_roomArray[ROOM_HALL4] = new CRoom(ROOM_HALL4, g_hall4Map, NULL, col_hall4, 160);
	m_roomArray[ROOM_LANDING] = new CRoom(ROOM_LANDING, g_landingMap, g_landing_front1Map, col_landing, 144);
	m_roomArray[ROOM_KITCHEN] = new CRoom(ROOM_KITCHEN, g_kitchenMap, NULL, col_kitchen, 160);
	m_roomArray[ROOM_STAIRS] = new CRoom(ROOM_STAIRS, g_stairsMap, NULL, col_stairs, 168);
	m_roomArray[ROOM_STUDY] = new CRoom(ROOM_STUDY, g_studyMap, NULL, col_study, 160);
	
	m_roomArray[ROOM_CLOCK] = new CRoom(ROOM_CLOCK, g_clockMap, NULL, col_clock, 160);
	m_roomArray[ROOM_CELLAR] = new CRoom(ROOM_CELLAR, g_cellarMap, NULL, col_cellar, 160);
	m_roomArray[ROOM_DRAWING] = new CRoom(ROOM_DRAWING, g_drawingMap, NULL, col_drawing, 160);
	m_roomArray[ROOM_LIBRARY] = new CRoom(ROOM_LIBRARY, g_libraryMap, NULL, col_library, 160);	
	m_roomArray[ROOM_UTILITY] = new CRoom(ROOM_UTILITY, g_utilityMap, NULL, col_utility, 160);
	m_roomArray[ROOM_GARDEN] = new CRoom(ROOM_GARDEN, g_gardenMap, g_garden_frontMap, col_garden, 152);
	m_roomArray[ROOM_GRAVEYARD] = new CRoom(ROOM_GRAVEYARD, g_graveyardMap, g_graveyard_frontMap, col_graveyard, 160);
	m_roomArray[ROOM_COURTYARD] = new CRoom(ROOM_COURTYARD, g_courtyardMap, g_courtyard_frontMap, col_courtyard, 160);
	m_roomArray[ROOM_ANGUS_LANDING] = new CRoom(ROOM_ANGUS_LANDING, g_angus_landingMap, g_angus_landing_frontMap, col_angus_landing, 144);
	m_roomArray[ROOM_ANGUS_ROOM] = new CRoom(ROOM_ANGUS_ROOM, g_angus_room1Map, g_angus_room_frontMap, col_angus_room2, 160);
	m_roomArray[ROOM_ANGUS_SECRET] = new CRoom(ROOM_ANGUS_SECRET, g_angus_secretMap, g_angus_secret_frontMap, col_angus_secret, 160);
	m_roomArray[ROOM_ANGUS_STAIRS] = new CRoom(ROOM_ANGUS_STAIRS, g_angus_stairsMap, NULL, col_angus_stairs, 168);
	m_roomArray[ROOM_DINING] = new CRoom(ROOM_DINING, g_diningMap, g_dining_frontMap, col_dining, 160);
	
	m_roomArray[ROOM_SNIDE]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_SNIDE], m_roomArray[ROOM_HALL2], ITEM_NONE));		
	m_roomArray[ROOM_REVEREND]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_REVEREND], m_roomArray[ROOM_HALL1], ITEM_NONE));
	m_roomArray[ROOM_REVEREND]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_HIDDEN, m_roomArray[ROOM_REVEREND], m_roomArray[ROOM_PASSAGE1], ITEM_NONE));		
	m_roomArray[ROOM_BENTLEY]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_BENTLEY], m_roomArray[ROOM_HALL3], ITEM_A_BUNCH_OF_KEYS));		
	m_roomArray[ROOM_COOK]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_COOK], m_roomArray[ROOM_HALL4], ITEM_NONE));
	m_roomArray[ROOM_GABRIEL]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_GABRIEL], m_roomArray[ROOM_HALL4], ITEM_NONE));
	m_roomArray[ROOM_CYNTHIA]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_CYNTHIA], m_roomArray[ROOM_HALL1], ITEM_NONE));
	m_roomArray[ROOM_PROFESSOR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_PROFESSOR], m_roomArray[ROOM_HALL2], ITEM_A_BIG_IRON_KEY));
	m_roomArray[ROOM_DOCTOR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_DOCTOR], m_roomArray[ROOM_HALL1], ITEM_NONE));
	m_roomArray[ROOM_MAJOR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_MAJOR], m_roomArray[ROOM_HALL2], ITEM_NONE));
	m_roomArray[ROOM_MAJOR]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_HIDDEN, m_roomArray[ROOM_MAJOR], m_roomArray[ROOM_OUTSIDE2], ITEM_NONE));
	m_roomArray[ROOM_DINGLE]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_DINGLE], m_roomArray[ROOM_HALL1], ITEM_NONE));
	m_roomArray[ROOM_OUTSIDE1]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_OUTSIDE1], m_roomArray[ROOM_HALL1], ITEM_NONE));
	m_roomArray[ROOM_OUTSIDE2]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE2], m_roomArray[ROOM_PASSAGE1], ITEM_NONE));
	m_roomArray[ROOM_OUTSIDE2]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE2], m_roomArray[ROOM_MAJOR], ITEM_NONE));
	m_roomArray[ROOM_OUTSIDE3]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_OUTSIDE3], m_roomArray[ROOM_CLOCK], ITEM_NONE));
	m_roomArray[ROOM_OUTSIDE4]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_HIDDEN, m_roomArray[ROOM_OUTSIDE4], m_roomArray[ROOM_CELLAR], ITEM_NONE));
	m_roomArray[ROOM_OUTSIDE4]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE4], m_roomArray[ROOM_DRAWING], ITEM_NONE));
	m_roomArray[ROOM_OUTSIDE4]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE4], m_roomArray[ROOM_GARDEN], ITEM_NONE));
	m_roomArray[ROOM_PASSAGE1]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE1], m_roomArray[ROOM_REVEREND], ITEM_NONE));
	m_roomArray[ROOM_PASSAGE1]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE1], m_roomArray[ROOM_OUTSIDE2], ITEM_NONE));
	m_roomArray[ROOM_PASSAGE2]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE2], m_roomArray[ROOM_HALL1], ITEM_NONE));
	m_roomArray[ROOM_PASSAGE2]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE2], m_roomArray[ROOM_HALL2], ITEM_NONE));
	m_roomArray[ROOM_PASSAGE3]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE3], m_roomArray[ROOM_KITCHEN], ITEM_NONE));
	m_roomArray[ROOM_PASSAGE3]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE3], m_roomArray[ROOM_CELLAR], ITEM_NONE));
	m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_REVEREND], ITEM_NONE));
	m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_CYNTHIA], ITEM_NONE));
	m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_DOCTOR], ITEM_NONE));
	m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR4, new CDoor(DOOR_DOOR4, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_DINGLE], ITEM_NONE));
	m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR5, new CDoor(DOOR_DOOR5, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_OUTSIDE1], ITEM_NONE));
	m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR6, new CDoor(DOOR_DOOR6, DOORSTATE_OPEN, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_LANDING], ITEM_NONE));
	m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR7, new CDoor(DOOR_DOOR7, DOORSTATE_OPEN, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_PASSAGE2], ITEM_NONE));
	m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_PROFESSOR], ITEM_A_BIG_IRON_KEY));
	m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_MAJOR], ITEM_NONE));
	m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPEN, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_PASSAGE2], ITEM_NONE));
	m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR4, new CDoor(DOOR_DOOR4, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_SNIDE], ITEM_NONE));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_KITCHEN], ITEM_NONE));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_STAIRS], ITEM_NONE));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_LOCKED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_STUDY], ITEM_A_BUNCH_OF_KEYS));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR4, new CDoor(DOOR_DOOR4, DOORSTATE_LOCKED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_BENTLEY], ITEM_A_BUNCH_OF_KEYS));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR5, new CDoor(DOOR_DOOR5, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_DRAWING], ITEM_NONE));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR6, new CDoor(DOOR_DOOR6, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_LIBRARY], ITEM_NONE));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR7, new CDoor(DOOR_DOOR7, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_UTILITY], ITEM_NONE));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR8, new CDoor(DOOR_DOOR8, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_HALL4], ITEM_NONE));
	m_roomArray[ROOM_HALL4]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_HALL3], ITEM_NONE));
	m_roomArray[ROOM_HALL4]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_COOK], ITEM_NONE));
	m_roomArray[ROOM_HALL4]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_GABRIEL], ITEM_NONE));
	m_roomArray[ROOM_LANDING]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_LANDING], m_roomArray[ROOM_HALL1], ITEM_NONE));
	m_roomArray[ROOM_LANDING]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_LANDING], m_roomArray[ROOM_STAIRS], ITEM_NONE));
	m_roomArray[ROOM_KITCHEN]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_HIDDEN, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_PASSAGE3], ITEM_NONE));
	m_roomArray[ROOM_KITCHEN]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_HALL3], ITEM_NONE));
	m_roomArray[ROOM_KITCHEN]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPEN, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_DINING], ITEM_NONE));
	m_roomArray[ROOM_STAIRS]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_LANDING], ITEM_NONE));
	m_roomArray[ROOM_STAIRS]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_HALL3], ITEM_NONE));
	m_roomArray[ROOM_STAIRS]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPEN, m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_COURTYARD], ITEM_NONE));
	m_roomArray[ROOM_STAIRS]->SetDoor(DOOR_DOOR4, new CDoor(DOOR_DOOR4, DOORSTATE_LOCKED, m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_ANGUS_STAIRS], ITEM_A_BUNCH_OF_KEYS));
	m_roomArray[ROOM_STUDY]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_STUDY], m_roomArray[ROOM_HALL3], ITEM_A_BUNCH_OF_KEYS));
	m_roomArray[ROOM_CLOCK]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_CLOCK], m_roomArray[ROOM_OUTSIDE3], ITEM_NONE));
	m_roomArray[ROOM_CLOCK]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_CLOCK], m_roomArray[ROOM_DRAWING], ITEM_NONE));
	m_roomArray[ROOM_CELLAR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_CELLAR], m_roomArray[ROOM_PASSAGE3], ITEM_NONE));
	m_roomArray[ROOM_CELLAR]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_HIDDEN, m_roomArray[ROOM_CELLAR], m_roomArray[ROOM_OUTSIDE4], ITEM_NONE));
	m_roomArray[ROOM_DRAWING]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_CLOCK], ITEM_NONE));
	m_roomArray[ROOM_DRAWING]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_HALL3], ITEM_NONE));
	m_roomArray[ROOM_DRAWING]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_HIDDEN, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_OUTSIDE4], ITEM_NONE));
	m_roomArray[ROOM_LIBRARY]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_LIBRARY], m_roomArray[ROOM_HALL3], ITEM_NONE));	
	m_roomArray[ROOM_UTILITY]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_UTILITY], m_roomArray[ROOM_HALL3], ITEM_NONE));
	m_roomArray[ROOM_GARDEN]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_GARDEN], m_roomArray[ROOM_GRAVEYARD], ITEM_A_RED_KEY));
	m_roomArray[ROOM_GARDEN]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_GARDEN], m_roomArray[ROOM_OUTSIDE4], ITEM_NONE));
	m_roomArray[ROOM_GRAVEYARD]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_GRAVEYARD], m_roomArray[ROOM_GARDEN], ITEM_A_RED_KEY));
	m_roomArray[ROOM_COURTYARD]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_COURTYARD], m_roomArray[ROOM_STAIRS], ITEM_NONE));
	m_roomArray[ROOM_ANGUS_LANDING]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_ANGUS_LANDING], m_roomArray[ROOM_ANGUS_ROOM], ITEM_A_BUNCH_OF_KEYS));
	m_roomArray[ROOM_ANGUS_LANDING]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_ANGUS_LANDING], m_roomArray[ROOM_ANGUS_STAIRS], ITEM_NONE));
	m_roomArray[ROOM_ANGUS_ROOM]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_ANGUS_ROOM], m_roomArray[ROOM_ANGUS_LANDING], ITEM_A_BUNCH_OF_KEYS));
	m_roomArray[ROOM_ANGUS_ROOM]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_ANGUS_ROOM], m_roomArray[ROOM_ANGUS_SECRET], ITEM_NONE));
	m_roomArray[ROOM_ANGUS_SECRET]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_ANGUS_SECRET], m_roomArray[ROOM_ANGUS_ROOM], ITEM_NONE));
	m_roomArray[ROOM_ANGUS_STAIRS]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_ANGUS_STAIRS], m_roomArray[ROOM_STAIRS], ITEM_A_BUNCH_OF_KEYS));
	m_roomArray[ROOM_ANGUS_STAIRS]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_ANGUS_STAIRS], m_roomArray[ROOM_ANGUS_LANDING], ITEM_NONE));
	m_roomArray[ROOM_DINING]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_DINING], m_roomArray[ROOM_KITCHEN], ITEM_NONE));
	
	m_roomArray[ROOM_SNIDE]->AddItemCache(0, COL_FOUR_POSTER_BED);
	m_roomArray[ROOM_SNIDE]->AddItemCache(1, COL_CHEST_OF_DRAWERS);
	
	m_roomArray[ROOM_REVEREND]->AddItemCache(0, COL_FOUR_POSTER_BED);
	m_roomArray[ROOM_REVEREND]->AddItemCache(1, COL_CHEST_OF_DRAWERS);
	
	m_roomArray[ROOM_BENTLEY]->AddItemCache(0, COL_BED);
	m_roomArray[ROOM_BENTLEY]->AddItemCache(1, COL_CLOTHES_CUPBOARD);
	
	m_roomArray[ROOM_COOK]->AddItemCache(0, COL_BED);
	m_roomArray[ROOM_COOK]->AddItemCache(1, COL_CLOTHES_CUPBOARD);
	
	m_roomArray[ROOM_GABRIEL]->AddItemCache(0, COL_BED);
	m_roomArray[ROOM_GABRIEL]->AddItemCache(1, COL_CLOTHES_CUPBOARD);
	
	m_roomArray[ROOM_CYNTHIA]->AddItemCache(0, COL_FOUR_POSTER_BED);
	m_roomArray[ROOM_CYNTHIA]->AddItemCache(1, COL_CHEST_OF_DRAWERS);
	
	m_roomArray[ROOM_PROFESSOR]->AddItemCache(0, COL_FOUR_POSTER_BED);
	m_roomArray[ROOM_PROFESSOR]->AddItemCache(1, COL_CHEST_OF_DRAWERS);
	
	m_roomArray[ROOM_DOCTOR]->AddItemCache(0, COL_FOUR_POSTER_BED);
	m_roomArray[ROOM_DOCTOR]->AddItemCache(1, COL_CHEST_OF_DRAWERS);
	
	m_roomArray[ROOM_MAJOR]->AddItemCache(0, COL_FOUR_POSTER_BED);
	m_roomArray[ROOM_MAJOR]->AddItemCache(1, COL_CHEST_OF_DRAWERS);
	
	m_roomArray[ROOM_DINGLE]->AddItemCache(0, COL_FOUR_POSTER_BED);
	m_roomArray[ROOM_DINGLE]->AddItemCache(1, COL_CHEST_OF_DRAWERS);
	
	m_roomArray[ROOM_OUTSIDE1]->AddItemCache(0, COL_WINDOW);
	
	m_roomArray[ROOM_OUTSIDE3]->AddItemCache(0, COL_WINDOW);
	
	m_roomArray[ROOM_KITCHEN]->AddItemCache(0, COL_WOODEN_BOX);
	m_roomArray[ROOM_KITCHEN]->AddItemCache(1, COL_CUPBOARD1);
	m_roomArray[ROOM_KITCHEN]->AddItemCache(2, COL_CUPBOARD2);
	m_roomArray[ROOM_KITCHEN]->AddItemCache(3, COL_CUPBOARD3);
	m_roomArray[ROOM_KITCHEN]->AddItemCache(4, COL_CUPBOARD4);
	m_roomArray[ROOM_KITCHEN]->AddItemCache(5, COL_SINK);
	
	m_roomArray[ROOM_STUDY]->AddItemCache(0, COL_DESK);
	m_roomArray[ROOM_STUDY]->AddItemCache(1, COL_SHELVES);
	
	m_roomArray[ROOM_CLOCK]->AddItemCache(0, COL_CLOCK);
	
	m_roomArray[ROOM_CELLAR]->AddItemCache(0, COL_BOXES1);
	m_roomArray[ROOM_CELLAR]->AddItemCache(1, COL_BOXES2);
	m_roomArray[ROOM_CELLAR]->AddItemCache(2, COL_BOXES3);
	
	m_roomArray[ROOM_DRAWING]->AddItemCache(0, COL_FIREPLACE);
	m_roomArray[ROOM_DRAWING]->AddItemCache(1, COL_COAL_BUCKET);
	m_roomArray[ROOM_DRAWING]->AddItemCache(2, COL_PICTURE);
	m_roomArray[ROOM_DRAWING]->AddItemCache(3, COL_SAFE);
	
	m_roomArray[ROOM_LIBRARY]->AddItemCache(0, COL_BOOKCASE1);
	m_roomArray[ROOM_LIBRARY]->AddItemCache(1, COL_BOOKCASE2);
	
	m_roomArray[ROOM_UTILITY]->AddItemCache(0, COL_WASHING_MACHINE);
	m_roomArray[ROOM_UTILITY]->AddItemCache(1, COL_WASHING_BASKET);
	m_roomArray[ROOM_UTILITY]->AddItemCache(2, COL_CUPBOARD);
	m_roomArray[ROOM_UTILITY]->AddItemCache(3, COL_WOODEN_CABINET);
	
	m_roomArray[ROOM_GARDEN]->AddItemCache(0, COL_WINDOW);
	
	m_roomArray[ROOM_GRAVEYARD]->AddItemCache(0, COL_HEADSTONE1);
	m_roomArray[ROOM_GRAVEYARD]->AddItemCache(1, COL_HEADSTONE2);
	
	m_roomArray[ROOM_COURTYARD]->AddItemCache(0, COL_FOUNTAIN);
	m_roomArray[ROOM_COURTYARD]->AddItemCache(1, COL_GARGOYLE1);
	m_roomArray[ROOM_COURTYARD]->AddItemCache(2, COL_GARGOYLE2);
	m_roomArray[ROOM_COURTYARD]->AddItemCache(3, COL_GARGOYLE3);
	
	m_roomArray[ROOM_ANGUS_LANDING]->AddItemCache(0, COL_GOAT_LIKE_PAINTING);
	m_roomArray[ROOM_ANGUS_LANDING]->AddItemCache(1, COL_DESK_WITH_A_STATUE);
	m_roomArray[ROOM_ANGUS_LANDING]->AddItemCache(2, COL_TROPHY);
	
	m_roomArray[ROOM_ANGUS_ROOM]->AddItemCache(0, COL_ANGUS_BOOKCASE);
	m_roomArray[ROOM_ANGUS_ROOM]->AddItemCache(1, COL_KNIGHT);
	m_roomArray[ROOM_ANGUS_ROOM]->AddItemCache(2, COL_COUCH);
	m_roomArray[ROOM_ANGUS_ROOM]->AddItemCache(3, COL_TABLE);
	
	m_roomArray[ROOM_ANGUS_SECRET]->AddItemCache(0, COL_HOURGLASS);
	m_roomArray[ROOM_ANGUS_SECRET]->AddItemCache(1, COL_GOLDEN_SKULL);
	
	m_roomArray[ROOM_DINING]->AddItemCache(0, COL_GLASS_CABINET);

	// ----------------------------
	
	CPathFinder::Initialize(m_roomArray);
	
	CGoal* pGoal = NULL;
	
	// ================================================================
	// Reverend
	// ================================================================
	
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(GOAL_JUMPROOM, m_roomArray[ROOM_DRAWING]));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(GOAL_JUMPPOINT, new Point(232, m_roomArray[ROOM_DRAWING]->CentreY())));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(GOAL_WAIT, 400));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(pGoal = new CGoal(GOAL_SPEAK, (const char*) NULL, 500));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(392, 144), 200));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(120, 184), 200));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(232, m_roomArray[ROOM_DRAWING]->CentreY()), 0));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(GOAL_GOTOGOAL, pGoal, 0));
	
	//	232, CENTRE_Y	(Drawing, Start, Wait)
	// Loop:
	//	Speak			""
	// Goto Loop
	//	392, 144		(Drawing, Fireplace, Wait)
	
	// ================================================================
	// Bentley
	// ================================================================
		
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_JUMPROOM, m_roomArray[ROOM_STAIRS]));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_JUMPPOINT, new Point(176, m_roomArray[ROOM_STAIRS]->CentreY())));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_SPEAK, "BENTLEY ADVANCES:\"THIS WAY TO YOUR ROOM SIR\"", 100));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_HALL2], 0));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(640, 144), 0));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_SPEAK, "\"YOUR ROOM SIR\"", 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_HALL3], 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(pGoal = new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_BENTLEY], 0));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(72, 160), 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_BENTLEY], m_roomArray[ROOM_DRAWING], 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_HALL3], 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_HALL4], 0));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(80, m_roomArray[ROOM_HALL4]->CentreY()), 0));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(128, m_roomArray[ROOM_HALL4]->CentreY()), 0));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(80, m_roomArray[ROOM_HALL4]->CentreY()), 0));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(128, m_roomArray[ROOM_HALL4]->CentreY()), 0));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_COOK], 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_COOK], m_roomArray[ROOM_LIBRARY], 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_LIBRARY], m_roomArray[ROOM_HALL3], 0));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(GOAL_GOTOGOAL, pGoal, 0));
	
	//	176, CENTRE_Y	(Stairs, Start, Wait)
	//	Speak			"THIS WAY TO YOUR ROOM SIR"
	//	Hall 2
	//	640, 144		(Hall 2, Wait)
	//	Speak			"YOUR ROOM SIR"
	// Loop:
	//	Hall 3			(wait)
	//	Bentley
	//	72, 160			(Wait)
	//	Drawing			(Wait)
	//	Hall 3			(Wait)
	//	Hall 4
	//	80, CENTRE_Y	(Hall 4, Wait)
	//	128, CENTRE_Y	(Hall 4, Wait)
	//	80, CENTRE_Y	(Hall 4, Wait)
	//	128, CENTRE_Y	(Hall 4, Wait)
	//	Cook			(Wait, If walk in Bentley says "Ahem" and leaves, What happens if you don't enter?)
	//	Library			(Wait)
	// Goto Loop
	
	//	Hall 3			(Wait)
	//	Bentley
	//	72, 160			(Wait)
	//	Drawing			(Wait)
	//	Hall 3			(Wait)
	//	Hall 4
	//	80, CENTRE_Y	(Hall 4, Wait for Cook)
	//	128, CENTRE_Y	(Hall 4, Wait for Cook)
	//	Cook			(Close Door with Cook, Wait)
	//	Library			(Doctor walked into Hall3 says "Dingles been strangled", Wait)
	//	Hall 3			(Wait)
	//	Bentley
	//	72, 160			(Wait)
	
	// ================================================================
	// Cook
	// ================================================================
	
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_JUMPROOM, m_roomArray[ROOM_KITCHEN]));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_JUMPPOINT, new Point(104, m_roomArray[ROOM_KITCHEN]->CentreY())));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_WAIT, 300));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(360, 152), 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(72, 152), 200));
	m_characterArray[CHARTYPE_COOK]->AddGoal(pGoal = new CGoal(GOAL_GOTOPOINT, new Point(360, 152), 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(96, 152), 200));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(360, 152), 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(32, 184), 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(392, 144), 200));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_COOK], 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(216, 144), 500));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_COOK], m_roomArray[ROOM_KITCHEN], 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(72, 152), 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(360, 152), 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(72, 152), 200));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(360, 152), 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(72, 152), 200));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(360, 152), 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(32, 184), 200));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(392, 144), 200));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_COOK], 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(216, 144), 500));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_COOK], m_roomArray[ROOM_KITCHEN], 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(72, 152), 200));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_SPEAK, "\"OOH YES I KNOW DEAR..\"", 200));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(GOAL_GOTOGOAL, pGoal, 0));
	
	//	104, CENTRE_Y	(Kitchen, Start, Wait)
	//	360, 152		(Kitchen)
	//	72, 152			(Kitchen, Wait)
	// Loop:
	//	360, 152		(Kitchen)
	//	96, 152			(Kitchen, Wait)
	//	360, 152		(Kitchen)
	//	32, 184			(Kitchen)
	//	Drawing
	//	392, 144		(Drawing, Fireplace, Wait)
	//	Cook
	//	216, 144		(Cook, Wait, Bentleys waiting outside her room)
	//	Kitchen
	//	72, 152			(Kitchen)
	//	360, 152		(Kitchen)
	//	72, 152			(Kitchen, Wait)
	//	360, 152		(Kitchen)
	//	96, 152			(Kitchen, Wait)
	//	360, 152		(Kitchen)
	//	32, 184			(Kitchen, Wait)
	//	Drawing
	//	392, 144		(Drawing, Fireplace)
	//	Cook			(Closes and locks door with Bentley instead)
	//	Kitchen
	//	72, 152			(Kitchen, Wait)
	//	Speaks			"OOH YES I KNOW DEAR.."
	// Goto Loop
	
	// ================================================================
	// Gabriel
	// ================================================================
	
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(GOAL_JUMPROOM, m_roomArray[ROOM_KITCHEN]));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(GOAL_JUMPPOINT, new Point(208, m_roomArray[ROOM_KITCHEN]->CentreY())));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(GOAL_WAIT, 500));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(pGoal = new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_HALL3], 0));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(464, 144), 0));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_GABRIEL], 0));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(288, 144), 200));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_GABRIEL], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(344, 144), 0));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_KITCHEN], 0));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(96, 168), 200));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(GOAL_SPEAK, "\"..DUM DE DAH..\"", 200));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(GOAL_GOTOGOAL, pGoal, 0));
	
	//	208, CENTRE_Y	(Kitchen, Start, Wait (Longer than Cook))
	// Loop:
	//	Hall 3
	//	464, 144		(Hall 3, (Outside Study, What if it's not locked?))
	//	Gabriel
	//	288, 144		(Gabriel, Wait)
	//	Drawing
	//	328, 144		(Drawing)
	//	Kitchen
	//	96, 168			(Wait)
	//	Speak			"..DUM DE DAH.."
	// Goto Loop
	
	// ================================================================
	// Cynthia
	// ================================================================
	
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_JUMPROOM, m_roomArray[ROOM_CYNTHIA]));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_JUMPPOINT, new Point(232, m_roomArray[ROOM_CYNTHIA]->CentreY())));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_WAIT, 500));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_CYNTHIA], m_roomArray[ROOM_HALL1], 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(pGoal = new CGoal(GOAL_GOTOPOINT, new Point(136, 144), 0));	// Reverend
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(312, 144), 0));	// Cynthia
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(592, 144), 0));	// Dingle
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_CYNTHIA], 200));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_SPEAK, "\"HELLO..\"", 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_CYNTHIA], m_roomArray[ROOM_OUTSIDE1], 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(240, 144), 200));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_SPEAK, "\"AWFUL WEATHER..\"", 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_OUTSIDE1], m_roomArray[ROOM_MAJOR], 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(240, 160), 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(248, 128), 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(240, 160), 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_MAJOR], m_roomArray[ROOM_LANDING], 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_LANDING], m_roomArray[ROOM_CYNTHIA], 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_CYNTHIA], m_roomArray[ROOM_HALL1], 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_CYNTHIA], 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(240, 160), 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_SPEAK, "CYNTHIA SNIFFS DISAPPROVINGLY..", 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(248, 128), 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_CYNTHIA], m_roomArray[ROOM_HALL1], 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(592, 144), 0));	// Dingle
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(328, 184), 0));	// Landing
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(GOAL_GOTOGOAL, pGoal, 0));
	
	//	232, CENTRE_Y	(Cynthia, Start, Wait)
	
	// ================================================================
	// Professor
	// ================================================================
	
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_JUMPROOM, m_roomArray[ROOM_LIBRARY]));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_JUMPPOINT, new Point(136, m_roomArray[ROOM_LIBRARY]->CentreY())));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_WAIT, 500));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(pGoal = new CGoal(GOAL_GOTOPOINT, new Point(112, 144), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_SPEAK, "\"WHERE IS IT?\"", 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(312, 144), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(112, 144), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(312, 144), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(112, 144), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_LIBRARY], m_roomArray[ROOM_HALL3], 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(96, m_roomArray[ROOM_HALL3]->CentreY()), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_SPEAK, "\"GOODNESS!\"", 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(472, 144), 0)); // Study (locked)
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_SPEAK, "\"THAT'S ODD\"", 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(136, 184), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(176, m_roomArray[ROOM_HALL3]->CentreY()), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(136, 184), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(176, m_roomArray[ROOM_HALL3]->CentreY()), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(136, 184), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(176, m_roomArray[ROOM_HALL3]->CentreY()), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_CLOCK], 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(72, 184), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_CLOCK], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(376, 144), 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_LIBRARY], 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(168, 144), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_SPEAK, "\"YES!\"", 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(GOAL_GOTOGOAL, pGoal, 0));
	
	//	136, CENTRE_Y	(Library, Start, Wait)
	
	// ================================================================
	// Doctor
	// ================================================================
	
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_JUMPROOM, m_roomArray[ROOM_OUTSIDE3]));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_JUMPPOINT, new Point(176, m_roomArray[ROOM_OUTSIDE3]->CentreY())));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_WAIT, 500));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(256, 184), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(176, m_roomArray[ROOM_OUTSIDE3]->CentreY()), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(256, 184), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_SPEAK, "THE DOCTOR GLANCES AT HIS WATCH..", 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(168, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(80, 184), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(32, 184), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(344, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(176, m_roomArray[ROOM_OUTSIDE3]->CentreY()), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(256, 184), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_SPEAK, "THE DOCTOR GLANCES AT HIS WATCH..", 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(168, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(80, 184), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(32, 184), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(344, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(176, m_roomArray[ROOM_OUTSIDE3]->CentreY()), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(256, 184), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_SPEAK, "THE DOCTOR GLANCES AT HIS WATCH..", 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(168, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(80, 184), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_OUTSIDE3], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(344, 144), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_SPEAK, "\"HAS ANYONE SEEN MY SCALPLES?\"", 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(312, m_roomArray[ROOM_DRAWING]->CentreY()), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(344, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_CLOCK], 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(80, 184), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_CLOCK], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(344, 144), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_SPEAK, "\"HAS ANYONE SEEN MY SCALPLES?\"", 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(312, m_roomArray[ROOM_DRAWING]->CentreY()), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(344, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_CLOCK], 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(80, 184), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_CLOCK], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(344, 144), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_SPEAK, "\"HAS ANYONE SEEN MY SCALPLES?\"", 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(312, m_roomArray[ROOM_DRAWING]->CentreY()), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(344, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_CLOCK], 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(80, 184), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_CLOCK], m_roomArray[ROOM_DRAWING], 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_DOCTOR], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(248, 152), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DOCTOR], m_roomArray[ROOM_DINGLE], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(248, 152), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(360, 120), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_SPEAK, "\"INSPECTOR..MR. DINGLE'S BEEN STRANGLED!\"", 200)); // "HERE.."
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_SPEAK, "\"POOR FELLOW ..TERRIBLE\"", 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DINGLE], m_roomArray[ROOM_DOCTOR], 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DOCTOR], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(368, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_HALL3], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(pGoal = new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_OUTSIDE3], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(240, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_OUTSIDE3], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(64, 184), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(GOAL_GOTOGOAL, pGoal, 0));
	
	//	176, CENTRE_Y	(Outside 3, Start, Wait)
	
	// ================================================================
	// Major
	// ================================================================
	
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(GOAL_JUMPROOM, m_roomArray[ROOM_MAJOR]));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(GOAL_JUMPPOINT, new Point(232, m_roomArray[ROOM_MAJOR]->CentreY())));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(GOAL_WAIT, 500));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(pGoal = new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_MAJOR], m_roomArray[ROOM_CYNTHIA], 0));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(240, 160), 0));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_CYNTHIA], m_roomArray[ROOM_HALL1], 0));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_OUTSIDE1], 0));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(264, 144), 200));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(80, 184), 200));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_OUTSIDE1], m_roomArray[ROOM_HALL2], 200));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_MAJOR], 200));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(GOAL_GOTOGOAL, pGoal, 0));
	
	
	//	232, CENTRE_Y	(Major, Start, Wait)
	
	// ================================================================
	// Dingle
	// ================================================================
	
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(GOAL_JUMPROOM, m_roomArray[ROOM_DRAWING]));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(GOAL_JUMPPOINT, new Point(232, m_roomArray[ROOM_DRAWING]->CentreY())));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(GOAL_WAIT, 700));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(392, 144), 200));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(480, 144), 200));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_HALL3], 0));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(392, 152), 200));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_HALL1], 0));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(376, 176), 200));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(GOAL_GOTOROOM, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_DINGLE], 0));
	
	//	232, CENTRE_Y	(Drawing, Start, Wait)
	//	392, 144		(Drawing, Fireplace, Wait)
	//	480, 144		(Drawing, Picture, Wait)
	//	Hall3
	//	392, 152		(Hall3, Wait)
	//	Hall1
	//	376, 176		(Hall1, Wait)
	//	Dingle			(Wait)
	//	Die				(Wait)
	//	Unlock door
	
	// ================================================================
	// Angus
	// ================================================================
	
	m_characterArray[CHARTYPE_ANGUS]->AddGoal(new CGoal(GOAL_JUMPROOM, m_roomArray[ROOM_ANGUS_ROOM]));
	m_characterArray[CHARTYPE_ANGUS]->AddGoal(new CGoal(GOAL_JUMPPOINT, new Point(232, m_roomArray[ROOM_ANGUS_ROOM]->CentreY())));
	m_characterArray[CHARTYPE_ANGUS]->AddGoal(new CGoal(GOAL_WAIT, 500));
	m_characterArray[CHARTYPE_ANGUS]->AddGoal(pGoal = new CGoal(GOAL_GOTOPOINT, new Point(64, 160), 500));
	m_characterArray[CHARTYPE_ANGUS]->AddGoal(new CGoal(GOAL_GOTOPOINT, new Point(232, 160), 500));
	m_characterArray[CHARTYPE_ANGUS]->AddGoal(new CGoal(GOAL_GOTOGOAL, pGoal, 0));
	
	//	232, CENTRE_Y	(Angus Room, Start, Wait)
	
	// ----------------------------
	
	m_eventArray[EVENT_SHOW_ROOM] = new CEvent(EVENT_SHOW_ROOM, new CTime(9, 10, 0, 0));
	m_eventArray[EVENT_GET_SHOT] = new CEvent(EVENT_SHOW_ROOM, new CTime(11, 30, 0, 0));	// 2:20
	
	m_cursor = new CCursor();
	m_pointer = new CPointer();
	
	m_console = new CConsole(m_cursor);
	m_keyboard = new CKeyboard(m_cursor);
	m_menu = new CMenu();

	m_watch = new CWatch(113, 21);
	m_timer = new CTimer();
	
	InitDoors();
	
	m_fxManager.SetFx(FXTYPE_C64, FXMODE_NORMAL, false);
	
	InitTitleScreen();
}

void CGame::Update()
{
	static u8 lastUpdate = 0;
	u8 elapsedTime;
	touchPosition touch;
	int keys_held, keys_pressed, keys_released;
	
	touchRead(&touch);
	scanKeys();
	
	keys_held = keysHeld();
	keys_pressed = keysDown();
	keys_released = keysUp();
	
	elapsedTime = m_timer->pCurrentTime()->MilliSeconds - lastUpdate;
	lastUpdate = m_timer->pCurrentTime()->MilliSeconds;
	
	//char buf[256];
	//sprintf(buf, "%02d:%02d:%02d:%02d Elapsed: %08d", m_timer->pCurrentTime()->Hours, m_timer->pCurrentTime()->Minutes, m_timer->pCurrentTime()->Seconds, m_timer->pCurrentTime()->MilliSeconds, elapsedTime);
	//fprintf(stderr, buf);
	
	if(keys_released & KEY_L || keys_released & KEY_R)
	{
		lcdSwap();
	}
	
	switch(m_gameMode)
	{
	case GAMEMODE_INTRO:
		if(keys_released & KEY_START)
			InitData();
		else
			UpdateIntro();
		break;
	case GAMEMODE_TITLESCREEN:
		if(keys_released & KEY_START)
			InitGame(GAMETYPE_NORMAL);
		else
			UpdateTitleScreen();
		break;
	case GAMEMODE_PAUSED:
		if(keys_released & KEY_A || keys_pressed & KEY_TOUCH)
		{
			m_gameMode = GAMEMODE_RUNNING;
			m_console->Clear();
			m_timer->Start();
		}
		else
		{
			m_console->Update();
			m_cursor->Update();
			m_cursor->Show();
		}
		break;
	case GAMEMODE_RUNNING:
		UpdateGame(touch, keys_held, keys_pressed, keys_released);
		break;
	case GAMEMODE_DYING:
		if(++m_dieFrameCount == 500)
		{
			m_dieFrameCount = 0;
			
			m_snide->SetCharacterMode(CHARMODE_DEAD);
			m_snide->Update(m_currentRoom);
			m_snide->Draw();
			m_console->AddText("YOU GASP IN AGONY AND DROP DEAD..");
			InitGameOver(GAMEOVERMODE_END);
		}
		else
			UpdateGame(touch, keys_held, keys_pressed, keys_released);
		break;
	case GAMEMODE_REVERSETIME:
		if(++m_reverseTimeFrameCount == 500)
		{
			m_reverseTimeFrameCount = 0;
			
			m_gameMode = GAMEMODE_RUNNING;
		}
		else
		{
			UpdateGame(touch, keys_held, keys_pressed, keys_released);
			m_timer->Reverse();
		}
		break;
	case GAMEMODE_GAMEOVER:
		if(keys_released & KEY_A || keys_pressed & KEY_TOUCH)
			InitTitleScreen();
		else UpdateGameOver();
		break;
	default:
		break;
	}
	
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
}

void CGame::UpdateDisplayMode(touchPosition touch, int keys_held, int keys_pressed, int keys_released)
{
	//static mm_sfxhand footsteps = 0;
	
	switch(m_displayMode)
	{
	case DISPLAYMODE_GAME:
		{
			m_openMode = OPENMODE_ROOM;

			UpdateSnideMovement(keys_held);
			
			if(m_questionMode == QUESTIONMODE_WAITING)
			{
				if(m_questionCharacter->GetCharacterMode() != CHARMODE_WAITING && 
					m_questionCharacter->GetCharacterMode() != CHARMODE_TALKING)
				{
					m_displayMode = DISPLAYMODE_GAME;
					m_questionMode = QUESTIONMODE_NONE;
					m_pointer->Hide();
					m_menu->Hide();
					m_console->HideMenu();
				}
				else if(keys_released & KEY_A || keys_pressed & KEY_TOUCH)
				{
					CharacterType charNear, charFar;
					
					if(CheckCharacterCollision(m_snide->Facing(), &charNear, &charFar))
					{					
						if(charNear == m_questionCharacter->GetCharacterType() || charFar == m_questionCharacter->GetCharacterType())
						{
							m_displayMode = DISPLAYMODE_CONSOLE_MENU;
							m_questionMode = QUESTIONMODE_ASKABOUT;
							m_lastIconType = ICON_QUESTION;
							
							m_questionCharacter->SetCharacterMode(CHARMODE_NONE);
							m_console->AddText("ASK ABOUT:");
							m_console->ClearMenu();
							m_console->AddMenuItem("MR MCFUNGUS", NULL);
							m_console->AddMenuItem("AN OBJECT", NULL);
							m_console->AddMenuItem("ANOTHER GUEST", NULL);
							m_console->ShowMenu();
							m_console->DrawSelectorBar();
						}
						else
						{
							m_displayMode = DISPLAYMODE_GAME;
							m_pointer->Hide();
							m_menu->Hide();
							m_console->HideMenu();
						}
					}
					else
					{
						m_displayMode = DISPLAYMODE_MENU;
						SetMenuIcons(MENUMODE_GENERAL, NULL);
						m_snide->SetCharacterMode(CHARMODE_NONE);
						m_pointer->SetRect(MENU_X, MENU_Y, MENU_WIDTH, MENU_HEIGHT);
						//m_pointer->SetRect(CONSOLE_MENU_X, CONSOLE_MENU_Y, CONSOLE_MENU_WIDTH, CONSOLE_MENU_HEIGHT);
					}
				}
			}
			else
			{
				if(keys_released & KEY_A || keys_pressed & KEY_TOUCH)
				{
					m_displayMode = DISPLAYMODE_MENU;
					SetMenuIcons(MENUMODE_GENERAL, NULL);
					m_snide->SetCharacterMode(CHARMODE_NONE);
					m_pointer->SetRect(MENU_X, MENU_Y, MENU_WIDTH, MENU_HEIGHT);
					//m_pointer->SetRect(CONSOLE_MENU_X, CONSOLE_MENU_Y, CONSOLE_MENU_WIDTH, CONSOLE_MENU_HEIGHT);
				}
			}
		}
		break;
	case DISPLAYMODE_MENU:
		{
			if(keys_pressed & KEY_TOUCH)
			{
				m_displayMode = DISPLAYMODE_GAME;
				
				ProcessMenu(touch.px, touch.py);
				m_pointer->Hide();
				m_menu->Hide();
			}
			else if(keys_released & KEY_A)
			{
				m_displayMode = DISPLAYMODE_GAME;

				Point* pPoint = m_pointer->pPoint();
				ProcessMenu(pPoint->X, pPoint->Y);
				m_pointer->Hide();
				m_menu->Hide();
			}
			else
			{
				Point* pPoint = m_pointer->pPoint();
				m_pointer->Move(keys_held);
				m_pointer->Update();
				m_menu->DrawBox(pPoint->X, pPoint->Y);
			}
		}
		break;
	case DISPLAYMODE_CONSOLE:
		{
			if(keys_released & KEY_A || keys_released & KEY_B || keys_released & KEY_LEFT || keys_released & KEY_RIGHT)
			{
				m_displayMode = DISPLAYMODE_GAME;
				m_pointer->Hide();
				m_menu->Hide();
				m_console->HideMenu();
			}
			else if(keys_released & KEY_UP)
			{
				m_console->Move(DIRECTION_UP);
			}
			else if(keys_released & KEY_DOWN)
			{
				m_console->Move(DIRECTION_DOWN);
			}
			else if(keys_pressed & KEY_TOUCH)
			{
				m_console->CheckTouch(touch.px, touch.py);
			}
		}
		break;
	case DISPLAYMODE_CONSOLE_MENU:
		{
			if(keys_released & KEY_A)
			{
				PostProcessMenu();
			}
			else if(keys_released & KEY_B || keys_released & KEY_LEFT || keys_released & KEY_RIGHT)
			{
				m_displayMode = DISPLAYMODE_GAME;
				m_pointer->Hide();
				m_menu->Hide();
				m_console->HideMenu();
			}
			else if(keys_released & KEY_UP)
			{
				m_console->MoveSelectorBar(DIRECTION_UP);
				m_console->DrawSelectorBar();
			}
			else if(keys_released & KEY_DOWN)
			{
				m_console->MoveSelectorBar(DIRECTION_DOWN);
				m_console->DrawSelectorBar();
			}
			else if(keys_pressed & KEY_TOUCH)
			{
				if(m_console->CheckMenuTouch(touch.px, touch.py))
				{
					PostProcessMenu();
				}
			}
		}
		break;
	case DISPLAYMODE_KEYBOARD:
		{
			if(keys_pressed & KEY_TOUCH)
			{		
				char c = m_keyboard->CheckKeyTouch(touch.px, touch.py);
				
				switch(c)
				{
				case 0:
					break;
				case '\e':	// Exit
					{
						m_displayMode = DISPLAYMODE_GAME;
						
						m_keyboard->Hide();
						m_fxManager.SetFx(FXTYPE_TEXT_SCROLLER, FXMODE_NORMAL, true);
						m_console->Clear();
						m_menu->Hide();
						
						mmEffectEx(&g_sfx_beep);
					}
					break;
				case '\n':
					{
						const char* text = m_keyboard->GetText();
						
						switch(m_keyboardMode)
						{
							case KEYBOARDMODE_BOOK1:
								{
									if(strcmp(text, "101 DETECTIVE STORIES") == 0)
									{
										if(m_itemArray[ITEM_A_HARDBACK_BOOK]->GetParent() == NULL)
										{
											m_console->AddText("YOU FIND THE BOOK.");
											CItemCache* itemCache = m_snide->GetItemCache();
											
											itemCache->AddItem(m_itemArray[ITEM_A_HARDBACK_BOOK]);
										}
										else
										{
											m_console->AddText("YOU DO NOT FIND THE BOOK.");
										}
									}
									else
									{
										m_console->AddText("YOU DO NOT FIND THE BOOK.");
									}
								}
								break;
							case KEYBOARDMODE_BOOK2:
								m_console->AddText("YOU DO NOT FIND THE BOOK.");
								break;
							case KEYBOARDMODE_SAFE:
								{
									if(strncmp(text, "210319", 6) == 0)
									{
										CItemCache* itemCache = m_currentRoom->GetItemCache(3);
										
										if(itemCache->ContainsItem(m_itemArray[ITEM_THE_WILL]))
										{									
											m_currentRoom->SetAnimFrame(DSTRECT_SAFE, 1);
											m_currentRoom->SetAnimState(DSTRECT_SAFE, ANIMSTATE_PLAY);
											m_currentRoom->Draw();
										}
										else
										{
											m_currentRoom->SetAnimFrame(DSTRECT_SAFE, 2);
											m_currentRoom->SetAnimState(DSTRECT_SAFE, ANIMSTATE_PLAY);
											m_currentRoom->Draw();
										}
										
										m_console->AddText("THE SAFE IS OPEN!");
										
										mmEffectEx(&g_sfx_opendoor);
									}
									else
									{
										m_console->AddText("THE SAFE DOESN'T OPEN");
									}
								}
								break;
						}
						
						m_displayMode = DISPLAYMODE_GAME;
						
						m_keyboard->Hide();
						m_fxManager.SetFx(FXTYPE_TEXT_SCROLLER, FXMODE_NORMAL, true);
						m_menu->Hide();
						
						mmEffectEx(&g_sfx_beep);
					}
					break;
				default:
					mmEffectEx(&g_sfx_click);
					break;
				}
			}
		}
		break;
	}
}

void CGame::UpdateSnideMovement(int keys_held)
{
	CollisionType colNear, colFar;
	CharacterType charNear, charFar;
	CDoor* pDoor = NULL;
	
	if(keys_held & KEY_UP)
	{
		if(!m_footsteps)
			m_footsteps = mmEffectEx(&g_sfx_footsteps);
		
		if(m_snide->SpriteX() < 256 - m_snide->Width() - 8)
		{
			m_snide->CheckCollision(DIRECTION_UP, &colNear, &colFar);
			
			//if(CheckCharacterCollision(DIRECTION_UP, &charNear, &charFar))
			//	DrawString(" DIRECTION UP      ", 0, 0, false);
			//else
			//	DrawString("                   ", 0, 0, false);
			
			if(colNear == COL_NOTHING_HERE)
				m_snide->Move(DIRECTION_UP);
			else
				m_snide->Face(DIRECTION_UP);
				
			if(colNear >= COL_GARGOYLE1 && colNear <= COL_GARGOYLE3)
			{
				if(colNear == COL_GARGOYLE3 && m_gargoyleActive[0] && m_gargoyleActive[1] && !m_gargoyleActive[2])
				{
					m_gargoyleActive[2] = true;
					
					m_currentRoom->SetAnimFrame(DSTRECT_FOUNTAIN, 0);
					m_currentRoom->SetAnimState(DSTRECT_FOUNTAIN, ANIMSTATE_STOP);
					m_currentRoom->Draw();
					
					//CItemCache* itemCache = m_roomArray[ROOM_COURTYARD]->GetItemCache(0);
					//itemCache->AddItem(m_itemArray[ITEM_RED_KEY]);
					mmEffectEx(&g_sfx_drain);
				}
				else if(colNear == COL_GARGOYLE1 && m_gargoyleActive[0])
					m_gargoyleActive[1] = true;
				else if(colNear == COL_GARGOYLE3)
					m_gargoyleActive[0] = true;
				else
					{ m_gargoyleActive[0] = false; m_gargoyleActive[1] = false; m_gargoyleActive[2] = false; }
			}
			
			if(TryGetDoor(colNear, colNear, &pDoor))
			{
				if(pDoor->GetDoorState() == DOORSTATE_OPEN)
				{		
					m_currentRoom = pDoor->pRoomOut();
					Point* pDoorPoint = pDoor->pDoorOut()->pPoint();
					
					int xDoor = pDoorPoint->X * 8;
					int yDoor = pDoorPoint->Y * 8;
					
					int xRoom = xDoor - 128;
					
					int xChar = xDoor;
					int yChar = yDoor - m_snide->Height() - 8;
						
					pDoor->pDoorOut()->SetDoorState(DOORSTATE_OPEN);
					
					m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
					
					m_currentRoom->Initialize(xRoom);
					m_snide->SetRoom(m_currentRoom);
					m_snide->SetPosition(xChar, yChar);
					
					m_console->AddText(g_enterRoomText[m_currentRoom->GetRoomType()]);
					
					InitRoom();
					
					//m_fxManager.SetFx(FX_FADE_BLACK_IN, true);
					
					//char buf[256];
					//sprintf(buf, "xDoor: %05d, xRoom: %05d, xChar: %05d", xDoor, xRoom, xChar);
					//DrawString(buf, 0, 1, false);
				}
			}
		}
	}
	else if(keys_held & KEY_DOWN)
	{
		if(!m_footsteps)
			m_footsteps = mmEffectEx(&g_sfx_footsteps);
		
		if(m_snide->SpriteX() > 8)
		{
			m_snide->CheckCollision(DIRECTION_DOWN, &colNear, &colFar);
			
			//if(CheckCharacterCollision(DIRECTION_DOWN, &charNear, &charFar))
			//	DrawString(" DIRECTION DOWN    ", 0, 0, false);
			//else
			//	DrawString("                   ", 0, 0, false);
			
			if(colNear == COL_NOTHING_HERE)
				m_snide->Move(DIRECTION_DOWN);
			else
				m_snide->Face(DIRECTION_DOWN);
			
			if(TryGetDoor(colNear, colNear, &pDoor))
			{
				if(pDoor->GetDoorState() == DOORSTATE_OPEN)
				{
					m_currentRoom = pDoor->pRoomOut();
					Point* pDoorPoint = pDoor->pDoorOut()->pPoint();
						
					int xDoor = pDoorPoint->X * 8;
					int yDoor = pDoorPoint->Y * 8;
					
					int xRoom = xDoor - 128;
					
					int xChar = xDoor;
					int yChar = yDoor - m_snide->Height() + 8;
					
					pDoor->pDoorOut()->SetDoorState(DOORSTATE_OPEN);
					
					m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
					
					m_currentRoom->Initialize(xRoom);
					m_snide->SetRoom(m_currentRoom);
					m_snide->SetPosition(xChar, yChar);
					
					m_console->AddText(g_enterRoomText[m_currentRoom->GetRoomType()]);
					
					InitRoom();
					
					//m_fxManager.SetFx(FX_FADE_BLACK_IN, true);
					
					//char buf[256];
					//sprintf(buf, "xDoor: %05d, xRoom: %05d, xChar: %05d", xDoor, xRoom, xChar);
					//DrawString(buf, 0, 1, false);
				}
			}
		}
	}
	else if(keys_held & KEY_LEFT)
	{
		if(!m_footsteps)
			m_footsteps = mmEffectEx(&g_sfx_footsteps);
		
		m_snide->CheckCollision(DIRECTION_LEFT, &colNear, &colFar);
		
		//if(CheckCharacterCollision(DIRECTION_LEFT, &charNear, &charFar))
		//	DrawString(" DIRECTION LEFT    ", 0, 0, false);
		//else
		//	DrawString("                   ", 0, 0, false);
		
		if(colNear == COL_NOTHING_HERE)
		{
			m_snide->Move(DIRECTION_LEFT);
			
			if(m_snide->SpriteX() < 128)
				m_currentRoom->Scroll(DIRECTION_LEFT);
		}
		else
		{
			if(TryGetDoor(colNear, colFar, &pDoor))
			{
				m_currentRoom = pDoor->pRoomOut();
				
				pDoor->pDoorOut()->SetDoorState(DOORSTATE_OPEN);
				
				int xChar = m_currentRoom->Width() - m_snide->Width() - 8;
				
				m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
			
				m_currentRoom->Initialize(m_currentRoom->Width() - 256);
				m_snide->SetRoom(m_currentRoom);
				m_snide->SetX(xChar);
				
				m_console->AddText(g_enterRoomText[m_currentRoom->GetRoomType()]);
				
				InitRoom();
			}
		}
	}
	else if(keys_held & KEY_RIGHT)
	{
		if(!m_footsteps)
			m_footsteps = mmEffectEx(&g_sfx_footsteps);
		
		m_snide->CheckCollision(DIRECTION_RIGHT, &colNear, &colFar);
		
		//if(CheckCharacterCollision(DIRECTION_RIGHT, &charNear, &charFar))
		//	DrawString(" DIRECTION RIGHT   ", 0, 0, false);
		//else
		//	DrawString("                   ", 0, 0, false);
		
		if(colNear == COL_NOTHING_HERE)
		{
			m_snide->Move(DIRECTION_RIGHT);
			
			if(m_snide->SpriteX() > 128)
				m_currentRoom->Scroll(DIRECTION_RIGHT);
		}
		else
		{
			if(TryGetDoor(colNear, colFar, &pDoor))
			{
				m_currentRoom = pDoor->pRoomOut();
				
				pDoor->pDoorOut()->SetDoorState(DOORSTATE_OPEN);
				
				int xChar = 8;
				
				m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
						
				m_currentRoom->Initialize(0);
				m_snide->SetRoom(m_currentRoom);
				m_snide->SetX(xChar);
				
				m_console->AddText(g_enterRoomText[m_currentRoom->GetRoomType()]);
				
				InitRoom();
			}
		}
	}
	else
	{
		mmEffectCancel(m_footsteps);
		m_footsteps = 0;
		
		m_snide->SetCharacterMode(CHARMODE_NONE);
	}
}

void CGame::SetMenuIcons(MenuMode menuMode, CItem* pItem)
{
	CollisionType colNear, colFar;
	CharacterType charNear, charFar;
	CDoor* pDoor = NULL;
	CItemCache* pItemCache = NULL;
	
	m_snide->CheckCollision(m_snide->Facing(), &colNear, &colFar);
	
	m_menu->ClearIcons();
	
	switch(menuMode)
	{
	case MENUMODE_GENERAL:
		if(TryGetDoor(colNear, colFar, &pDoor))
		{
			if(!pDoor->Hidden())
			{
				if(pDoor->GetDoorState() == DOORSTATE_OPEN)
					m_menu->AddIconSet(ICONSET_DOOR_CLOSE);
				else
					m_menu->AddIconSet(ICONSET_DOOR_OPEN);
			}
			else
			{
				m_menu->AddIconSet(ICONSET_GENERAL);
				
				if(m_someoneInRoom)
					m_menu->AddIcon(ICON_QUESTION);
			}
		}
		else
		{
			m_menu->AddIconSet(ICONSET_GENERAL);
			
			if(m_someoneInRoom)
				m_menu->AddIcon(ICON_QUESTION);
		}
		break;
	case MENUMODE_ITEM:
		if(colNear != COL_NOTHING_HERE)
		{
			if(TryGetRoomCache(m_currentRoom, colNear, &pItemCache))
				m_menu->AddIcon(ICON_DROP);
		}
		
		m_menu->AddIconSet(ICONSET_ITEM);
		
		if(pItem->GetItemAttribs() & ITEMATTRIB_OPEN)
			m_menu->AddIcon(ICON_OPEN);
		
		if(pItem->GetItemAttribs() & ITEMATTRIB_SHOOT)
			m_menu->AddIcon(ICON_SHOOT);
		
		if(pItem->GetItemAttribs() & ITEMATTRIB_USE_KEY)
			m_menu->AddIcon(ICON_USE_KEY);
		
		if(pItem->GetItemAttribs() & ITEMATTRIB_READ)
			m_menu->AddIcon(ICON_READ);
		
		if(pItem->GetItemAttribs() & ITEMATTRIB_CONSUME)
			m_menu->AddIcon(ICON_CONSUME);
		break;
	}
	
	mmEffectCancel(m_footsteps);
	m_footsteps = 0;
	
	m_menu->Show(menuMode);
	
	mmEffectEx(&g_sfx_beep);
}

bool CGame::TryGetDoor(CollisionType colNear, CollisionType colFar, CDoor** pDoor)
{
	*pDoor = NULL;
	
	if(colNear >= COL_DOOR1 && colNear <= COL_DOOR8)
	{
		*pDoor = m_currentRoom->GetDoor((int)colNear);
		
		if(*pDoor != NULL)
			return true;
	}
	else if(colFar >= COL_DOOR1 && colFar <= COL_DOOR8)
	{
		*pDoor = m_currentRoom->GetDoor((int)colFar);
		
		if(*pDoor != NULL)		
			return true;
	}
	
	return false;
}

bool CGame::TryGetRoomCache(CRoom* pRoom, CollisionType colType, CItemCache** pItemCache)
{
	*pItemCache = NULL;
	
	if(colType == COL_NOTHING_HERE)
		return false;
	
	for(int i=0; i<MAX_ITEM_CACHE; i++)
	{
		*pItemCache = pRoom->GetItemCache(i);
		
		if(pItemCache != NULL)
		{
			if((*pItemCache)->GetItemColType() == colType)
				return true;
		}
	}
	
	return false;
}

int CGame::ShowItemMenu(const char* text, CItemCache* pItemCache, CItem* pItemExclude)
{
	int itemCount = 0;
	
	m_displayMode = DISPLAYMODE_CONSOLE_MENU;

	m_console->ClearMenu();
	
	for(int i=0; i<pItemCache->ItemCount(); i++)
	{
		CItem* pItem = pItemCache->GetItem(i);
		
		if(pItem != NULL && pItem != pItemExclude)
		{
			m_console->AddMenuItem(g_itemName[pItem->GetItemType()], pItem);
			itemCount++;
		}
	}
	
	if(itemCount > 0)
	{
		m_console->AddText(text);
		m_console->ShowMenu();
		m_console->DrawSelectorBar();
	}
	else
	{
		m_displayMode = DISPLAYMODE_GAME;
		sprintf(m_buffer, "%s\n\nNOTHING...", text);
		m_console->AddText(m_buffer);
		m_console->HideMenu();
	}
	
	return itemCount;
}

void CGame::ShowVisibleCharactersMenu()
{
	m_displayMode = DISPLAYMODE_CONSOLE_MENU;
	
	if(m_someoneInRoom)
	{
		m_console->AddText("IN THE ROOM YOU SEE:");
		m_console->ClearMenu();
		
		for(int i=1; i<MAX_CHARACTERS; i++)
			if(m_charactersInRoom[i])
				m_console->AddMenuItem(g_characterName[i], m_characterArray[i]);
			
		m_console->ShowMenu();
		m_console->DrawSelectorBar();
	}
	else
	{
		m_console->AddText("IN THE ROOM YOU SEE:\n\nNOBODY..");
	}
}

void CGame::ShowCharacterMenu(const char* text, CCharacter* pCharacterExclude)
{
	m_displayMode = DISPLAYMODE_CONSOLE_MENU;
	
	m_console->AddText(text);
	m_console->ClearMenu();
	
	for(int i=1; i<MAX_CHARACTERS-1; i++)
		if(m_characterArray[i] != pCharacterExclude)
			m_console->AddMenuItem(g_characterName[i], m_characterArray[i]);
		
	m_console->ShowMenu();
	m_console->DrawSelectorBar();
}

void CGame::ProcessMenu(int x, int y)
{
	CollisionType colNear, colFar;
	IconType iconType = m_menu->CheckIconHit(x, y);
	m_lastIconType = iconType;
	CDoor* pDoor = NULL;
	CItemCache* pItemCache = NULL;
	
	//DrawString("                                ", 0, 0, false);
	//DrawString(g_iconName[(int) iconType], 0, 0, false);
	switch(iconType)
	{
	case ICON_NONE:
		{
			//m_displayMode = DISPLAYMODE_GAME;

			//m_pointer->Hide();
			//m_menu->Hide();
		}
		break;
	case ICON_OPEN:
		{
			switch(m_openMode)
			{
			case OPENMODE_ROOM:
				{
					m_snide->CheckCollision(m_snide->Facing(), &colNear, &colFar);
					
					switch(colNear)
					{
					case COL_PICTURE:
						{
							if(m_currentRoom->GetAnimState(DSTRECT_SAFE) == ANIMSTATE_PLAY)
							{
								switch(m_currentRoom->GetAnimFrameNum(DSTRECT_SAFE))
								{
								case 0:
									m_displayMode = DISPLAYMODE_KEYBOARD;
									m_keyboardMode = KEYBOARDMODE_SAFE;
									m_console->Clear();
									m_menu->Hide();
									m_console->HideMenu();
									m_fxManager.SetFx(FXTYPE_TEXT_SCROLLER, FXMODE_NORMAL, false);
									m_keyboard->Show("TYPE IN THE COMBINATION:");
									break;
								case 1:
								case 2:
									{
										CItemCache* pItemCache = NULL;
											
										if(TryGetRoomCache(m_currentRoom, COL_SAFE, &pItemCache))
										{
											ShowItemMenu("YOU FIND:", pItemCache, NULL);
										}
										else
										{
											m_console->AddText("NOTHING HERE.");
										}
									}
									break;
								}
							}
							else
							{
								CItemCache* pItemCache = NULL;
										
								if(TryGetRoomCache(m_currentRoom, colNear, &pItemCache))
								{
									ShowItemMenu("YOU FIND:", pItemCache, NULL);
								}
								else
								{
									m_console->AddText("NOTHING HERE.");
								}
							}
						}
						break;
					default:
						{
							CItemCache* pItemCache = NULL;
									
							if(TryGetRoomCache(m_currentRoom, colNear, &pItemCache))
							{
								ShowItemMenu("YOU FIND:", pItemCache, NULL);
							}
							else
							{
								m_console->AddText("NOTHING HERE.");
							}
						}
						break;
					}
				}
				break;
			case OPENMODE_ITEM:
				{
					CItem* pItem = (CItem*) m_console->SelectedObject();
					CItemCache* pItemCache = pItem->GetItemCache();
					
					if(pItem->GetLocked())
					{
						m_console->AddText("IT'S LOCKED.");
					}
					else
					{
						if(pItem->GetItemType() == ITEM_PADDED_ENVELOPES)
							ShowItemMenu("EVIDENCE COLLECTED:", pItemCache, NULL);
						else
							ShowItemMenu("YOU FIND:", pItemCache, NULL);
					}
				
					m_openMode = OPENMODE_ROOM;
				}
				break;
			}
		}
		break;
	case ICON_EXAMINE:
		{
			if(m_menu->GetMenuMode() == MENUMODE_GENERAL)
			{
				m_snide->CheckCollision(m_snide->Facing(), &colNear, &colFar);
				
				if(TryGetDoor(colNear, colFar, &pDoor))
				{			
					if(pDoor->GetDoorState() == DOORSTATE_HIDDEN)
					{
						pDoor->SetDoorState(DOORSTATE_OPEN);
						m_currentRoom->Draw();
						mmEffectEx(&g_sfx_secretdoor);
						
						m_console->AddText("YOU FIND:\n\nA SECRET PASSAGE!");
					}
				}
				else
				{
					sprintf(m_buffer, "YOU SEE:\n\n%s", g_colName[colNear]);
					m_console->AddText(m_buffer);
				}
			}
			else
			{
				CItem* pItem = (CItem*) m_console->SelectedObject();
				const char* pText = g_itemExamine[pItem->GetItemType()];

				if(pText == NULL)
					m_console->AddText(g_itemExamine[0]);
				else
					m_console->AddText(g_itemExamine[pItem->GetItemType()]);
			}
		}
		break;
	case ICON_INVENTORY:
		{
			m_displayMode = DISPLAYMODE_CONSOLE_MENU;
			m_openMode = OPENMODE_ITEM;
			
			ShowItemMenu("YOU ARE CARRYING:", m_snide->GetItemCache(), NULL);
			
			return;
		}
		break;
	case ICON_DROP:
		{
			m_snide->CheckCollision(m_snide->Facing(), &colNear, &colFar);
			
			if(TryGetRoomCache(m_currentRoom, colNear, &pItemCache))
			{
				CItem* pItem = (CItem*) m_console->SelectedObject();
				
				if(colNear == COL_PICTURE && pItem->GetItemType() != ITEM_A_PICTURE && m_currentRoom->GetAnimFrameNum(DSTRECT_SAFE) < 1)
				{
					m_console->AddText("SORRY, YOU CAN'T DO THAT.");
				}
				else
				{
					if(colNear == COL_PICTURE && pItem->GetItemType() != ITEM_A_PICTURE && m_currentRoom->GetAnimFrameNum(DSTRECT_SAFE) > 0)
					{
						TryGetRoomCache(m_currentRoom, COL_SAFE, &pItemCache);
					}
					
					if(pItemCache->AddItem(pItem))
					{
						sprintf(m_buffer, "YOU DROP:\n\n%s", g_itemName[pItem->GetItemType()]);
						m_console->AddText(m_buffer);
						
						switch(colNear)
						{
						case COL_PICTURE:
							switch(pItem->GetItemType())
							{
							case ITEM_THE_WILL:
								if(m_currentRoom->GetAnimFrameNum(DSTRECT_SAFE) == 2)
								{
									m_currentRoom->SetAnimFrame(DSTRECT_SAFE, 1);
									m_currentRoom->SetAnimState(DSTRECT_SAFE, ANIMSTATE_PLAY);
									m_currentRoom->Draw();
								}
								break;
							case ITEM_A_PICTURE:
								{			
									m_currentRoom->SetAnimFrame(DSTRECT_SAFE, 0);
									m_currentRoom->SetAnimState(DSTRECT_SAFE, ANIMSTATE_STOP);
									m_currentRoom->Draw();
									
									mmEffectEx(&g_sfx_opendoor);
								}
								break;
							default:
								break;
							}
							break;
						case COL_KNIGHT:
							switch(pItem->GetItemType())
							{
							case ITEM_A_SWORD:
								m_currentRoom->SetAnimFrame(DSTRECT_SWORD, 0);
								m_currentRoom->SetAnimState(DSTRECT_SWORD, ANIMSTATE_STOP);
								m_currentRoom->Draw();
								break;
							case ITEM_A_BALL_ON_CHAIN:
								m_currentRoom->SetAnimFrame(DSTRECT_BALL_ON_CHAIN, 0);
								m_currentRoom->SetAnimState(DSTRECT_BALL_ON_CHAIN, ANIMSTATE_STOP);
								m_currentRoom->Draw();
								break;
							default:
								break;
							}
							break;
						case COL_TROPHY:
							if(pItem->GetItemType() == ITEM_A_BALL_ON_CHAIN)
							{
								m_currentRoom->SetAnimFrame(DSTRECT_TROPHY, 0);
								m_currentRoom->SetAnimState(DSTRECT_TROPHY, ANIMSTATE_PLAY);
								m_currentRoom->Draw();
								
								m_currentRoom->SetAnimFrame(DSTRECT_STATUE, 0);
								m_currentRoom->SetAnimState(DSTRECT_STATUE, ANIMSTATE_PLAY);
								m_currentRoom->Draw();
								
								CItemCache* itemCache = m_roomArray[ROOM_ANGUS_LANDING]->GetItemCache(1);
								itemCache->AddItem(m_itemArray[ITEM_A_RED_KEY]);
								
								mmEffectEx(&g_sfx_keydrop);
							}
							break;
						case COL_DESK_WITH_A_STATUE:
							if(pItem->GetItemType() == ITEM_A_RED_KEY)
							{
								m_currentRoom->SetAnimFrame(DSTRECT_STATUE, 0);
								m_currentRoom->SetAnimState(DSTRECT_STATUE, ANIMSTATE_PLAY);
								m_currentRoom->Draw();
							}
							break;
						default:
							break;
						}
					}
					else
					{
						m_console->AddText("IT WON'T FIT!");
					}
				}
			}
		}
		break;
	case ICON_SAVE:
	case ICON_LOAD:
	case ICON_SHOOT:
		{
			m_console->AddText("YOU CAN'T USE THAT HERE, YOU MIGHT HURT SOMEONE!");
		}
		break;
	case ICON_ACCUSE:
		{
			ShowCharacterMenu("WHO IS THE MURDERER?", NULL);
		}
		break;
	case ICON_DOOR_OPEN:
	case ICON_DOOR_CLOSE:
		{
			m_snide->CheckCollision(m_snide->Facing(), &colNear, &colFar);
			
			if(TryGetDoor(colNear, colFar, &pDoor))
			{
				if(pDoor->GetDoorState() == DOORSTATE_LOCKED)
				{
					m_console->AddText("IT'S LOCKED.");
				}
				else if(pDoor->GetDoorState() == DOORSTATE_CLOSED)
				{
					pDoor->SetDoorState(DOORSTATE_OPEN);
					m_currentRoom->Draw();
					
					if(m_currentRoom->GetRoomType() == ROOM_GARDEN || m_currentRoom->GetRoomType() == ROOM_GRAVEYARD)
						mmEffectEx(&g_sfx_gate);
					else
						mmEffectEx(&g_sfx_opendoor);
				}
				else if(pDoor->GetDoorState() == DOORSTATE_OPEN)
				{
					pDoor->SetDoorState(pDoor->Hidden() ? DOORSTATE_HIDDEN : DOORSTATE_CLOSED);
					m_currentRoom->Draw();
					
					if(m_currentRoom->GetRoomType() == ROOM_GARDEN || m_currentRoom->GetRoomType() == ROOM_GRAVEYARD)
						mmEffectEx(&g_sfx_gate);
					else
						mmEffectEx(&g_sfx_closedoor);
				}
			}
		}
		break;
	case ICON_USE_KEY:
		{
			m_snide->CheckCollision(m_snide->Facing(), &colNear, &colFar);
			
			CItem* pItem = (CItem*) m_console->SelectedObject();
				
			switch(colNear)
			{
			case COL_FOUNTAIN:
				{
					if(pItem->GetItemType() == ITEM_A_RED_KEY && m_currentRoom->GetAnimState(DSTRECT_FOUNTAIN) == ANIMSTATE_STOP)
					{
						m_roomArray[ROOM_ANGUS_ROOM]->SetMap(g_angus_room2Map);
						m_roomArray[ROOM_ANGUS_ROOM]->SetColMap(col_angus_room2);
						
						mmEffectEx(&g_sfx_secretdoor);
						
						m_console->AddText("YOU FIND:\n\nA SECRET PASSAGE!");
					}
					else
					{
						m_console->AddText("SORRY, YOU CAN'T DO THAT.");
					}
				}
				break;
			default:
				{
					if(TryGetDoor(colNear, colFar, &pDoor))
					{
						if(pItem->GetItemType() == pDoor->GetKeyItemType())
						{
							switch(pDoor->GetDoorState())
							{
							case DOORSTATE_OPEN:
							case DOORSTATE_CLOSED:
								m_console->AddText("OKAY.");
								pDoor->SetDoorState(DOORSTATE_LOCKED);
								m_currentRoom->Draw();
								
								mmEffectEx(&g_sfx_unlock);
								break;
							case DOORSTATE_LOCKED:
								m_console->AddText("OKAY.");
								pDoor->SetDoorState(DOORSTATE_CLOSED);
								
								mmEffectEx(&g_sfx_unlock);
							default:
								break;
							}
						}
						else
							m_console->AddText("THE KEY WILL NOT FIT.");
					}
					else
					{
						m_console->AddText("YOU SEE NO DOOR.");
					}
					break;
				}
			}
		}
		break;
	case ICON_QUESTION:
		{
			m_questionMode = QUESTIONMODE_WAITING;
			
			ShowVisibleCharactersMenu();
		}
		break;
	case ICON_READ:
		{
			CItem* pItem = (CItem*) m_console->SelectedObject();
			
			if(m_console->AddText(g_itemRead[pItem->GetItemType()]))
				m_displayMode = DISPLAYMODE_CONSOLE;
		}
		break;
	case ICON_CONSUME:
		{
			CItem* pItem = (CItem*) m_console->SelectedObject();
			
			switch(pItem->GetItemType())
			{
			case ITEM_A_SMALL_BOTTLE:
				m_snide->SetCharacterMode(CHARMODE_DEAD);
				m_console->AddText("YOU GASP IN AGONY AND DROP DEAD..");
				InitGameOver(GAMEOVERMODE_END);
				break;
			case ITEM_A_BOTTLE_OF_PILLS:
				m_snide->SetGreen(true);
				m_console->AddText("YUK.. THAT DIDN'T TASTE TOO GOOD..!");
				break;
			default:
				break;
			}
		}
		break;
	case ICON_USE:
		{
			m_useMode = USEMODE_USE;
			m_displayMode = DISPLAYMODE_CONSOLE_MENU;
			
			ShowItemMenu("USE:", m_snide->GetItemCache(), NULL);
		}
		break;
	case ICON_TIME:
		{
			sprintf(m_buffer, " THE TIME IS NOW:\n\n      %02d: %02d\n\n PAUSED..PRESS A TO CONTINUE.", m_timer->pCurrentTime()->Hours, m_timer->pCurrentTime()->Minutes);
			m_console->AddText(m_buffer);
			m_gameMode = GAMEMODE_PAUSED;
			m_timer->Stop();
		}
		break;
	case ICON_PLACE:
		{
			m_displayMode = DISPLAYMODE_CONSOLE_MENU;
			
			m_placeItem = (CItem*) m_console->SelectedObject();
			
			ShowItemMenu("PUT IN:", m_snide->GetItemCache(), m_placeItem);
		}
		break;
	case ICON_BAG:
		break;
	}
}

void CGame::PostProcessMenu()
{
	CollisionType colNear, colFar;
	CharacterType charNear, charFar;
	CDoor* pDoor = NULL;
	
	switch(m_lastIconType)
	{
	case ICON_NONE:
		{
			//m_displayMode = DISPLAYMODE_GAME;

			//m_pointer->Hide();
			//m_menu->Hide();
		}
		break;
	case ICON_OPEN:
		{
			CItem* pItem = (CItem*) m_console->SelectedObject();
			
			if(pItem == NULL) fprintf(stderr, "ERROR!");
			
			switch(pItem->GetItemType())
			{
				case ITEM_BOOKS1:
				case ITEM_BOOKS2:
					{
						CItemCache* pItemCache = m_snide->GetItemCache();
						
						if(pItemCache->IsSpaceAvailable())
						{
							m_displayMode = DISPLAYMODE_KEYBOARD;
							m_keyboardMode = (pItem->GetItemType() == ITEM_BOOKS1 ? KEYBOARDMODE_BOOK1 : KEYBOARDMODE_BOOK2);
							m_console->Clear();
							m_menu->Hide();
							m_console->HideMenu();
							m_fxManager.SetFx(FXTYPE_TEXT_SCROLLER, FXMODE_NORMAL, false);
							m_keyboard->Show("WHAT BOOK DO YOU WANT?");
						}
						else
						{
							m_console->AddText("YOU CAN'T CARRY ANY MORE!");
														
							m_displayMode = DISPLAYMODE_GAME;
							m_pointer->Hide();
							m_menu->Hide();
							m_console->HideMenu();
						}
					}
					break;
				default:
					{
						CItemCache* pItemCache = m_snide->GetItemCache();
						CollisionType colType = pItem->GetParent()->GetItemColType();
										
						if(pItemCache->AddItem(pItem))
						{
							sprintf(m_buffer, "YOU TAKE:\n\n%s", g_itemName[pItem->GetItemType()]);
							m_console->AddText(m_buffer);
							
							switch(colType)
							{
							case COL_HOURGLASS:
								if(pItem->GetItemType() == ITEM_AN_HOURGLASS)
								{
									pItemCache->RemoveItem(m_itemArray[ITEM_AN_HOURGLASS]);
									m_fxManager.SetFx(FXTYPE_PARTICLES, FXMODE_HOURGLASS, true);
									
									mmEffectEx(&g_sfx_timewarp);
									
									m_gameMode = GAMEMODE_REVERSETIME;
								}
								break;
							case COL_GOLDEN_SKULL:
								if(pItem->GetItemType() == ITEM_A_GOLDEN_SKULL)
								{
									pItemCache->RemoveItem(m_itemArray[ITEM_A_GOLDEN_SKULL]);
									m_fxManager.SetFx(FXTYPE_PARTICLES, FXMODE_SKULL, true);
									
									mmEffectEx(&g_sfx_magic);
									
									m_gameMode = GAMEMODE_DYING;
								}
								break;
							case COL_SAFE:
							case COL_PICTURE:
								switch(pItem->GetItemType())
								{
								case ITEM_A_PICTURE:
									if(m_currentRoom->GetAnimState(DSTRECT_SAFE) == ANIMSTATE_STOP)
									{
										m_currentRoom->SetAnimFrame(DSTRECT_SAFE, 0);
										m_currentRoom->SetAnimState(DSTRECT_SAFE, ANIMSTATE_PLAY);
										m_currentRoom->Draw();
										
										mmEffectEx(&g_sfx_opendoor);
										
										m_console->AddText("YOU FIND A SAFE!");
									}
									break;
								case ITEM_THE_WILL:
									m_currentRoom->SetAnimFrame(DSTRECT_SAFE, 2);
									m_currentRoom->SetAnimState(DSTRECT_SAFE, ANIMSTATE_PLAY);
									m_currentRoom->Draw();
									break;
								default:
									
									break;
								}
								break;
							case COL_KNIGHT:
								switch(pItem->GetItemType())
								{
								case ITEM_A_SWORD:
									m_currentRoom->SetAnimFrame(DSTRECT_SWORD, 0);
									m_currentRoom->SetAnimState(DSTRECT_SWORD, ANIMSTATE_PLAY);
									m_currentRoom->Draw();
									break;
								case ITEM_A_BALL_ON_CHAIN:
									m_currentRoom->SetAnimFrame(DSTRECT_BALL_ON_CHAIN, 0);
									m_currentRoom->SetAnimState(DSTRECT_BALL_ON_CHAIN, ANIMSTATE_PLAY);
									m_currentRoom->Draw();
									break;
								default:
									break;
								}
								break;
							case COL_TROPHY:
								if(pItem->GetItemType() == ITEM_A_BALL_ON_CHAIN)
								{
									m_currentRoom->SetAnimFrame(DSTRECT_TROPHY, 0);
									m_currentRoom->SetAnimState(DSTRECT_TROPHY, ANIMSTATE_STOP);
									m_currentRoom->Draw();
								}
								break;
							case COL_DESK_WITH_A_STATUE:
								if(pItem->GetItemType() == ITEM_A_RED_KEY)
								{
									m_currentRoom->SetAnimFrame(DSTRECT_STATUE, 0);
									m_currentRoom->SetAnimState(DSTRECT_STATUE, ANIMSTATE_STOP);
									m_currentRoom->Draw();
								}
								break;
							default:
								break;
							}
						}
						else
						{
							m_console->AddText("YOU CAN'T CARRY ANY MORE!");
						}
						
						m_displayMode = DISPLAYMODE_GAME;
						m_pointer->Hide();
						m_menu->Hide();
						m_console->HideMenu();
						break;
					}
			}
		}
		//char buf[256];
		//sprintf(buf, g_accuseName[m_console->MenuItem()]);
		//fprintf(stderr, buf);
		break;
	case ICON_EXAMINE:
		break;
	case ICON_INVENTORY:
		{
			CItem* pItem = (CItem*) m_console->SelectedObject();
			
			//if(pItem == NULL) fprintf(stderr, "ERROR!");
			
			//sprintf(m_buffer, "YOU SELECTED:\n\n%s", g_itemName[pItem->GetItemType()]);
			//m_console->AddText(m_buffer);
			m_displayMode = DISPLAYMODE_MENU;
			SetMenuIcons(MENUMODE_ITEM, pItem);
			m_pointer->SetRect(MENU_X, MENU_Y, MENU_WIDTH, MENU_HEIGHT);
			//m_pointer->SetRect(CONSOLE_MENU_X, CONSOLE_MENU_Y, CONSOLE_MENU_WIDTH, CONSOLE_MENU_HEIGHT);
	
			//m_snide->CheckCollision(m_snide->Facing(), &colNear, &colFar);
		
			//m_displayMode = DISPLAYMODE_GAME;
			m_pointer->Hide();
			//m_menu->Hide();
			m_console->HideMenu();
		}
		break;
	case ICON_DROP:
	case ICON_SAVE:
	case ICON_LOAD:
	case ICON_SHOOT:
		break;
	case ICON_ACCUSE:
		{
			m_displayMode = DISPLAYMODE_GAME;
			m_console->AddText("YOU DO NOT HAVE THE EVIDENCE TO PROVE IT.");
			m_pointer->Hide();
			m_menu->Hide();
			m_console->HideMenu();
			
			//char buf[256];
			//sprintf(buf, g_accuseName[m_console->MenuItem()]);
			//fprintf(stderr, buf);
			}
		break;
	case ICON_DOOR_OPEN:
	case ICON_DOOR_CLOSE:
	case ICON_USE_KEY:
		break;
	case ICON_QUESTION:
		{
			switch(m_questionMode)
			{
			case QUESTIONMODE_NONE:
				break;
			case QUESTIONMODE_WAITING:
				{
					m_questionCharacter = (CCharacter*) m_console->SelectedObject();
					
					if(m_questionCharacter->GetRoom() == m_currentRoom)
					{
						m_displayMode = DISPLAYMODE_GAME;
						m_pointer->Hide();
						m_menu->Hide();
						m_console->HideMenu();
						m_console->AddText((m_questionCharacter->GetCharacterSex() == CHARSEX_MALE ? "HE IS WAITING." : "SHE IS WAITING."));
						m_questionCharacter->SetCharacterMode(CHARMODE_WAITING);
					}
					else
					{
						m_displayMode = DISPLAYMODE_GAME;
						m_questionMode = QUESTIONMODE_NONE;
						m_console->AddText((m_questionCharacter->GetCharacterSex() == CHARSEX_MALE ? "HE LEFT" : "SHE LEFT"));
						m_pointer->Hide();
						m_menu->Hide();
						m_console->HideMenu();
					}
				}
				break;
			case QUESTIONMODE_ASKABOUT:
				{
					m_questionType = (QuestionType) m_console->SelectedIndex();
					
					switch(m_questionType)
					{
						case QUESTIONTYPE_MRMCFUNGUS:
							m_displayMode = DISPLAYMODE_GAME;
							m_questionMode = QUESTIONMODE_WAITING;
							
							m_questionCharacter->SetCharacterMode(CHARMODE_TALKING);
							
							CharacterSpeak(m_questionCharacter, g_askAboutCharacter[m_questionCharacter->GetCharacterType() * MAX_CHARACTERS + MAX_CHARACTERS - 1]);

							m_pointer->Hide();
							m_menu->Hide();
							m_console->HideMenu();
							break;
						case QUESTIONTYPE_ANOBJECT:
							m_displayMode = DISPLAYMODE_CONSOLE_MENU;
							m_questionMode = QUESTIONMODE_REPLY;
							ShowItemMenu("ASK ABOUT:", m_snide->GetItemCache(), NULL);
							break;
						case QUESTIONTYPE_ANOTHERGUEST:
							m_displayMode = DISPLAYMODE_CONSOLE_MENU;
							m_questionMode = QUESTIONMODE_REPLY;
							ShowCharacterMenu("ASK ABOUT:", m_questionCharacter);
							break;
					}
				}
				break;
			case QUESTIONMODE_REPLY:
				switch(m_questionType)
				{
					case QUESTIONTYPE_MRMCFUNGUS:
						{
						}
						break;
					case QUESTIONTYPE_ANOBJECT:
						{
							m_displayMode = DISPLAYMODE_GAME;
							m_questionMode = QUESTIONMODE_WAITING;
							
							CItem* pItem = (CItem*) m_console->SelectedObject();
							const char* pReplyText = g_askAboutItem[m_questionCharacter->GetCharacterType() * MAX_ITEMS + pItem->GetItemType()];
							
							m_questionCharacter->SetCharacterMode(CHARMODE_TALKING);
							
							switch(m_questionCharacter->GetCharacterType())
							{
							case CHARTYPE_BENTLEY:
								if(pReplyText == NULL)
								{
									sprintf(m_buffer, "\"IT IS QUITE OBVIOUSLY %s\"", g_itemName[pItem->GetItemType()]);
									CharacterSpeak(m_questionCharacter, m_buffer);
								}
								else
									CharacterSpeak(m_questionCharacter, pReplyText);
								break;
							default:
								CharacterSpeak(m_questionCharacter, (pReplyText == NULL ? "\"DON'T KNOW ANYTHING ABOUT IT.\"" : pReplyText));
								break;
							}
							
							m_pointer->Hide();
							m_menu->Hide();
							m_console->HideMenu();
						}
						break;
					case QUESTIONTYPE_ANOTHERGUEST:
						{
							m_displayMode = DISPLAYMODE_GAME;
							m_questionMode = QUESTIONMODE_WAITING;
							
							CCharacter* pCharacter = (CCharacter*) m_console->SelectedObject();
							const char* pReplyText = g_askAboutCharacter[m_questionCharacter->GetCharacterType() * MAX_CHARACTERS + pCharacter->GetCharacterType()];
							
							m_questionCharacter->SetCharacterMode(CHARMODE_TALKING);
							
							switch(m_questionCharacter->GetCharacterType())
							{
							case CHARTYPE_SNIDE:
								break;
							case CHARTYPE_REVEREND:
								CharacterSpeak(m_questionCharacter, (pReplyText == NULL ? "\"IT'S NONE OF MY BUSINESS\"" : pReplyText));
								break;
							case CHARTYPE_BENTLEY:
								CharacterSpeak(m_questionCharacter, (pReplyText == NULL ? "\"I'M VERY BUSY AT THE MOMENT SIR\"" : pReplyText));
								break;
							case CHARTYPE_COOK:
								CharacterSpeak(m_questionCharacter, (pReplyText == NULL ? "\"DON'T REALLY KNOW MUCH.\"" : pReplyText));
								break;
							case CHARTYPE_GABRIEL:
								CharacterSpeak(m_questionCharacter, (pReplyText == NULL ? "\"WELL, I MUSTN'T GOSSIP.\"" : pReplyText));
								break;
							case CHARTYPE_CYNTHIA:
								CharacterSpeak(m_questionCharacter, (pReplyText == NULL ? "\"YES I TOTALLY AGREE, DARLING..\"" : pReplyText));
								break;
							case CHARTYPE_PROFESSOR:
								CharacterSpeak(m_questionCharacter, g_askAboutProfessorRandom[rand() % 5]);
								break;
							case CHARTYPE_DOCTOR:
								CharacterSpeak(m_questionCharacter, (pReplyText == NULL ? "\"CAN'T TELL YOU MUCH I'M AFRAID.\"" : pReplyText));
								break;
							case CHARTYPE_MAJOR:
								CharacterSpeak(m_questionCharacter, g_askAboutMajorRandom[rand() % 4]);
								break;
							case CHARTYPE_DINGLE:
								CharacterSpeak(m_questionCharacter, (pReplyText == NULL ? "\"SORRY, NO COMMENT\"" : pReplyText));
								break;
							case CHARTYPE_ANGUS:
								mmEffectEx(&g_sfx_ghostly);
								CharacterSpeak(m_questionCharacter, "\"WOOOOOO!\"");
								break;
							default:
								break;
							}
							
							m_pointer->Hide();
							m_menu->Hide();
							m_console->HideMenu();
						}
						break;
				}
				break;
			}
		}
		break;
	case ICON_READ:
	case ICON_CONSUME:
		break;
	case ICON_USE:
		{
			switch(m_useMode)
			{
			case USEMODE_USE:
				m_useMode = USEMODE_TO;
				m_useItem = (CItem*) m_console->SelectedObject();
				
				m_console->AddText("TO:");
				m_console->ClearMenu();
				m_console->AddMenuItem("OPEN", NULL);
				m_console->AddMenuItem("BREAK", NULL);
				m_console->AddMenuItem("CUT", NULL);
				m_console->AddMenuItem("EXAMINE", NULL);
				m_console->ShowMenu();
				m_console->DrawSelectorBar();
				break;
			case USEMODE_TO:
				m_useMode = USEMODE_WITH;
				m_useType = (UseType) m_console->SelectedIndex();
				
				ShowItemMenu("", m_snide->GetItemCache(), NULL);
				break;
			case USEMODE_WITH:
				m_displayMode = DISPLAYMODE_GAME;
				
				m_withItem = (CItem*) m_console->SelectedObject();
				CItemCache* pItemCache = m_withItem->GetParent();
				
				bool useSuccess = false;
				
				switch(m_useType)
				{
				case USETYPE_OPEN:
					if(m_useItem->GetItemType() == ITEM_A_SCREWDRIVER && m_withItem->GetItemType() == ITEM_A_LOCKET)
					{
						useSuccess = true;
						pItemCache->ReplaceItem(m_withItem, m_itemArray[ITEM_AN_OPEN_LOCKET]);
					}
					
					if(m_useItem->GetItemType() == ITEM_A_SMALL_KEY && m_withItem->GetItemType() == ITEM_A_BRIEFCASE)
					{
						useSuccess = true;
						m_withItem->SetLocked(!m_withItem->GetLocked());
						
						mmEffectEx(&g_sfx_unlock);
					}
					break;
				case USETYPE_BREAK:
					if(m_useItem->GetItemType() == ITEM_A_HAMMER && m_withItem->GetItemType() == ITEM_A_PAPERWEIGHT)
					{
						useSuccess = true;
						pItemCache->ReplaceItem(m_withItem, m_itemArray[ITEM_A_BIG_IRON_KEY]);
					}
					
					if(m_useItem->GetItemType() == ITEM_A_HAMMER && m_withItem->GetItemType() == ITEM_DIRTY_PLATES)
					{
						useSuccess = true;
						pItemCache->ReplaceItem(m_withItem, m_itemArray[ITEM_BROKEN_PLATES]);
					}
					break;
				case USETYPE_CUT:
					if(m_useItem->GetItemType() == ITEM_A_KNIFE && m_withItem->GetItemType() == ITEM_A_WAD_OF_NOTES)
					{
						useSuccess = true;
						pItemCache->ReplaceItem(m_withItem, m_itemArray[ITEM_SHREDDED_PAPER]);
					}
					break;
				case USETYPE_EXAMINE:
					break;
				}
				
				if(useSuccess)
					m_console->AddText("OKAY.");
				else
					m_console->AddText("SORRY, YOU CAN'T DO THAT.");
				
				m_pointer->Hide();
				m_menu->Hide();
				m_console->HideMenu();
				break;
			}
		}
		break;
	case ICON_TIME:
		{
			m_displayMode = DISPLAYMODE_GAME;
			m_console->Clear();
		}
		break;
	case ICON_PLACE:
		{
			m_inItem = (CItem*) m_console->SelectedObject();
			
			if(m_inItem->GetItemAttribs() & ITEMATTRIB_OPEN)
			{
				CItemCache* itemCache = m_inItem->GetItemCache();
				
				if(itemCache->AddItem(m_placeItem))
				{
					m_console->AddText("OKAY.");
				}
				else
				{
					m_console->AddText("IT WON'T FIT!");
				}
			}
			else
			{
				m_console->AddText("SORRY, YOU CAN'T DO THAT.");
			}
			
			m_displayMode = DISPLAYMODE_GAME;
			m_pointer->Hide();
			m_menu->Hide();
			m_console->HideMenu();
			
			//sprintf(m_buffer, "Place %s in %s",g_itemName[m_placeItem->GetItemType()], g_itemName[m_inItem->GetItemType()]);
			//fprintf(stderr, m_buffer);
		}
	case ICON_BAG:
		break;
	}
}

void CGame::InitRoom()
{
	switch(m_currentRoom->GetRoomType())
	{
	case ROOM_OUTSIDE1:
	case ROOM_OUTSIDE3:
		mmSetJingleVolume(1024);
		break;
	case ROOM_OUTSIDE2:
	case ROOM_OUTSIDE4:
	case ROOM_GARDEN:
	case ROOM_GRAVEYARD:
	case ROOM_COURTYARD:
		//mmJingle(MOD_WEATHER);
		mmSetJingleVolume(1024);
		m_fxManager.SetFx(FXTYPE_PARTICLES, FXMODE_RAIN, true);
		break;
	default:
		mmSetJingleVolume(0);
		m_fxManager.SetFx(FXTYPE_PARTICLES, FXMODE_RAIN, false);
		break;
	}
	
	dmaCopy(sprite_watchPal, SPRITE_PALETTE_SUB, sprite_watchPalLen);
}

void CGame::UpdateFx()
{
	switch(m_currentRoom->GetRoomType())
	{
	case ROOM_OUTSIDE1:
	case ROOM_OUTSIDE2:
	case ROOM_OUTSIDE3:
	case ROOM_OUTSIDE4:
	case ROOM_GARDEN:
	case ROOM_GRAVEYARD:
	case ROOM_COURTYARD:
		{
			static int lastUpdate = 0;
			
			lastUpdate++;
			
			((CFxParticles*)m_fxManager.GetFx(FXTYPE_PARTICLES))->SetXOffset(m_currentRoom->Width() - m_currentRoom->X());
			
			if(lastUpdate == 8)
			{
				lastUpdate = 0;
				int x = rand() % 32;
				
				if(x == 31)
				{
					m_currentRoom->SetPalette(g_lightningBgPal);
					dmaCopy(g_lightningSpritePal, SPRITE_PALETTE_SUB, 512);
				}
				else
				{
					m_currentRoom->RestorePalette();
					dmaCopy(sprite_watchPal, SPRITE_PALETTE_SUB, sprite_watchPalLen);
				}
			}
		}
		break;
	default:
		break;
	}
}

void CGame::InitDoors()
{
	for (int i=0; i < MAX_ROOMS; i++)
		m_roomArray[i]->InitializeDoors();
}

void CGame::ResetRooms()
{
	for (int i=0; i < MAX_ROOMS; i++)
		m_roomArray[i]->Reset();
}

void CGame::SortSprites()
{
	for (int i=0; i < MAX_CHARACTERS; i++)
	{
		m_characterArray[i]->Disable();
		
		for(int j=0; j < MAX_CHARACTERS; j++)
		{
			if(m_characterArray[i] != m_characterArray[j])
			{
				if (m_characterArray[i]->pPoint()->Y > m_characterArray[j]->pPoint()->Y &&
					m_characterArray[i]->OamIndex() > m_characterArray[j]->OamIndex())
				{
					int temp = m_characterArray[i]->OamIndex();
					m_characterArray[i]->SetOamIndex(m_characterArray[j]->OamIndex());
					m_characterArray[j]->SetOamIndex(temp);
				}
			}
		}
		
		if(m_currentRoom->OverlayY() < m_characterArray[i]->pPoint()->Y)
			m_characterArray[i]->SetPriority(0);
		else
			m_characterArray[i]->SetPriority(1);
		
		//char buf[256];
		//sprintf(buf, "%d",m_characterArray[CHARTYPE_SNIDE]->Priority());
		//DrawString(buf, 0, 0, false);
	}
}

void CGame::UpdateCharacters()
{
	m_someoneInRoom = false;
	const char* string = NULL;

	for (int i=0; i < MAX_CHARACTERS; i++)
	{
		m_characterArray[i]->Update(m_currentRoom);
		
		if(m_characterArray[i]->TryGetSpeech(&string))
		{
			if(m_characterArray[i]->GetRoom() == m_currentRoom)
				CharacterSpeak(m_characterArray[i], string);
		}
		
		if(m_characterArray[i]->IsVisible(m_currentRoom))
			m_characterArray[i]->Show();
		else
			m_characterArray[i]->Hide();
		
		m_characterArray[i]->Draw();
		
		if(i > CHARTYPE_SNIDE)
		{
			if(m_characterArray[i]->GetRoom() == m_currentRoom)
			{
				m_someoneInRoom = true;
				m_charactersInRoom[i] = true;
			}
			else
				m_charactersInRoom[i] = false;
		}
		
		if(m_characterArray[i]->GetCharacterType() == CHARTYPE_MAJOR)
		{
			if(m_characterArray[i]->GetRoom() == m_currentRoom && rand() % 400 == 0)
				if(((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->ScrollerEmpty())
					((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText(g_askAboutMajorRandom[rand() % 4]);
		}
	}
}

void CGame::CharacterSpeak(CCharacter* pCharacter, const char* string)
{
	if(m_speakCharacter != pCharacter)
	{
		if(string[0] == '"')
		{
			m_speakCharacter = pCharacter;
			
			sprintf(m_buffer, "%s SPEAKS %s", g_characterName[pCharacter->GetCharacterType()], string);
			((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText(m_buffer);
		}
		else
		{
			((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText(string);
		}
	}
	else
		((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText(string);
}

void CGame::HideCharacters()
{
	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		m_characterArray[i]->Hide();
		m_characterArray[i]->Disable();
		m_characterArray[i]->Draw();
	}
}

bool CGame::CheckCharacterCollision(DirectionType directionType, CharacterType* charNear, CharacterType* charFar)
{
	for (int i=1; i < MAX_CHARACTERS; i++)
	{
		if(m_characterArray[i]->GetRoom() == m_currentRoom)
		{
			if(m_snide->CheckCollision(directionType, m_characterArray[i], charNear, charFar))
				return true;
		}
	}
	
	return false;
}

mm_word CGame::MusicEventHandler(mm_word msg, mm_word param)
{
	//char buf[256];
	
	switch( msg )
	{

	case MMCB_SONGMESSAGE:
		//sprintf(buf, "MMCB_SONGMESSAGE: msg: %d, param: %d", msg, param);
		//fprintf(stderr, buf);
        break;
	case MMCB_SONGFINISHED:
		mmJingle(MOD_WEATHER);
		//sprintf(buf, "MMCB_SONGFINISHED: msg: %d, param: %d", msg, param);
		//fprintf(stderr, buf);
		break;
    }
	
	return 0;
}

void CGame::UpdateVBlank()
{
	m_fxManager.UpdateVBlank();
}

void CGame::UpdateHBlank()
{
	if(REG_VCOUNT < 80)
		REG_DISPCNT |= DISPLAY_BG2_ACTIVE;
	else if(REG_VCOUNT > 80)
		REG_DISPCNT &= ~DISPLAY_BG2_ACTIVE;

	m_fxManager.UpdateHBlank();
}

void CGame::UpdateTimer1()
{
}

void CGame::UpdateTimer2()
{
	m_timer->Update();
}

void CGame::InitVideoIntro()
{
	videoSetMode(MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE);
	videoSetModeSub(MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE);
	
	vramSetMainBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE_0x06400000, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);

	bgInit(0, BgType_Text8bpp, BgSize_T_256x256, INTRO_BG0_MAP_BASE, INTRO_BG0_TILE_BASE);
	bgInit(1, BgType_Text8bpp, BgSize_T_256x256, INTRO_BG1_MAP_BASE, INTRO_BG1_TILE_BASE);
	
	bgInitSub(0, BgType_Text8bpp, BgSize_T_256x256, INTRO_BG0_MAP_BASE_SUB, INTRO_BG0_TILE_BASE_SUB);
	bgInitSub(1, BgType_Text8bpp, BgSize_T_256x256, INTRO_BG1_MAP_BASE_SUB, INTRO_BG1_TILE_BASE_SUB);
	
	lcdMainOnBottom();
}

void CGame::InitVideoMain()
{
	videoSetMode(MODE_0_2D | DISPLAY_WIN0_ON | DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE);
	videoSetModeSub(MODE_0_2D | DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE);
	
	vramSetMainBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE_0x06400000, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);
	//vramSetMainBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);
	//vramSetMainBanks(VRAM_A_MAIN_SPRITE, VRAM_B_MAIN_BG, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);
	
	//vramSetBankA(VRAM_A_MAIN_SPRITE);
	//vramSetBankD(VRAM_D_SUB_SPRITE);
	
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
	
	videoBgDisableSub(0);
	
	lcdMainOnBottom();
	
	dmaCopy(sprite_miscPal, SPRITE_PALETTE, sprite_miscPalLen);
	dmaCopy(sprite_watchPal, SPRITE_PALETTE_SUB, sprite_watchPalLen);
	
	dmaCopy(fontTiles, BG_TILE_RAM(BG0_TILE_BASE), fontTilesLen);
	dmaCopy(fontTiles, BG_TILE_RAM_SUB(BG0_TILE_BASE_SUB) , fontTilesLen);
	
	dmaCopy(fontPal, BG_PALETTE, fontPalLen);
	dmaCopy(fontPal, BG_PALETTE_SUB, fontPalLen);
	
	BG_PALETTE[0] = 0;
	BG_PALETTE_SUB[0] = 0;
	
	dmaCopy(font_largeTiles, BG_TILE_RAM(BG0_TILE_BASE) + fontTilesLen, font_largeTilesLen);
	dmaCopy(font_largeTiles, BG_TILE_RAM_SUB(BG0_TILE_BASE_SUB) + fontTilesLen, font_largeTilesLen);
	
	WIN_IN = WIN0_BG0 | WIN0_BG1 | WIN0_BG2 | WIN0_BG3 | WIN0_SPRITES | WIN0_BLENDS;
	WIN_OUT = WIN0_BG1 | WIN0_BG2 | WIN0_BG3 | WIN0_SPRITES | WIN0_BLENDS;
	WIN0_Y0 = 0;
	WIN0_Y1 = 192;
	WIN0_X0 = 8;
	WIN0_X1 = 248;
	
	//WIN_IN = WIN0_BG0 | WIN0_BG1 | WIN0_BG2 | WIN0_BG3 | WIN0_SPRITES | WIN0_BLENDS;
	//WIN_OUT = WIN0_BG0 | WIN0_BG1 | WIN0_BG3 | WIN0_SPRITES | WIN0_BLENDS;
	//WIN0_Y0 = 0;
	//WIN0_Y1 = 80;
	//WIN0_X0 = 0;
	//WIN0_X1 = 255;
	
	//WIN_IN |= WIN1_BG0 | WIN1_BG1 | WIN1_BG2 | WIN1_BG3 | WIN1_SPRITES | WIN1_BLENDS;
	//WIN_OUT |= WIN1_BG1 | WIN1_BG2 | WIN1_BG3 | WIN1_SPRITES | WIN1_BLENDS;
	//WIN1_Y0 = 0;
	//WIN1_Y1 = 192;
	//WIN1_X0 = 8;
	//WIN1_X1 = 248;
	
	//oamInit(&oamMain, SpriteMapping_1D_32, false);
	//oamInit(&oamSub, SpriteMapping_1D_32, false);
	
	oamInit(&oamMain, SpriteMapping_Bmp_1D_128, false);
	oamInit(&oamSub, SpriteMapping_Bmp_1D_128, false);
}

void CGame::InitIntro()
{
	m_introIndex = 0;
	m_introFrameCount = 0;
	
	InitVideoIntro();
	
	dmaCopy(intro_headsoftPal, BG_PALETTE_SUB, intro_headsoftPalLen);
	dmaCopy(intro_headsoftPal, BG_PALETTE, intro_headsoftPalLen);
	
	dmaCopy(intro_headsoftTiles, BG_TILE_RAM_SUB(INTRO_BG0_TILE_BASE_SUB), intro_headsoftTilesLen);
	dmaCopy(intro_headsoftMap, BG_MAP_RAM_SUB(INTRO_BG0_MAP_BASE_SUB), intro_headsoftMapLen);
	
	dmaCopy(intro_proteusTiles, BG_TILE_RAM(INTRO_BG0_TILE_BASE), intro_proteusTilesLen);
	dmaCopy(intro_proteusMap, BG_MAP_RAM(INTRO_BG0_MAP_BASE), intro_proteusMapLen);
	
	dmaCopy(intro_infectuousTiles, BG_TILE_RAM_SUB(INTRO_BG1_TILE_BASE_SUB), intro_infectuousTilesLen);
	dmaCopy(intro_infectuousMap, BG_MAP_RAM_SUB(INTRO_BG1_MAP_BASE_SUB), intro_infectuousMapLen);
	
	dmaCopy(intro_spacefractalTiles, BG_TILE_RAM(INTRO_BG1_TILE_BASE), intro_spacefractalTilesLen);
	dmaCopy(intro_spacefractalMap, BG_MAP_RAM(INTRO_BG1_MAP_BASE), intro_spacefractalMapLen);
}

void CGame::UpdateIntro()
{
	if(m_introFrameCount++ == 100)
	{
		m_introFrameCount = 0;
		
		switch(m_introIndex)
		{
		case 0:
			dmaCopy(intro_infectuousTiles, BG_TILE_RAM_SUB(INTRO_BG0_TILE_BASE_SUB), intro_infectuousTilesLen);
			dmaCopy(intro_infectuousMap, BG_MAP_RAM_SUB(INTRO_BG0_MAP_BASE_SUB), intro_infectuousMapLen);
			
			dmaCopy(intro_spacefractalTiles, BG_TILE_RAM(INTRO_BG0_TILE_BASE), intro_spacefractalTilesLen);
			dmaCopy(intro_spacefractalMap, BG_MAP_RAM(INTRO_BG0_MAP_BASE), intro_spacefractalMapLen);
			
			dmaCopy(intro_retrobytesTiles, BG_TILE_RAM_SUB(INTRO_BG1_TILE_BASE_SUB), intro_retrobytesTilesLen);
			dmaCopy(intro_retrobytesMap, BG_MAP_RAM_SUB(INTRO_BG1_MAP_BASE_SUB), intro_retrobytesMapLen);
			
			dmaCopy(intro_retrogamerTiles, BG_TILE_RAM(INTRO_BG1_TILE_BASE), intro_retrogamerTilesLen);
			dmaCopy(intro_retrogamerMap, BG_MAP_RAM(INTRO_BG1_MAP_BASE), intro_retrogamerMapLen);
			break;
		case 1:
			dmaCopy(intro_retrobytesTiles, BG_TILE_RAM_SUB(INTRO_BG0_TILE_BASE_SUB), intro_retrobytesTilesLen);
			dmaCopy(intro_retrobytesMap, BG_MAP_RAM_SUB(INTRO_BG0_MAP_BASE_SUB), intro_retrobytesMapLen);
			
			dmaCopy(intro_retrogamerTiles, BG_TILE_RAM(INTRO_BG0_TILE_BASE), intro_retrogamerTilesLen);
			dmaCopy(intro_retrogamerMap, BG_MAP_RAM(INTRO_BG0_MAP_BASE), intro_retrogamerMapLen);
			break;
		case 2:	
			InitData();
			break;
		}
		
		m_introIndex++;
	}
}

void CGame::InitGame(GameType gameType)
{
	m_gameType = gameType;

	m_gameMode = GAMEMODE_RUNNING;
	m_displayMode = DISPLAYMODE_GAME;
	m_questionMode = QUESTIONMODE_NONE;
	m_openMode = OPENMODE_ROOM;
	m_footsteps = 0;
	m_gameOverFrameCount = 0;
	m_dieFrameCount = 0;
	m_reverseTimeFrameCount = 0;
	
	m_questionCharacter = NULL;
	m_speakCharacter = NULL;
	
	m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
	
	videoBgDisableSub(0);
	
	ClearBG(0, false);
	ClearBG(1, false);
	
	DrawString("@2009 HEADSOFT", 9, 1, false);
	
	((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->SetLoop(false);
	((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->ClearText();
	
	dmaCopy(watchTiles, BG_TILE_RAM_SUB(BG1_TILE_BASE_SUB), watchTilesLen);
	dmaCopy(watchMap, BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB), watchMapLen);
	dmaCopy(watchPal, BG_PALETTE_SUB, watchPalLen);
	
	dmaCopy(iconsTiles, BG_TILE_RAM(BG1_TILE_BASE), iconsTilesLen);
	
	dmaCopy(menu_questionsTiles, BG_TILE_RAM(BG2_TILE_BASE), menu_questionsTilesLen);
	dmaCopy(menu_questionsMap, BG_MAP_RAM(BG2_MAP_BASE), menu_questionsMapLen);
	
	dmaCopy(menu_bottomTiles, BG_TILE_RAM(BG3_TILE_BASE), menu_bottomTilesLen);
	dmaCopy(menu_bottomMap, BG_MAP_RAM(BG3_MAP_BASE), menu_bottomMapLen);
	dmaCopy(menu_bottomPal, BG_PALETTE, menu_bottomPalLen);
	
	BG_PALETTE[0] = 0;
	BG_PALETTE_SUB[0] = 0;
	
	ResetRooms();

	switch(m_gameType)
	{
	case GAMETYPE_NORMAL:
		m_gargoyleActive[0] = false;
		m_gargoyleActive[1] = false;
		m_gargoyleActive[2] = false;
		
		m_itemArray[ITEM_A_SOGGY_ENVELOPE]->AddItems(m_itemArray[ITEM_A_LETTER], NULL, NULL, NULL, NULL);
		m_itemArray[ITEM_A_HARDBACK_BOOK]->AddItems(m_itemArray[ITEM_A_FOLDED_DOCUMENT], NULL, NULL, NULL, NULL);
		m_itemArray[ITEM_A_BLACK_BAG]->AddItems(m_itemArray[ITEM_A_WAD_OF_NOTES], m_itemArray[ITEM_SCALPELS], m_itemArray[ITEM_A_SMALL_BOTTLE], NULL, NULL);
		m_itemArray[ITEM_A_JACKET]->AddItems(m_itemArray[ITEM_A_BUNCH_OF_KEYS], m_itemArray[ITEM_A_SOGGY_ENVELOPE], NULL, NULL, NULL);
		m_itemArray[ITEM_NOTEBOOKS]->AddItems(m_itemArray[ITEM_PLANS], NULL, NULL, NULL, NULL);
		m_itemArray[ITEM_A_BRIEFCASE]->AddItems(m_itemArray[ITEM_A_NOTE], m_itemArray[ITEM_NEWSPAPER_CUTTING], NULL, NULL, NULL);
		m_itemArray[ITEM_A_FOLDER]->ClearItems();
		m_itemArray[ITEM_PADDED_ENVELOPES]->ClearItems();
		
		m_itemArray[ITEM_A_BRIEFCASE]->SetLocked(true);
		
		// ------------------------------------

		m_characterArray[CHARTYPE_GABRIEL]->AddItems(m_itemArray[ITEM_A_LOCKET], m_itemArray[ITEM_A_SYRINGE], NULL, NULL, NULL);
		m_characterArray[CHARTYPE_DINGLE]->AddItems(m_itemArray[ITEM_A_SMALL_KEY], m_itemArray[ITEM_A_CRAVATE], NULL, NULL, NULL);
		
		// ------------------------------------

		//m_roomArray[ROOM_STAIRS]->SetOverlay(g_stairs_frontMap, 168);
		m_roomArray[ROOM_GRAVEYARD]->SetOverlay(g_graveyard_frontMap, 176);
		m_roomArray[ROOM_ANGUS_SECRET]->SetOverlay(g_angus_secret_frontMap, 168);
		m_roomArray[ROOM_ANGUS_ROOM]->SetOverlay(g_angus_room_frontMap, 176);
		m_roomArray[ROOM_DINING]->SetOverlay(g_dining_frontMap, 168);
	
		m_roomArray[ROOM_ANGUS_ROOM]->SetMap(g_angus_room1Map);
		m_roomArray[ROOM_ANGUS_ROOM]->SetColMap(col_angus_room1);
		
		// -------------------------------------
		
		m_roomArray[ROOM_SNIDE]->AddItems(1, m_itemArray[ITEM_PADDED_ENVELOPES], m_itemArray[ITEM_A_HOT_WATER_BOTTLE], NULL, NULL, NULL);
		m_roomArray[ROOM_REVEREND]->AddItems(1, m_itemArray[ITEM_A_BOTTLE_OF_PILLS], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_BENTLEY]->AddItems(0, m_itemArray[ITEM_A_COMB], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_BENTLEY]->AddItems(1, m_itemArray[ITEM_A_JACKET], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_CYNTHIA]->AddItems(1,m_itemArray[ITEM_A_MIRROR], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_PROFESSOR]->AddItems(1, m_itemArray[ITEM_NOTEBOOKS], m_itemArray[ITEM_A_SMALL_BOOK], NULL, NULL, NULL);		m_roomArray[ROOM_DOCTOR]->AddItems(1, m_itemArray[ITEM_COLOGNE], m_itemArray[ITEM_A_BLACK_BAG], NULL, NULL, NULL);
		m_roomArray[ROOM_MAJOR]->AddItems(0, m_itemArray[ITEM_AN_ELEPHANT_GUN], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_MAJOR]->AddItems(1, m_itemArray[ITEM_BLANK_BULLETS], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_DINGLE]->AddItems(1, m_itemArray[ITEM_A_BRIEFCASE], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_KITCHEN]->AddItems(0, m_itemArray[ITEM_A_HAMMER], m_itemArray[ITEM_A_CANDLESTICK], NULL, NULL, NULL);
		m_roomArray[ROOM_KITCHEN]->AddItems(1, m_itemArray[ITEM_A_BOTTLE_OF_WINE], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_KITCHEN]->AddItems(2, m_itemArray[ITEM_A_SILVER_TRAY], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_KITCHEN]->AddItems(4, m_itemArray[ITEM_CUTLERY], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_KITCHEN]->AddItems(5, m_itemArray[ITEM_DIRTY_PLATES], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_STUDY]->AddItems(0, m_itemArray[ITEM_BULLETS], m_itemArray[ITEM_A_PAPERWEIGHT], m_itemArray[ITEM_A_LETTER_OPENER], m_itemArray[ITEM_A_DIARY], NULL);
		m_roomArray[ROOM_STUDY]->AddItems(1, m_itemArray[ITEM_A_FOLDER], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_CELLAR]->AddItems(0, m_itemArray[ITEM_A_SCREWDRIVER], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_CELLAR]->AddItems(1, m_itemArray[ITEM_A_PIECE_OF_CARD], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_DRAWING]->AddItems(2, m_itemArray[ITEM_A_PICTURE], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_DRAWING]->AddItems(3, m_itemArray[ITEM_THE_WILL], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_LIBRARY]->AddItems(0, m_itemArray[ITEM_BOOKS1], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_LIBRARY]->AddItems(1, m_itemArray[ITEM_BOOKS2], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_UTILITY]->AddItems(0, m_itemArray[ITEM_A_DIRTY_SHIRT], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_UTILITY]->AddItems(2, m_itemArray[ITEM_WASHING_POWDER], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_UTILITY]->AddItems(3, m_itemArray[ITEM_A_FIREPLACE_BELLOW], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_ANGUS_ROOM]->AddItems(1, m_itemArray[ITEM_A_SWORD], m_itemArray[ITEM_A_BALL_ON_CHAIN], NULL, NULL, NULL);
		m_roomArray[ROOM_ANGUS_SECRET]->AddItems(0, m_itemArray[ITEM_AN_HOURGLASS], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_ANGUS_SECRET]->AddItems(1, m_itemArray[ITEM_A_GOLDEN_SKULL], NULL, NULL, NULL, NULL);
		break;
	}
		
	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		m_characterArray[i]->Reset();
		m_characterArray[i]->Disable();
		m_characterArray[i]->SetSub(true);
		m_characterArray[i]->SetGoalMode(true);
		m_characterArray[i]->SetCharacterMode(CHARMODE_GOAL);
	}
	
	m_question->Disable();
	m_question->Hide();
	
	m_currentRoom = m_roomArray[ROOM_STAIRS];
	m_currentRoom->Initialize(69);
	
	m_console->AddText(g_enterRoomText[m_currentRoom->GetRoomType()]);
	
	m_snide = m_characterArray[CHARTYPE_SNIDE];
	
	m_snide->AddItems(NULL, NULL, NULL, NULL, NULL);
	m_snide->SetRoom(m_currentRoom);
	m_snide->SetPosition(208, 104);
	m_snide->SetGoalMode(false);
	m_snide->SetCharacterMode(CHARMODE_WAITING);
	
	m_characterArray[CHARTYPE_ANGUS]->SetAlpha(0x7);
	
	//m_displayMode = DISPLAYMODE_CONSOLE;
	//m_console->AddText(g_itemRead[ITEM_THE_WILL]);
	
	m_console->Clear();
	
	m_timer->Start(9, 10, 0, 0);
		
	// ------------------------
	//m_roomArray[ROOM_ANGUS_ROOM]->SetMap(g_angus_room2Map);
	//m_roomArray[ROOM_ANGUS_ROOM]->SetColMap(col_angus_room2);
	// ------------------------
	
	mmStart(MOD_DETECTIVE, MM_PLAY_ONCE);
	mmPosition(3);
}

void CGame::UpdateGame(touchPosition touch, int keys_held, int keys_pressed, int keys_released)
{
	for(int i=0; i<MAX_EVENTS; i++)
	{
		if(m_eventArray[i] != NULL)
		{
			if(m_eventArray[i]->Update(m_timer->pCurrentTime()))
			{
				m_eventArray[i] = NULL;
				//fprintf(stderr,"Event!");
			}
		}
	}
	
	UpdateDisplayMode(touch, keys_held, keys_pressed, keys_released);
	
	m_currentRoom->Update(m_timer->pCurrentTime());
	
	SortSprites();
	UpdateCharacters();
	
	UpdateFx();
	
	//DrawTime(m_timer->pCurrentTime());
	m_watch->Draw(m_timer->pCurrentTime());
	m_console->Update();
	m_cursor->Update();
	m_cursor->Show();
	
	BACKGROUND.scroll[2].y = --m_bg2MainVScroll;
}

void CGame::InitGameOver(GameOverMode gameOverMode)
{
	m_gameMode = GAMEMODE_GAMEOVER;
	m_gameOverMode = gameOverMode;
	
	((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("THE GAME IS OVER.");
}

void CGame::UpdateGameOver()
{
	switch(m_gameOverMode)
	{
	case GAMEOVERMODE_WIN:
	case GAMEOVERMODE_LOSE:
	case GAMEOVERMODE_END:
		BACKGROUND.scroll[2].y = --m_bg2MainVScroll;

		UpdateFx();
		
		//DrawTime(m_timer->pCurrentTime());
		m_console->Update();
		m_cursor->Update();
		m_cursor->Show();
		break;
	case GAMEOVERMODE_NOTHING:
		break;
	}
	
	if(++m_gameOverFrameCount == 500)
	{
		switch(m_gameOverMode)
		{
		case GAMEOVERMODE_WIN:
			m_gameOverMode = GAMEOVERMODE_NOTHING;
			m_gameOverFrameCount = 0;		

			m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
			
			ClearBG(0, false);
			ClearBG(1, false);
			ClearBG(2, false);
			
			m_console->Clear();
			m_cursor->Hide();
			
			HideCharacters();
			
			oamClear(&oamMain, 0, 0);
			oamClear(&oamSub, 0, 0);
			
			dmaCopy(end_top_winTiles, BG_TILE_RAM_SUB(BG1_TILE_BASE_SUB), end_top_winTilesLen);
			dmaCopy(end_top_winMap, BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB), end_top_winMapLen);
			dmaCopy(end_top_winPal, BG_PALETTE_SUB, menu_topPalLen);
			
			dmaCopy(end_bottomTiles, BG_TILE_RAM(BG3_TILE_BASE), end_bottomTilesLen);
			dmaCopy(end_bottomMap, BG_MAP_RAM(BG3_MAP_BASE), end_bottomMapLen);
			dmaCopy(end_bottomPal, BG_PALETTE, end_bottomPalLen);
			break;
		case GAMEOVERMODE_LOSE:
			m_gameOverMode = GAMEOVERMODE_NOTHING;
			m_gameOverFrameCount = 0;
			
			m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
			
			ClearBG(0, false);
			ClearBG(1, false);
			ClearBG(2, false);
			
			m_console->Clear();
			m_cursor->Hide();
					
			HideCharacters();
			
			oamClear(&oamMain, 0, 0);
			oamClear(&oamSub, 0, 0);
			
			dmaCopy(end_top_loseTiles, BG_TILE_RAM_SUB(BG1_TILE_BASE_SUB), end_top_loseTilesLen);
			dmaCopy(end_top_loseMap, BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB), end_top_loseMapLen);
			dmaCopy(end_top_losePal, BG_PALETTE_SUB, menu_topPalLen);
			
			dmaCopy(end_bottomTiles, BG_TILE_RAM(BG3_TILE_BASE), end_bottomTilesLen);
			dmaCopy(end_bottomMap, BG_MAP_RAM(BG3_MAP_BASE), end_bottomMapLen);
			dmaCopy(end_bottomPal, BG_PALETTE, end_bottomPalLen);
			break;
		case GAMEOVERMODE_END:
			m_gameOverFrameCount = 0;
			
			InitTitleScreen();
			break;
		case GAMEOVERMODE_NOTHING:
			m_gameOverFrameCount = 0;
			
			InitTitleScreen();
			break;
		}
	}
}

void CGame::InitTitleScreen()
{
	m_gameMode = GAMEMODE_TITLESCREEN;
	
	m_characterPos = -1;
	m_characterFrameCount = 0;
	
	m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
	
	videoBgDisableSub(0);
	
	ClearBG(0, false);
	ClearBG(1, false);
	
	HideCharacters();
	
	oamClear(&oamMain, 0, 0);
	oamClear(&oamSub, 0, 0);
	
	DrawString("@2009 HEADSOFT", 9, 1, false);
	
	((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->ClearText();
	((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->SetLoop(true);
	((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("THE DETECTIVE GAME  -  WRITTEN BY HEADKAZE....GRAPHICS BY LOBO....MUSIC BY SPACE FRACTAL....ORIGINAL BY SAM MANTHORPE....CHARACTERS BY PAUL JAY....PLOT CUNNINGLY DEVISED BY THE MAGNIFICENT SEVEN....   PRESS BUTTON TO START INVESTIGATION                               ");
	
	m_console->AddText("\n\n    INTRODUCING\n     THE CAST..");

	dmaCopy(menu_topTiles, BG_TILE_RAM_SUB(BG1_TILE_BASE_SUB), menu_topTilesLen);
	dmaCopy(menu_topMap, BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB), menu_topMapLen);
	dmaCopy(menu_topPal, BG_PALETTE_SUB, menu_topPalLen);
	
	dmaCopy(menu_questionsTiles, BG_TILE_RAM(BG2_TILE_BASE), menu_questionsTilesLen);
	dmaCopy(menu_questionsMap, BG_MAP_RAM(BG2_MAP_BASE), menu_questionsMapLen);
	
	dmaCopy(menu_bottomTiles, BG_TILE_RAM(BG3_TILE_BASE), menu_bottomTilesLen);
	dmaCopy(menu_bottomMap, BG_MAP_RAM(BG3_MAP_BASE), menu_bottomMapLen);
	dmaCopy(menu_bottomPal, BG_PALETTE, menu_bottomPalLen);
	
	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		m_characterArray[i]->Reset();
		m_characterArray[i]->Disable();
		m_characterArray[i]->SetSub(false);
		m_characterArray[i]->SetPriority(0);
		m_characterArray[i]->SetPosition(192, 128);
		m_characterArray[i]->SetCharacterMode(CHARMODE_TALKING);
		m_characterArray[i]->SetGoalMode(false);
	}
	
	m_question->Reset();
	m_question->SetSub(false);
	m_question->SetPriority(0);
	m_question->SetPosition(192, 128);
	m_question->SetCharacterMode(CHARMODE_QUESTION);
	m_question->SetLoop(false);
	
	mmStart(MOD_DETECTIVE, MM_PLAY_LOOP);
	mmPosition(0);
}

void CGame::UpdateTitleScreen()
{
	m_characterFrameCount++;
	
	BACKGROUND.scroll[2].y = --m_bg2MainVScroll;
	
	UpdateFx();
	
	if(m_characterPos != -1)
	{
		if(m_characterFrameCount == 160)
		{
			m_question->Disable();
			m_question->Hide();
			
			m_characterArray[m_characterPos]->Show();
		}
		
		if(m_characterFrameCount == 600)
		{
			m_characterArray[m_characterPos]->Disable();
			m_characterArray[m_characterPos]->Hide();

			m_question->Disable();
			m_question->Hide();
			
			m_console->Clear();
		}
	}
	
	if(m_characterFrameCount > 700)
	{
		m_characterFrameCount = 0;
		
		if(++m_characterPos == MAX_CHARACTERS-1)
			m_characterPos = 0;
		
		m_question->ResetAnimation();
		m_question->Show();
		
		m_console->AddText(g_characterText[m_characterPos]);
	}
	
	if(m_characterPos != -1)
	{
		m_characterArray[m_characterPos]->Update(NULL);
		m_characterArray[m_characterPos]->Draw();
	}
	
	if(m_characterFrameCount > 80)
		m_question->Update(NULL);
	
	m_question->Draw();
	
	//DrawTime(m_timer->pCurrentTime());
	m_console->Update();
	m_cursor->Update();
	m_cursor->Show();
}
