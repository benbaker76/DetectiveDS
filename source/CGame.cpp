#include <nds.h>
#include <stdio.h>
#include "CGame.h"
#include "TDG.h"
#include "Text.h"
#include "Gfx.h"

CGame::CGame(GameType gameType)
{
	m_gameType = gameType;
}

CGame::~CGame()
{
}

void CGame::Initialize()
{
	m_video.Initialize();
	
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
		/* m_spriteArray[SPRITE_SNIDE_HEAD] = new CSprite(SPRITE_SNIDE_HEAD, sprite_snide_headTiles, sprite_snide_headTilesLen, sprite_snide_headPal, sprite_snide_headPalLen, g_snideHeadFrames, 8);
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
		m_spriteArray[SPRITE_ANGUS_HEAD] = new CSprite(SPRITE_ANGUS_HEAD, sprite_angus_headTiles, sprite_angus_headTilesLen, sprite_angus_headPal, sprite_angus_headPalLen, g_angusHeadFrames, 5);
		m_spriteArray[SPRITE_ANGUS_BODY] = new CSprite(SPRITE_ANGUS_BODY, sprite_angus_bodyTiles, sprite_angus_bodyTilesLen, sprite_angus_bodyPal, sprite_angus_bodyPalLen, g_angusBodyFrames, 7); */
		
		m_spriteArray[SPRITE_SNIDE_HEAD] = new CSprite(SPRITE_SNIDE_HEAD, sprite_snide_headBitmap, g_snideHeadFrames, 8);
		m_spriteArray[SPRITE_SNIDE_BODY] = new CSprite(SPRITE_SNIDE_BODY, sprite_snide_bodyBitmap, g_snideBodyFrames, 17);
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
		m_spriteArray[SPRITE_DINGLE_BODY] = new CSprite(SPRITE_DINGLE_BODY, sprite_dingle_bodyBitmap, g_dingleBodyFrames, 7);
		m_spriteArray[SPRITE_ANGUS_HEAD] = new CSprite(SPRITE_ANGUS_HEAD, sprite_angus_headBitmap, g_angusHeadFrames, 5);
		m_spriteArray[SPRITE_ANGUS_BODY] = new CSprite(SPRITE_ANGUS_BODY, sprite_angus_bodyBitmap, g_angusBodyFrames, 7);
		
		m_characterArray[CHARACTER_SNIDE] = new CCharacter(CHARACTER_SNIDE, m_spriteArray[SPRITE_SNIDE_HEAD], m_spriteArray[SPRITE_SNIDE_BODY], 24, 53);
		m_characterArray[CHARACTER_REVEREND] = new CCharacter(CHARACTER_REVEREND, m_spriteArray[SPRITE_REVEREND_HEAD], m_spriteArray[SPRITE_REVEREND_BODY], 24, 53);
		m_characterArray[CHARACTER_BENTLEY] = new CCharacter(CHARACTER_BENTLEY, m_spriteArray[SPRITE_BENTLEY_HEAD], m_spriteArray[SPRITE_BENTLEY_BODY], 24, 53);
		m_characterArray[CHARACTER_COOK] = new CCharacter(CHARACTER_COOK, m_spriteArray[SPRITE_COOK_HEAD], m_spriteArray[SPRITE_COOK_BODY], 24, 44);
		m_characterArray[CHARACTER_GABRIEL] = new CCharacter(CHARACTER_GABRIEL, m_spriteArray[SPRITE_GABRIEL_HEAD], m_spriteArray[SPRITE_GABRIEL_BODY], 24, 48);
		m_characterArray[CHARACTER_CYNTHIA] = new CCharacter(CHARACTER_CYNTHIA, m_spriteArray[SPRITE_CYNTHIA_HEAD], m_spriteArray[SPRITE_CYNTHIA_BODY], 24, 49);
		m_characterArray[CHARACTER_PROFESSOR] = new CCharacter(CHARACTER_PROFESSOR, m_spriteArray[SPRITE_PROFESSOR_HEAD], m_spriteArray[SPRITE_PROFESSOR_BODY], 24, 48);
		m_characterArray[CHARACTER_DOCTOR] = new CCharacter(CHARACTER_DOCTOR, m_spriteArray[SPRITE_DOCTOR_HEAD], m_spriteArray[SPRITE_DOCTOR_BODY], 24, 49);
		m_characterArray[CHARACTER_MAJOR] = new CCharacter(CHARACTER_MAJOR, m_spriteArray[SPRITE_MAJOR_HEAD], m_spriteArray[SPRITE_MAJOR_BODY], 24, 46);
		m_characterArray[CHARACTER_DINGLE] = new CCharacter(CHARACTER_DINGLE, m_spriteArray[SPRITE_DINGLE_HEAD], m_spriteArray[SPRITE_DINGLE_BODY], 24, 48);
		m_characterArray[CHARACTER_ANGUS] = new CCharacter(CHARACTER_ANGUS, m_spriteArray[SPRITE_ANGUS_HEAD], m_spriteArray[SPRITE_ANGUS_BODY], 24, 48);
		
		m_roomArray[ROOM_SNIDE] = new CRoom(ROOM_SNIDE, &g_room1Map, NULL, col_room1);
		m_roomArray[ROOM_REVEREND] = new CRoom(ROOM_REVEREND, &g_room1Map, NULL, col_room3);
		m_roomArray[ROOM_BENTLEY] = new CRoom(ROOM_BENTLEY, &g_room2Map, NULL, col_room2);
		m_roomArray[ROOM_COOK] = new CRoom(ROOM_COOK, &g_room2Map, NULL, col_room2);
		m_roomArray[ROOM_GABRIEL] = new CRoom(ROOM_GABRIEL, &g_room2Map, NULL, col_room2);
		m_roomArray[ROOM_CYNTHIA] = new CRoom(ROOM_CYNTHIA, &g_room1Map, NULL, col_room1);
		m_roomArray[ROOM_PROFESSOR] = new CRoom(ROOM_PROFESSOR, &g_room1Map, NULL, col_room1);
		m_roomArray[ROOM_DOCTOR] = new CRoom(ROOM_DOCTOR, &g_room1Map, NULL, col_room1);		
		m_roomArray[ROOM_MAJOR] = new CRoom(ROOM_MAJOR, &g_room1Map, NULL, col_room3);
		m_roomArray[ROOM_DINGLE] = new CRoom(ROOM_DINGLE, &g_room1Map, NULL, col_room1);
		m_roomArray[ROOM_OUTSIDE1] = new CRoom(ROOM_OUTSIDE1, &g_outside1Map, NULL, col_outside1);
		m_roomArray[ROOM_OUTSIDE2] = new CRoom(ROOM_OUTSIDE2, &g_outside2Map, &g_outside2_frontMap, col_outside2);
		m_roomArray[ROOM_OUTSIDE3] = new CRoom(ROOM_OUTSIDE3, &g_outside1Map, NULL, col_outside1);
		m_roomArray[ROOM_OUTSIDE4] = new CRoom(ROOM_OUTSIDE4, &g_outside2Map, &g_outside2_frontMap, col_outside3);
		m_roomArray[ROOM_PASSAGE1] = new CRoom(ROOM_PASSAGE1, &g_passage1Map, NULL, col_passage1);
		m_roomArray[ROOM_PASSAGE2] = new CRoom(ROOM_PASSAGE2, &g_passage2Map, NULL, col_passage2);
		m_roomArray[ROOM_PASSAGE3] = new CRoom(ROOM_PASSAGE3, &g_passage1Map, NULL, col_passage1);
		m_roomArray[ROOM_HALL1] = new CRoom(ROOM_HALL1, &g_hall1Map, NULL, col_hall1);
		m_roomArray[ROOM_HALL2] = new CRoom(ROOM_HALL2, &g_hall2Map, NULL, col_hall2);
		m_roomArray[ROOM_HALL3] = new CRoom(ROOM_HALL3, &g_hall3Map, NULL, col_hall3);
		m_roomArray[ROOM_HALL4] = new CRoom(ROOM_HALL4, &g_hall4Map, NULL, col_hall4);
		m_roomArray[ROOM_LANDING] = new CRoom(ROOM_LANDING, &g_landingMap, &g_landing_front1Map, col_landing);
		m_roomArray[ROOM_KITCHEN] = new CRoom(ROOM_KITCHEN, &g_kitchenMap, NULL, col_kitchen);
		m_roomArray[ROOM_STAIRS] = new CRoom(ROOM_STAIRS, &g_stairsMap, NULL, col_stairs);
		m_roomArray[ROOM_STUDY] = new CRoom(ROOM_STUDY, &g_studyMap, NULL, col_study);
		m_roomArray[ROOM_CLOCK] = new CRoom(ROOM_CLOCK, &g_clockMap, NULL, col_clock);
		m_roomArray[ROOM_CELLAR] = new CRoom(ROOM_CELLAR, &g_cellarMap, NULL, col_cellar);
		m_roomArray[ROOM_DRAWING] = new CRoom(ROOM_DRAWING, &g_drawingMap, NULL, col_drawing);
		m_roomArray[ROOM_LIBRARY] = new CRoom(ROOM_LIBRARY, &g_libraryMap, NULL, col_library);
		m_roomArray[ROOM_GARDEN] = new CRoom(ROOM_GARDEN, &g_gardenMap, &g_garden_frontMap, col_garden);
		m_roomArray[ROOM_GRAVEYARD] = new CRoom(ROOM_GRAVEYARD, &g_graveyardMap, &g_graveyard_frontMap, col_graveyard);
		
		//m_roomArray[ROOM_STAIRS]->SetOverlay(&g_stairs_frontMap, 168);
		m_roomArray[ROOM_GRAVEYARD]->SetOverlay(&g_graveyard_frontMap, 176);
		
		m_roomArray[ROOM_SNIDE]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_SNIDE], m_roomArray[ROOM_HALL2]));		
		m_roomArray[ROOM_REVEREND]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_REVEREND], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_REVEREND]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_REVEREND], m_roomArray[ROOM_PASSAGE1]));		
		m_roomArray[ROOM_BENTLEY]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_BENTLEY], m_roomArray[ROOM_HALL3]));		
		m_roomArray[ROOM_COOK]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_COOK], m_roomArray[ROOM_HALL4]));
		m_roomArray[ROOM_GABRIEL]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_GABRIEL], m_roomArray[ROOM_HALL4]));
		m_roomArray[ROOM_CYNTHIA]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_CYNTHIA], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_PROFESSOR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_PROFESSOR], m_roomArray[ROOM_HALL2]));
		m_roomArray[ROOM_DOCTOR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_DOCTOR], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_MAJOR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_MAJOR], m_roomArray[ROOM_HALL2]));
		m_roomArray[ROOM_MAJOR]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_MAJOR], m_roomArray[ROOM_OUTSIDE2]));
		m_roomArray[ROOM_DINGLE]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_DINGLE], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_OUTSIDE1]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE1], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_OUTSIDE2]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE2], m_roomArray[ROOM_PASSAGE1]));
		m_roomArray[ROOM_OUTSIDE2]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE2], m_roomArray[ROOM_MAJOR]));
		m_roomArray[ROOM_OUTSIDE3]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE3], m_roomArray[ROOM_CLOCK]));
		m_roomArray[ROOM_OUTSIDE4]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE4], m_roomArray[ROOM_GARDEN]));
		m_roomArray[ROOM_OUTSIDE4]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE4], m_roomArray[ROOM_CELLAR]));
		m_roomArray[ROOM_OUTSIDE4]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE4], m_roomArray[ROOM_DRAWING]));
		m_roomArray[ROOM_PASSAGE1]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE1], m_roomArray[ROOM_REVEREND]));
		m_roomArray[ROOM_PASSAGE1]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE1], m_roomArray[ROOM_OUTSIDE2]));
		m_roomArray[ROOM_PASSAGE2]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE2], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_PASSAGE2]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE2], m_roomArray[ROOM_HALL2]));
		m_roomArray[ROOM_PASSAGE3]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE3], m_roomArray[ROOM_KITCHEN]));
		m_roomArray[ROOM_PASSAGE3]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_PASSAGE3], m_roomArray[ROOM_CELLAR]));
		m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_REVEREND]));
		m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_CYNTHIA]));
		m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPEN, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_DOCTOR]));
		m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR4, new CDoor(DOOR_DOOR4, DOORSTATE_OPEN, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_DINGLE]));
		m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR5, new CDoor(DOOR_DOOR5, DOORSTATE_OPEN, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_OUTSIDE1]));
		m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR6, new CDoor(DOOR_DOOR6, DOORSTATE_OPEN, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_LANDING]));
		m_roomArray[ROOM_HALL1]->SetDoor(DOOR_DOOR7, new CDoor(DOOR_DOOR7, DOORSTATE_OPEN, m_roomArray[ROOM_HALL1], m_roomArray[ROOM_PASSAGE2]));
		m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_PROFESSOR]));
		m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_MAJOR]));
		m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPEN, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_PASSAGE2]));
		m_roomArray[ROOM_HALL2]->SetDoor(DOOR_DOOR4, new CDoor(DOOR_DOOR4, DOORSTATE_OPEN, m_roomArray[ROOM_HALL2], m_roomArray[ROOM_SNIDE]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_KITCHEN]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_STAIRS]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPEN, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_STUDY]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR4, new CDoor(DOOR_DOOR4, DOORSTATE_OPEN, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_BENTLEY]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR5, new CDoor(DOOR_DOOR5, DOORSTATE_OPEN, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_DRAWING]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR6, new CDoor(DOOR_DOOR6, DOORSTATE_OPEN, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_LIBRARY]));
		m_roomArray[ROOM_HALL3]->SetDoor(DOOR_DOOR7, new CDoor(DOOR_DOOR7, DOORSTATE_OPEN, m_roomArray[ROOM_HALL3], m_roomArray[ROOM_HALL4]));
		m_roomArray[ROOM_HALL4]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_HALL3]));
		m_roomArray[ROOM_HALL4]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_COOK]));
		m_roomArray[ROOM_HALL4]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPEN, m_roomArray[ROOM_HALL4], m_roomArray[ROOM_GABRIEL]));
		m_roomArray[ROOM_LANDING]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_LANDING], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_LANDING]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_LANDING], m_roomArray[ROOM_STAIRS]));
		m_roomArray[ROOM_KITCHEN]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_PASSAGE3]));
		m_roomArray[ROOM_KITCHEN]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_KITCHEN], m_roomArray[ROOM_HALL3]));
		m_roomArray[ROOM_STAIRS]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_LANDING]));
		m_roomArray[ROOM_STAIRS]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_STAIRS], m_roomArray[ROOM_HALL3]));
		m_roomArray[ROOM_STUDY]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_STUDY], m_roomArray[ROOM_HALL3]));
		m_roomArray[ROOM_CLOCK]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_CLOCK], m_roomArray[ROOM_OUTSIDE3]));
		m_roomArray[ROOM_CLOCK]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_CLOCK], m_roomArray[ROOM_DRAWING]));
		m_roomArray[ROOM_CELLAR]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_CELLAR], m_roomArray[ROOM_PASSAGE3]));
		m_roomArray[ROOM_CELLAR]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_CELLAR], m_roomArray[ROOM_OUTSIDE4]));
		m_roomArray[ROOM_DRAWING]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_CLOCK]));
		m_roomArray[ROOM_DRAWING]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_HALL3]));
		m_roomArray[ROOM_DRAWING]->SetDoor(DOOR_DOOR3, new CDoor(DOOR_DOOR3, DOORSTATE_OPEN, m_roomArray[ROOM_DRAWING], m_roomArray[ROOM_OUTSIDE4]));
		m_roomArray[ROOM_LIBRARY]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_LIBRARY], m_roomArray[ROOM_HALL3]));
		m_roomArray[ROOM_GARDEN]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_GARDEN], m_roomArray[ROOM_GRAVEYARD]));
		m_roomArray[ROOM_GARDEN]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_GARDEN], m_roomArray[ROOM_OUTSIDE4]));
		m_roomArray[ROOM_GRAVEYARD]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_GRAVEYARD], m_roomArray[ROOM_GARDEN]));
		
		m_eventArray[EVENT_SHOW_ROOM] = new CEvent(EVENT_SHOW_ROOM, new CTime(9, 10, 0, 0));
		m_eventArray[EVENT_GET_SHOT] = new CEvent(EVENT_SHOW_ROOM, new CTime(12, 0, 0, 0));
		break;
	}
	
	InitializeDoors();
	
	m_snide = m_characterArray[CHARACTER_SNIDE];
	m_snide->SetPosition(142, 105);
	m_snide->Show();
	
	m_currentRoom = m_roomArray[ROOM_STAIRS];
	m_currentRoom->Initialize(69);
	
	m_characterArray[CHARACTER_ANGUS]->SetAlpha(0x7);
	
	/* for(int i=1; i<MAX_CHARACTERS; i++)
	{
		m_characterArray[i]->SetPosition((i - 1) * CHARACTER_WIDTH, 168 - CHARACTER_HEIGHT);
		m_characterArray[i]->SetFrameType(FRAME_SPEAK);
		m_characterArray[i]->Show();
	} */
	
	m_fxManager.Initialize();
	m_fxManager.SetFx(FX_LIGHTS_BLACK_OUT, true);
	
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
	
	if(keys_held & KEY_UP)
	{
		CollisionType collisionType = m_snide->CheckCollision(DIRECTION_UP, m_currentRoom);
		
		if(m_snide->X() < 256 - m_snide->Width() - 8 && collisionType == COL_PATH)
			m_snide->Move(DIRECTION_UP);
		else
			m_snide->Face(DIRECTION_UP);
		
		if(collisionType >= COL_DOOR1 && collisionType <= COL_SECRET_PASSAGE)
		{
			CDoor* pDoor = m_currentRoom->GetDoor((int)collisionType);
			
			if(pDoor != NULL)
			{
				m_currentRoom = pDoor->pRoomOut();
				
				int xDoor = pDoor->pDoorOut()->X() + (pDoor->pDoorOut()->Width() / 2) - 1;
				int xRoom = xDoor - 128;
				
				int xChar = 128;
				int yChar = pDoor->pDoorOut()->Y() + pDoor->pDoorOut()->Height() - m_characterArray[CHARACTER_SNIDE]->Height();
				
				if(xRoom + 256 > m_currentRoom->Width()) xRoom = m_currentRoom->Width() - 256;
				if(xRoom < 0) xRoom = 0;
			
				if(xDoor< 128) xChar = xDoor;
				if(xDoor > m_currentRoom->Width() - 128) xChar = 256 - (m_currentRoom->Width() - xDoor);	
				
				m_fxManager.SetFx(FX_LIGHTS_BLACK_OUT, true);
				
				m_currentRoom->Initialize(xRoom);
				m_snide->SetPosition(xChar, yChar);
				
				//m_fxManager.SetFx(FX_FADE_BLACK_IN, true);
				
				//char buf[256];
				//sprintf(buf, "xRoom: %05d, xChar: %05d", xRoom, xChar);
				//DrawText(buf, 0, 1, false);
			}
		}
	}
	else if(keys_held & KEY_DOWN)
	{
		CollisionType collisionType = m_snide->CheckCollision(DIRECTION_DOWN, m_currentRoom);
		
		if(m_snide->X() > 8 && collisionType == COL_PATH)
			m_snide->Move(DIRECTION_DOWN);
		else
			m_snide->Face(DIRECTION_DOWN);
		
		if(collisionType >= COL_DOOR1 && collisionType <= COL_SECRET_PASSAGE)
		{
			CDoor* pDoor = m_currentRoom->GetDoor((int)collisionType);
			
			if(pDoor != NULL)
			{
				m_currentRoom = pDoor->pRoomOut();
			
				int xDoor = pDoor->pDoorOut()->X() + (pDoor->pDoorOut()->Width() / 2) - 1;
				int xRoom = xDoor - 128;
				
				int xChar = 128;
				int yChar = pDoor->pDoorOut()->Y() + pDoor->pDoorOut()->Height() - m_characterArray[CHARACTER_SNIDE]->Height() + 16;
				
				if(xRoom + 256 > m_currentRoom->Width()) xRoom = m_currentRoom->Width() - 256;
				if(xRoom < 0) xRoom = 0;
				
				if(xDoor < 128) xChar = xDoor;
				if(xDoor > m_currentRoom->Width() - 128) xChar = 256 - (m_currentRoom->Width() - xDoor);
				
				m_fxManager.SetFx(FX_LIGHTS_BLACK_OUT, true);
				
				m_currentRoom->Initialize(xRoom);
				m_snide->SetPosition(xChar, yChar);
				
				//m_fxManager.SetFx(FX_FADE_BLACK_IN, true);
				
				//char buf[256];
				//sprintf(buf, "xRoom: %05d, xChar: %05d", xRoom, xChar);
				//DrawText(buf, 0, 1, false);
			}
		}
	}
	else if(keys_held & KEY_LEFT)
	{
		CollisionType collisionType = m_snide->CheckCollision(DIRECTION_LEFT, m_currentRoom);
		
		if(collisionType >= COL_DOOR1 && collisionType <= COL_SECRET_PASSAGE)
		{
			CDoor* pDoor = m_currentRoom->GetDoor((int)collisionType);
			
			if(pDoor != NULL)
			{
				m_currentRoom = pDoor->pRoomOut();
				
				int xChar = 256 - m_characterArray[CHARACTER_SNIDE]->Width() - 8;
				//int yChar =  pDoor->pDoorOut()->Y() + (pDoor->pDoorOut()->Height() / 2) -  m_characterArray[CHARACTER_SNIDE]->Height();
				
				m_fxManager.SetFx(FX_LIGHTS_BLACK_OUT, true);
				
				m_currentRoom->Initialize(m_currentRoom->Width() - 256);
				//m_snide->SetPosition(xChar, yChar);
				m_snide->SetX(xChar);
			}
		}
		else if(collisionType == COL_PATH)
		{
			if(m_snide->X() > 128)
			{
				m_snide->Move(DIRECTION_LEFT);
			}
			else
			{
				if(!m_currentRoom->Scroll(DIRECTION_LEFT))
					m_snide->Move(DIRECTION_LEFT);
				else
					m_snide->Face(DIRECTION_LEFT);
			}
		}
		else
			m_snide->Face(DIRECTION_LEFT);
	}
	else if(keys_held & KEY_RIGHT)
	{
		CollisionType collisionType = m_snide->CheckCollision(DIRECTION_RIGHT, m_currentRoom);
		
		if(collisionType >= COL_DOOR1 && collisionType <= COL_SECRET_PASSAGE)
		{
			CDoor* pDoor = m_currentRoom->GetDoor((int)collisionType);
			
			if(pDoor != NULL)
			{
				m_currentRoom = pDoor->pRoomOut();
				
				int xChar = 8;
				//int yChar = pDoor->pDoorOut()->Y() + (pDoor->pDoorOut()->Height() / 2) -  m_characterArray[CHARACTER_SNIDE]->Height();
				
				m_fxManager.SetFx(FX_LIGHTS_BLACK_OUT, true);
				
				m_currentRoom->Initialize(0);
				//m_snide->SetPosition(xChar, yChar);
				m_snide->SetX(xChar);
			}
		}
		else if(collisionType == COL_PATH)
		{
			if(m_snide->X() < 128)
			{
				m_snide->Move(DIRECTION_RIGHT);
			}
			else
			{
				if(!m_currentRoom->Scroll(DIRECTION_RIGHT))
					m_snide->Move(DIRECTION_RIGHT);
				else
					m_snide->Face(DIRECTION_RIGHT);
			}
		}
		else
			m_snide->Face(DIRECTION_RIGHT);
	}
	else if(keys_held & KEY_A)
	{
		m_snide->SetFrameType(FRAME_SPEAK);
	}
	else
	{
		m_snide->SetFrameType(FRAME_NONE);
	}
	
	SortSprites();
	AnimateCharacters(elapsedTime);
	DrawCharacters();
	
	oamUpdate(&oamSub);
}

