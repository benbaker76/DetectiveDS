#include <nds.h>
#include <stdio.h>
#include "TDG.h"
#include "CGame.h"
#include "Text.h"
#include "Gfx.h"

CGame::CGame(GameType gameType)
{
	m_gameType = gameType;
	m_gameMode = GAMEMODE_RUNNING;
	m_displayMode = DISPLAYMODE_GAME;
}

CGame::~CGame()
{
}

void CGame::Initialize()
{
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
		
	switch(m_gameType)
	{
	case GAMETYPE_NORMAL:
		m_spriteArray[SPRITE_SNIDE_HEAD] = new CSprite(SPRITE_SNIDE_HEAD, sprite_snide_headTiles, sprite_snide_headTilesLen, sprite_snide_headPal, sprite_snide_headPalLen, g_snideHeadFrames, 8);
		m_spriteArray[SPRITE_SNIDE_BODY] = new CSprite(SPRITE_SNIDE_BODY, sprite_snide_bodyTiles, sprite_snide_bodyTilesLen, sprite_snide_bodyPal, sprite_snide_bodyPalLen, g_snideBodyFrames, 17);
		m_spriteArray[SPRITE_REVEREND_HEAD] = new CSprite(SPRITE_REVEREND_HEAD, sprite_reverend_headTiles, sprite_reverend_headTilesLen, sprite_reverend_headPal, sprite_reverend_headPalLen, g_reverendHeadFrames, 4);
		m_spriteArray[SPRITE_REVEREND_BODY] = new CSprite(SPRITE_REVEREND_BODY, sprite_reverend_bodyTiles, sprite_reverend_bodyTilesLen, sprite_reverend_bodyPal, sprite_reverend_bodyPalLen, g_reverendBodyFrames, 6);
		m_spriteArray[SPRITE_BENTLEY_HEAD] = new CSprite(SPRITE_BENTLEY_HEAD, sprite_bentley_headTiles, sprite_bentley_headTilesLen, sprite_bentley_headPal, sprite_bentley_headPalLen, g_bentleyHeadFrames, 4);
		m_spriteArray[SPRITE_BENTLEY_BODY] = new CSprite(SPRITE_BENTLEY_BODY, sprite_bentley_bodyTiles, sprite_bentley_bodyTilesLen, sprite_bentley_bodyPal, sprite_bentley_bodyPalLen, g_bentleyBodyFrames, 6);
		m_spriteArray[SPRITE_COOK_HEAD] = new CSprite(SPRITE_COOK_HEAD, sprite_cook_headTiles, sprite_cook_headTilesLen, sprite_cook_headPal, sprite_cook_headPalLen, g_cookHeadFrames, 4);
		m_spriteArray[SPRITE_COOK_BODY] = new CSprite(SPRITE_COOK_BODY, sprite_cook_bodyTiles, sprite_cook_bodyTilesLen, sprite_cook_bodyPal, sprite_cook_bodyPalLen, g_cookBodyFrames, 6);
		m_spriteArray[SPRITE_GABRIEL_HEAD] = new CSprite(SPRITE_GABRIEL_HEAD, sprite_gabriel_headTiles, sprite_gabriel_headTilesLen, sprite_gabriel_headPal, sprite_gabriel_headPalLen, g_gabrielHeadFrames, 5);
		m_spriteArray[SPRITE_GABRIEL_BODY] = new CSprite(SPRITE_GABRIEL_BODY, sprite_gabriel_bodyTiles, sprite_gabriel_bodyTilesLen, sprite_gabriel_bodyPal, sprite_gabriel_bodyPalLen, g_gabrielBodyFrames, 7);
		m_spriteArray[SPRITE_CYNTHIA_HEAD] = new CSprite(SPRITE_CYNTHIA_HEAD, sprite_cynthia_headTiles, sprite_cynthia_headTilesLen, sprite_cynthia_headPal, sprite_cynthia_headPalLen, g_cynthiaHeadFrames, 4);
		m_spriteArray[SPRITE_CYNTHIA_BODY] = new CSprite(SPRITE_CYNTHIA_BODY, sprite_cynthia_bodyTiles, sprite_cynthia_bodyTilesLen, sprite_cynthia_bodyPal, sprite_cynthia_bodyPalLen, g_cynthiaBodyFrames, 6);
		m_spriteArray[SPRITE_PROFESSOR_HEAD] = new CSprite(SPRITE_PROFESSOR_HEAD, sprite_professor_headTiles, sprite_professor_headTilesLen, sprite_professor_headPal, sprite_professor_headPalLen, g_professorHeadFrames, 5);
		m_spriteArray[SPRITE_PROFESSOR_BODY] = new CSprite(SPRITE_PROFESSOR_BODY, sprite_professor_bodyTiles, sprite_professor_bodyTilesLen, sprite_professor_bodyPal, sprite_professor_bodyPalLen, g_professorBodyFrames, 7);
		m_spriteArray[SPRITE_DOCTOR_HEAD] = new CSprite(SPRITE_DOCTOR_HEAD, sprite_doctor_headTiles, sprite_doctor_headTilesLen, sprite_doctor_headPal, sprite_doctor_headPalLen, g_doctorHeadFrames, 5);
		m_spriteArray[SPRITE_DOCTOR_BODY] = new CSprite(SPRITE_DOCTOR_BODY, sprite_doctor_bodyTiles, sprite_doctor_bodyTilesLen, sprite_doctor_bodyPal, sprite_doctor_bodyPalLen, g_doctorBodyFrames, 7);
		m_spriteArray[SPRITE_MAJOR_HEAD] = new CSprite(SPRITE_MAJOR_HEAD, sprite_major_headTiles, sprite_major_headTilesLen, sprite_major_headPal, sprite_major_headPalLen, g_majorHeadFrames, 4);
		m_spriteArray[SPRITE_MAJOR_BODY] = new CSprite(SPRITE_MAJOR_BODY, sprite_major_bodyTiles, sprite_major_bodyTilesLen, sprite_major_bodyPal, sprite_major_bodyPalLen, g_majorBodyFrames, 6);		
		m_spriteArray[SPRITE_DINGLE_HEAD] = new CSprite(SPRITE_DINGLE_HEAD, sprite_dingle_headTiles, sprite_dingle_headTilesLen, sprite_dingle_headPal, sprite_dingle_headPalLen, g_dingleHeadFrames, 5);
		m_spriteArray[SPRITE_DINGLE_BODY] = new CSprite(SPRITE_DINGLE_BODY, sprite_dingle_bodyTiles, sprite_dingle_bodyTilesLen, sprite_dingle_bodyPal, sprite_dingle_bodyPalLen, g_dingleBodyFrames, 7);
		/* m_spriteArray[SPRITE_ANGUS_HEAD] = new CSprite(SPRITE_ANGUS_HEAD, sprite_angus_headTiles, sprite_angus_headTilesLen, sprite_angus_headPal, sprite_angus_headPalLen, g_angusHeadFrames, 5);
		m_spriteArray[SPRITE_ANGUS_BODY] = new CSprite(SPRITE_ANGUS_BODY, sprite_angus_bodyTiles, sprite_angus_bodyTilesLen, sprite_angus_bodyPal, sprite_angus_bodyPalLen, g_angusBodyFrames, 7); */
		
		/* m_spriteArray[SPRITE_SNIDE_HEAD] = new CSprite(SPRITE_SNIDE_HEAD, sprite_snide_headBitmap, g_snideHeadFrames, 16);
		m_spriteArray[SPRITE_SNIDE_BODY] = new CSprite(SPRITE_SNIDE_BODY, sprite_snide_bodyBitmap, g_snideBodyFrames, 18);
		m_spriteArray[SPRITE_REVEREND_HEAD] = new CSprite(SPRITE_REVEREND_HEAD, sprite_reverend_headBitmap, g_reverendHeadFrames, 4);
		m_spriteArray[SPRITE_REVEREND_BODY] = new CSprite(SPRITE_REVEREND_BODY, sprite_reverend_bodyBitmap, g_reverendBodyFrames, 6);
		m_spriteArray[SPRITE_BENTLEY_HEAD] = new CSprite(SPRITE_BENTLEY_HEAD, sprite_bentley_headBitmap, g_bentleyHeadFrames, 4);
		m_spriteArray[SPRITE_BENTLEY_BODY] = new CSprite(SPRITE_BENTLEY_BODY, sprite_bentley_bodyBitmap, g_bentleyBodyFrames, 6);
		m_spriteArray[SPRITE_COOK_HEAD] = new CSprite(SPRITE_COOK_HEAD, sprite_cook_headBitmap, g_cookHeadFrames, 4);
		m_spriteArray[SPRITE_COOK_BODY] = new CSprite(SPRITE_COOK_BODY, sprite_cook_bodyBitmap, g_cookBodyFrames, 6);
		m_spriteArray[SPRITE_GABRIEL_HEAD] = new CSprite(SPRITE_GABRIEL_HEAD, sprite_gabriel_headBitmap, g_gabrielHeadFrames, 5);
		m_spriteArray[SPRITE_GABRIEL_BODY] = new CSprite(SPRITE_GABRIEL_BODY, sprite_gabriel_bodyBitmap, g_gabrielBodyFrames, 7);
		m_spriteArray[SPRITE_CYNTHIA_HEAD] = new CSprite(SPRITE_CYNTHIA_HEAD, sprite_cynthia_headBitmap, g_cynthiaHeadFrames, 4);
		m_spriteArray[SPRITE_CYNTHIA_BODY] = new CSprite(SPRITE_CYNTHIA_BODY, sprite_cynthia_bodyBitmap, g_cynthiaBodyFrames, 6);
		m_spriteArray[SPRITE_PROFESSOR_HEAD] = new CSprite(SPRITE_PROFESSOR_HEAD, sprite_professor_headBitmap, g_professorHeadFrames, 5);
		m_spriteArray[SPRITE_PROFESSOR_BODY] = new CSprite(SPRITE_PROFESSOR_BODY, sprite_professor_bodyBitmap, g_professorBodyFrames, 7);
		m_spriteArray[SPRITE_DOCTOR_HEAD] = new CSprite(SPRITE_DOCTOR_HEAD, sprite_doctor_headBitmap, g_doctorHeadFrames, 5);
		m_spriteArray[SPRITE_DOCTOR_BODY] = new CSprite(SPRITE_DOCTOR_BODY, sprite_doctor_bodyBitmap, g_doctorBodyFrames, 7);
		m_spriteArray[SPRITE_MAJOR_HEAD] = new CSprite(SPRITE_MAJOR_HEAD, sprite_major_headBitmap, g_majorHeadFrames, 4);
		m_spriteArray[SPRITE_MAJOR_BODY] = new CSprite(SPRITE_MAJOR_BODY, sprite_major_bodyBitmap, g_majorBodyFrames, 6);		
		m_spriteArray[SPRITE_DINGLE_HEAD] = new CSprite(SPRITE_DINGLE_HEAD, sprite_dingle_headBitmap, g_dingleHeadFrames, 5);
		m_spriteArray[SPRITE_DINGLE_BODY] = new CSprite(SPRITE_DINGLE_BODY, sprite_dingle_bodyBitmap, g_dingleBodyFrames, 7); */
		m_spriteArray[SPRITE_ANGUS_HEAD] = new CSprite(SPRITE_ANGUS_HEAD, sprite_angus_headBitmap, g_angusHeadFrames, 5);
		m_spriteArray[SPRITE_ANGUS_BODY] = new CSprite(SPRITE_ANGUS_BODY, sprite_angus_bodyBitmap, g_angusBodyFrames, 7);
		
		m_characterArray[CHARTYPE_SNIDE] = new CCharacter(CHARTYPE_SNIDE, m_spriteArray[SPRITE_SNIDE_HEAD], m_spriteArray[SPRITE_SNIDE_BODY], 24, 53);
		m_characterArray[CHARTYPE_REVEREND] = new CCharacter(CHARTYPE_REVEREND, m_spriteArray[SPRITE_REVEREND_HEAD], m_spriteArray[SPRITE_REVEREND_BODY], 24, 53);
		m_characterArray[CHARTYPE_BENTLEY] = new CCharacter(CHARTYPE_BENTLEY, m_spriteArray[SPRITE_BENTLEY_HEAD], m_spriteArray[SPRITE_BENTLEY_BODY], 24, 53);
		m_characterArray[CHARTYPE_COOK] = new CCharacter(CHARTYPE_COOK, m_spriteArray[SPRITE_COOK_HEAD], m_spriteArray[SPRITE_COOK_BODY], 24, 44);
		m_characterArray[CHARTYPE_GABRIEL] = new CCharacter(CHARTYPE_GABRIEL, m_spriteArray[SPRITE_GABRIEL_HEAD], m_spriteArray[SPRITE_GABRIEL_BODY], 24, 48);
		m_characterArray[CHARTYPE_CYNTHIA] = new CCharacter(CHARTYPE_CYNTHIA, m_spriteArray[SPRITE_CYNTHIA_HEAD], m_spriteArray[SPRITE_CYNTHIA_BODY], 24, 49);
		m_characterArray[CHARTYPE_PROFESSOR] = new CCharacter(CHARTYPE_PROFESSOR, m_spriteArray[SPRITE_PROFESSOR_HEAD], m_spriteArray[SPRITE_PROFESSOR_BODY], 24, 48);
		m_characterArray[CHARTYPE_DOCTOR] = new CCharacter(CHARTYPE_DOCTOR, m_spriteArray[SPRITE_DOCTOR_HEAD], m_spriteArray[SPRITE_DOCTOR_BODY], 24, 49);
		m_characterArray[CHARTYPE_MAJOR] = new CCharacter(CHARTYPE_MAJOR, m_spriteArray[SPRITE_MAJOR_HEAD], m_spriteArray[SPRITE_MAJOR_BODY], 24, 46);
		m_characterArray[CHARTYPE_DINGLE] = new CCharacter(CHARTYPE_DINGLE, m_spriteArray[SPRITE_DINGLE_HEAD], m_spriteArray[SPRITE_DINGLE_BODY], 24, 48);
		m_characterArray[CHARTYPE_ANGUS] = new CCharacter(CHARTYPE_ANGUS, m_spriteArray[SPRITE_ANGUS_HEAD], m_spriteArray[SPRITE_ANGUS_BODY], 24, 48);
		
		m_roomArray[ROOM_SNIDE] = new CRoom(ROOM_SNIDE, &g_room1Map, NULL, col_room1, 144);
		m_roomArray[ROOM_REVEREND] = new CRoom(ROOM_REVEREND, &g_room1Map, NULL, col_room1, 144);
		m_roomArray[ROOM_BENTLEY] = new CRoom(ROOM_BENTLEY, &g_room2Map, NULL, col_room2, 168);
		m_roomArray[ROOM_COOK] = new CRoom(ROOM_COOK, &g_room2Map, NULL, col_room2, 168);
		m_roomArray[ROOM_GABRIEL] = new CRoom(ROOM_GABRIEL, &g_room2Map, NULL, col_room2, 168);
		m_roomArray[ROOM_CYNTHIA] = new CRoom(ROOM_CYNTHIA, &g_room1Map, NULL, col_room1, 144);
		m_roomArray[ROOM_PROFESSOR] = new CRoom(ROOM_PROFESSOR, &g_room1Map, NULL, col_room1, 144);
		m_roomArray[ROOM_DOCTOR] = new CRoom(ROOM_DOCTOR, &g_room1Map, NULL, col_room1, 144);		
		m_roomArray[ROOM_MAJOR] = new CRoom(ROOM_MAJOR, &g_room1Map, NULL, col_room1, 144);
		m_roomArray[ROOM_DINGLE] = new CRoom(ROOM_DINGLE, &g_room1Map, NULL, col_room1, 144);
		m_roomArray[ROOM_OUTSIDE1] = new CRoom(ROOM_OUTSIDE1, &g_outside1Map, NULL, col_outside1, 160);
		m_roomArray[ROOM_OUTSIDE2] = new CRoom(ROOM_OUTSIDE2, &g_outside2Map, &g_outside2_frontMap, col_outside2, 152);
		m_roomArray[ROOM_OUTSIDE3] = new CRoom(ROOM_OUTSIDE3, &g_outside1Map, NULL, col_outside1, 160);
		m_roomArray[ROOM_OUTSIDE4] = new CRoom(ROOM_OUTSIDE4, &g_outside2Map, &g_outside2_frontMap, col_outside2, 152);
		m_roomArray[ROOM_PASSAGE1] = new CRoom(ROOM_PASSAGE1, &g_passage1Map, NULL, col_passage1, 152);
		m_roomArray[ROOM_PASSAGE2] = new CRoom(ROOM_PASSAGE2, &g_passage2Map, NULL, col_passage2, 152);
		m_roomArray[ROOM_PASSAGE3] = new CRoom(ROOM_PASSAGE3, &g_passage1Map, NULL, col_passage1, 152);
		m_roomArray[ROOM_HALL1] = new CRoom(ROOM_HALL1, &g_hall1Map, NULL, col_hall1, 160);
		m_roomArray[ROOM_HALL2] = new CRoom(ROOM_HALL2, &g_hall2Map, NULL, col_hall2, 160);
		m_roomArray[ROOM_HALL3] = new CRoom(ROOM_HALL3, &g_hall3Map, NULL, col_hall3, 160);
		m_roomArray[ROOM_HALL4] = new CRoom(ROOM_HALL4, &g_hall4Map, NULL, col_hall4, 160);
		m_roomArray[ROOM_LANDING] = new CRoom(ROOM_LANDING, &g_landingMap, &g_landing_front1Map, col_landing, 144);
		m_roomArray[ROOM_KITCHEN] = new CRoom(ROOM_KITCHEN, &g_kitchenMap, NULL, col_kitchen, 160);
		m_roomArray[ROOM_STAIRS] = new CRoom(ROOM_STAIRS, &g_stairsMap, NULL, col_stairs, 168);
		m_roomArray[ROOM_STUDY] = new CRoom(ROOM_STUDY, &g_studyMap, NULL, col_study, 160);
		m_roomArray[ROOM_CLOCK] = new CRoom(ROOM_CLOCK, &g_clockMap, NULL, col_clock, 160);
		m_roomArray[ROOM_CELLAR] = new CRoom(ROOM_CELLAR, &g_cellarMap, NULL, col_cellar, 160);
		m_roomArray[ROOM_DRAWING] = new CRoom(ROOM_DRAWING, &g_drawingMap, NULL, col_drawing, 160);
		m_roomArray[ROOM_LIBRARY] = new CRoom(ROOM_LIBRARY, &g_libraryMap, NULL, col_library, 160);	
		m_roomArray[ROOM_UTILITY] = new CRoom(ROOM_UTILITY, &g_utilityMap, NULL, col_utility, 160);
		m_roomArray[ROOM_GARDEN] = new CRoom(ROOM_GARDEN, &g_gardenMap, &g_garden_frontMap, col_garden, 152);
		m_roomArray[ROOM_GRAVEYARD] = new CRoom(ROOM_GRAVEYARD, &g_graveyardMap, &g_graveyard_frontMap, col_graveyard, 160);
		m_roomArray[ROOM_COURTYARD] = new CRoom(ROOM_COURTYARD, &g_courtyardMap, &g_courtyard_frontMap, col_courtyard, 160);
		m_roomArray[ROOM_ANGUS_LANDING] = new CRoom(ROOM_ANGUS_LANDING, &g_angus_landingMap, &g_angus_landing_frontMap, col_angus_landing, 144);
		m_roomArray[ROOM_ANGUS_ROOM] = new CRoom(ROOM_ANGUS_ROOM, &g_angus_room2Map, &g_angus_room_frontMap, col_angus_room2, 160);
		m_roomArray[ROOM_ANGUS_SECRET] = new CRoom(ROOM_ANGUS_SECRET, &g_angus_secretMap, &g_angus_secret_frontMap, col_angus_secret, 160);
		m_roomArray[ROOM_ANGUS_STAIRS] = new CRoom(ROOM_ANGUS_STAIRS, &g_angus_stairsMap, NULL, col_angus_stairs, 168);
		
		//m_roomArray[ROOM_STAIRS]->SetOverlay(&g_stairs_frontMap, 168);
		m_roomArray[ROOM_GRAVEYARD]->SetOverlay(&g_graveyard_frontMap, 176);
		m_roomArray[ROOM_ANGUS_SECRET]->SetOverlay(&g_angus_secret_frontMap, 168);
		m_roomArray[ROOM_ANGUS_ROOM]->SetOverlay(&g_angus_room_frontMap, 176);
		
		//m_roomArray[ROOM_STAIRS]->SetColMap(col_stairs_front);
		
		m_roomArray[ROOM_SNIDE]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_SNIDE], m_roomArray[ROOM_HALL2]));		
		m_roomArray[ROOM_REVEREND]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_REVEREND], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_REVEREND]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_HIDDEN, m_roomArray[ROOM_REVEREND], m_roomArray[ROOM_PASSAGE1]));		
		m_roomArray[ROOM_BENTLEY]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_BENTLEY], m_roomArray[ROOM_HALL3]));		
		m_roomArray[ROOM_COOK]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_COOK], m_roomArray[ROOM_HALL4]));
		m_roomArray[ROOM_GABRIEL]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_GABRIEL], m_roomArray[ROOM_HALL4]));
		m_roomArray[ROOM_CYNTHIA]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_CYNTHIA], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_PROFESSOR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_PROFESSOR], m_roomArray[ROOM_HALL2]));
		m_roomArray[ROOM_DOCTOR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_DOCTOR], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_MAJOR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_MAJOR], m_roomArray[ROOM_HALL2]));
		m_roomArray[ROOM_MAJOR]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_HIDDEN, m_roomArray[ROOM_MAJOR], m_roomArray[ROOM_OUTSIDE2]));
		m_roomArray[ROOM_DINGLE]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_DINGLE], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_OUTSIDE1]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_OUTSIDE1], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_OUTSIDE2]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE2], m_roomArray[ROOM_PASSAGE1]));
		m_roomArray[ROOM_OUTSIDE2]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE2], m_roomArray[ROOM_MAJOR]));
		m_roomArray[ROOM_OUTSIDE3]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_OUTSIDE3], m_roomArray[ROOM_CLOCK]));
		m_roomArray[ROOM_OUTSIDE4]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE4], m_roomArray[ROOM_CELLAR]));
		m_roomArray[ROOM_OUTSIDE4]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE4], m_roomArray[ROOM_DRAWING]));
		m_roomArray[ROOM_OUTSIDE4]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE4], m_roomArray[ROOM_GARDEN]));
		m_roomArray[ROOM_PASSAGE1]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE1], m_roomArray[ROOM_REVEREND]));
		m_roomArray[ROOM_PASSAGE1]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE1], m_roomArray[ROOM_OUTSIDE2]));
		m_roomArray[ROOM_PASSAGE2]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE2], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_PASSAGE2]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE2], m_roomArray[ROOM_HALL2]));
		m_roomArray[ROOM_PASSAGE3]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE3], m_roomArray[ROOM_KITCHEN]));
		m_roomArray[ROOM_PASSAGE3]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE3], m_roomArray[ROOM_CELLAR]));
		m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_REVEREND]));
		m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_CYNTHIA]));
		m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_DOCTOR]));
		m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR4, new CDoor(DOOR_DOOR4, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_DINGLE]));
		m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR5, new CDoor(DOOR_DOOR5, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_OUTSIDE1]));
		m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR6, new CDoor(DOOR_DOOR6, DOORSTATE_OPEN, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_LANDING]));
		m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR7, new CDoor(DOOR_DOOR7, DOORSTATE_OPEN, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_PASSAGE2]));
		m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_PROFESSOR]));
		m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_MAJOR]));
		m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPEN, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_PASSAGE2]));
		m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR4, new CDoor(DOOR_DOOR4, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_SNIDE]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_KITCHEN]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_STAIRS]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_LOCKED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_STUDY]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR4, new CDoor(DOOR_DOOR4, DOORSTATE_LOCKED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_BENTLEY]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR5, new CDoor(DOOR_DOOR5, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_DRAWING]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR6, new CDoor(DOOR_DOOR6, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_LIBRARY]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR7, new CDoor(DOOR_DOOR7, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_UTILITY]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR8, new CDoor(DOOR_DOOR8, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_HALL4]));
		m_roomArray[ROOM_HALL4]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_HALL3]));
		m_roomArray[ROOM_HALL4]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_COOK]));
		m_roomArray[ROOM_HALL4]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_CLOSED, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_GABRIEL]));
		m_roomArray[ROOM_LANDING]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_LANDING], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_LANDING]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_LANDING], m_roomArray[ROOM_STAIRS]));
		m_roomArray[ROOM_KITCHEN]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_HIDDEN, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_PASSAGE3]));
		m_roomArray[ROOM_KITCHEN]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_HALL3]));
		m_roomArray[ROOM_STAIRS]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_LANDING]));
		m_roomArray[ROOM_STAIRS]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_HALL3]));
		m_roomArray[ROOM_STAIRS]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPEN, m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_COURTYARD]));
		m_roomArray[ROOM_STAIRS]->SetDoor(DOOR_DOOR4, new CDoor(DOOR_DOOR4, DOORSTATE_LOCKED, m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_ANGUS_STAIRS]));
		m_roomArray[ROOM_STUDY]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_STUDY], m_roomArray[ROOM_HALL3]));
		m_roomArray[ROOM_CLOCK]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_CLOCK], m_roomArray[ROOM_OUTSIDE3]));
		m_roomArray[ROOM_CLOCK]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_CLOCK], m_roomArray[ROOM_DRAWING]));
		m_roomArray[ROOM_CELLAR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_CELLAR], m_roomArray[ROOM_PASSAGE3]));
		m_roomArray[ROOM_CELLAR]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_CELLAR], m_roomArray[ROOM_OUTSIDE4]));
		m_roomArray[ROOM_DRAWING]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_CLOCK]));
		m_roomArray[ROOM_DRAWING]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_CLOSED, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_HALL3]));
		m_roomArray[ROOM_DRAWING]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_HIDDEN, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_OUTSIDE4]));
		m_roomArray[ROOM_LIBRARY]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_LIBRARY], m_roomArray[ROOM_HALL3]));	
		m_roomArray[ROOM_UTILITY]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_CLOSED, m_roomArray[ROOM_UTILITY], m_roomArray[ROOM_HALL3]));
		m_roomArray[ROOM_GARDEN]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_GARDEN], m_roomArray[ROOM_GRAVEYARD]));
		m_roomArray[ROOM_GARDEN]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_GARDEN], m_roomArray[ROOM_OUTSIDE4]));
		m_roomArray[ROOM_GRAVEYARD]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_GRAVEYARD], m_roomArray[ROOM_GARDEN]));
		m_roomArray[ROOM_COURTYARD]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_COURTYARD], m_roomArray[ROOM_STAIRS]));
		m_roomArray[ROOM_ANGUS_LANDING]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_ANGUS_LANDING], m_roomArray[ROOM_ANGUS_ROOM]));
		m_roomArray[ROOM_ANGUS_LANDING]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_ANGUS_LANDING], m_roomArray[ROOM_ANGUS_STAIRS]));
		m_roomArray[ROOM_ANGUS_ROOM]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_ANGUS_ROOM], m_roomArray[ROOM_ANGUS_LANDING]));
		m_roomArray[ROOM_ANGUS_ROOM]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_ANGUS_ROOM], m_roomArray[ROOM_ANGUS_SECRET]));
		m_roomArray[ROOM_ANGUS_SECRET]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_ANGUS_SECRET], m_roomArray[ROOM_ANGUS_ROOM]));
		m_roomArray[ROOM_ANGUS_STAIRS]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_LOCKED, m_roomArray[ROOM_ANGUS_STAIRS], m_roomArray[ROOM_STAIRS]));
		m_roomArray[ROOM_ANGUS_STAIRS]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_ANGUS_STAIRS], m_roomArray[ROOM_ANGUS_LANDING]));
		
		m_itemArray[ITEM_NOTHING_HERE] = new CItem(ITEM_NOTHING_HERE, false);
		m_itemArray[ITEM_A_HOT_WATER_BOTTLE] = new CItem(ITEM_A_HOT_WATER_BOTTLE, false);
		m_itemArray[ITEM_BLANK_BULLETS] = new CItem(ITEM_BLANK_BULLETS, false);
		m_itemArray[ITEM_A_CANDLESTICK] = new CItem(ITEM_A_CANDLESTICK, false);
		m_itemArray[ITEM_THE_WILL] = new CItem(ITEM_THE_WILL, true); // Clue #1
		m_itemArray[ITEM_A_KNIFE] = new CItem(ITEM_A_KNIFE, true); // Clue #8
		m_itemArray[ITEM_NEWSPAPER_CUTTING] = new CItem(ITEM_NEWSPAPER_CUTTING, false);
		m_itemArray[ITEM_A_NOTE] = new CItem(ITEM_A_NOTE, true); // Clue #4
		m_itemArray[ITEM_A_SMALL_BOTTLE] = new CItem(ITEM_A_SMALL_BOTTLE, true); // Clue #6
		m_itemArray[ITEM_A_CRAVATE] = new CItem(ITEM_A_CRAVATE, true); // Clue #3
		m_itemArray[ITEM_A_SOGGY_ENVELOPE] = new CItem(ITEM_A_SOGGY_ENVELOPE, false);
		m_itemArray[ITEM_A_LETTER] = new CItem(ITEM_A_LETTER, false);
		m_itemArray[ITEM_SCALPELS] = new CItem(ITEM_SCALPELS, false);
		m_itemArray[ITEM_A_SYRINGE] = new CItem(ITEM_A_SYRINGE, true); // Clue #9
		m_itemArray[ITEM_A_BOTTLE_OF_PILLS] = new CItem(ITEM_A_BOTTLE_OF_PILLS, false);
		m_itemArray[ITEM_A_HAMMER] = new CItem(ITEM_A_HAMMER, false);
		m_itemArray[ITEM_A_BUNCH_OF_KEYS] = new CItem(ITEM_A_BUNCH_OF_KEYS, false);
		m_itemArray[ITEM_A_BIG_IRON_KEY] = new CItem(ITEM_A_BIG_IRON_KEY, false);
		m_itemArray[ITEM_A_SILVER_TRAY] = new CItem(ITEM_A_SILVER_TRAY, false);
		m_itemArray[ITEM_A_BOTTLE_OF_WINE] = new CItem(ITEM_A_BOTTLE_OF_WINE, false);
		m_itemArray[ITEM_A_COMB] = new CItem(ITEM_A_COMB, false);
		m_itemArray[ITEM_A_HARDBACK_BOOK] = new CItem(ITEM_A_HARDBACK_BOOK, false);
		m_itemArray[ITEM_A_FOLDED_DOCUMENT] = new CItem(ITEM_A_FOLDED_DOCUMENT, true); // Clue #2
		m_itemArray[ITEM_AN_ELEPHANT_GUN] = new CItem(ITEM_AN_ELEPHANT_GUN, false);
		m_itemArray[ITEM_A_DIARY] = new CItem(ITEM_A_DIARY, false);
		m_itemArray[ITEM_A_BLACK_BAG] = new CItem(ITEM_A_BLACK_BAG, false);
		m_itemArray[ITEM_COLOGNE] = new CItem(ITEM_COLOGNE, false);
		m_itemArray[ITEM_A_SMALL_BOOK] = new CItem(ITEM_A_SMALL_BOOK, false);
		m_itemArray[ITEM_DIRTY_PLATES] = new CItem(ITEM_DIRTY_PLATES, false);
		m_itemArray[ITEM_A_PICTURE] = new CItem(ITEM_A_PICTURE, false);
		m_itemArray[ITEM_A_WAD_OF_NOTES] = new CItem(ITEM_A_WAD_OF_NOTES, true); // Clue #5
		m_itemArray[ITEM_A_LOCKET] = new CItem(ITEM_A_LOCKET, false);
		m_itemArray[ITEM_A_SCREWDRIVER] = new CItem(ITEM_A_SCREWDRIVER, false);
		m_itemArray[ITEM_AN_OPEN_LOCKET] = new CItem(ITEM_AN_OPEN_LOCKET, true); // Clue #10
		m_itemArray[ITEM_BROKEN_PLATES] = new CItem(ITEM_BROKEN_PLATES, false);
		m_itemArray[ITEM_BROKEN_GLASS] = new CItem(ITEM_BROKEN_GLASS, false);
		m_itemArray[ITEM_SHREDDED_PAPER] = new CItem(ITEM_SHREDDED_PAPER, false);
		m_itemArray[ITEM_BOOKS1] = new CItem(ITEM_BOOKS1, false);
		m_itemArray[ITEM_BOOKS2] = new CItem(ITEM_BOOKS2, false);
		m_itemArray[ITEM_A_LETTER_OPENER] = new CItem(ITEM_A_LETTER_OPENER, false);
		m_itemArray[ITEM_A_JACKET] = new CItem(ITEM_A_JACKET, false);
		m_itemArray[ITEM_NOTEBOOKS] = new CItem(ITEM_NOTEBOOKS, false);
		m_itemArray[ITEM_PLANS] = new CItem(ITEM_PLANS, false);
		m_itemArray[ITEM_A_MIRROR] = new CItem(ITEM_A_MIRROR, false);
		m_itemArray[ITEM_CUTLERY] = new CItem(ITEM_CUTLERY, false);
		m_itemArray[ITEM_A_PIECE_OF_CARD] = new CItem(ITEM_A_PIECE_OF_CARD, false);
		m_itemArray[ITEM_A_BRIEFCASE] = new CItem(ITEM_A_BRIEFCASE, false);
		m_itemArray[ITEM_A_FOLDER] = new CItem(ITEM_A_FOLDER, false);
		m_itemArray[ITEM_A_PAPERWEIGHT] = new CItem(ITEM_A_PAPERWEIGHT, false);
		m_itemArray[ITEM_PADDED_ENVELOPES] = new CItem(ITEM_PADDED_ENVELOPES, false);
		m_itemArray[ITEM_A_BOMB] = new CItem(ITEM_A_BOMB, true); // Clue #7
		m_itemArray[ITEM_A_SMALL_KEY] = new CItem(ITEM_A_SMALL_KEY, false);
		m_itemArray[ITEM_BULLETS] = new CItem(ITEM_BULLETS, false);
		
		m_eventArray[EVENT_SHOW_ROOM] = new CEvent(EVENT_SHOW_ROOM, new CTime(9, 10, 0, 0));
		m_eventArray[EVENT_GET_SHOT] = new CEvent(EVENT_SHOW_ROOM, new CTime(12, 0, 0, 0));
		break;
	}
	
	InitializeDoors();
	
	m_currentRoom = m_roomArray[ROOM_STAIRS];
	m_currentRoom->Initialize(69);
	
	m_snide = m_characterArray[CHARTYPE_SNIDE];
	m_snide->SetRoom(m_currentRoom);
	m_snide->SetPosition(208, 104);
	
	m_characterArray[CHARTYPE_REVEREND]->SetPosition(168, 168 - m_characterArray[CHARTYPE_REVEREND]->Height());
	m_characterArray[CHARTYPE_REVEREND]->SetRoom(m_roomArray[ROOM_DRAWING]);
	m_characterArray[CHARTYPE_REVEREND]->SetCharacterMode(CHARMODE_TALKING);
	
	m_characterArray[CHARTYPE_BENTLEY]->SetPosition(176, 168 - m_characterArray[CHARTYPE_BENTLEY]->Height());
	m_characterArray[CHARTYPE_BENTLEY]->SetRoom(m_roomArray[ROOM_STAIRS]);
	//m_characterArray[CHARTYPE_BENTLEY]->SetCharacterMode(CHARMODE_TALKING);
	m_characterArray[CHARTYPE_BENTLEY]->SetCharacterMode(CHARMODE_WALKING);
	
	m_characterArray[CHARTYPE_COOK]->SetPosition(104, 168 - m_characterArray[CHARTYPE_COOK]->Height());
	m_characterArray[CHARTYPE_COOK]->SetRoom(m_roomArray[ROOM_KITCHEN]);
	m_characterArray[CHARTYPE_COOK]->SetCharacterMode(CHARMODE_TALKING);
	
	m_characterArray[CHARTYPE_GABRIEL]->SetPosition(208, 168 - m_characterArray[CHARTYPE_GABRIEL]->Height());
	m_characterArray[CHARTYPE_GABRIEL]->SetRoom(m_roomArray[ROOM_KITCHEN]);
	m_characterArray[CHARTYPE_GABRIEL]->SetCharacterMode(CHARMODE_TALKING);

	m_characterArray[CHARTYPE_CYNTHIA]->SetPosition(232, 168 - m_characterArray[CHARTYPE_CYNTHIA]->Height());
	m_characterArray[CHARTYPE_CYNTHIA]->SetRoom(m_roomArray[ROOM_CYNTHIA]);
	m_characterArray[CHARTYPE_CYNTHIA]->SetCharacterMode(CHARMODE_TALKING);
	
	m_characterArray[CHARTYPE_PROFESSOR]->SetPosition(136, 168 - m_characterArray[CHARTYPE_PROFESSOR]->Height());
	m_characterArray[CHARTYPE_PROFESSOR]->SetRoom(m_roomArray[ROOM_LIBRARY]);
	m_characterArray[CHARTYPE_PROFESSOR]->SetCharacterMode(CHARMODE_TALKING);
	
	m_characterArray[CHARTYPE_DOCTOR]->SetPosition(176, 168 - m_characterArray[CHARTYPE_DOCTOR]->Height());
	m_characterArray[CHARTYPE_DOCTOR]->SetRoom(m_roomArray[ROOM_OUTSIDE3]);
	m_characterArray[CHARTYPE_DOCTOR]->SetCharacterMode(CHARMODE_TALKING);
	
	m_characterArray[CHARTYPE_MAJOR]->SetPosition(232, 168 - m_characterArray[CHARTYPE_MAJOR]->Height());
	m_characterArray[CHARTYPE_MAJOR]->SetRoom(m_roomArray[ROOM_MAJOR]);
	m_characterArray[CHARTYPE_MAJOR]->SetCharacterMode(CHARMODE_TALKING);
	
	m_characterArray[CHARTYPE_DINGLE]->SetPosition(240, 168 - m_characterArray[CHARTYPE_DINGLE]->Height());
	m_characterArray[CHARTYPE_DINGLE]->SetRoom(m_roomArray[ROOM_DRAWING]);
	m_characterArray[CHARTYPE_DINGLE]->SetCharacterMode(CHARMODE_TALKING);
	
	m_characterArray[CHARTYPE_ANGUS]->SetPosition(232, 168 - m_characterArray[CHARTYPE_ANGUS]->Height());
	m_characterArray[CHARTYPE_ANGUS]->SetRoom(m_roomArray[ROOM_ANGUS_ROOM]);
	m_characterArray[CHARTYPE_ANGUS]->SetAlpha(0x7);
	m_characterArray[CHARTYPE_ANGUS]->SetCharacterMode(CHARMODE_TALKING);
	
	m_cursor = new CCursor();
	m_pointer = new CPointer();
	
	m_console = new CConsole(m_cursor);
	m_console->AddText(g_enterRoomText[m_currentRoom->GetRoomType()]);
		
	/* for(int i=1; i<MAX_CHARACTERS; i++)
	{
		m_characterArray[i]->SetPosition(i * m_characterArray[i]->Width(), 168 - m_characterArray[i]->Height());
		m_characterArray[i]->SetCharacterMode(CHARMODE_TALKING);
		m_characterArray[i]->SetRoom(m_roomArray[ROOM_STAIRS]);
		m_characterArray[i]->Show();
	} */
	
	ClearBG(1, true);
	
	dmaCopy(watchTiles, BG_TILE_RAM_SUB(BG1_TILE_BASE_SUB), watchTilesLen);
	dmaCopy(watchMap, BG_MAP_RAM_SUB(BG1_MAP_BASE_SUB), watchMapLen);
		
	m_fxManager.Initialize();
	m_fxManager.SetFx(FXTYPE_FADE_RAMP, FXMODE_BLACK_OUT, true);
	m_fxManager.SetFx(FXTYPE_TEXT_SCROLLER, FXMODE_NORMAL, true);
	m_fxManager.SetFx(FXTYPE_COLOUR, FXMODE_NORMAL, true);
	
	//m_keyboard = new CKeyboard(&m_cursor);
	//m_keyboard->Initialize();
	
	CPath* path = new CPath(m_roomArray);
	path->FindRoute(m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_SNIDE]);
	
	for(int i=1; i<MAX_ROOMS; i++)
	{
		if(path->GetRoom(i) != NULL)
		{
			//fprintf(stderr, g_roomName[path->GetRoom(i)->GetRoomType()]);
			m_characterArray[CHARTYPE_BENTLEY]->SetPath(i - 1, path->GetRoom(i));
		}
	}
	
	((CFxTextScroller*)m_fxManager.GetFx(FXTYPE_TEXT_SCROLLER))->AddText("BENTLY ADVANCES:\"THIS WAY TO YOUR ROOM SIR\"");

	m_menu = new CMenu();
	m_menu->DrawMenu();
	
	m_watch = new CWatch(113, 21);
	m_timer = new CTimer(9, 10, 0, 0);
	m_timer->Start();
}

