#include <nds.h>
#include <stdio.h>
#include "TDG.h"
#include "CGame.h"
#include "Text.h"
#include "Gfx.h"
#include "CFxParticles.h"
#include "CFxRat.h"
#include "CFxLeak.h"
#include "windows.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::Initialize()
{
	m_timer = new CTimer();
	InitIntro1();
}

void CGame::InitData(int param)
{
	InitVideoMain();
	
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
	m_itemArray[ITEM_AN_ELEPHANT_GUN] = new CItem(ITEM_AN_ELEPHANT_GUN, ITEMATTRIB_SHOOT);
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
	m_itemArray[ITEM_A_BOMB] = new CItem(ITEM_A_BOMB, ITEMATTRIB_EVIDENCE | ITEMATTRIB_OPEN);				// Clue #7
	m_itemArray[ITEM_A_SMALL_KEY] = new CItem(ITEM_A_SMALL_KEY, ITEMATTRIB_USE_KEY);
	m_itemArray[ITEM_BULLETS] = new CItem(ITEM_BULLETS, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_SWORD] = new CItem(ITEM_A_SWORD, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_BALL_ON_CHAIN] = new CItem(ITEM_A_BALL_ON_CHAIN, ITEMATTRIB_NONE);
	m_itemArray[ITEM_AN_HOURGLASS] = new CItem(ITEM_AN_HOURGLASS, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_GOLDEN_SKULL] = new CItem(ITEM_A_GOLDEN_SKULL, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_RED_KEY] = new CItem(ITEM_A_RED_KEY, ITEMATTRIB_USE_KEY);
	m_itemArray[ITEM_A_VACUUM_CLEANER] = new CItem(ITEM_A_VACUUM_CLEANER, ITEMATTRIB_VACUUM | ITEMATTRIB_OPEN);
	m_itemArray[ITEM_WASHING_POWDER] = new CItem(ITEM_WASHING_POWDER, ITEMATTRIB_NONE);
	m_itemArray[ITEM_A_DIRTY_SHIRT] = new CItem(ITEM_A_DIRTY_SHIRT, ITEMATTRIB_NONE);
	m_itemArray[ITEM_ANGUS_MCFUNGUS] = new CItem(ITEM_ANGUS_MCFUNGUS, ITEMATTRIB_NONE);
	
	m_itemArray[ITEM_A_BRIEFCASE]->SetKeyItemType(ITEM_A_SMALL_KEY);
	
	m_spriteArray[SPRITE_SNIDE_HEAD] = new CSprite(SPRITE_SNIDE_HEAD, sprite_snide_headTiles, sprite_snide_headTilesLen, sprite_snide_headPal, sprite_snide_headPalLen, g_snideHeadFrames, 16);
	m_spriteArray[SPRITE_SNIDE_BODY] = new CSprite(SPRITE_SNIDE_BODY, sprite_snide_bodyTiles, sprite_snide_bodyTilesLen, sprite_snide_bodyPal, sprite_snide_bodyPalLen, g_snideBodyFrames, 18);
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
	
	m_questionMark = new CCharacter(CHARTYPE_QUESTIONMARK, m_spriteArray[SPRITE_QUESTION_HEAD], m_spriteArray[SPRITE_QUESTION_BODY], CHARSEX_NONE, 24, 48);
	
	m_characterArray[CHARTYPE_SNIDE]->SetDeadSide(true);
	m_characterArray[CHARTYPE_DOCTOR]->SetDeadSide(true);
	
	m_characterArray[CHARTYPE_BENTLEY]->SetKeyItemType(ITEM_A_BUNCH_OF_KEYS);
	m_characterArray[CHARTYPE_COOK]->SetKeyItemType(ITEM_A_HIDDEN_KEY);
	//m_characterArray[CHARTYPE_DINGLE]->SetKeyItemType(ITEM_A_HIDDEN_KEY);
	
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
	m_roomArray[ROOM_CELLAR] = new CRoom(ROOM_CELLAR, g_cellarMap, NULL, col_cellar, 168);
	m_roomArray[ROOM_DRAWING] = new CRoom(ROOM_DRAWING, g_drawingMap, NULL, col_drawing, 160);
	m_roomArray[ROOM_LIBRARY] = new CRoom(ROOM_LIBRARY, g_libraryMap, NULL, col_library, 160);
	m_roomArray[ROOM_LAUNDRY] = new CRoom(ROOM_LAUNDRY, g_laundryMap, NULL, col_laundry, 160);
	m_roomArray[ROOM_GARDEN] = new CRoom(ROOM_GARDEN, g_gardenMap, g_garden_frontMap, col_garden, 152);
	m_roomArray[ROOM_GRAVEYARD] = new CRoom(ROOM_GRAVEYARD, g_graveyardMap, g_graveyard_frontMap, col_graveyard, 160);
	m_roomArray[ROOM_COURTYARD] = new CRoom(ROOM_COURTYARD, g_courtyardMap, g_courtyard_frontMap, col_courtyard, 160);
	m_roomArray[ROOM_ANGUS_LANDING] = new CRoom(ROOM_ANGUS_LANDING, g_angus_landingMap, g_angus_landing_frontMap, col_angus_landing, 144);
	m_roomArray[ROOM_ANGUS_ROOM] = new CRoom(ROOM_ANGUS_ROOM, g_angus_room1Map, g_angus_room_frontMap, col_angus_room2, 160);
	m_roomArray[ROOM_ANGUS_SECRET] = new CRoom(ROOM_ANGUS_SECRET, g_angus_secretMap, g_angus_secret_frontMap, col_angus_secret, 160);
	m_roomArray[ROOM_ANGUS_STAIRS] = new CRoom(ROOM_ANGUS_STAIRS, g_angus_stairsMap, NULL, col_angus_stairs, 168);
	m_roomArray[ROOM_DINING] = new CRoom(ROOM_DINING, g_diningMap, g_dining_frontMap, col_dining, 160);
	m_roomArray[ROOM_SEWERS] = new CRoom(ROOM_SEWERS, g_sewersMap, NULL, col_sewers, 160);
	
	m_roomArray[ROOM_SNIDE]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_SNIDE], m_roomArray[ROOM_HALL2], ITEM_NONE));		
	m_roomArray[ROOM_REVEREND]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_REVEREND], m_roomArray[ROOM_HALL1], ITEM_NONE));
	m_roomArray[ROOM_REVEREND]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_HIDDEN, m_roomArray[ROOM_REVEREND], m_roomArray[ROOM_PASSAGE1], ITEM_NONE));
	m_roomArray[ROOM_BENTLEY]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_BENTLEY], m_roomArray[ROOM_HALL3], ITEM_A_BUNCH_OF_KEYS));		
	m_roomArray[ROOM_COOK]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_COOK], m_roomArray[ROOM_HALL4], ITEM_A_HIDDEN_KEY));
	m_roomArray[ROOM_GABRIEL]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_GABRIEL], m_roomArray[ROOM_HALL4], ITEM_A_BUNCH_OF_KEYS));
	m_roomArray[ROOM_CYNTHIA]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_CYNTHIA], m_roomArray[ROOM_HALL1], ITEM_NONE));
	m_roomArray[ROOM_PROFESSOR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_PROFESSOR], m_roomArray[ROOM_HALL2], ITEM_A_BIG_IRON_KEY));
	m_roomArray[ROOM_DOCTOR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_DOCTOR], m_roomArray[ROOM_HALL1], ITEM_NONE));
	m_roomArray[ROOM_MAJOR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_MAJOR], m_roomArray[ROOM_HALL2], ITEM_NONE));
	m_roomArray[ROOM_MAJOR]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_HIDDEN, m_roomArray[ROOM_MAJOR], m_roomArray[ROOM_OUTSIDE2], ITEM_NONE));
	m_roomArray[ROOM_DINGLE]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_DINGLE], m_roomArray[ROOM_HALL1], ITEM_A_HIDDEN_KEY));
	m_roomArray[ROOM_OUTSIDE1]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_OUTSIDE1], m_roomArray[ROOM_HALL1], ITEM_NONE));
	m_roomArray[ROOM_OUTSIDE2]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE2], m_roomArray[ROOM_PASSAGE1], ITEM_NONE));
	m_roomArray[ROOM_OUTSIDE2]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE2], m_roomArray[ROOM_MAJOR], ITEM_NONE));
	m_roomArray[ROOM_OUTSIDE3]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_OUTSIDE3], m_roomArray[ROOM_CLOCK], ITEM_NONE));
	m_roomArray[ROOM_OUTSIDE4]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_HIDDEN, m_roomArray[ROOM_OUTSIDE4], m_roomArray[ROOM_CELLAR], ITEM_NONE));
	m_roomArray[ROOM_OUTSIDE4]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE4], m_roomArray[ROOM_DRAWING], ITEM_NONE));
	m_roomArray[ROOM_OUTSIDE4]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPENING, m_roomArray[ROOM_OUTSIDE4], m_roomArray[ROOM_GARDEN], ITEM_NONE));
	m_roomArray[ROOM_PASSAGE1]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE1], m_roomArray[ROOM_REVEREND], ITEM_NONE));
	m_roomArray[ROOM_PASSAGE1]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPENING, m_roomArray[ROOM_PASSAGE1], m_roomArray[ROOM_OUTSIDE2], ITEM_NONE));
	m_roomArray[ROOM_PASSAGE2]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPENING, m_roomArray[ROOM_PASSAGE2], m_roomArray[ROOM_HALL1], ITEM_NONE));
	m_roomArray[ROOM_PASSAGE2]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPENING, m_roomArray[ROOM_PASSAGE2], m_roomArray[ROOM_HALL2], ITEM_NONE));
	m_roomArray[ROOM_PASSAGE3]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE3], m_roomArray[ROOM_KITCHEN], ITEM_NONE));
	m_roomArray[ROOM_PASSAGE3]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPENING, m_roomArray[ROOM_PASSAGE3], m_roomArray[ROOM_CELLAR], ITEM_NONE));
	m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_REVEREND], ITEM_NONE));
	m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_CYNTHIA], ITEM_NONE));
	m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_DOCTOR], ITEM_NONE));
	m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR4, new CDoor(DOOR_DOOR4, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_DINGLE], ITEM_A_HIDDEN_KEY));
	m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR5, new CDoor(DOOR_DOOR5, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_OUTSIDE1], ITEM_NONE));
	m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR6, new CDoor(DOOR_DOOR6, DOORSTATE_OPENING, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_LANDING], ITEM_NONE));
	m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR7, new CDoor(DOOR_DOOR7, DOORSTATE_OPENING, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_PASSAGE2], ITEM_NONE));
	m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_PROFESSOR], ITEM_A_BIG_IRON_KEY));
	m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_MAJOR], ITEM_NONE));
	m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPENING, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_PASSAGE2], ITEM_NONE));
	m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR4, new CDoor(DOOR_DOOR4, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_SNIDE], ITEM_NONE));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_KITCHEN], ITEM_NONE));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_STAIRS], ITEM_NONE));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_LOCKED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_STUDY], ITEM_A_BUNCH_OF_KEYS));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR4, new CDoor(DOOR_DOOR4, DOORSTATE_LOCKED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_BENTLEY], ITEM_A_BUNCH_OF_KEYS));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR5, new CDoor(DOOR_DOOR5, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_DRAWING], ITEM_NONE));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR6, new CDoor(DOOR_DOOR6, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_LIBRARY], ITEM_NONE));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR7, new CDoor(DOOR_DOOR7, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_LAUNDRY], ITEM_NONE));
	m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR8, new CDoor(DOOR_DOOR8, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_HALL4], ITEM_NONE));
	m_roomArray[ROOM_HALL4]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_HALL3], ITEM_NONE));
	m_roomArray[ROOM_HALL4]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_COOK], ITEM_A_HIDDEN_KEY));
	m_roomArray[ROOM_HALL4]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_GABRIEL], ITEM_A_BUNCH_OF_KEYS));
	m_roomArray[ROOM_LANDING]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPENING, m_roomArray[ROOM_LANDING], m_roomArray[ROOM_HALL1], ITEM_NONE));
	m_roomArray[ROOM_LANDING]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPENING, m_roomArray[ROOM_LANDING], m_roomArray[ROOM_STAIRS], ITEM_NONE));
	m_roomArray[ROOM_KITCHEN]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_HIDDEN, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_PASSAGE3], ITEM_NONE));
	m_roomArray[ROOM_KITCHEN]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_HALL3], ITEM_NONE));
	m_roomArray[ROOM_KITCHEN]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPENING, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_DINING], ITEM_NONE));
	m_roomArray[ROOM_STAIRS]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPENING, m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_LANDING], ITEM_NONE));
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
	m_roomArray[ROOM_LAUNDRY]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_LAUNDRY], m_roomArray[ROOM_HALL3], ITEM_NONE));
	m_roomArray[ROOM_GARDEN]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_GARDEN], m_roomArray[ROOM_GRAVEYARD], ITEM_A_RED_KEY));
	m_roomArray[ROOM_GARDEN]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPENING, m_roomArray[ROOM_GARDEN], m_roomArray[ROOM_OUTSIDE4], ITEM_NONE));
	m_roomArray[ROOM_GRAVEYARD]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_GRAVEYARD], m_roomArray[ROOM_GARDEN], ITEM_A_RED_KEY));
	m_roomArray[ROOM_COURTYARD]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_COURTYARD], m_roomArray[ROOM_STAIRS], ITEM_NONE));
	m_roomArray[ROOM_ANGUS_LANDING]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_ANGUS_LANDING], m_roomArray[ROOM_ANGUS_ROOM], ITEM_A_BUNCH_OF_KEYS));
	m_roomArray[ROOM_ANGUS_LANDING]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPENING, m_roomArray[ROOM_ANGUS_LANDING], m_roomArray[ROOM_ANGUS_STAIRS], ITEM_NONE));
	m_roomArray[ROOM_ANGUS_ROOM]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_ANGUS_ROOM], m_roomArray[ROOM_ANGUS_LANDING], ITEM_A_BUNCH_OF_KEYS));
	m_roomArray[ROOM_ANGUS_ROOM]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPENING, m_roomArray[ROOM_ANGUS_ROOM], m_roomArray[ROOM_ANGUS_SECRET], ITEM_NONE));
	m_roomArray[ROOM_ANGUS_SECRET]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_ANGUS_SECRET], m_roomArray[ROOM_ANGUS_ROOM], ITEM_NONE));
	m_roomArray[ROOM_ANGUS_STAIRS]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_ANGUS_STAIRS], m_roomArray[ROOM_STAIRS], ITEM_A_BUNCH_OF_KEYS));
	m_roomArray[ROOM_ANGUS_STAIRS]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPENING, m_roomArray[ROOM_ANGUS_STAIRS], m_roomArray[ROOM_ANGUS_LANDING], ITEM_NONE));
	m_roomArray[ROOM_DINING]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPENING, m_roomArray[ROOM_DINING], m_roomArray[ROOM_KITCHEN], ITEM_NONE));
	
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
	m_roomArray[ROOM_GABRIEL]->AddItemCache(2, COL_GABRIELS_BODY);
	
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
	m_roomArray[ROOM_DINGLE]->AddItemCache(2, COL_DINGLES_BODY);
	
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
	
	m_roomArray[ROOM_LAUNDRY]->AddItemCache(0, COL_WASHING_MACHINE);
	m_roomArray[ROOM_LAUNDRY]->AddItemCache(1, COL_WASHING_BASKET);
	m_roomArray[ROOM_LAUNDRY]->AddItemCache(2, COL_CUPBOARD);
	m_roomArray[ROOM_LAUNDRY]->AddItemCache(3, COL_WOODEN_CABINET);
	
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
	
	// ================================================================
	// Reverend
	// ================================================================
	
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(0, GOAL_JUMPROOM, m_roomArray[ROOM_DRAWING]));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(0, GOAL_JUMPPOINT, new Point(232, m_roomArray[ROOM_DRAWING]->CentreY())));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(0, GOAL_WAIT, 400));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(1, GOAL_SPEAK, (const char*) NULL, 500)); 
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(392, 144), 200));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(120, 184), 200));
	
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(0, GOAL_SPEAK, "THE REVEREND BELCHES", 100));
	
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(232, m_roomArray[ROOM_DRAWING]->CentreY()), 0));
	
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 2, EVENTFLAG_MURDER_DOCTOR, 0, 1));
	
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 1, 0, 0, LOOP_INFINITE));
	
	// 9:54
	
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(2, GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_LIBRARY], 0));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(112, 144), 0));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"LOOKING FOR CLUES INSPECTOR?\"", 200));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_LIBRARY], m_roomArray[ROOM_DRAWING], 100));
	m_characterArray[CHARTYPE_REVEREND]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 1, 0, 0, LOOP_INFINITE));
	
	// ================================================================
	// Bentley
	// ================================================================
		
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_JUMPROOM, m_roomArray[ROOM_STAIRS]));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_JUMPPOINT, new Point(176, m_roomArray[ROOM_STAIRS]->CentreY())));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_SPEAK, "BENTLEY ADVANCES:\"THIS WAY TO YOUR ROOM SIR\"", 100));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_HALL2], 0));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(640, 144), 0));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"YOUR ROOM SIR\"", 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_HALL3], 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(1, GOAL_GOTOROOM, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_BENTLEY], 0));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(72, 160), 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"YOU'LL FIND NOTHING OF INTEREST HERE..\"", 200));
	
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_BENTLEY], m_roomArray[ROOM_HALL3], 0));
	
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_LOCKDOOR, 0));
	
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_DRAWING], 0));
	
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"IS EVERYTHING SATISFACTORY, SIR?\"", 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_HALL3], 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_HALL4], 0));
	
	
	
	
	
	
	
	
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_HALL4], 0));
	
	
	
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(2, GOAL_GOTOPOINT, new Point(80, m_roomArray[ROOM_HALL4]->CentreY()), 0));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_WAIT, 100));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(128, m_roomArray[ROOM_HALL4]->CentreY()), 0));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_WAIT, 100));
	
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 2, EVENTFLAG_COOK_NOT_IN_ROOM, 0, 4));
	
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_COOK], 0));
	
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(3, GOAL_WAIT, 100));
	
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 4, EVENTFLAG_SNIDE_IN_ROOM, 0, 1));
	
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 3, EVENTFLAG_SNIDE_NOT_IN_ROOM, 0, 7));
	
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(4, GOAL_SPEAK, "\"AHEM\"", 0));
	
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_COOK], m_roomArray[ROOM_LIBRARY], 200));
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_LIBRARY], m_roomArray[ROOM_HALL3], 0));
	
	m_characterArray[CHARTYPE_BENTLEY]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 1, 0, 0, LOOP_INFINITE));
	
	// ================================================================
	// Cook
	// ================================================================
	
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_JUMPROOM, m_roomArray[ROOM_KITCHEN]));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_JUMPPOINT, new Point(104, m_roomArray[ROOM_KITCHEN]->CentreY())));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_WAIT, 300));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(360, 152), 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(72, 152), 100));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(1, GOAL_GOTOPOINT, new Point(360, 152), 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(96, 152), 100));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(360, 152), 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(32, 184), 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(392, 144), 100));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_COOK], 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(216, 144), 0));
	
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_WAIT, 200));
	
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"YOU'LL FIND YOUR ROOM UPSTAIRS.. THIS ONE'S MINE\"", 200));
	
	
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(2, GOAL_WAIT, 100));
	
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 2, EVENTFLAG_BENTLEY_NOT_IN_ROOM, 0, 32));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 3, EVENTFLAG_SNIDE_IN_ROOM, 0, 1));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_LOCKDOOR, 0));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(3, GOAL_WAIT, 500));
	
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_COOK], m_roomArray[ROOM_HALL4], 0));
	
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_KITCHEN], 0));
	
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(72, 152), 200));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"OOH YES I KNOW DEAR..\"", 200));
	m_characterArray[CHARTYPE_COOK]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 1, 0, 0, LOOP_INFINITE));
	
	// ================================================================
	// Gabriel
	// ================================================================
	
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(0, GOAL_JUMPROOM, m_roomArray[ROOM_KITCHEN]));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(0, GOAL_JUMPPOINT, new Point(208, m_roomArray[ROOM_KITCHEN]->CentreY())));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(0, GOAL_WAIT, 500));
	
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(1, GOAL_GOTOROOM, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_STUDY], 2, 0));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(264, 144), 0));
	
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(2, GOAL_GOTOROOM, m_roomArray[ROOM_HALL4], 0));
	
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_GABRIEL], 3, 0));
	
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(288, 144), 200));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(3, GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(344, 144), 0));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_KITCHEN], 0));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(96, 168), 200));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"..DUM DE DAH..\"", 200));
	m_characterArray[CHARTYPE_GABRIEL]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 1, 0, 0, LOOP_INFINITE));
	
	// ================================================================
	// Cynthia
	// ================================================================
	
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_JUMPROOM, m_roomArray[ROOM_CYNTHIA]));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_JUMPPOINT, new Point(232, m_roomArray[ROOM_CYNTHIA]->CentreY())));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_WAIT, 500));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_CYNTHIA], m_roomArray[ROOM_HALL1], 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(1, GOAL_GOTOPOINT, new Point(136, 144), 0));	// Reverend
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(312, 144), 0));	// Cynthia
	
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_DINGLE], 2, 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"SORRY.. WRONG ROOM\"", 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_DINGLE], m_roomArray[ROOM_HALL1], 0));
	
	
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(2, GOAL_GOTOROOM, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_CYNTHIA], 200));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"HELLO..\"", 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_CYNTHIA], m_roomArray[ROOM_OUTSIDE1], 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(240, 144), 200));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"AWFUL WEATHER..\"", 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_OUTSIDE1], m_roomArray[ROOM_MAJOR], 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(240, 160), 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(248, 128), 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"TSK TSK.. SUCH A MESS..\"", 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(240, 160), 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_MAJOR], m_roomArray[ROOM_LANDING], 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_LANDING], m_roomArray[ROOM_CYNTHIA], 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_CYNTHIA], m_roomArray[ROOM_HALL1], 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_CYNTHIA], 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(240, 160), 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_SPEAK, "CYNTHIA SNIFFS DISAPPROVINGLY..", 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(248, 128), 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_CYNTHIA], m_roomArray[ROOM_HALL1], 0));
	
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_DINGLE], 3, 0));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"SORRY.. WRONG ROOM\"", 100));
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_DINGLE], m_roomArray[ROOM_HALL1], 0));
	
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(3, GOAL_GOTOPOINT, new Point(328, 184), 0));	// Landing
	m_characterArray[CHARTYPE_CYNTHIA]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 1, 0, 0, LOOP_INFINITE));

	// ================================================================
	// Professor
	// ================================================================
	
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_JUMPROOM, m_roomArray[ROOM_LIBRARY]));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_JUMPPOINT, new Point(136, m_roomArray[ROOM_LIBRARY]->CentreY())));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_WAIT, 500));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(1, GOAL_GOTOPOINT, new Point(112, 144), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"WHERE IS IT?\"", 200));
	
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(2, GOAL_GOTOPOINT, new Point(312, 144), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(112, 144), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(96, m_roomArray[ROOM_LIBRARY]->CentreY()), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"..ER..\"", 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 2, 0, 0, 4));
	
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_LIBRARY], m_roomArray[ROOM_HALL3], 0));
	
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"MORNING INSPECTOR\"", 200));
	
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(96, m_roomArray[ROOM_HALL3]->CentreY()), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"GOODNESS!\"", 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(472, 144), 0)); // Study (locked)
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"THAT'S ODD\"", 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(136, 184), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(176, m_roomArray[ROOM_HALL3]->CentreY()), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(136, 184), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(176, m_roomArray[ROOM_HALL3]->CentreY()), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(136, 184), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(176, m_roomArray[ROOM_HALL3]->CentreY()), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_WAIT, 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_CLOCK], 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(72, 184), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_CLOCK], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(376, 144), 200));
		
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_LIBRARY], 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(168, 144), 0));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"YES!\"", 200));
	m_characterArray[CHARTYPE_PROFESSOR]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 1, 0, 0, LOOP_INFINITE));
	
	// ================================================================
	// Doctor
	// ================================================================
	
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_JUMPROOM, m_roomArray[ROOM_OUTSIDE3]));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_JUMPPOINT, new Point(176, m_roomArray[ROOM_OUTSIDE3]->CentreY())));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_WAIT, 500));
	
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(256, 184), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(176, m_roomArray[ROOM_OUTSIDE3]->CentreY()), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(256, 184), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_SPEAK, "THE DOCTOR GLANCES AT HIS WATCH..", 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(168, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(80, 184), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(32, 184), 200));	
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(344, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(176, m_roomArray[ROOM_OUTSIDE3]->CentreY()), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(256, 184), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_SPEAK, "THE DOCTOR GLANCES AT HIS WATCH..", 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(168, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(80, 184), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(32, 184), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(344, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(176, m_roomArray[ROOM_OUTSIDE3]->CentreY()), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(256, 184), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_SPEAK, "THE DOCTOR GLANCES AT HIS WATCH..", 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(168, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(80, 184), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_OUTSIDE3], m_roomArray[ROOM_DRAWING], 0));

	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(4, GOAL_GOTOPOINT, new Point(344, 144), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"HAS ANYONE SEEN MY SCALPELS?\"", 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(312, m_roomArray[ROOM_DRAWING]->CentreY()), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(344, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_CLOCK], 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(80, 184), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_CLOCK], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"GOOD EVENING\"", 200));
	
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 5, EVENTFLAG_MURDER_DINGLE, 0, 1));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 4, 0, 0, LOOP_INFINITE));
	
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(5, GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_DOCTOR], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(248, 152), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_DOCTOR], m_roomArray[ROOM_DINGLE], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(248, 152), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(360, 120), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(1, GOAL_GOTOCHAR, m_characterArray[CHARTYPE_SNIDE], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 1, 0, 0, 3));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"INSPECTOR..MR. DINGLE'S BEEN STRANGLED!\"", 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_DINGLE], 200));
	
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(248, 152), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(360, 120), 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"..TRAGIC.. POOR FELLOW\"", 200));
	
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_DINGLE], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(368, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_HALL3], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(2, GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_OUTSIDE3], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(240, 144), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_OUTSIDE3], m_roomArray[ROOM_DRAWING], 0));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(64, 184), 200));
	m_characterArray[CHARTYPE_DOCTOR]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 2, 0, 0, LOOP_INFINITE));
	
	// ================================================================
	// Major
	// ================================================================
	
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(0, GOAL_JUMPROOM, m_roomArray[ROOM_MAJOR]));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(0, GOAL_JUMPPOINT, new Point(232, m_roomArray[ROOM_MAJOR]->CentreY())));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(0, GOAL_WAIT, 500));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(1, GOAL_GOTOROOM, m_roomArray[ROOM_MAJOR], m_roomArray[ROOM_CYNTHIA], 0));
	
	
	
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(240, 160), 0));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_CYNTHIA], m_roomArray[ROOM_HALL1], 0));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_OUTSIDE1], 0));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(264, 144), 200));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(80, 184), 200));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_OUTSIDE1], m_roomArray[ROOM_HALL1], 200));
	
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(0, GOAL_SPEAK, "\"HAVE YOU SEEN THAT PIANO DOWNSTAIRS, SNIDE?\"", EVENTFLAG_MURDER_CYNTHIA, 200));
	
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_HALL2], 200));
	
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_MAJOR], 200));
	m_characterArray[CHARTYPE_MAJOR]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 1, 0, 0, LOOP_INFINITE));
	
	// ================================================================
	// Dingle
	// ================================================================
	
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_JUMPROOM, m_roomArray[ROOM_DRAWING]));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_JUMPPOINT, new Point(232, m_roomArray[ROOM_DRAWING]->CentreY())));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_WAIT, 700));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(392, 144), 200));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(480, 144), 200));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_HALL3], 0));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(392, 152), 200));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_HALL1], 0));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(376, 176), 200));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_GOTOROOM, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_DINGLE], 0));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(1, GOAL_SPEAK, "\"WOULD YOU MIND LEAVING MY ROOM PLEASE, SIR..\"", 500));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_SPEAK, "MR DINGLE ASKS YOU TO GO", 500));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_WAIT, 0));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 1, EVENTFLAG_SNIDE_IN_ROOM, 0, LOOP_INFINITE));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_SETEVENT, EVENTFLAG_LOCK_DINGLES_ROOM, 500));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_SETEVENT, EVENTFLAG_READY_MURDER_DINGLE, 0));
	m_characterArray[CHARTYPE_DINGLE]->AddGoal(new CGoal(0, GOAL_STOP, 0));
		
	// ... Walk to door in cellar
	
	// ================================================================
	// Angus
	// ================================================================
	
	m_characterArray[CHARTYPE_ANGUS]->AddGoal(new CGoal(0, GOAL_JUMPROOM, m_roomArray[ROOM_ANGUS_ROOM]));
	m_characterArray[CHARTYPE_ANGUS]->AddGoal(new CGoal(0, GOAL_JUMPPOINT, new Point(232, m_roomArray[ROOM_ANGUS_ROOM]->CentreY())));
	m_characterArray[CHARTYPE_ANGUS]->AddGoal(new CGoal(0, GOAL_WAIT, 500));
	m_characterArray[CHARTYPE_ANGUS]->AddGoal(new CGoal(1, GOAL_GOTOPOINT, new Point(64, 160), 500));
	m_characterArray[CHARTYPE_ANGUS]->AddGoal(new CGoal(0, GOAL_GOTOPOINT, new Point(232, 160), 500));
	m_characterArray[CHARTYPE_ANGUS]->AddGoal(new CGoal(0, GOAL_GOTOGOAL, 1, 0, 0, LOOP_INFINITE));
	
	// ----------------------------
	
	// 2:20
	m_eventArray[EVENT_START_GAME] = new CEvent(EVENT_START_GAME, new CTime(9, 10, 0, 0), EVENTFLAG_NONE, EVENTFLAG_NONE);
	m_eventArray[EVENT_MURDER_DINGLE] = new CEvent(EVENT_MURDER_DINGLE, new CTime(9, 12, 0, 0), EVENTFLAG_READY_MURDER_DINGLE | EVENTFLAG_NONE, EVENTFLAG_MURDER_DINGLE); // 9:12

	m_eventArray[EVENT_EVIDENCE_COUNT_6] = new CEvent(EVENT_EVIDENCE_COUNT_6, new CTime(9, 20, 0, 0), EVENTFLAG_MURDER_DINGLE | EVENTFLAG_EVIDENCE_COUNT_6 | EVENTFLAG_HALL3, EVENTFLAG_MURDER_CYNTHIA); // 9:15
	m_eventArray[EVENT_EVIDENCE_COUNT_7] = new CEvent(EVENT_EVIDENCE_COUNT_7, new CTime(9, 21, 0, 0), EVENTFLAG_EVIDENCE_COUNT_7 | EVENTFLAG_HALL1, EVENTFLAG_MURDER_DOCTOR); // 9:17
	m_eventArray[EVENT_EVIDENCE_COUNT_8] = new CEvent(EVENT_EVIDENCE_COUNT_8, new CTime(9, 22, 0, 0), EVENTFLAG_EVIDENCE_COUNT_8 | EVENTFLAG_HALL1, EVENTFLAG_MURDER_GABRIEL); // 9:18
	
	m_eventArray[EVENT_LOCK_DINGLES_ROOM] = new CEvent(EVENT_LOCK_DINGLES_ROOM, new CTime(9, 20, 0, 0), EVENTFLAG_MURDER_DINGLE | EVENTFLAG_HALL3, EVENT_LOCK_DINGLES_ROOM); // 9:20
	m_eventArray[EVENT_MURDER_CYNTHIA] = new CEvent(EVENT_MURDER_CYNTHIA, new CTime(9, RandomInt(20, 30), 0, 0), EVENTFLAG_MURDER_DINGLE | EVENTFLAG_HALL3, EVENTFLAG_MURDER_CYNTHIA); // 9:30
	m_eventArray[EVENT_MURDER_DOCTOR] = new CEvent(EVENT_MURDER_DOCTOR, new CTime(9, RandomInt(30, 40), 0, 0), EVENTFLAG_MURDER_CYNTHIA | EVENTFLAG_HALL1, EVENTFLAG_MURDER_DOCTOR); // 10:00
	m_eventArray[EVENT_MURDER_GABRIEL] = new CEvent(EVENT_MURDER_GABRIEL, new CTime(9, RandomInt(40, 50), 0, 0), EVENTFLAG_MURDER_DOCTOR | EVENTFLAG_HALL1, EVENTFLAG_MURDER_GABRIEL); // 10:30
	m_eventArray[EVENT_REMOVE_BULLETS] = new CEvent(EVENT_REMOVE_BULLETS, new CTime(11, 00, 0, 0), EVENTFLAG_MURDER_GABRIEL, EVENTFLAG_REMOVE_BULLETS); // 11:00
	m_eventArray[EVENT_GET_SHOT] = new CEvent(EVENT_GET_SHOT, new CTime(11, 30, 0, 0), EVENTFLAG_NONE, EVENTFLAG_GAME_OVER);
	// 11:30

	//m_eventArray[EVENT_MURDER_DINGLE] = new CEvent(EVENT_MURDER_DINGLE, new CTime(9, 10, 0, 0), EVENTFLAG_READY_MURDER_DINGLE | EVENTFLAG_NONE, EVENTFLAG_MURDER_DINGLE);
	//m_eventArray[EVENT_LOCK_DINGLES_ROOM] = new CEvent(EVENT_LOCK_DINGLES_ROOM, new CTime(9, 20, 0, 0), EVENTFLAG_MURDER_DINGLE | EVENTFLAG_HALL3, EVENT_LOCK_DINGLES_ROOM);
	//m_eventArray[EVENT_MURDER_CYNTHIA] = new CEvent(EVENT_MURDER_CYNTHIA, new CTime(9, 10, 0, 0), EVENTFLAG_MURDER_DINGLE | EVENTFLAG_HALL3, EVENTFLAG_MURDER_CYNTHIA);
	//m_eventArray[EVENT_MURDER_DOCTOR] = new CEvent(EVENT_MURDER_DOCTOR, new CTime(9, 10, 0, 0), EVENTFLAG_MURDER_CYNTHIA | EVENTFLAG_HALL1, EVENTFLAG_MURDER_DOCTOR);
	//m_eventArray[EVENT_MURDER_GABRIEL] = new CEvent(EVENT_MURDER_GABRIEL, new CTime(9, 10, 0, 0), EVENTFLAG_MURDER_DOCTOR | EVENTFLAG_HALL1, EVENTFLAG_MURDER_GABRIEL);
	//m_eventArray[EVENT_REMOVE_BULLETS] = new CEvent(EVENT_REMOVE_BULLETS, new CTime(9, 10, 0, 0), EVENTFLAG_MURDER_GABRIEL, EVENTFLAG_REMOVE_BULLETS);
	//m_eventArray[EVENT_GET_SHOT] = new CEvent(EVENT_GET_SHOT, new CTime(11, 30, 0, 0), EVENTFLAG_NONE, EVENTFLAG_GAME_OVER);
	
	//m_ratPoints[0] = new Point(88, 144);
	//m_ratPoints[1] = new Point(192, 136);
	//m_ratPoints[2] = new Point(144, 176);
	//m_ratPoints[3] = new Point(168, 160);
	
	m_ratPoints[0] = new Point(88, 144);
	m_ratPoints[1] = new Point(264, 144);
	m_ratPoints[2] = new Point(200, 176);
	m_ratPoints[3] = new Point(32, 176);

	m_cursor = new CCursor();
	m_pointer = new CPointer();
	
	m_console = new CConsole(m_cursor);
	m_keyboard = new CKeyboard(m_cursor);
	m_menu = new CMenu();

	m_watch = new CWatch(113, 21);
	
	m_save = new CSave(1024 * 32, m_characterArray, m_spriteArray, m_roomArray, m_itemArray, m_eventArray);
	
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
	
	switch(m_gameMode)
	{
	case GAMEMODE_INTRO:
		if(keys_released & KEY_START)
			InitData(0);
		else
			UpdateIntro();
		return;
	case GAMEMODE_TITLESCREEN:
		if(keys_released & KEY_START)
			InitGame(GAMETYPE_NORMAL);
		else
			UpdateTitleScreen();
		break;
	case GAMEMODE_PAUSED:
		if(keys_released & KEY_START || keys_released & KEY_A || keys_pressed & KEY_TOUCH)
		{
			m_gameMode = GAMEMODE_RUNNING;
			
			mmResume();
			InitRoom();
					
			ClearBG(0, true);
			
			m_console->Clear();
			m_timer->Start();
		}
		else if(keys_released & KEY_SELECT)
		{
			InitTitleScreen();
		}
		else if(keys_released & KEY_B)
		{
			InitGame(GAMETYPE_NORMAL);
		}
		else
		{
			m_console->Update();
			m_cursor->Update();
			m_cursor->Show();
		}
		break;
	case GAMEMODE_FREEZE:
		if(++m_frameCount == 200)
		{
			m_frameCount = 0;
			
			m_gameMode = GAMEMODE_RUNNING;
		}
		else
		{
			//DrawTime(m_timer->pCurrentTime());
			m_watch->Draw(m_timer->pCurrentTime());
			m_console->Update();
			m_cursor->Update();
			m_cursor->Show();
			
			if(m_currentRoom != NULL)
				m_currentRoom->Update(m_timer->pCurrentTime());
			
			BACKGROUND.scroll[2].y = --m_bg2MainVScroll;
		}
		break;
	case GAMEMODE_RUNNING:
		if(keys_released & KEY_START && m_displayMode == DISPLAYMODE_GAME)
			PauseGame();
		else if(keys_released & KEY_L || keys_released & KEY_R)
			lcdSwap();
		else
			UpdateGame(touch, keys_held, keys_pressed, keys_released);
		break;
	case GAMEMODE_DYING:
		if(++m_frameCount == 500)
		{
			m_frameCount = 0;
			
			m_snide->SetCharacterMode(CHARMODE_DEAD);
			m_snide->Update(m_currentRoom, m_eventFlags);
			m_snide->Draw();
			m_console->AddText("YOU GASP IN AGONY AND DROP DEAD..");
			InitGameOver(GAMEOVERMODE_END);
		}
		else
			UpdateGame(touch, keys_held, keys_pressed, keys_released);
		break;
	case GAMEMODE_ANGUS:
		if(++m_frameCount == 100)
		{
			m_characterArray[CHARTYPE_ANGUS]->SetCharacterMode(CHARMODE_TALKING);
			
			((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("MR MCFUNGUS SPEAKS \"THANK YOU INSPECTOR! YOU HAVE SET ME FREE!\"");
		}
		else if(m_frameCount == 800)
		{
			m_frameCount = 0;
			
			m_characterArray[CHARTYPE_ANGUS]->SetGoalMode(false);
			m_characterArray[CHARTYPE_ANGUS]->SetRoom(NULL);
		
			m_characterArray[CHARTYPE_ANGUS]->Disable();
			m_characterArray[CHARTYPE_ANGUS]->Hide();
			m_characterArray[CHARTYPE_ANGUS]->Draw();
						
			mmEffectEx(&g_sfx_magic);
			
			m_gameMode = GAMEMODE_RUNNING;
		}
		else
			UpdateGame(touch, keys_held, keys_pressed, keys_released);
		break;
	case GAMEMODE_REVERSETIME:
		if(++m_frameCount == 365) // 100:8:13
		{
			m_frameCount = 0;
				
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
	case GAMEMODE_ENDING:
		UpdateEnding(touch, keys_held, keys_pressed, keys_released);
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
							
							m_questionCharacter->SetCharacterMode(CHARMODE_WAITING);
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
						m_pointer->SetRect(MENU_X+8, MENU_Y+8, MENU_WIDTH-(8 * 2), MENU_HEIGHT-(8 * 2));
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
					m_pointer->SetRect(MENU_X+8, MENU_Y+8, MENU_WIDTH-(8 * 2), MENU_HEIGHT-(8 * 2));
					//m_pointer->SetRect(CONSOLE_MENU_X, CONSOLE_MENU_Y, CONSOLE_MENU_WIDTH, CONSOLE_MENU_HEIGHT);
				}
			}
		}
		break;
	case DISPLAYMODE_MENU:
		{
			if(keys_released & KEY_B)
			{
				m_displayMode = DISPLAYMODE_GAME;

				m_pointer->Hide();
				m_menu->Hide();
			}
			else if(keys_pressed & KEY_TOUCH)
			{
				m_displayMode = DISPLAYMODE_GAME;
				
				ProcessMenu(touch.px, touch.py);
			}
			else if(keys_released & KEY_A)
			{
				m_displayMode = DISPLAYMODE_GAME;

				Point* pPoint = m_pointer->pPoint();
				ProcessMenu(pPoint->X, pPoint->Y);
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
				m_questionMode = QUESTIONMODE_NONE;
				
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
				m_questionMode = QUESTIONMODE_NONE;
				
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
			if(keys_released & KEY_B)
			{
				m_displayMode = DISPLAYMODE_GAME;
				
				m_keyboard->Hide();
				m_fxManager.SetFx(FXTYPE_TEXT_SCROLLER, FXMODE_NORMAL, true);
				m_console->Clear();
				m_menu->Hide();
				
				DrawString("@2009 HEADSOFT", 9, 1, false);
				
				mmEffectEx(&g_sfx_beep);
			}
			else
			{
				char c = '\0';
				
				if(keys_pressed & KEY_TOUCH)
					c = m_keyboard->CheckKeyTouch(touch.px, touch.py);
				else
					c = m_keyboard->CheckKeyPress(keys_released);
					
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
						
						DrawString("@2009 HEADSOFT", 9, 1, false);
						
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
						
						DrawString("@2009 HEADSOFT", 9, 1, false);
						
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
					
					//CItemCache* pItemCache = m_roomArray[ROOM_COURTYARD]->GetItemCache(0);
					//pItemCache->AddItem(m_itemArray[ITEM_RED_KEY]);
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
				if(pDoor->GetDoorState() == DOORSTATE_OPEN || pDoor->GetDoorState() == DOORSTATE_OPENING)
				{		
					m_currentRoom = pDoor->pRoomOut();
					Point* pDoorPoint = pDoor->pDoorOut()->pPoint();
					
					int xDoor = pDoorPoint->X * 8;
					int yDoor = pDoorPoint->Y * 8;
					
					int xRoom = xDoor - 128;
					
					int xChar = xDoor;
					int yChar = yDoor - m_snide->Height() - 8;
					
					if(pDoor->GetDoorState() != DOORSTATE_OPENING)
						pDoor->pDoorOut()->SetDoorState(DOORSTATE_OPEN);
					
					m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
					
					m_currentRoom->Initialize(xRoom);
					m_snide->SetRoom(m_currentRoom);
					m_snide->SetPosition(xChar, yChar);
					
					m_console->AddText(g_enterRoomText[m_currentRoom->GetRoomType()]);
					
					InitRoom();
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
				if(pDoor->GetDoorState() == DOORSTATE_OPEN || pDoor->GetDoorState() == DOORSTATE_OPENING)
				{
					m_currentRoom = pDoor->pRoomOut();
					Point* pDoorPoint = pDoor->pDoorOut()->pPoint();
						
					int xDoor = pDoorPoint->X * 8;
					int yDoor = pDoorPoint->Y * 8;
					
					int xRoom = xDoor - 128;
					
					int xChar = xDoor;
					int yChar = yDoor - m_snide->Height() + 8;
					
					if(pDoor->GetDoorState() != DOORSTATE_OPENING)
						pDoor->pDoorOut()->SetDoorState(DOORSTATE_OPEN);
					
					m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
					
					m_currentRoom->Initialize(xRoom);
					m_snide->SetRoom(m_currentRoom);
					m_snide->SetPosition(xChar, yChar);
					
					m_console->AddText(g_enterRoomText[m_currentRoom->GetRoomType()]);
					
					InitRoom();
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
				
				if(pDoor->GetDoorState() != DOORSTATE_OPENING)
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
				
				if(pDoor->GetDoorState() != DOORSTATE_OPENING)
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
	CDoor* pDoor = NULL;
	CItemCache* pItemCache = NULL;
	
	m_snide->CheckCollision(m_snide->Facing(), &colNear, &colFar);
	
	m_menu->ClearIcons();
	
	switch(menuMode)
	{
	case MENUMODE_GENERAL:
		if(TryGetDoor(colNear, colFar, &pDoor))
		{
			if(!pDoor->Hidden() && pDoor->GetDoorState() != DOORSTATE_OPENING)
			{			
				if(pDoor->GetDoorState() == DOORSTATE_OPEN)
					m_menu->AddIconSet(ICONSET_DOOR_CLOSE);
				else
					m_menu->AddIconSet(ICONSET_DOOR_OPEN);
			}
			else
			{
				m_menu->AddIconSet(ICONSET_GENERAL);
				
				if((m_eventFlags & 0x7FELL) != 0)
					m_menu->AddIcon(ICON_QUESTION);
				
				m_menu->AddIcon(ICON_LOAD);
				m_menu->AddIcon(ICON_SAVE);
			}
		}
		else
		{
			m_menu->AddIconSet(ICONSET_GENERAL);
			
			if((m_eventFlags & 0x7FELL) != 0)
				m_menu->AddIcon(ICON_QUESTION);
			
			m_menu->AddIcon(ICON_LOAD);
			m_menu->AddIcon(ICON_SAVE);
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
			
		if(pItem->GetItemAttribs() & ITEMATTRIB_VACUUM)
			m_menu->AddIcon(ICON_VACUUM);
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
	static char buffer[MAX_TEXT_BUFFER];
	
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
		sprintf(buffer, "%s\n\nNOTHING...", text);
		m_console->AddText(buffer);
		m_console->HideMenu();
	}
	
	return itemCount;
}

bool CGame::ShowVisibleCharactersMenu()
{
	m_displayMode = DISPLAYMODE_CONSOLE_MENU;
	
	if((m_eventFlags & 0x7FELL) != 0)
	{
		m_console->AddText("IN THE ROOM YOU SEE:");
		m_console->ClearMenu();
		
		for(int i=1; i<MAX_CHARACTERS; i++)
			if(m_eventFlags & BIT64(i))
				m_console->AddMenuItem(g_characterName[i], m_characterArray[i]);
			
		m_console->ShowMenu();
		m_console->DrawSelectorBar();
		
		return true;
	}
	else
	{
		m_console->AddText("IN THE ROOM YOU SEE:\n\nNOBODY..");
		
		return false;
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

void CGame::ShowSaveMenu(const char* text)
{
	m_displayMode = DISPLAYMODE_CONSOLE_MENU;
	
	m_console->AddText(text);
	m_console->ClearMenu();
	
	static char buf[256];
	CTime time;
	
	for(int i=0; i<5; i++)
	{
		if(m_save->ReadTimeStamp(g_saveName[i], &time))
		{
			sprintf(buf, "Slot %02d (%02d:%02d:%02d)", i + 1, time.Hours, time.Minutes, time.Seconds);
			m_console->AddMenuItem(buf, NULL);
		}
		else
		{
			sprintf(buf, "Slot %02d (Empty)", i + 1);
			m_console->AddMenuItem(buf, NULL);
		}
	}
		
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
	static char buffer[MAX_TEXT_BUFFER];
	
	//DrawString("                                ", 0, 0, false);
	//DrawString(g_iconName[(int) iconType], 0, 0, false);
	switch(iconType)
	{
	case ICON_NONE:
		{
			//m_displayMode = DISPLAYMODE_GAME;

			m_pointer->Hide();
			m_menu->Hide();
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
					
					m_pointer->Hide();
					m_menu->Hide();
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
						else if(pItem->GetItemType() == ITEM_A_BOMB)
						{
							mmEffectEx(&g_sfx_bomb);
							m_snide->SetCharacterMode(CHARMODE_BOMB);
							InitGameOver(GAMEOVERMODE_END);
						}
						else
							ShowItemMenu("YOU FIND:", pItemCache, NULL);
					}
				
					m_openMode = OPENMODE_ROOM;
					m_pointer->Hide();
					m_menu->Hide();
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
					sprintf(buffer, "YOU SEE:\n\n%s", g_colName[colNear]);
					m_console->AddText(buffer);
				}
				
				m_pointer->Hide();
				m_menu->Hide();
			}
			else
			{
				CItem* pItem = (CItem*) m_console->SelectedObject();
				const char* pText = g_itemExamine[pItem->GetItemType()];

				if(pText == NULL)
					m_console->AddText(g_itemExamine[0]);
				else
				{
					//m_console->AddText(g_itemExamine[pItem->GetItemType()]);
					if(m_console->AddText(g_itemExamine[pItem->GetItemType()]))
						m_displayMode = DISPLAYMODE_CONSOLE;
				}
				
				m_pointer->Hide();
				m_menu->Hide();
				m_menu->DrawItem(pItem->GetItemType(), 24, 18, false);
			}
		}
		break;
	case ICON_INVENTORY:
		{
			m_displayMode = DISPLAYMODE_CONSOLE_MENU;
			m_openMode = OPENMODE_ITEM;
			
			ShowItemMenu("YOU ARE CARRYING:", m_snide->GetItemCache(), NULL);
			
			m_pointer->Hide();
			m_menu->Hide();
			
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
						sprintf(buffer, "YOU DROP:\n\n%s", g_itemName[pItem->GetItemType()]);
						m_console->AddText(buffer);
						
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
								
								if(!(m_eventFlags & EVENTFLAG_COLLECTED_RED_KEY))
								{
									m_eventFlags |= EVENTFLAG_COLLECTED_RED_KEY;
									
									CItemCache* itemCache = m_roomArray[ROOM_ANGUS_LANDING]->GetItemCache(1);
									itemCache->AddItem(m_itemArray[ITEM_A_RED_KEY]);
									
									mmEffectEx(&g_sfx_keydrop);
								}
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
						case COL_HEADSTONE1:
							if(pItem->GetItemType() == ITEM_ANGUS_MCFUNGUS)
							{
								pItemCache->RemoveItem(m_itemArray[ITEM_ANGUS_MCFUNGUS]);
								
								m_characterArray[CHARTYPE_ANGUS]->SetGoalMode(false);
								m_characterArray[CHARTYPE_ANGUS]->SetCharacterMode(CHARMODE_NONE);
								m_characterArray[CHARTYPE_ANGUS]->SetRoom(m_roomArray[ROOM_GRAVEYARD]);
								m_characterArray[CHARTYPE_ANGUS]->SetPosition(8, 176 - m_characterArray[CHARTYPE_ANGUS]->Height());
								m_characterArray[CHARTYPE_ANGUS]->Face(DIRECTION_LEFT);
								m_characterArray[CHARTYPE_ANGUS]->SetHFlip(true);
							
								m_characterArray[CHARTYPE_ANGUS]->Show();
								m_characterArray[CHARTYPE_ANGUS]->Draw();
								
								mmEffectEx(&g_sfx_magic);
								
								m_frameCount = 0;
								
								m_gameMode = GAMEMODE_ANGUS;
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
			
			m_pointer->Hide();
			m_menu->Hide();
		}
		break;
	case ICON_SAVE:
		ShowSaveMenu("SELECT SAVE SLOT:");
		
		m_pointer->Hide();
		m_menu->Hide();
		break;
	case ICON_LOAD:
		ShowSaveMenu("SELECT LOAD SLOT:");
		
		m_pointer->Hide();
		m_menu->Hide();
		break;
	case ICON_SHOOT:
		{	
			if(m_endingMode == ENDINGMODE_ESCAPING)
			{
				m_endingMode = ENDINGMODE_ARREST;
					
				m_frameCount = 50;
			}
			else
			{
				m_console->AddText("YOU CAN'T USE THAT HERE, YOU MIGHT HURT SOMEONE!");
			}
			
			m_pointer->Hide();
			m_menu->Hide();
		}
		break;
	case ICON_ACCUSE:
		{
			ShowCharacterMenu("WHO IS THE MURDERER?", NULL);
			
			m_pointer->Hide();
			m_menu->Hide();
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
			
			m_pointer->Hide();
			m_menu->Hide();
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
			
			m_pointer->Hide();
			m_menu->Hide();
		}
		break;
	case ICON_QUESTION:
		{
			m_questionMode = QUESTIONMODE_WAITING;
			
			if(!ShowVisibleCharactersMenu())
			{
				m_questionMode = QUESTIONMODE_NONE;
				m_displayMode = DISPLAYMODE_GAME;
				m_console->HideMenu();
			}
			
			m_pointer->Hide();
			m_menu->Hide();
		}
		break;
	case ICON_READ:
		{
			CItem* pItem = (CItem*) m_console->SelectedObject();
			
			if(m_console->AddText(g_itemRead[pItem->GetItemType()]))
				m_displayMode = DISPLAYMODE_CONSOLE;
				
			m_pointer->Hide();
			m_menu->Hide();
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
			
			m_pointer->Hide();
			m_menu->Hide();
		}
		break;
	case ICON_USE:
		{
			m_useMode = USEMODE_USE;
			m_displayMode = DISPLAYMODE_CONSOLE_MENU;
			
			ShowItemMenu("USE:", m_snide->GetItemCache(), NULL);
			
			m_pointer->Hide();
			m_menu->Hide();
		}
		break;
	case ICON_TIME:
		{
			PauseGame();
		}
		break;
	case ICON_PLACE:
		{
			m_displayMode = DISPLAYMODE_CONSOLE_MENU;
			
			m_placeItem = (CItem*) m_console->SelectedObject();
			
			ShowItemMenu("PUT IN:", m_snide->GetItemCache(), m_placeItem);
			
			m_pointer->Hide();
			m_menu->Hide();
		}
		break;
	case ICON_VACUUM:
		{
			mmEffectEx(&g_sfx_vacuum);
					
			CharacterType charNear, charFar;
			
			if(CheckCharacterCollision(m_snide->Facing(), &charNear, &charFar))
			{			
				if(charNear == CHARTYPE_ANGUS || charFar == CHARTYPE_ANGUS)
				{
					CItemCache* pItemCache = m_itemArray[ITEM_A_VACUUM_CLEANER]->GetItemCache();
					
					if(pItemCache->AddItem(m_itemArray[ITEM_ANGUS_MCFUNGUS]))
					{
						if(!(m_eventFlags & EVENTFLAG_COLLECTED_ANGUS))
						{
							m_eventFlags |= EVENTFLAG_COLLECTED_ANGUS;
						
							m_characterArray[CHARTYPE_ANGUS]->SetGoalMode(false);
							m_characterArray[CHARTYPE_ANGUS]->SetRoom(NULL);
						
							m_characterArray[CHARTYPE_ANGUS]->Disable();
							m_characterArray[CHARTYPE_ANGUS]->Hide();
							m_characterArray[CHARTYPE_ANGUS]->Draw();
						}
					}
				}
			}
			
			m_pointer->Hide();
			m_menu->Hide();
		}
		break;
	}
}

void CGame::PostProcessMenu()
{
	static char buffer[MAX_TEXT_BUFFER];

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
							sprintf(buffer, "YOU TAKE:\n\n%s", g_itemName[pItem->GetItemType()]);
							m_console->AddText(buffer);
							
							m_menu->DrawItem(pItem->GetItemType(), 24, 18, false);
							
							switch(colType)
							{
							case COL_HOURGLASS:
								if(pItem->GetItemType() == ITEM_AN_HOURGLASS)
								{
									pItemCache->RemoveItem(m_itemArray[ITEM_AN_HOURGLASS]);
									m_fxManager.SetFx(FXTYPE_PARTICLES, FXMODE_HOURGLASS, true);
									
									((CFxParticles*)m_fxManager.GetFx(FXTYPE_PARTICLES))->SetPosition(88, 152);
									
									mmEffectEx(&g_sfx_timewarp);
									
									m_gameMode = GAMEMODE_REVERSETIME;
								}
								break;
							case COL_GOLDEN_SKULL:
								if(pItem->GetItemType() == ITEM_A_GOLDEN_SKULL)
								{
									pItemCache->RemoveItem(m_itemArray[ITEM_A_GOLDEN_SKULL]);
									m_fxManager.SetFx(FXTYPE_PARTICLES, FXMODE_SKULL, true);
									
									((CFxParticles*)m_fxManager.GetFx(FXTYPE_PARTICLES))->SetPosition(152, 152);
									
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
						//m_menu->Hide();
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
			
			//sprintf(buffer, "YOU SELECTED:\n\n%s", g_itemName[pItem->GetItemType()]);
			//m_console->AddText(buffer);
			m_displayMode = DISPLAYMODE_MENU;
			SetMenuIcons(MENUMODE_ITEM, pItem);
			m_pointer->SetRect(MENU_X+8, MENU_Y+8, MENU_WIDTH-(8 * 2), MENU_HEIGHT-(8 * 2));
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
		Save(g_saveName[m_console->SelectedIndex()]);
		
		m_console->AddText("SAVED.");
	
		m_displayMode = DISPLAYMODE_GAME;
		m_pointer->Hide();
		m_menu->Hide();
		m_console->HideMenu();
		break;
	case ICON_LOAD:
		if(Load(g_saveName[m_console->SelectedIndex()]))	
			m_console->AddText("LOADED.");
		else
			m_console->AddText("LOAD FAILED.");
	
		m_displayMode = DISPLAYMODE_GAME;
		m_pointer->Hide();
		m_menu->Hide();
		m_console->HideMenu();
		break;
	case ICON_SHOOT:
		break;
	case ICON_ACCUSE:
		{
			CItemCache* pItemCache = m_snide->GetItemCache();
			int evidenceCount = 0;
			
			if(pItemCache->ContainsItem(m_itemArray[ITEM_PADDED_ENVELOPES]))
			{
				pItemCache = m_itemArray[ITEM_PADDED_ENVELOPES]->GetItemCache();
				
				for(int i=0; i<pItemCache->ItemCount(); i++)
				{
					CItem* pItem = pItemCache->GetItem(i);
					
					if(pItem != NULL)
						if(pItem->GetItemAttribs() & ITEMATTRIB_EVIDENCE)
							evidenceCount++;
				}
			}
			
			if(evidenceCount == 10 && m_console->SelectedIndex() == 8)
				InitEnding(ENDINGMODE_LEDATGUNPOINT);
			else
				m_console->AddText("YOU DO NOT HAVE THE EVIDENCE TO PROVE IT.");
		
			m_displayMode = DISPLAYMODE_GAME;
			m_pointer->Hide();
			m_menu->Hide();
			m_console->HideMenu();
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
							static char buffer[MAX_TEXT_BUFFER];
							
							CItem* pItem = (CItem*) m_console->SelectedObject();
							const char* pReplyText = g_askAboutItem[m_questionCharacter->GetCharacterType() * MAX_ITEMS + pItem->GetItemType()];
							
							m_questionCharacter->SetCharacterMode(CHARMODE_TALKING);
							
							switch(m_questionCharacter->GetCharacterType())
							{
							case CHARTYPE_BENTLEY:
								if(pReplyText == NULL)
								{
									sprintf(buffer, "\"IT IS QUITE OBVIOUSLY %s\"", g_itemName[pItem->GetItemType()]);
									CharacterSpeak(m_questionCharacter, buffer);
								}
								else
									CharacterSpeak(m_questionCharacter, pReplyText);
								break;
							case CHARTYPE_MAJOR:
								CharacterSpeak(m_questionCharacter, g_askAboutMajorRandom[rand() % 4]);
								break;
							case CHARTYPE_ANGUS:
								mmEffectEx(&g_sfx_ghostly);
								CharacterSpeak(m_questionCharacter, "\"WOOOOOO!\"");
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
						
						mmEffectEx(&g_sfx_glass);
					}
					
					if(m_useItem->GetItemType() == ITEM_A_HAMMER && m_withItem->GetItemType() == ITEM_DIRTY_PLATES)
					{
						useSuccess = true;
						pItemCache->ReplaceItem(m_withItem, m_itemArray[ITEM_BROKEN_PLATES]);
						
						mmEffectEx(&g_sfx_glass);
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
			
			if(m_inItem->GetItemAttribs() & ITEMATTRIB_OPEN && !m_inItem->GetLocked())
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
			
			//sprintf(buffer, "Place %s in %s",g_itemName[m_placeItem->GetItemType()], g_itemName[m_inItem->GetItemType()]);
			//fprintf(stderr, buffer);
		}
	case ICON_VACUUM:
		break;
	}
}

void CGame::InitRoom()
{
	switch(m_currentRoom->GetRoomType())
	{
	case ROOM_DINGLE:
		SoundOff();
		FxOff();
		
		if((m_eventFlags & EVENTFLAG_MURDER_DINGLE) && !(m_eventFlags & EVENTFLAG_WITNESS_MURDER_DINGLE))
		{
			m_gameMode = GAMEMODE_FREEZE;
			m_frameCount = 0;
			PlaySong(SONGTYPE_MURDER);
			m_eventFlags |= EVENTFLAG_WITNESS_MURDER_DINGLE;
		}
		break;
	case ROOM_STAIRS:
		SoundOff();
		FxOff();
		
		if((m_eventFlags & EVENTFLAG_MURDER_CYNTHIA) && !(m_eventFlags & EVENTFLAG_WITNESS_MURDER_CYNTHIA))
		{
			m_gameMode = GAMEMODE_FREEZE;
			m_frameCount = 0;
			PlaySong(SONGTYPE_MURDER);
			m_eventFlags |= EVENTFLAG_WITNESS_MURDER_CYNTHIA;
		}
		break;
	case ROOM_GABRIEL:
		SoundOff();
		FxOff();
		
		if((m_eventFlags & EVENTFLAG_MURDER_GABRIEL) && !(m_eventFlags & EVENTFLAG_WITNESS_MURDER_GABRIEL))
		{
			m_gameMode = GAMEMODE_FREEZE;
			m_frameCount = 0;
			PlaySong(SONGTYPE_MURDER);
			m_eventFlags |= EVENTFLAG_WITNESS_MURDER_GABRIEL;
		}
		break;
	case ROOM_OUTSIDE1:
	case ROOM_OUTSIDE3:
		SoundOff();
		mmSetJingleVolume(1024);
		FxOff();
		break;
	case ROOM_OUTSIDE2:
	case ROOM_OUTSIDE4:
	case ROOM_GARDEN:
	case ROOM_GRAVEYARD:
	case ROOM_COURTYARD:
		SoundOff();
		FxOff();
		mmSetJingleVolume(1024);
		m_fxManager.SetFx(FXTYPE_PARTICLES, FXMODE_RAIN, true);
		break;
	case ROOM_CLOCK:
		SoundOff();
		FxOff();
		m_clock = mmEffectEx(&g_sfx_clock);
		
		if((m_eventFlags & EVENTFLAG_MURDER_DOCTOR) && !(m_eventFlags & EVENTFLAG_WITNESS_MURDER_DOCTOR))
		{
			m_gameMode = GAMEMODE_FREEZE;
			m_frameCount = 0;
			PlaySong(SONGTYPE_MURDER);
			m_eventFlags |= EVENTFLAG_WITNESS_MURDER_DOCTOR;
		}
		break;
	case ROOM_DRAWING:
		SoundOff();
		FxOff();
		
		m_fireplace = mmEffectEx(&g_sfx_fireplace);
		break;
	case ROOM_LAUNDRY:
	case ROOM_SEWERS:
		SoundOff();
		FxOff();
		
		//m_waterdrip = mmEffectEx(&g_sfx_waterdrip);
	
		m_fxManager.SetFx(FXTYPE_RAT, FXMODE_NORMAL, true);
		m_fxManager.SetFx(FXTYPE_LEAK, FXMODE_NORMAL, true);
		
		if(m_currentRoom->GetRoomType() == ROOM_LAUNDRY)
		{
			((CFxRat*)m_fxManager.GetFx(FXTYPE_RAT))->SetPoints(m_ratPoints[0], m_ratPoints[1], m_ratPoints[2], m_ratPoints[3]);
			((CFxLeak*)m_fxManager.GetFx(FXTYPE_LEAK))->SetLocation(80, 56, 80, 128);
		}
		else
		{
			((CFxRat*)m_fxManager.GetFx(FXTYPE_RAT))->SetPoints(m_ratPoints[0], m_ratPoints[1], m_ratPoints[2], m_ratPoints[3]);
			((CFxLeak*)m_fxManager.GetFx(FXTYPE_LEAK))->SetLocation(152, 104, 152, 136);
		}
		break;
	default:
		SoundOff();
		FxOff();
		break;
	}
	
	dmaCopy(sprite_watchPal, SPRITE_PALETTE_SUB, sprite_watchPalLen);
}

void CGame::InitMurder(MurderType murderType)
{
	switch(murderType)
	{
	case MURDERTYPE_DINGLE:
		m_characterArray[CHARTYPE_DINGLE]->Reset();
		m_characterArray[CHARTYPE_DINGLE]->SetRoom(m_roomArray[ROOM_DINGLE]);
		m_characterArray[CHARTYPE_DINGLE]->SetPosition(336, 80);
		m_characterArray[CHARTYPE_DINGLE]->SetCharacterMode(CHARMODE_DEAD);
		
		m_roomArray[ROOM_DINGLE]->SetColMap(col_dingle_murder);
		break;
	case MURDERTYPE_CYNTHIA:
		m_characterArray[CHARTYPE_CYNTHIA]->Reset();
		m_characterArray[CHARTYPE_CYNTHIA]->SetRoom(m_roomArray[ROOM_STAIRS]);
		m_characterArray[CHARTYPE_CYNTHIA]->SetPosition(232, 148);
		m_characterArray[CHARTYPE_CYNTHIA]->SetCharacterMode(CHARMODE_DEAD);
		
		m_roomArray[ROOM_STAIRS]->SetColMap(col_stairs_murder);
		m_roomArray[ROOM_STAIRS]->SetOverlay(g_stairs_frontMap, 168);
		m_roomArray[ROOM_LANDING]->SetOverlay(g_landing_front2Map);
		
		m_roomArray[ROOM_SNIDE]->AddItem(0, m_itemArray[ITEM_A_BOMB], true);
		
		((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("YOU HEAR A SCREAM ..FOLLOWED BY A LOUD CRASH!");
		break;
	case MURDERTYPE_DOCTOR:
		m_characterArray[CHARTYPE_DOCTOR]->Reset();
		m_characterArray[CHARTYPE_DOCTOR]->SetRoom(m_roomArray[ROOM_CLOCK]);
		m_characterArray[CHARTYPE_DOCTOR]->SetPosition(56, 132);
		m_characterArray[CHARTYPE_DOCTOR]->SetCharacterMode(CHARMODE_DEAD);
		
		m_roomArray[ROOM_CLOCK]->SetColMap(col_clock_murder);
		
		m_roomArray[ROOM_COOK]->AddItem(0, m_itemArray[ITEM_A_KNIFE], true);
		
		((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("YOU HEAR A RATHER UNPLEASANT, GASPING SCREAM FROM DOWNSTAIRS!");
		break;
	case MURDERTYPE_GABRIEL:
		m_characterArray[CHARTYPE_GABRIEL]->Reset();
		m_characterArray[CHARTYPE_GABRIEL]->SetRoom(m_roomArray[ROOM_GABRIEL]);
		m_characterArray[CHARTYPE_GABRIEL]->SetPosition(208, 112);
		m_characterArray[CHARTYPE_GABRIEL]->SetCharacterMode(CHARMODE_DEAD);
		
		m_roomArray[ROOM_GABRIEL]->SetColMap(col_gabriel_murder);
		break;
	}
}

void CGame::UpdateFx()
{
	if(m_currentRoom->GetRoomType() == ROOM_GRAVEYARD && rand() % 3000 == 0)
		mmEffectEx(&g_sfx_howling);
	
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
			
			((CFxParticles*)m_fxManager.GetFx(FXTYPE_PARTICLES))->SetXOffset(m_currentRoom->X());
			
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
	case ROOM_SEWERS:
	case ROOM_LAUNDRY:
		((CFxRat*)m_fxManager.GetFx(FXTYPE_RAT))->SetXOffset(m_currentRoom->X());
		((CFxLeak*)m_fxManager.GetFx(FXTYPE_LEAK))->SetXOffset(m_currentRoom->X());
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
		
		if(m_currentRoom->OverlayY() < m_characterArray[i]->Y() + m_characterArray[i]->Height())
			m_characterArray[i]->SetPriority(0);
		else
			m_characterArray[i]->SetPriority(1);
		
		if(!(m_eventFlags & BIT64(i)) && !m_characterArray[i]->Dead())
			continue;
		
		for(int j=0; j < MAX_CHARACTERS; j++)
		{
			if(m_characterArray[i] == m_characterArray[j])
				continue;
			
			if (!(m_eventFlags & BIT64(j)) && !m_characterArray[j]->Dead())
				continue;

			if (IntersectRect(m_characterArray[i]->pRect(), m_characterArray[j]->pRect()))
			{
				if (m_characterArray[i]->Y() + m_characterArray[i]->Height() > m_characterArray[j]->Y() + m_characterArray[j]->Height() &&
					m_characterArray[i]->OamIndex() > m_characterArray[j]->OamIndex())
				{
					int temp = m_characterArray[i]->OamIndex();
					m_characterArray[i]->SetOamIndex(m_characterArray[j]->OamIndex());
					m_characterArray[j]->SetOamIndex(temp);
				}
			}
		}
	}
}
		
uint64 CGame::GetCharactersInRoom(CRoom* pRoom)
{
	uint64 charsInRoom = 0;

	for (int i=0; i < MAX_CHARACTERS; i++)
	{
		if(!m_characterArray[i]->Dead() && m_characterArray[i]->GetRoom() == pRoom)
			charsInRoom |= BIT64(i);
	}
	
	charsInRoom |= ((~charsInRoom & 0x7FFLL) << 11);
	
	return charsInRoom;
}

void CGame::UpdateCharacters()
{
	const char* string = NULL;
	
	m_eventFlags &= ~0x3FFFFFLL;

	for (int i=0; i < MAX_CHARACTERS; i++)
	{
		m_eventFlags = (m_characterArray[i]->Update(m_currentRoom, (m_eventFlags | GetCharactersInRoom(m_characterArray[i]->GetRoom()))) & ~0x3FFFFFLL);
		
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
		
		if(m_characterArray[i]->GetCharacterType() == CHARTYPE_MAJOR)
		{
			if(m_characterArray[i]->GetRoom() == m_currentRoom && rand() % 500 == 0)
				if(((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->ScrollerEmpty())
					((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText(g_askAboutMajorRandom[rand() % 4]);
		}
	}
	
	m_eventFlags |= GetCharactersInRoom(m_currentRoom);
}

void CGame::CharacterSpeak(CCharacter* pCharacter, const char* string)
{
	static char buffer[MAX_TEXT_BUFFER];
	
	if(string == NULL)
		return;

	if(m_speakCharacter != pCharacter)
	{
		if(string[0] == '\"')
		{
			m_speakCharacter = pCharacter;

			sprintf(buffer, "%s SPEAKS %s", g_characterName[pCharacter->GetCharacterType()], string);
			((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText(buffer);
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
	//static char buf[256];
	
	switch( msg )
	{
	case MMCB_SONGMESSAGE:
		//sprintf(buf, "MMCB_SONGMESSAGE: msg: %d, param: %d", msg, param);
		//fprintf(stderr, buf);
		
		switch(param)
		{
		case 0:
			switch(m_songType)
			{
			case SONGTYPE_TITLESCREEN:
				//fprintf(stderr, "SONGTYPE_TITLESCREEN");
				break;
			case SONGTYPE_MURDER:
				//fprintf(stderr, "SONGTYPE_MURDER");
				PlaySong(SONGTYPE_TENSION);
				break;
			case SONGTYPE_INGAME:
				//fprintf(stderr, "SONGTYPE_INGAME");
				//StopSong();
				break;
			case SONGTYPE_TENSION:
				//fprintf(stderr, "SONGTYPE_TENSION");
				//StopSong();
				break;
			}
			break;
		default:
			break;
		}
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
	if(m_gameMode == GAMEMODE_PAUSED)
	{
		m_fxManager.GetFx(FXTYPE_FADE_RAMP)->UpdateVBlank();
		m_fxManager.GetFx(FXTYPE_COLOUR)->UpdateVBlank();
	}
	else
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
	dmaFillHalfWords(0, BG_PALETTE_SUB, 512);
	dmaFillHalfWords(0, BG_PALETTE, 512);
	dmaFillHalfWords(0, BG_MAP_RAM_SUB(INTRO_BG0_MAP_BASE_SUB), 2048);
	dmaFillHalfWords(0, BG_MAP_RAM(INTRO_BG0_MAP_BASE), 2048);
	dmaFillHalfWords(0, BG_MAP_RAM_SUB(INTRO_BG1_MAP_BASE_SUB), 2048);
	dmaFillHalfWords(0, BG_MAP_RAM(INTRO_BG1_MAP_BASE), 2048); 
	
	videoSetMode(MODE_0_2D | DISPLAY_WIN0_ON | DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE);
	videoSetModeSub(MODE_0_2D | DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE);
	
	vramSetMainBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE_0x06400000, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);
	
	bgInit(0, BgType_Text4bpp, BgSize_T_256x256, BG0_MAP_BASE, BG0_TILE_BASE);
	bgInit(1, BgType_Text8bpp, BgSize_T_256x256, BG1_MAP_BASE, BG1_TILE_BASE);
	bgInit(2, BgType_Text8bpp, BgSize_T_256x256, BG2_MAP_BASE, BG2_TILE_BASE);
	bgInit(3, BgType_Text8bpp, BgSize_T_256x256, BG3_MAP_BASE, BG3_TILE_BASE);
	
	bgInitSub(0, BgType_Text8bpp, BgSize_T_256x256, BG0_MAP_BASE_SUB, BG0_TILE_BASE_SUB);
	bgInitSub(1, BgType_Text8bpp, BgSize_T_256x256, BG1_MAP_BASE_SUB, BG1_TILE_BASE_SUB);
	int bg2Sub = bgInitSub(2, BgType_Text8bpp, BgSize_T_512x256, BG2_MAP_BASE_SUB, BG2_TILE_BASE_SUB);
	int bg3Sub = bgInitSub(3, BgType_Text8bpp, BgSize_T_512x256, BG3_MAP_BASE_SUB, BG3_TILE_BASE_SUB);
	
	bgSetControlBits(bg2Sub, BG_PRIORITY_0);
	bgSetControlBits(bg3Sub, BG_PRIORITY_2);
	
	ClearBG(0, true);
	
	dmaFillHalfWords(0, BG_TILE_RAM_SUB(BG0_TILE_BASE_SUB), 8 * 8 * 2);
	
	videoBgEnableSub(0);
	
	lcdMainOnBottom();
	
	dmaCopy(sprite_miscPal, SPRITE_PALETTE, sprite_miscPalLen);
	dmaCopy(sprite_watchPal, SPRITE_PALETTE_SUB, sprite_watchPalLen);
	
	dmaCopy(fontTiles, BG_TILE_RAM(BG0_TILE_BASE), fontTilesLen);
	//dmaCopy(fontTiles, BG_TILE_RAM_SUB(BG0_TILE_BASE_SUB) , fontTilesLen);
	
	dmaCopy(fontPal, BG_PALETTE, fontPalLen);
	//dmaCopy(fontPal, BG_PALETTE_SUB, fontPalLen);
	
	BG_PALETTE[0] = 0;
	BG_PALETTE_SUB[0] = 0;
	
	dmaCopy(font_largeTiles, BG_TILE_RAM(BG0_TILE_BASE) + (fontTilesLen / 2), font_largeTilesLen);
	//dmaCopy(font_largeTiles, BG_TILE_RAM_SUB(BG0_TILE_BASE_SUB) + (fontTilesLen / 2), font_largeTilesLen);
	
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
	
	//m_fxManager.Initialize();
	
	((CFxParticles*)m_fxManager.GetFx(FXTYPE_PARTICLES))->AllocateGfx();
	((CFxFade*)m_fxManager.GetFx(FXTYPE_FADE))->SetBG(BG2_SUB | BG3_SUB | SPRITE_SUB, 0);

	m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
	m_fxManager.SetFx(FXTYPE_TEXT_SCROLLER, FXMODE_NORMAL, true);
	m_fxManager.SetFx(FXTYPE_COLOUR, FXMODE_NORMAL, true);
	m_fxManager.SetFx(FXTYPE_C64, FXMODE_NORMAL, true);
}

void CGame::InitIntro1()
{
	m_introIndex = 0;
	m_frameCount = 0;
	
	m_gameMode = GAMEMODE_INTRO;
	
	InitVideoIntro();
	
	dmaCopy(intro_headsoftPal, BG_PALETTE_SUB, intro_headsoftPalLen);
	dmaCopy(intro_headsoftPal, BG_PALETTE, intro_headsoftPalLen);
	
	BG_PALETTE[0] = 0;
	BG_PALETTE_SUB[0] = 0;
	
	m_fxManager.Initialize();
	
	((CFxFade*)m_fxManager.GetFx(FXTYPE_FADE))->SetBG(BG0 | BG0_SUB, BG1 | BG1_SUB);
	
	m_fxManager.SetFx(FXTYPE_FADE, FXMODE_BLACK_OUT, true);
	
	dmaCopy(intro_headsoftTiles, BG_TILE_RAM_SUB(INTRO_BG0_TILE_BASE_SUB), intro_headsoftTilesLen);
	dmaCopy(intro_headsoftMap, BG_MAP_RAM_SUB(INTRO_BG0_MAP_BASE_SUB), intro_headsoftMapLen);
	
	dmaCopy(intro_proteusTiles, BG_TILE_RAM(INTRO_BG0_TILE_BASE), intro_proteusTilesLen);
	dmaCopy(intro_proteusMap, BG_MAP_RAM(INTRO_BG0_MAP_BASE), intro_proteusMapLen);
	
	dmaCopy(intro_infectuousTiles, BG_TILE_RAM_SUB(INTRO_BG1_TILE_BASE_SUB), intro_infectuousTilesLen);
	dmaCopy(intro_infectuousMap, BG_MAP_RAM_SUB(INTRO_BG1_MAP_BASE_SUB), intro_infectuousMapLen);
	
	dmaCopy(intro_spacefractalTiles, BG_TILE_RAM(INTRO_BG1_TILE_BASE), intro_spacefractalTilesLen);
	dmaCopy(intro_spacefractalMap, BG_MAP_RAM(INTRO_BG1_MAP_BASE), intro_spacefractalMapLen);
}

void CGame::InitIntro2(int param)
{
	dmaCopy(intro_infectuousTiles, BG_TILE_RAM_SUB(INTRO_BG0_TILE_BASE_SUB), intro_infectuousTilesLen);
	dmaCopy(intro_infectuousMap, BG_MAP_RAM_SUB(INTRO_BG0_MAP_BASE_SUB), intro_infectuousMapLen);

	dmaCopy(intro_spacefractalTiles, BG_TILE_RAM(INTRO_BG0_TILE_BASE), intro_spacefractalTilesLen);
	dmaCopy(intro_spacefractalMap, BG_MAP_RAM(INTRO_BG0_MAP_BASE), intro_spacefractalMapLen);

	dmaCopy(intro_retrobytesTiles, BG_TILE_RAM_SUB(INTRO_BG1_TILE_BASE_SUB), intro_retrobytesTilesLen);
	dmaCopy(intro_retrobytesMap, BG_MAP_RAM_SUB(INTRO_BG1_MAP_BASE_SUB), intro_retrobytesMapLen);

	dmaCopy(intro_retrogamerTiles, BG_TILE_RAM(INTRO_BG1_TILE_BASE), intro_retrogamerTilesLen);
	dmaCopy(intro_retrogamerMap, BG_MAP_RAM(INTRO_BG1_MAP_BASE), intro_retrogamerMapLen);
}

void CGame::InitIntro3(int param)
{
	dmaCopy(intro_retrobytesTiles, BG_TILE_RAM_SUB(INTRO_BG0_TILE_BASE_SUB), intro_retrobytesTilesLen);
	dmaCopy(intro_retrobytesMap, BG_MAP_RAM_SUB(INTRO_BG0_MAP_BASE_SUB), intro_retrobytesMapLen);
	
	dmaCopy(intro_retrogamerTiles, BG_TILE_RAM(INTRO_BG0_TILE_BASE), intro_retrogamerTilesLen);
	dmaCopy(intro_retrogamerMap, BG_MAP_RAM(INTRO_BG0_MAP_BASE), intro_retrogamerMapLen);
}

void CGame::UpdateIntro()
{
	if(m_frameCount++ == 100)
	{
		m_frameCount = 0;
		
		switch(m_introIndex)
		{
		case 0:
			m_fxManager.SetFx(FXTYPE_FADE, FXMODE_ALPHA_IN, true);
			((CFxFade*)m_fxManager.GetFx(FXTYPE_FADE))->SetCallback(new CCallback<CGame, void, int>(this, &CGame::InitIntro2));
			break;
		case 1:
			m_fxManager.SetFx(FXTYPE_FADE, FXMODE_ALPHA_IN, true);
			((CFxFade*)m_fxManager.GetFx(FXTYPE_FADE))->SetCallback(new CCallback<CGame, void, int>(this, &CGame::InitIntro3));
			break;
		case 2:	
			m_fxManager.SetFx(FXTYPE_FADE, FXMODE_BLACK_IN, true);
			((CFxFade*)m_fxManager.GetFx(FXTYPE_FADE))->SetCallback(new CCallback<CGame, void, int>(this, &CGame::InitData));
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
	m_endingMode = ENDINGMODE_NONE;
	m_footsteps = 0;
	m_clock = 0;
	m_fireplace = 0;
	//m_waterdrip = 0;
	m_frameCount = 0;
	m_eventFlags = 0;	
	
	m_questionCharacter = NULL;
	m_speakCharacter = NULL;
	
	SoundOff();
	FxOff();
	
	m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
	
	videoBgEnableSub(0);
	
	ClearBG(0, false);
	ClearBG(1, false);
	
	ClearBG(0, true);
	
	DrawString("@2009 HEADSOFT", 9, 1, false);
	
	((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->SetLoop(false);
	((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->ClearText();
	
	dmaFillHalfWords(0, BG_TILE_RAM_SUB(BG0_TILE_BASE_SUB), 8 * 8 * 2);
	
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
			
		m_roomArray[ROOM_DINGLE]->SetColMap(col_room1);

		m_roomArray[ROOM_CLOCK]->SetColMap(col_clock);
		
		m_roomArray[ROOM_GABRIEL]->SetColMap(col_room2);
		
		m_roomArray[ROOM_STAIRS]->SetColMap(col_stairs);
		m_roomArray[ROOM_STAIRS]->SetOverlay(NULL);
		
		m_roomArray[ROOM_ANGUS_ROOM]->SetMap(g_angus_room1Map);
		m_roomArray[ROOM_ANGUS_ROOM]->SetColMap(col_angus_room1);
		
		m_roomArray[ROOM_LANDING]->SetOverlay(g_landing_front1Map);
		
		m_roomArray[ROOM_GRAVEYARD]->SetOverlay(g_graveyard_frontMap, 176);
		m_roomArray[ROOM_ANGUS_SECRET]->SetOverlay(g_angus_secret_frontMap, 168);
		m_roomArray[ROOM_ANGUS_ROOM]->SetOverlay(g_angus_room_frontMap, 176);
		m_roomArray[ROOM_DINING]->SetOverlay(g_dining_frontMap, 168);
		
		// -------------------------------------
		
		m_roomArray[ROOM_SNIDE]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_SNIDE]->AddItems(1, m_itemArray[ITEM_PADDED_ENVELOPES], m_itemArray[ITEM_A_HOT_WATER_BOTTLE], NULL, NULL, NULL);
		
		m_roomArray[ROOM_REVEREND]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_REVEREND]->AddItems(1, m_itemArray[ITEM_A_BOTTLE_OF_PILLS], NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_BENTLEY]->AddItems(0, m_itemArray[ITEM_A_COMB], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_BENTLEY]->AddItems(1, m_itemArray[ITEM_A_JACKET], NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_COOK]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_COOK]->AddItems(1, NULL, NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_GABRIEL]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_GABRIEL]->AddItems(1, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_GABRIEL]->AddItems(2, m_itemArray[ITEM_A_LOCKET], m_itemArray[ITEM_A_SYRINGE], NULL, NULL, NULL);

		m_roomArray[ROOM_CYNTHIA]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_CYNTHIA]->AddItems(1,m_itemArray[ITEM_A_MIRROR], NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_PROFESSOR]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_PROFESSOR]->AddItems(1, m_itemArray[ITEM_NOTEBOOKS], m_itemArray[ITEM_A_SMALL_BOOK], NULL, NULL, NULL);
		
		m_roomArray[ROOM_DOCTOR]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_DOCTOR]->AddItems(1, m_itemArray[ITEM_COLOGNE], m_itemArray[ITEM_A_BLACK_BAG], NULL, NULL, NULL);
		
		m_roomArray[ROOM_MAJOR]->AddItems(0, m_itemArray[ITEM_AN_ELEPHANT_GUN], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_MAJOR]->AddItems(1, m_itemArray[ITEM_BLANK_BULLETS], NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_DINGLE]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_DINGLE]->AddItems(1, m_itemArray[ITEM_A_BRIEFCASE], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_DINGLE]->AddItems(2, m_itemArray[ITEM_A_SMALL_KEY], m_itemArray[ITEM_A_CRAVATE], NULL, NULL, NULL);
		
		m_roomArray[ROOM_OUTSIDE1]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_OUTSIDE3]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_KITCHEN]->AddItems(0, m_itemArray[ITEM_A_HAMMER], m_itemArray[ITEM_A_CANDLESTICK], NULL, NULL, NULL);
		m_roomArray[ROOM_KITCHEN]->AddItems(1, m_itemArray[ITEM_A_BOTTLE_OF_WINE], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_KITCHEN]->AddItems(2, m_itemArray[ITEM_A_SILVER_TRAY], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_KITCHEN]->AddItems(3, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_KITCHEN]->AddItems(4, m_itemArray[ITEM_CUTLERY], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_KITCHEN]->AddItems(5, m_itemArray[ITEM_DIRTY_PLATES], NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_STUDY]->AddItems(0, m_itemArray[ITEM_BULLETS], m_itemArray[ITEM_A_PAPERWEIGHT], m_itemArray[ITEM_A_LETTER_OPENER], m_itemArray[ITEM_A_DIARY], NULL);
		m_roomArray[ROOM_STUDY]->AddItems(1, m_itemArray[ITEM_A_FOLDER], NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_CLOCK]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_CELLAR]->AddItems(0, m_itemArray[ITEM_A_SCREWDRIVER], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_CELLAR]->AddItems(1, m_itemArray[ITEM_A_PIECE_OF_CARD], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_CELLAR]->AddItems(2, NULL, NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_DRAWING]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_DRAWING]->AddItems(1, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_DRAWING]->AddItems(2, m_itemArray[ITEM_A_PICTURE], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_DRAWING]->AddItems(3, m_itemArray[ITEM_THE_WILL], NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_LIBRARY]->AddItems(0, m_itemArray[ITEM_BOOKS1], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_LIBRARY]->AddItems(1, m_itemArray[ITEM_BOOKS2], NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_LAUNDRY]->AddItems(0, m_itemArray[ITEM_A_DIRTY_SHIRT], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_LAUNDRY]->AddItems(1, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_LAUNDRY]->AddItems(2, m_itemArray[ITEM_WASHING_POWDER], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_LAUNDRY]->AddItems(3, m_itemArray[ITEM_A_VACUUM_CLEANER], NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_GARDEN]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_GRAVEYARD]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_GRAVEYARD]->AddItems(1, NULL, NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_COURTYARD]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_COURTYARD]->AddItems(1, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_COURTYARD]->AddItems(2, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_COURTYARD]->AddItems(3, NULL, NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_ANGUS_LANDING]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_ANGUS_LANDING]->AddItems(1, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_ANGUS_LANDING]->AddItems(2, NULL, NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_ANGUS_ROOM]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_ANGUS_ROOM]->AddItems(1, m_itemArray[ITEM_A_SWORD], m_itemArray[ITEM_A_BALL_ON_CHAIN], NULL, NULL, NULL);
		m_roomArray[ROOM_ANGUS_ROOM]->AddItems(2, NULL, NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_ANGUS_ROOM]->AddItems(3, NULL, NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_ANGUS_SECRET]->AddItems(0, m_itemArray[ITEM_AN_HOURGLASS], NULL, NULL, NULL, NULL);
		m_roomArray[ROOM_ANGUS_SECRET]->AddItems(1, m_itemArray[ITEM_A_GOLDEN_SKULL], NULL, NULL, NULL, NULL);
		
		m_roomArray[ROOM_DINING]->AddItems(0, NULL, NULL, NULL, NULL, NULL);
		
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
	
	for(int i=0; i<MAX_EVENTS; i++)
		if(m_eventArray[i] != NULL)
			m_eventArray[i]->SetDone(false);
	
	m_questionMark->Disable();
	m_questionMark->Hide();
	
	// ------------------------
	
	//InitMurder(MURDERTYPE_GABRIEL);
	
	// ------------------------
	
	m_currentRoom = m_roomArray[ROOM_STAIRS];
	//m_currentRoom = m_roomArray[ROOM_DINGLE];
	//m_currentRoom = m_roomArray[ROOM_GABRIEL];
	//m_currentRoom = m_roomArray[ROOM_CLOCK];
	
	m_snide = m_characterArray[CHARTYPE_SNIDE];
	
	m_snide->AddItems(NULL, NULL, NULL, NULL, NULL);
	m_snide->SetRoom(m_currentRoom);
	m_snide->SetPosition(208, 104);
	//m_snide->SetPosition(150, 104);
	m_snide->SetGoalMode(false);
	m_snide->SetCharacterMode(CHARMODE_WAITING);
	
	m_characterArray[CHARTYPE_ANGUS]->SetAlpha(0x7);
	
	m_timer->Start(9, 10, 0, 0);
		
	// ------------------------
	//m_roomArray[ROOM_ANGUS_ROOM]->SetMap(g_angus_room2Map);
	//m_roomArray[ROOM_ANGUS_ROOM]->SetColMap(col_angus_room2);
	// ------------------------
	
	//m_menu->DrawItem(ITEM_ANGUS_MCFUNGUS, 24, 18, false);
	
	PlaySong(SONGTYPE_INGAME);
	
	m_currentRoom->Initialize(m_snide->X() - 128);
	
	m_console->Clear();
	m_console->AddText(g_enterRoomText[m_currentRoom->GetRoomType()]);
	
	//m_roomArray[ROOM_STUDY]->RemoveItem(0, m_itemArray[ITEM_BULLETS]);
	//m_roomArray[ROOM_STUDY]->AddItem(0, m_itemArray[ITEM_BLANK_BULLETS], true);
	
	//m_snide->AddItems(m_itemArray[ITEM_AN_ELEPHANT_GUN], m_itemArray[ITEM_BULLETS], m_itemArray[ITEM_A_BUNCH_OF_KEYS], m_itemArray[ITEM_A_RED_KEY], m_itemArray[ITEM_A_VACUUM_CLEANER]);
	//m_snide->AddItems(m_itemArray[ITEM_A_RED_KEY], m_itemArray[ITEM_ANGUS_MCFUNGUS], m_itemArray[ITEM_A_BUNCH_OF_KEYS], NULL, NULL);
	//m_snide->AddItems(m_itemArray[ITEM_A_RED_KEY], m_itemArray[ITEM_A_BUNCH_OF_KEYS], m_itemArray[ITEM_A_VACUUM_CLEANER], NULL, NULL);
	
	/* m_snide->AddItems(m_itemArray[ITEM_PADDED_ENVELOPES], NULL, NULL, NULL, NULL);
	m_itemArray[ITEM_PADDED_ENVELOPES]->AddItem(m_itemArray[ITEM_THE_WILL]);
	m_itemArray[ITEM_PADDED_ENVELOPES]->AddItem(m_itemArray[ITEM_A_KNIFE]);
	m_itemArray[ITEM_PADDED_ENVELOPES]->AddItem(m_itemArray[ITEM_A_NOTE]);
	m_itemArray[ITEM_PADDED_ENVELOPES]->AddItem(m_itemArray[ITEM_A_SMALL_BOTTLE]);
	m_itemArray[ITEM_PADDED_ENVELOPES]->AddItem(m_itemArray[ITEM_A_CRAVATE]);
	m_itemArray[ITEM_PADDED_ENVELOPES]->AddItem(m_itemArray[ITEM_A_SYRINGE]);
	m_itemArray[ITEM_PADDED_ENVELOPES]->AddItem(m_itemArray[ITEM_A_FOLDED_DOCUMENT]);
	m_itemArray[ITEM_PADDED_ENVELOPES]->AddItem(m_itemArray[ITEM_A_WAD_OF_NOTES]);
	m_itemArray[ITEM_PADDED_ENVELOPES]->AddItem(m_itemArray[ITEM_AN_OPEN_LOCKET]);
	m_itemArray[ITEM_PADDED_ENVELOPES]->AddItem(m_itemArray[ITEM_A_BOMB]); */
}

void CGame::UpdateGame(touchPosition touch, int keys_held, int keys_pressed, int keys_released)
{
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
	
	UpdateEventFlags();
	UpdateEvents();
}

void CGame::PauseGame()
{
	static char buffer[64];
	
	m_gameMode = GAMEMODE_PAUSED;
	
	dmaCopy(pausedTiles, BG_TILE_RAM_SUB(BG0_TILE_BASE_SUB), pausedTilesLen);
	dmaCopy(pausedMap, BG_MAP_RAM_SUB(BG0_MAP_BASE_SUB), pausedMapLen);
	
	sprintf(buffer, " THE TIME IS NOW:\n\n      %02d: %02d\n\nPAUSED..", m_timer->pCurrentTime()->Hours, m_timer->pCurrentTime()->Minutes);
	m_console->AddText(buffer);
				
	m_timer->Stop();
	m_pointer->Hide();
	m_menu->Hide();
	
	mmPause();
	SoundOff();
}

void CGame::UpdateEvents()
{
	if(m_eventFlags & EVENTFLAG_LOCK_DINGLES_ROOM)
	{
		m_eventFlags &= ~EVENTFLAG_LOCK_DINGLES_ROOM;
		
		CDoor* pDoor = m_roomArray[ROOM_DINGLE]->GetDoor(DOOR_DOOR1);
	
		if(pDoor->GetDoorState() != DOORSTATE_LOCKED)
		{
			pDoor->SetDoorState(DOORSTATE_LOCKED);
			
			if(m_currentRoom == m_roomArray[ROOM_DINGLE] || m_currentRoom == m_roomArray[ROOM_HALL1])
				m_currentRoom->Draw();
		}
	}
	
	for(int i=0; i<MAX_EVENTS; i++)
	{
		if(m_eventArray[i] != NULL)
		{
			if(!m_eventArray[i]->GetDone())
			{
				if(m_eventArray[i]->Update(m_timer->pCurrentTime()))
				{		
					if((m_eventArray[i]->Condition() & m_eventFlags) == m_eventArray[i]->Condition())
					{
						m_eventArray[i]->SetDone(true);
						m_eventFlags |= m_eventArray[i]->Action();
						
						switch(m_eventArray[i]->GetEventType())
						{
						case EVENT_START_GAME:
							break;
						case EVENT_MURDER_DINGLE:
							{
								CDoor* pDoor = m_roomArray[ROOM_DINGLE]->GetDoor(DOOR_DOOR1);
							
								pDoor->SetDoorState(DOORSTATE_CLOSED);
								
								if(m_currentRoom == m_roomArray[ROOM_DINGLE] || m_currentRoom == m_roomArray[ROOM_HALL1])
									m_currentRoom->Draw();
							
								InitMurder(MURDERTYPE_DINGLE);
							}
							break;
						case EVENT_EVIDENCE_COUNT_6:
						case EVENT_MURDER_CYNTHIA:
							m_eventArray[EVENT_EVIDENCE_COUNT_6]->SetDone(true);
							m_eventArray[EVENT_MURDER_CYNTHIA]->SetDone(true);
							
							InitMurder(MURDERTYPE_CYNTHIA);
							break;
						case EVENT_EVIDENCE_COUNT_7:
						case EVENT_MURDER_DOCTOR:
							m_eventArray[EVENT_EVIDENCE_COUNT_7]->SetDone(true);
							m_eventArray[EVENT_MURDER_DOCTOR]->SetDone(true);
							
							InitMurder(MURDERTYPE_DOCTOR);
							break;
						case EVENT_EVIDENCE_COUNT_8:
						case EVENT_MURDER_GABRIEL:
							m_eventArray[EVENT_EVIDENCE_COUNT_8]->SetDone(true);
							m_eventArray[EVENT_MURDER_GABRIEL]->SetDone(true);
							
							InitMurder(MURDERTYPE_GABRIEL);
							break;
						case EVENT_LOCK_DINGLES_ROOM:
							{
								CDoor* pDoor = m_roomArray[ROOM_DINGLE]->GetDoor(DOOR_DOOR1);
							
								if(pDoor->GetDoorState() != DOORSTATE_LOCKED)
								{
									pDoor->SetDoorState(DOORSTATE_LOCKED);
									
									if(m_currentRoom == m_roomArray[ROOM_DINGLE] || m_currentRoom == m_roomArray[ROOM_HALL1])
										m_currentRoom->Draw();
								}
							}
							break;
						case EVENT_REMOVE_BULLETS:
							{
								CItemCache* pItemCache = m_roomArray[ROOM_STUDY]->GetItemCache(0);
								
								if(pItemCache->ContainsItem(m_itemArray[ITEM_BULLETS]))
									pItemCache->RemoveItem(m_itemArray[ITEM_BULLETS]);
							}
							break;
						case EVENT_GET_SHOT:
							InitEnding(ENDINGMODE_SHOT);
							break;
						}
					}
				}
			}
		}
	}
}

void CGame::UpdateEventFlags()
{
	m_eventFlags &= ~(EVENTFLAG_HALL1 | EVENTFLAG_HALL3);
	
	switch(m_currentRoom->GetRoomType())
	{
		case ROOM_HALL1:
			m_eventFlags |= EVENTFLAG_HALL1;
			break;
		case ROOM_HALL3:
			m_eventFlags |= EVENTFLAG_HALL3;
			break;
		default:
			break;
	}
	
	int evidenceCount = GetEvidenceCount();
	
	m_eventFlags |= (evidenceCount == 6 ? EVENTFLAG_EVIDENCE_COUNT_6 : 0);
	m_eventFlags |= (evidenceCount == 7 ? EVENTFLAG_EVIDENCE_COUNT_7 : 0);
	m_eventFlags |= (evidenceCount == 8 ? EVENTFLAG_EVIDENCE_COUNT_8 : 0);
}

void CGame::InitGameOver(GameOverMode gameOverMode)
{
	m_gameMode = GAMEMODE_GAMEOVER;
	m_gameOverMode = gameOverMode;
	
	m_frameCount = 500;
	
	videoBgDisableSub(0);
	
	SoundOff();
	FxOff();
	
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
		
		//DrawTime(m_timer->pCurrentTime());
		m_console->Update();
		m_cursor->Update();
		m_cursor->Show();
		break;
	case GAMEOVERMODE_NOTHING:
		break;
	}
	
	if(--m_frameCount == 0)
	{
		switch(m_gameOverMode)
		{
		case GAMEOVERMODE_WIN:
			m_gameOverMode = GAMEOVERMODE_NOTHING;
			m_frameCount = 500;		

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
			m_frameCount = 500;
			
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
			m_frameCount = 500;
			
			InitTitleScreen();
			break;
		case GAMEOVERMODE_NOTHING:
			m_frameCount = 500;
			
			InitTitleScreen();
			break;
		}
	}
}

void CGame::InitEnding(EndingMode endingMode)
{
	m_gameMode = GAMEMODE_ENDING;
	
	m_endingMode = endingMode;
	m_frameCount = 300;
	
	ClearBG(0, true);
	
	SoundOff();
	FxOff();
	
	m_pointer->Hide();
	m_menu->Hide();
	m_console->HideMenu();
	
	m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, false);
	
	REG_BLDCNT_SUB = BLEND_FADE_BLACK | BLEND_ALPHA | BLEND_SRC_BG2 | BLEND_SRC_BG3 | BLEND_SRC_SPRITE | BLEND_DST_BG2 | BLEND_DST_BG3;
	REG_BLDCNT_SUB &= ~BLEND_FADE_WHITE;
	REG_BLDCNT_SUB |= BLEND_FADE_BLACK;
	REG_BLDY_SUB = 17;
	
	((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("THE LIGHTS GO OUT..");
	
	m_console->Clear();
	
	m_currentRoom = m_roomArray[ROOM_SEWERS];
	m_currentRoom->Initialize(0);
	
	PlaySong(SONGTYPE_TENSION);
}

void CGame::UpdateEnding(touchPosition touch, int keys_held, int keys_pressed, int keys_released)
{
	switch(m_endingMode)
	{
	case ENDINGMODE_NONE:
	case ENDINGMODE_SHOT:
	case ENDINGMODE_LEDATGUNPOINT:
	case ENDINGMODE_DINGLESPEAKS:
	case ENDINGMODE_PULLTRIGGER:
	case ENDINGMODE_ESCAPE:
	case ENDINGMODE_ESCAPED:
	case ENDINGMODE_ARREST:
	case ENDINGMODE_GAMEOVER_WIN:
	case ENDINGMODE_GAMEOVER_LOSE:
	case ENDINGMODE_GAMEOVER_END:
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
		break;
	case ENDINGMODE_ESCAPING:
		{
			Point p;
			
			UpdateGame(touch, keys_held, keys_pressed, keys_released);
			
			p.X = 288;
			p.Y = 144;
								
			if(m_characterArray[CHARTYPE_DINGLE]->MoveTo(&p))
			{
				m_endingMode = ENDINGMODE_ESCAPED;
				m_frameCount = 1;
				
				m_characterArray[CHARTYPE_DINGLE]->SetRoom(NULL);
			}
		}
		break;
	}
	
	if(--m_frameCount == 0)
	{
		switch(m_endingMode)
		{
		case ENDINGMODE_NONE:
		case ENDINGMODE_SHOT:
			m_endingMode = ENDINGMODE_GAMEOVER_LOSE;
			m_frameCount = 500;
			
			((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("YOU ARE SHOT BY AN UNSEEN ASSASSIN..");
			
			mmEffectEx(&g_sfx_gunshot);
			break;
		case ENDINGMODE_LEDATGUNPOINT:
			m_endingMode = ENDINGMODE_DINGLESPEAKS;
			m_frameCount = 500;
			
			((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("YOU ARE LED AT GUNPOINT THROUGH A DARK TUNNEL");
			break;
		case ENDINGMODE_DINGLESPEAKS:
			{
				m_endingMode = ENDINGMODE_PULLTRIGGER;
				m_frameCount = 1200;
				
				m_characterArray[CHARTYPE_DINGLE]->Reset();
				m_characterArray[CHARTYPE_DINGLE]->SetHFlip(true);
				m_characterArray[CHARTYPE_DINGLE]->SetRoom(m_roomArray[ROOM_SEWERS]);
				m_characterArray[CHARTYPE_DINGLE]->SetPosition(96, m_characterArray[CHARTYPE_DINGLE]->CentreY());
				m_characterArray[CHARTYPE_DINGLE]->SetCharacterMode(CHARMODE_TALKING);
				
				m_snide->Reset();
				m_snide->SetRoom(m_roomArray[ROOM_SEWERS]);
				m_snide->SetPosition(136, m_snide->CentreY());
				m_snide->SetCharacterMode(CHARMODE_QUESTION);
				
				((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("DINGLE SPEAKS \"VERY CLEVER, SNIDE.. I PAID THE DOCTOR TO CERTIFY ME DEAD, AND THEN TOOK CARE OF HIM... NOW I JUST HAVE TO TAKE CARE OF YOU!\"");
				
				m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
				
				m_console->Clear();
				m_console->AddText(g_enterRoomText[m_currentRoom->GetRoomType()]);
				
				InitRoom();
			}
			break;
		case ENDINGMODE_PULLTRIGGER:
			{
				m_endingMode = ENDINGMODE_ESCAPE;
				m_frameCount = 500;
				
				m_characterArray[CHARTYPE_DINGLE]->SetCharacterMode(CHARMODE_ATTACK);
				
				CItemCache* pItemCache = m_roomArray[ROOM_STUDY]->GetItemCache(0);
				
				if(pItemCache->ContainsItem(m_itemArray[ITEM_BLANK_BULLETS]) && !pItemCache->ContainsItem(m_itemArray[ITEM_BULLETS]))
				{
					((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("HE PULLS THE TRIGGER, BUT NOTHING HAPPENS..");
				}
				else
				{
					mmEffectEx(&g_sfx_gunshot);
					
					m_snide->SetCharacterMode(CHARMODE_DEAD);
					
					m_endingMode = ENDINGMODE_GAMEOVER_END;
				}
			}
			break;
		case ENDINGMODE_ESCAPE:
			{
				m_endingMode = ENDINGMODE_ESCAPING;
				m_frameCount = 1000;			
			}
			break;
		case ENDINGMODE_ESCAPING:
			break;
		case ENDINGMODE_ESCAPED:
			m_endingMode = ENDINGMODE_GAMEOVER_END;
			m_frameCount = 500;
			
			mmEffectCancel(m_footsteps);
			m_footsteps = 0;
			
			m_snide->SetCharacterMode(CHARMODE_NONE);
			
			((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("DINGLE HAS ESCAPED.. NEVER TO BE SEEN AGAIN..");
			break;
		case ENDINGMODE_ARREST:
			m_endingMode = ENDINGMODE_GAMEOVER_WIN;
			m_frameCount = 1000;
			
			mmEffectCancel(m_footsteps);
			m_footsteps = 0;
			
			m_snide->SetCharacterMode(CHARMODE_NONE);
			
			m_characterArray[CHARTYPE_DINGLE]->SetCharacterMode(CHARMODE_SURRENDER);
			
			((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("DON'T SHOOT! I'LL COME QUIETLY..");
			((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("WELL DONE, INSPECTOR.... YOU'RE A CREDIT TO THE FORCE, TAKE A PROMOTION!");
			break;
		case ENDINGMODE_GAMEOVER_WIN:
			InitGameOver(GAMEOVERMODE_WIN);
			break;
		case ENDINGMODE_GAMEOVER_LOSE:
			InitGameOver(GAMEOVERMODE_LOSE);
			break;
		case ENDINGMODE_GAMEOVER_END:
			InitGameOver(GAMEOVERMODE_END);
			break;
		}
	}
}

void CGame::InitTitleScreen()
{
	m_gameMode = GAMEMODE_TITLESCREEN;
	
	m_characterIndex = -1;
	m_frameCount = 0;
	
	FxOff();
	
	m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
	
	videoBgDisableSub(0);
	
	lcdMainOnBottom();
	
	ClearBG(0, false);
	ClearBG(1, false);
	
	ClearBG(0, true);
	
	dmaFillHalfWords(0, BG_TILE_RAM_SUB(BG0_TILE_BASE_SUB), 8 * 8 * 2);
	
	HideCharacters();
	
	oamClear(&oamMain, 0, 0);
	oamClear(&oamSub, 0, 0);
	
	DrawString("@2009 HEADSOFT", 9, 1, false);
	
	((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->ClearText();
	((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->SetLoop(true);
	((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("THE DETECTIVE GAME  -  WRITTEN BY HEADKAZE....GRAPHICS BY LOBO....MUSIC BY SPACE FRACTAL....SUPPORT BY FLASH....TESTING BY SASHANAN AND SVERX....ORIGINAL BY SAM MANTHORPE....CHARACTERS BY PAUL JAY....PLOT CUNNINGLY DEVISED BY THE MAGNIFICENT SEVEN....   PRESS START TO BEGIN INVESTIGATION                               ");
	
	m_console->AddText("\n\n    INTRODUCING\n     THE CAST..");

	dmaCopy(menu_topTiles, BG_TILE_RAM_SUB(BG1_TILE_BASE_SUB), menu_topTilesLen);
	dmaCopy(menu_topMap, BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB), menu_topMapLen);
	dmaCopy(menu_topPal, BG_PALETTE_SUB, menu_topPalLen);
	
	dmaCopy(menu_questionsTiles, BG_TILE_RAM(BG2_TILE_BASE), menu_questionsTilesLen);
	dmaCopy(menu_questionsMap, BG_MAP_RAM(BG2_MAP_BASE), menu_questionsMapLen);
	
	dmaCopy(menu_bottomTiles, BG_TILE_RAM(BG3_TILE_BASE), menu_bottomTilesLen);
	dmaCopy(menu_bottomMap, BG_MAP_RAM(BG3_MAP_BASE), menu_bottomMapLen);
	dmaCopy(menu_bottomPal, BG_PALETTE, menu_bottomPalLen);
	
	BG_PALETTE[0] = 0;
	BG_PALETTE_SUB[0] = 0;
	
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
	
	m_questionMark->Reset();
	m_questionMark->SetSub(false);
	m_questionMark->SetPriority(0);
	m_questionMark->SetPosition(192, 128);
	m_questionMark->SetCharacterMode(CHARMODE_QUESTION);
	m_questionMark->SetLoop(false);
	
	PlaySong(SONGTYPE_TITLESCREEN);
}

void CGame::UpdateTitleScreen()
{
	m_frameCount++;
	
	BACKGROUND.scroll[2].y = --m_bg2MainVScroll;
	
	if(m_characterIndex != -1)
	{
		if(m_frameCount == 160)
		{
			m_questionMark->Disable();
			m_questionMark->Hide();
			
			m_characterArray[m_characterIndex]->Show();
		}
		
		if(m_frameCount == 600)
		{
			m_characterArray[m_characterIndex]->Disable();
			m_characterArray[m_characterIndex]->Hide();

			m_questionMark->Disable();
			m_questionMark->Hide();
			
			m_console->Clear();
		}
	}
	
	if(m_frameCount > 700)
	{
		m_frameCount = 0;
		
		if(++m_characterIndex == MAX_CHARACTERS-1)
			m_characterIndex = 0;
		
		m_questionMark->ResetAnimation();
		m_questionMark->Show();
		
		m_console->AddText(g_characterText[m_characterIndex]);
	}
	
	if(m_characterIndex != -1)
	{
		m_characterArray[m_characterIndex]->Update(NULL, 0);
		m_characterArray[m_characterIndex]->Draw();
	}
	
	if(m_frameCount > 80)
		m_questionMark->Update(NULL, 0);
	
	m_questionMark->Draw();
	
	//DrawTime(m_timer->pCurrentTime());
	m_console->Update();
	m_cursor->Update();
	m_cursor->Show();
}

void CGame::SoundOff()
{
	mmEffectCancel(m_footsteps);
	mmEffectCancel(m_clock);
	mmEffectCancel(m_fireplace);
	//mmEffectCancel(m_waterdrip);
	
	mmEffectCancelAll();
	
	m_footsteps = 0;
	m_clock = 0;
	m_fireplace = 0;
	//m_waterdrip = 0;
	
	mmSetJingleVolume(0);
}

void CGame::FxOff()
{
	m_fxManager.SetFx(FXTYPE_PARTICLES, FXMODE_RAIN, false);
	m_fxManager.SetFx(FXTYPE_RAT, FXMODE_NORMAL, false);
	m_fxManager.SetFx(FXTYPE_LEAK, FXMODE_NORMAL, false);
}

void CGame::PlaySong(SongType songType)
{
	m_songType = songType;

	switch(m_songType)
	{
	case SONGTYPE_TITLESCREEN:
		mmStart(MOD_DETECTIVE, MM_PLAY_LOOP);
		mmPosition(0);
		break;
	case SONGTYPE_MURDER:
		mmStart(MOD_DETECTIVE, MM_PLAY_ONCE);
		mmPosition(1);
		break;
	case SONGTYPE_TENSION:
		mmStart(MOD_DETECTIVE, MM_PLAY_ONCE);
		mmPosition(2);
		break;
	case SONGTYPE_INGAME:
		mmStart(MOD_DETECTIVE, MM_PLAY_ONCE);
		mmPosition(3);
		break;
	}
}

void CGame::StopSong()
{
	mmStop();
}

int CGame::GetEvidenceCount()
{
	CItemCache* pItemCache = m_snide->GetItemCache();
	int evidenceCount = 0;
	
	for(int i=0; i<pItemCache->ItemCount(); i++)
	{
		CItem* pItem = pItemCache->GetItem(i);
		
		if(pItem != NULL)
		{
			if(pItem->GetItemAttribs() & ITEMATTRIB_EVIDENCE)
				evidenceCount++;
	
			CItemCache* pItemItemCache = pItem->GetItemCache();
			
			if(pItemItemCache != NULL)
			{
				for(int j=0; j<pItemItemCache->ItemCount(); j++)
				{
					CItem* pItemItem = pItemItemCache->GetItem(j);
					
					if(pItemItem->GetItemAttribs() & ITEMATTRIB_EVIDENCE)
						evidenceCount++;
				}
			}
		}
	}
	
	return evidenceCount;
}

void CGame::Save(const char* fileName)
{
	m_save->SetBufferPos(0);
	m_save->ClearBuffer();

	m_save->WriteString("TDG");
	m_timer->Save(m_save);
	
	for(int i=0; i<MAX_CHARACTERS; i++)
		if(m_characterArray[i] != NULL)
			m_characterArray[i]->Save(m_save);
	
	for(int i=0; i<MAX_SPRITES; i++)
		if(m_spriteArray[i] != NULL)
			m_spriteArray[i]->Save(m_save);
	
	for(int i=0; i<MAX_ROOMS; i++)
		if(m_roomArray[i] != NULL)
			m_roomArray[i]->Save(m_save);
		
	for(int i=0; i<MAX_ITEMS; i++)
		if(m_itemArray[i] != NULL)
			m_itemArray[i]->Save(m_save);
	
	for(int i=0; i<MAX_EVENTS; i++)
		if(m_eventArray[i] != NULL)
			m_eventArray[i]->Save(m_save);
	
	m_save->WriteByte(m_questionMode);
	m_save->WriteByte(m_questionType);
	
	m_save->WriteByte(m_useMode);
	m_save->WriteByte(m_useType);
	
	m_save->WriteByte(m_openMode);
	m_save->WriteByte(m_keyboardMode);
	m_save->WriteByte(m_gameOverMode);
	m_save->WriteByte(m_endingMode);
	m_save->WriteByte(m_displayMode);
	
	m_save->WriteByte(m_lastIconType);
	m_save->WriteByte(m_songType);
	
	m_save->WriteItem(m_useItem);
	m_save->WriteItem(m_withItem);
	m_save->WriteItem(m_placeItem);
	m_save->WriteItem(m_inItem);
	
	m_save->WriteCharacter(m_questionCharacter);
	m_save->WriteCharacter(m_speakCharacter);
	
	m_save->WriteBool(m_gargoyleActive[0]);
	m_save->WriteBool(m_gargoyleActive[1]);
	m_save->WriteBool(m_gargoyleActive[2]);
	
	m_save->WriteRoom(m_currentRoom);
	
	m_save->WriteUInt32(m_frameCount);
	
	m_save->WriteUInt32(m_introIndex);
	
	m_save->WriteUInt32(m_characterIndex);
		
	m_save->WriteUInt64(m_eventFlags);
	
	m_save->WriteBool(m_roomArray[ROOM_DINGLE]->GetColMap() == col_room1);
	m_save->WriteBool(m_roomArray[ROOM_CLOCK]->GetColMap() == col_clock);
	m_save->WriteBool(m_roomArray[ROOM_GABRIEL]->GetColMap() == col_room2);
	m_save->WriteBool(m_roomArray[ROOM_STAIRS]->GetColMap() == col_stairs);
	m_save->WriteBool(m_roomArray[ROOM_STAIRS]->GetOverlay() == NULL);
	m_save->WriteBool(m_roomArray[ROOM_LANDING]->GetOverlay() == g_landing_front1Map);
	m_save->WriteBool(m_roomArray[ROOM_ANGUS_ROOM]->GetMap() == g_angus_room1Map);
	m_save->WriteBool(m_roomArray[ROOM_ANGUS_ROOM]->GetColMap() == col_angus_room1);
	
	m_save->WriteBuffer(fileName);
	DC_FlushAll();
	
	//static char buf[256];
	//sprintf(buf, "Saved %d Bytes, %d KB", m_save->GetBufferPos(), m_save->GetBufferPos() / 1024);
	//fprintf(stderr, buf);
}

bool CGame::Load(const char* fileName)
{
	m_save->SetBufferPos(0);
	m_save->ClearBuffer();

	static char buf[256];

	if(m_save->ReadBuffer(fileName) != m_save->GetBufferSize())
		return false;
	
	DC_FlushAll();
	
	m_save->ReadString(buf);
	
	if(strcmp(buf, "TDG") != 0)
		return false;
	
	m_timer->Load(m_save);
	
	for(int i=0; i<MAX_CHARACTERS; i++)
		if(m_characterArray[i] != NULL)
			m_characterArray[i]->Load(m_save);
	
	for(int i=0; i<MAX_SPRITES; i++)
		if(m_spriteArray[i] != NULL)
			m_spriteArray[i]->Load(m_save);
	
	for(int i=0; i<MAX_ROOMS; i++)
		if(m_roomArray[i] != NULL)
			m_roomArray[i]->Load(m_save);
		
	for(int i=0; i<MAX_ITEMS; i++)
		if(m_itemArray[i] != NULL)
			m_itemArray[i]->Load(m_save);
	
	for(int i=0; i<MAX_EVENTS; i++)
		if(m_eventArray[i] != NULL)
			m_eventArray[i]->Load(m_save);
	
	m_save->ReadByte((byte*)&m_questionMode);
	m_save->ReadByte((byte*)&m_questionType);
	
	m_save->ReadByte((byte*)&m_useMode);
	m_save->ReadByte((byte*)&m_useType);
	
	m_save->ReadByte((byte*)&m_openMode);
	m_save->ReadByte((byte*)&m_keyboardMode);
	m_save->ReadByte((byte*)&m_gameOverMode);
	m_save->ReadByte((byte*)&m_endingMode);
	m_save->ReadByte((byte*)&m_displayMode);
	
	m_save->ReadByte((byte*)&m_lastIconType);
	m_save->ReadByte((byte*)&m_songType);
	
	m_save->ReadItem(&m_useItem);
	m_save->ReadItem(&m_withItem);
	m_save->ReadItem(&m_placeItem);
	m_save->ReadItem(&m_inItem);
	
	m_save->ReadCharacter(&m_questionCharacter);
	m_save->ReadCharacter(&m_speakCharacter);
	
	m_save->ReadBool(&m_gargoyleActive[0]);
	m_save->ReadBool(&m_gargoyleActive[1]);
	m_save->ReadBool(&m_gargoyleActive[2]);
	
	m_save->ReadRoom(&m_currentRoom);
	
	m_save->ReadUInt32((u32*)&m_frameCount);
	
	m_save->ReadUInt32((u32*)&m_introIndex);
	
	m_save->ReadUInt32((u32*)&m_characterIndex);
		
	m_save->ReadUInt64(&m_eventFlags);
	
	m_roomArray[ROOM_DINGLE]->SetColMap(m_save->ReadBool() ? col_room1 : col_dingle_murder);		
	m_roomArray[ROOM_CLOCK]->SetColMap(m_save->ReadBool() ? col_clock : col_clock_murder);
	m_roomArray[ROOM_GABRIEL]->SetColMap(m_save->ReadBool() ? col_room2 : col_gabriel_murder);
	m_roomArray[ROOM_STAIRS]->SetColMap(m_save->ReadBool() ? col_stairs : col_stairs_murder);
	m_roomArray[ROOM_STAIRS]->SetOverlay(m_save->ReadBool() ? NULL : g_stairs_frontMap, 168);
	m_roomArray[ROOM_LANDING]->SetOverlay(m_save->ReadBool() ? g_landing_front1Map : g_landing_front2Map);
	m_roomArray[ROOM_ANGUS_ROOM]->SetMap(m_save->ReadBool() ? g_angus_room1Map : g_angus_room2Map);
	m_roomArray[ROOM_ANGUS_ROOM]->SetColMap(m_save->ReadBool() ? col_angus_room1 : col_angus_room2);
		
	//m_currentRoom = m_snide->GetRoom();
	m_currentRoom->Initialize(m_snide->X() - 128);
	InitRoom();
	
	//sprintf(buf, "Loaded %d Bytes, %d KB", m_save->GetBufferPos(), m_save->GetBufferPos() / 1024);
	//fprintf(stderr, buf);
	
	return true;
}