void CGame::InitializeDoors()
{
	for (int i=0; i < MAX_ROOMS; i++)
	{
		for(int j=0; j < MAX_DOORS; j++)
		{
			if(m_roomArray[i] != NULL)
			{
				CDoor* pDoor = m_roomArray[i]->GetDoor(j);
				
				if(pDoor != NULL)
					pDoor->Initialize();
			}
		}
	}
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
		//sprintf(buf, "%d",m_characterArray[CHARACTER_SNIDE]->Priority());
		//DrawText(buf, 0, 0, false);
	}
}

void CGame::AnimateCharacters(int elapsedTime)
{
	for (int i=0; i < MAX_CHARACTERS; i++)
		m_characterArray[i]->Animate(elapsedTime);
}

void CGame::DrawCharacters()
{
	for (int i=0; i < MAX_CHARACTERS; i++)
		m_characterArray[i]->Draw();
}

void CGame::UpdateVBlank()
{
	m_fxManager.UpdateVBlank();
}

void CGame::UpdateHBlank()
{
	/* if(REG_VCOUNT == 0)
	{
		REG_DISPCNT_SUB &= ~DISPLAY_SPRITE_ATTR_MASK;
		REG_DISPCNT_SUB |= SpriteMapping_1D_32;
	}
	if(REG_VCOUNT == 40)
	{
		REG_DISPCNT_SUB &= ~DISPLAY_SPRITE_ATTR_MASK;
		REG_DISPCNT_SUB |= SpriteMapping_Bmp_1D_128;
	} */

	m_fxManager.UpdateHBlank();
}

void CGame::UpdateTimer1()
{
}

void CGame::UpdateTimer2()
{
	m_timer->Update();
}