void CGame::Update()
{
	static mm_sfxhand footsteps = 0;
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
	
	//DrawTime(m_timer->pCurrentTime());
	m_watch->Draw(m_timer->pCurrentTime());
	m_console->Update();
	m_cursor->Update();
	m_cursor->Draw();
	
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
	
	BACKGROUND.scroll[2].y = --m_bg2MainVScroll;
	
	if(keys_released & KEY_L || keys_released & KEY_R)
	{
		lcdSwap();
	}
	
	if(m_gameMode == GAMEMODE_PAUSED)
	{
		if(keys_released & KEY_A)
		{
			m_gameMode = GAMEMODE_RUNNING;
			m_console->ClearText();
			m_timer->Start();
		}
		
		return;
	}
	
	if(m_displayMode == DISPLAYMODE_GAME)
	{
		if((keys_released & KEY_UP) ||
			(keys_released & KEY_DOWN) ||
			(keys_released & KEY_LEFT) ||
			(keys_released & KEY_RIGHT))
		{
			mmEffectCancel(footsteps);
			footsteps = 0;
		}
		
		if(((keys_held & KEY_UP) ||
			(keys_held & KEY_DOWN) ||
			(keys_held & KEY_LEFT) ||
			(keys_held & KEY_RIGHT)) &&
			(footsteps == 0))
		{
			footsteps = mmEffectEx(&g_sfx_footsteps);
		}
	
		if(keys_pressed & KEY_TOUCH)
		{		
			ProcessMenu(touch.px, touch.py);
		}
	
		UpdateSnideMovement(keys_held);
		
		if(keys_released & KEY_A)
		{
			m_displayMode = DISPLAYMODE_MENU;
			m_snide->SetCharacterMode(CHARMODE_NONE);
			m_pointer->SetRect(MENU_X, MENU_Y, MENU_WIDTH, MENU_HEIGHT);
			//m_pointer->SetRect(CONSOLE_MENU_X, CONSOLE_MENU_Y, CONSOLE_MENU_WIDTH, CONSOLE_MENU_HEIGHT);
		}
	}
	else if(m_displayMode == DISPLAYMODE_MENU)
	{
		if(keys_released & KEY_A)
		{
			m_displayMode = DISPLAYMODE_GAME;

			PPOINT pPoint = m_pointer->pPoint();
			ProcessMenu(pPoint->X, pPoint->Y);
			m_pointer->Hide();
			m_menu->HideBox();
		}
		else
		{
			PPOINT pPoint = m_pointer->pPoint();
			m_pointer->Move(keys_held);
			m_pointer->Draw();
			m_menu->DrawBox(pPoint->X, pPoint->Y);
		}
	}
	else if(m_displayMode == DISPLAYMODE_CONSOLE)
	{
		if(keys_released & KEY_A)
		{
			PostProcessMenu();
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
	}
	else if(m_displayMode == DISPLAYMODE_KEYBOARD)
	{
		m_keyboard->CheckKeyTouch(touch.px, touch.py);
	}
	
	m_currentRoom->Animate(m_timer->pCurrentTime());
	
	SortSprites();
	UpdateCharacters(elapsedTime);
	
	//char buf[256];
	//sprintf(buf, " X: %04d", m_characterArray[CHARTYPE_BENTLEY]->AbsX());
	//DrawText(buf, 0, 1, false);
	
	UpdateFx();
	
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
}

void CGame::UpdateSnideMovement(int keys_held)
{
	CollisionType colNear, colFar;
	CDoor* pDoor = NULL;
	
	if(keys_held & KEY_UP)
	{
		if(m_snide->SpriteX() < 256 - m_snide->Width() - 8)
		{
			m_snide->CheckCollision(DIRECTION_UP, &colNear, &colFar);
			
			SetMenuIcons(colNear, colFar);
			
			if(colNear == COL_NOTHING_HERE)
				m_snide->Move(DIRECTION_UP);
			else
				m_snide->Face(DIRECTION_UP);
			
			if(TryGetDoor(colNear, colNear, &pDoor))
			{
				if(pDoor->GetDoorState() == DOORSTATE_OPEN)
				{		
					m_currentRoom = pDoor->pRoomOut();
					PPOINT pDoorPoint = pDoor->pDoorOut()->pPoint();
					
					int xDoor = pDoorPoint->X * 8;
					int yDoor = pDoorPoint->Y * 8;
					
					int xRoom = xDoor - 128;
					
					int xChar = xDoor;
					int yChar = yDoor - m_snide->Height();
						
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
					//DrawText(buf, 0, 1, false);
				}
			}
		}
	}
	else if(keys_held & KEY_DOWN)
	{
		if(m_snide->SpriteX() > 8)
		{
			m_snide->CheckCollision(DIRECTION_DOWN, &colNear, &colFar);
			
			SetMenuIcons(colNear, colFar);
			
			if(colNear == COL_NOTHING_HERE)
				m_snide->Move(DIRECTION_DOWN);
			else
				m_snide->Face(DIRECTION_DOWN);
			
			if(TryGetDoor(colNear, colNear, &pDoor))
			{
				if(pDoor->GetDoorState() == DOORSTATE_OPEN)
				{
					m_currentRoom = pDoor->pRoomOut();
					PPOINT pDoorPoint = pDoor->pDoorOut()->pPoint();
						
					int xDoor = pDoorPoint->X * 8;
					int yDoor = pDoorPoint->Y * 8;
					
					int xRoom = xDoor - 128;
					
					int xChar = xDoor;
					int yChar = yDoor - m_snide->Height() + 16;
					
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
					//DrawText(buf, 0, 1, false);
				}
			}
		}
	}
	else if(keys_held & KEY_LEFT)
	{
		m_snide->CheckCollision(DIRECTION_LEFT, &colNear, &colFar);
		
		SetMenuIcons(colNear, colFar);
		
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
		m_snide->CheckCollision(DIRECTION_RIGHT, &colNear, &colFar);
		
		SetMenuIcons(colNear, colFar);
		
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
		m_snide->SetCharacterMode(CHARMODE_NONE);
}

void CGame::SetMenuIcons(CollisionType colNear, CollisionType colFar)
{
	CDoor* pDoor = NULL;
	
	if(colNear == COL_NOTHING_HERE && colFar == COL_NOTHING_HERE)
		m_menu->AddIconSet(ICONSET_GENERAL);
	else
	{
		if(TryGetDoor(colNear, colFar, &pDoor))
		{
			if(!pDoor->Hidden())
			{
				if(pDoor->GetDoorState() == DOORSTATE_OPEN)
					m_menu->AddIconSet(ICONSET_DOOR_CLOSE);
				else
					m_menu->AddIconSet(ICONSET_DOOR_OPEN);
			}
		}
	}
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

void CGame::ProcessMenu(int x, int y)
{
	static char buf[512];
	CollisionType colNear, colFar;
	IconType iconType = m_menu->CheckIconHit(x, y);
	m_lastIconType = iconType;
	CDoor* pDoor = NULL;
	
	//DrawText("                                ", 0, 0, false);
	//DrawText(g_iconName[(int) iconType], 0, 0, false);
	switch(iconType)
	{
	case ICON_DOOR_OPEN:
	case ICON_DOOR_CLOSE:
		m_snide->CheckCollision(m_snide->Facing(), &colNear, &colFar);
		
		if(TryGetDoor(colNear, colFar, &pDoor))
		{
			if(pDoor->GetDoorState() == DOORSTATE_CLOSED || pDoor->GetDoorState() == DOORSTATE_LOCKED)
			{
				pDoor->SetDoorState(DOORSTATE_OPEN);
				m_currentRoom->Draw();
				mmEffectEx(&g_sfx_opendoor);
				SetMenuIcons(colNear, colFar);
			}
			else if(pDoor->GetDoorState() == DOORSTATE_OPEN)
			{
				pDoor->SetDoorState(DOORSTATE_CLOSED);
				m_currentRoom->Draw();
				mmEffectEx(&g_sfx_closedoor);
				SetMenuIcons(colNear, colFar);
			}
		}
		break;
	case ICON_EXAMINE:
		m_snide->CheckCollision(m_snide->Facing(), &colNear, &colFar);
		
		if(TryGetDoor(colNear, colFar, &pDoor))
		{			
			if(pDoor->GetDoorState() == DOORSTATE_HIDDEN)
			{
				pDoor->SetDoorState(DOORSTATE_OPEN);
				m_currentRoom->Draw();
				mmEffectEx(&g_sfx_opendoor);
				
				m_console->AddText("YOU FIND:\nA SECRET PASSAGE!");
			}
		}
		else
			m_console->AddText(g_colName[colNear]);
		break;
	case ICON_TIME:
		sprintf(buf, " THE TIME IS NOW:\n\n      %02d: %02d\n\n PAUSED..PRESS\nA TO CONTINUE.", m_timer->pCurrentTime()->Hours, m_timer->pCurrentTime()->Minutes);
		m_console->AddText(buf);
		m_gameMode = GAMEMODE_PAUSED;
		m_timer->Stop();
		break;
	case ICON_INVENTORY:
		m_displayMode = DISPLAYMODE_CONSOLE;
		
		if(false)
		{
			m_console->AddText("YOU ARE CARRYING:");
			m_console->CreateMenu(NULL, 0);
			m_console->DrawSelectorBar();
		}
		else
		{
			m_displayMode = DISPLAYMODE_GAME;
			m_console->AddText("YOU ARE CARRYING:\n\nNOTHING...");
		}
		break;
	case ICON_USE:
		m_displayMode = DISPLAYMODE_CONSOLE;
		
		if(false)
		{
			m_console->AddText("USE:");
			m_console->CreateMenu(NULL, 0);
			m_console->DrawSelectorBar();
		}
		else
		{
			m_displayMode = DISPLAYMODE_GAME;
			m_console->AddText("USE:\n\nNOTHING...");
		}
		break;
	case ICON_ACCUSE:
		m_displayMode = DISPLAYMODE_CONSOLE;
		
		m_console->AddText("WHO IS THE\nMURDERER?");
		m_console->CreateMenu(g_accuseName, 9);
		m_console->DrawSelectorBar();
		break;
	default:
		break;
	}
}

void CGame::PostProcessMenu()
{
	switch(m_lastIconType)
	{
	case ICON_DOOR_OPEN:
	case ICON_DOOR_CLOSE:
		break;
	case ICON_EXAMINE:
		break;
	case ICON_TIME:
		m_displayMode = DISPLAYMODE_GAME;
		m_console->ClearText();
		break;
	case ICON_INVENTORY:
		m_displayMode = DISPLAYMODE_GAME;
		m_console->ClearText();
		m_pointer->Hide();
		m_menu->HideBox();
		m_console->HideMenu();
		break;
	case ICON_USE:
		m_displayMode = DISPLAYMODE_GAME;
		m_console->ClearText();
		m_pointer->Hide();
		m_menu->HideBox();
		m_console->HideMenu();
		break;
	case ICON_ACCUSE:
		m_displayMode = DISPLAYMODE_GAME;
		m_console->AddText("YOU DO NOT HAVE\nTHE EVIDENCE TO\nPROVE IT.");
		m_pointer->Hide();
		m_menu->HideBox();
		m_console->HideMenu();
		
		//char buf[256];
		//sprintf(buf, g_accuseName[m_console->MenuItem()]);
		//fprintf(stderr, buf);
		break;
	default:
		break;
	}
}

void CGame::InitRoom()
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
			static int frameCount = 0;
			
			frameCount++;
			
			if(frameCount == 8)
			{
				frameCount = 0;
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

void CGame::InitializeDoors()
{
	for (int i=0; i < MAX_ROOMS; i++)
		m_roomArray[i]->InitializeDoors();
}

void CGame::SortSprites()
{
	for (int i=0; i < MAX_CHARACTERS; i++)
	{
		m_characterArray[i]->Disable();
		
		for(int j=0; j < MAX_CHARACTERS; j++)
		{
			if (m_characterArray[i]->Y() + m_characterArray[i]->Height() > m_characterArray[j]->Y() + m_characterArray[j]->Height() &&
				m_characterArray[i]->OamIndex() > m_characterArray[j]->OamIndex())
			{
				int temp = m_characterArray[i]->OamIndex();
				m_characterArray[i]->SetOamIndex(m_characterArray[j]->OamIndex());
				m_characterArray[j]->SetOamIndex(temp);
			}
		}
		
		if(m_currentRoom->OverlayY() < m_characterArray[i]->Y() + m_characterArray[i]->Height())
			m_characterArray[i]->SetPriority(0);
		else
			m_characterArray[i]->SetPriority(1);
		
		//char buf[256];
		//sprintf(buf, "%d",m_characterArray[CHARTYPE_SNIDE]->Priority());
		//DrawText(buf, 0, 0, false);
	}
}

void CGame::UpdateCharacters(int elapsedTime)
{
	for (int i=0; i < MAX_CHARACTERS; i++)
	{
		m_characterArray[i]->Animate(elapsedTime);
		m_characterArray[i]->UpdatePosition();
		m_characterArray[i]->SetVisible(m_currentRoom);		
		m_characterArray[i]->Draw();
	}
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
