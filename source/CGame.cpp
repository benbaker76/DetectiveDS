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
		
	for(int i=0; i<MAX_MAPS; i++)
		m_mapArray[i] = NULL;
		
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
		m_spriteArray[SPRITE_HEAD_SNIDE] = new CSprite(SPRITE_HEAD_SNIDE, sprite_snide_headTiles, sprite_snide_headTilesLen, sprite_snide_headPal, sprite_snide_headPalLen, g_snideHeadFrames, 8);
		m_spriteArray[SPRITE_BODY_SNIDE] = new CSprite(SPRITE_BODY_SNIDE, sprite_snide_bodyTiles, sprite_snide_bodyTilesLen, sprite_snide_bodyPal, sprite_snide_bodyPalLen, g_snideBodyFrames, 17);
		m_spriteArray[SPRITE_HEAD_REVEREND] = new CSprite(SPRITE_HEAD_REVEREND, sprite_reverend_headTiles, sprite_reverend_headTilesLen, sprite_reverend_headPal, sprite_reverend_headPalLen, g_reverendHeadFrames, 4);
		m_spriteArray[SPRITE_BODY_REVEREND] = new CSprite(SPRITE_BODY_REVEREND, sprite_reverend_bodyTiles, sprite_reverend_bodyTilesLen, sprite_reverend_bodyPal, sprite_reverend_bodyPalLen, g_reverendBodyFrames, 6);
		m_spriteArray[SPRITE_HEAD_BENTLEY] = new CSprite(SPRITE_HEAD_BENTLEY, sprite_bentley_headTiles, sprite_bentley_headTilesLen, sprite_bentley_headPal, sprite_bentley_headPalLen, g_bentleyHeadFrames, 4);
		m_spriteArray[SPRITE_BODY_BENTLEY] = new CSprite(SPRITE_BODY_BENTLEY, sprite_bentley_bodyTiles, sprite_bentley_bodyTilesLen, sprite_bentley_bodyPal, sprite_bentley_bodyPalLen, g_bentleyBodyFrames, 6);
		m_spriteArray[SPRITE_HEAD_COOK] = new CSprite(SPRITE_HEAD_COOK, sprite_cook_headTiles, sprite_cook_headTilesLen, sprite_cook_headPal, sprite_cook_headPalLen, g_cookHeadFrames, 4);
		m_spriteArray[SPRITE_BODY_COOK] = new CSprite(SPRITE_BODY_COOK, sprite_cook_bodyTiles, sprite_cook_bodyTilesLen, sprite_cook_bodyPal, sprite_cook_bodyPalLen, g_cookBodyFrames, 6);
		m_spriteArray[SPRITE_HEAD_GABRIEL] = new CSprite(SPRITE_HEAD_GABRIEL, sprite_gabriel_headTiles, sprite_gabriel_headTilesLen, sprite_gabriel_headPal, sprite_gabriel_headPalLen, g_gabrielHeadFrames, 5);
		m_spriteArray[SPRITE_BODY_GABRIEL] = new CSprite(SPRITE_BODY_GABRIEL, sprite_gabriel_bodyTiles, sprite_gabriel_bodyTilesLen, sprite_gabriel_bodyPal, sprite_gabriel_bodyPalLen, g_gabrielBodyFrames, 7);
		m_spriteArray[SPRITE_HEAD_CYNTHIA] = new CSprite(SPRITE_HEAD_CYNTHIA, sprite_cynthia_headTiles, sprite_cynthia_headTilesLen, sprite_cynthia_headPal, sprite_cynthia_headPalLen, g_cynthiaHeadFrames, 4);
		m_spriteArray[SPRITE_BODY_CYNTHIA] = new CSprite(SPRITE_BODY_CYNTHIA, sprite_cynthia_bodyTiles, sprite_cynthia_bodyTilesLen, sprite_cynthia_bodyPal, sprite_cynthia_bodyPalLen, g_cynthiaBodyFrames, 6);
		m_spriteArray[SPRITE_HEAD_PROFESSOR] = new CSprite(SPRITE_HEAD_PROFESSOR, sprite_professor_headTiles, sprite_professor_headTilesLen, sprite_professor_headPal, sprite_professor_headPalLen, g_professorHeadFrames, 5);
		m_spriteArray[SPRITE_BODY_PROFESSOR] = new CSprite(SPRITE_BODY_PROFESSOR, sprite_professor_bodyTiles, sprite_professor_bodyTilesLen, sprite_professor_bodyPal, sprite_professor_bodyPalLen, g_professorBodyFrames, 7);
		m_spriteArray[SPRITE_HEAD_DOCTOR] = new CSprite(SPRITE_HEAD_DOCTOR, sprite_doctor_headTiles, sprite_doctor_headTilesLen, sprite_doctor_headPal, sprite_doctor_headPalLen, g_doctorHeadFrames, 5);
		m_spriteArray[SPRITE_BODY_DOCTOR] = new CSprite(SPRITE_BODY_DOCTOR, sprite_doctor_bodyTiles, sprite_doctor_bodyTilesLen, sprite_doctor_bodyPal, sprite_doctor_bodyPalLen, g_doctorBodyFrames, 7);
		m_spriteArray[SPRITE_HEAD_MAJOR] = new CSprite(SPRITE_HEAD_MAJOR, sprite_major_headTiles, sprite_major_headTilesLen, sprite_major_headPal, sprite_major_headPalLen, g_majorHeadFrames, 4);
		m_spriteArray[SPRITE_BODY_MAJOR] = new CSprite(SPRITE_BODY_MAJOR, sprite_major_bodyTiles, sprite_major_bodyTilesLen, sprite_major_bodyPal, sprite_major_bodyPalLen, g_majorBodyFrames, 6);		
		m_spriteArray[SPRITE_HEAD_DINGLE] = new CSprite(SPRITE_HEAD_DINGLE, sprite_dingle_headTiles, sprite_dingle_headTilesLen, sprite_dingle_headPal, sprite_dingle_headPalLen, g_dingleHeadFrames, 5);
		m_spriteArray[SPRITE_BODY_DINGLE] = new CSprite(SPRITE_BODY_DINGLE, sprite_dingle_bodyTiles, sprite_dingle_bodyTilesLen, sprite_dingle_bodyPal, sprite_dingle_bodyPalLen, g_dingleBodyFrames, 7);
		
		m_characterArray[CHARACTER_SNIDE] = new CCharacter(CHARACTER_SNIDE, m_spriteArray[SPRITE_HEAD_SNIDE], m_spriteArray[SPRITE_BODY_SNIDE]);
		m_characterArray[CHARACTER_REVEREND] = new CCharacter(CHARACTER_REVEREND, m_spriteArray[SPRITE_HEAD_REVEREND], m_spriteArray[SPRITE_BODY_REVEREND]);
		m_characterArray[CHARACTER_BENTLEY] = new CCharacter(CHARACTER_BENTLEY, m_spriteArray[SPRITE_HEAD_BENTLEY], m_spriteArray[SPRITE_BODY_BENTLEY]);
		m_characterArray[CHARACTER_COOK] = new CCharacter(CHARACTER_COOK, m_spriteArray[SPRITE_HEAD_COOK], m_spriteArray[SPRITE_BODY_COOK]);
		m_characterArray[CHARACTER_GABRIEL] = new CCharacter(CHARACTER_GABRIEL, m_spriteArray[SPRITE_HEAD_GABRIEL], m_spriteArray[SPRITE_BODY_GABRIEL]);
		m_characterArray[CHARACTER_CYNTHIA] = new CCharacter(CHARACTER_CYNTHIA, m_spriteArray[SPRITE_HEAD_CYNTHIA], m_spriteArray[SPRITE_BODY_CYNTHIA]);
		m_characterArray[CHARACTER_PROFESSOR] = new CCharacter(CHARACTER_PROFESSOR, m_spriteArray[SPRITE_HEAD_PROFESSOR], m_spriteArray[SPRITE_BODY_PROFESSOR]);
		m_characterArray[CHARACTER_DOCTOR] = new CCharacter(CHARACTER_DOCTOR, m_spriteArray[SPRITE_HEAD_DOCTOR], m_spriteArray[SPRITE_BODY_DOCTOR]);
		m_characterArray[CHARACTER_MAJOR] = new CCharacter(CHARACTER_MAJOR, m_spriteArray[SPRITE_HEAD_MAJOR], m_spriteArray[SPRITE_BODY_MAJOR]);
		m_characterArray[CHARACTER_DINGLE] = new CCharacter(CHARACTER_DINGLE, m_spriteArray[SPRITE_HEAD_DINGLE], m_spriteArray[SPRITE_BODY_DINGLE]);
		
		m_mapArray[MAP_CELLAR] = new CMap(400, 192, map_cellarTiles, map_cellarTilesLen, map_cellarMap, map_cellarMapLen, map_cellarPal, map_cellarPalLen);
		m_mapArray[MAP_CLOCK] = new CMap(304, 192, map_clockTiles, map_clockTilesLen, map_clockMap, map_clockMapLen, map_clockPal, map_clockPalLen);
		m_mapArray[MAP_DRAWING] = new CMap(640, 192, map_drawingTiles, map_drawingTilesLen, map_drawingMap, map_drawingMapLen, map_drawingPal, map_drawingPalLen);
		m_mapArray[MAP_HALL1] = new CMap(832, 192, map_hall1Tiles, map_hall1TilesLen, map_hall1Map, map_hall1MapLen, map_hall1Pal, map_hall1PalLen);
		m_mapArray[MAP_HALL2] = new CMap(832, 192, map_hall2Tiles, map_hall2TilesLen, map_hall2Map, map_hall2MapLen, map_hall2Pal, map_hall2PalLen);
		m_mapArray[MAP_HALL3] = new CMap(832, 192, map_hall3Tiles, map_hall3TilesLen, map_hall3Map, map_hall3MapLen, map_hall3Pal, map_hall3PalLen);
		m_mapArray[MAP_HALL4] = new CMap(544, 192, map_hall4Tiles, map_hall4TilesLen, map_hall4Map, map_hall4MapLen, map_hall4Pal, map_hall4PalLen);
		m_mapArray[MAP_KITCHEN] = new CMap(536, 192, map_kitchenTiles, map_kitchenTilesLen, map_kitchenMap, map_kitchenMapLen, map_kitchenPal, map_kitchenPalLen);
		m_mapArray[MAP_LANDING] = new CMap(400, 192, map_landingTiles, map_landingTilesLen, map_landingMap, map_landingMapLen, map_landingPal, map_landingPalLen);
		m_mapArray[MAP_LIBRARY] = new CMap(416, 192, map_libraryTiles, map_libraryTilesLen, map_libraryMap, map_libraryMapLen, map_libraryPal, map_libraryPalLen);
		m_mapArray[MAP_OUTSIDE1] = new CMap(400, 192, map_outside1Tiles, map_outside1TilesLen, map_outside1Map, map_outside1MapLen, map_outside1Pal, map_outside1PalLen);
		m_mapArray[MAP_OUTSIDE2] = new CMap(544, 192, map_outside2Tiles, map_outside2TilesLen, map_outside2Map, map_outside2MapLen, map_outside2Pal, map_outside2PalLen);
		m_mapArray[MAP_PASSAGE1] = new CMap(256, 192, map_passage1Tiles, map_passage1TilesLen, map_passage1Map, map_passage1MapLen, map_passage1Pal, map_passage1PalLen);
		m_mapArray[MAP_PASSAGE2] = new CMap(256, 192, map_passage2Tiles, map_passage2TilesLen, map_passage2Map, map_passage2MapLen, map_passage2Pal, map_passage2PalLen);
		m_mapArray[MAP_ROOM1] = new CMap(400, 192, map_room1Tiles, map_room1TilesLen, map_room1Map, map_room1MapLen, map_room1Pal, map_room1PalLen);
		m_mapArray[MAP_ROOM2] = new CMap(344, 192, map_room2Tiles, map_room2TilesLen, map_room2Map, map_room2MapLen, map_room2Pal, map_room2PalLen);
		m_mapArray[MAP_STAIRS] = new CMap(336, 192, map_stairsTiles, map_stairsTilesLen, map_stairsMap, map_stairsMapLen, map_stairsPal, map_stairsPalLen);
		m_mapArray[MAP_STUDY] = new CMap(320, 192, map_studyTiles, map_studyTilesLen, map_studyMap, map_studyMapLen, map_studyPal, map_studyPalLen);
		
		m_mapArray[MAP_LANDING]->SetOverlay(map_landing_front1Tiles, map_landing_front1TilesLen, map_landing_front1Map, map_landing_front1MapLen);
		m_mapArray[MAP_OUTSIDE2]->SetOverlay(map_outside2_frontTiles, map_outside2_frontTilesLen, map_outside2_frontMap, map_outside2_frontMapLen);
		//m_mapArray[MAP_STAIRS]->SetOverlay(map_stairs_frontTiles, map_stairs_frontTilesLen, map_stairs_frontMap, map_stairs_frontMapLen);
		
		m_roomArray[ROOM_SNIDE] = new CRoom(ROOM_SNIDE, m_mapArray[MAP_ROOM1], col_room1);
		m_roomArray[ROOM_REVEREND] = new CRoom(ROOM_REVEREND, m_mapArray[MAP_ROOM1], col_room1);
		m_roomArray[ROOM_BENTLEY] = new CRoom(ROOM_BENTLEY, m_mapArray[MAP_ROOM2], col_room2);
		m_roomArray[ROOM_COOK] = new CRoom(ROOM_COOK, m_mapArray[MAP_ROOM2], col_room2);
		m_roomArray[ROOM_GABRIEL] = new CRoom(ROOM_GABRIEL, m_mapArray[MAP_ROOM2], col_room2);
		m_roomArray[ROOM_CYNTHIA] = new CRoom(ROOM_CYNTHIA, m_mapArray[MAP_ROOM1], col_room1);
		m_roomArray[ROOM_PROFESSOR] = new CRoom(ROOM_PROFESSOR, m_mapArray[MAP_ROOM1], col_room1);
		m_roomArray[ROOM_DOCTOR] = new CRoom(ROOM_DOCTOR, m_mapArray[MAP_ROOM1], col_room1);		
		m_roomArray[ROOM_MAJOR] = new CRoom(ROOM_MAJOR, m_mapArray[MAP_ROOM1], col_room1);
		m_roomArray[ROOM_DINGLE] = new CRoom(ROOM_DINGLE, m_mapArray[MAP_ROOM1], col_room1);
		m_roomArray[ROOM_OUTSIDE1] = new CRoom(ROOM_OUTSIDE1, m_mapArray[MAP_OUTSIDE1], col_outside1);
		m_roomArray[ROOM_OUTSIDE2] = new CRoom(ROOM_OUTSIDE2, m_mapArray[MAP_OUTSIDE2], col_outside2);
		m_roomArray[ROOM_OUTSIDE3] = new CRoom(ROOM_OUTSIDE3, m_mapArray[MAP_OUTSIDE1], col_outside1);
		m_roomArray[ROOM_OUTSIDE4] = new CRoom(ROOM_OUTSIDE4, m_mapArray[MAP_OUTSIDE2], col_outside2);
		m_roomArray[ROOM_PASSAGE1] = new CRoom(ROOM_PASSAGE1, m_mapArray[MAP_PASSAGE1], col_passage1);
		m_roomArray[ROOM_PASSAGE2] = new CRoom(ROOM_PASSAGE2, m_mapArray[MAP_PASSAGE2], col_passage2);
		m_roomArray[ROOM_PASSAGE3] = new CRoom(ROOM_PASSAGE3, m_mapArray[MAP_PASSAGE1], col_passage1);
		m_roomArray[ROOM_HALL1] = new CRoom(ROOM_HALL1, m_mapArray[MAP_HALL1], col_hall1);
		m_roomArray[ROOM_HALL2] = new CRoom(ROOM_HALL2, m_mapArray[MAP_HALL2], col_hall2);
		m_roomArray[ROOM_HALL3] = new CRoom(ROOM_HALL3, m_mapArray[MAP_HALL3], col_hall3);
		m_roomArray[ROOM_HALL4] = new CRoom(ROOM_HALL4, m_mapArray[MAP_HALL4], col_hall4);
		m_roomArray[ROOM_LANDING] = new CRoom(ROOM_LANDING, m_mapArray[MAP_LANDING], col_landing);
		m_roomArray[ROOM_KITCHEN] = new CRoom(ROOM_KITCHEN, m_mapArray[MAP_KITCHEN], col_kitchen);
		m_roomArray[ROOM_STAIRS] = new CRoom(ROOM_STAIRS, m_mapArray[MAP_STAIRS], col_stairs);
		m_roomArray[ROOM_STUDY] = new CRoom(ROOM_STUDY, m_mapArray[MAP_STUDY], col_study);
		m_roomArray[ROOM_CLOCK] = new CRoom(ROOM_CLOCK, m_mapArray[MAP_CLOCK], col_clock);
		m_roomArray[ROOM_CELLAR] = new CRoom(ROOM_CELLAR, m_mapArray[MAP_CELLAR], col_cellar);
		m_roomArray[ROOM_DRAWING] = new CRoom(ROOM_DRAWING, m_mapArray[MAP_DRAWING], col_drawing);
		m_roomArray[ROOM_LIBRARY] = new CRoom(ROOM_LIBRARY, m_mapArray[MAP_LIBRARY], col_library);
		
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
		m_roomArray[ROOM_DINGLE]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_DINGLE], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_OUTSIDE1]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE1], m_roomArray[ROOM_HALL1]));
		m_roomArray[ROOM_OUTSIDE2]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE2], m_roomArray[ROOM_PASSAGE1]));
		m_roomArray[ROOM_OUTSIDE3]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE3], m_roomArray[ROOM_CLOCK]));
		m_roomArray[ROOM_OUTSIDE4]->SetDoor(DOOR_DOOR1, new CDoor(DOOR_DOOR1, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE4], m_roomArray[ROOM_CELLAR]));
		m_roomArray[ROOM_OUTSIDE4]->SetDoor(DOOR_DOOR2, new CDoor(DOOR_DOOR2, DOORSTATE_OPEN, m_roomArray[ROOM_OUTSIDE4], m_roomArray[ROOM_DRAWING]));
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
					
		m_eventArray[EVENT_SHOW_ROOM] = new CEvent(EVENT_SHOW_ROOM, new CTime(9, 10, 0, 0));
		m_eventArray[EVENT_GET_SHOT] = new CEvent(EVENT_SHOW_ROOM, new CTime(12, 0, 0, 0));
		break;
	}
	
	InitializeDoors();
	
	m_snide = m_characterArray[CHARACTER_SNIDE];
	m_snide->SetPosition(142, 105);
	
	m_currentRoom = m_roomArray[ROOM_STAIRS];
	m_currentRoom->Initialize(69);
	
	//m_characterArray[CHARACTER_GABRIEL]->SetPosition(64, 168 - CHARACTER_HEIGHT);
	//m_characterArray[CHARACTER_GABRIEL]->SetFrameType(FRAME_SPEAK);
	
	m_fxManager.Initialize();
	m_fxManager.SetFx(FX_LIGHTS_BLACK_OUT, true);
	
	m_watch = new CWatch(113, 21);
	m_timer = new CTimer(9, 10, 0, 0);
	m_timer->Start();
}

void CGame::Update()
{
	static mm_sfxhand footsteps = 0;
	touchPosition touch;
	int keys_held, keys_pressed, keys_released;
	
	touchRead(&touch);
	scanKeys();
	
	keys_held = keysHeld();
	keys_pressed = keysDown();
	keys_released = keysUp();
	
	m_elapsedTime = m_timer->pCurrentTime()->MilliSeconds - m_lastUpdate;
	m_lastUpdate = m_timer->pCurrentTime()->MilliSeconds;
	
	//char buf[256];
	//sprintf(buf, "%02d:%02d:%02d:%02d Elapsed: %08d", m_timer->pCurrentTime()->Hours, m_timer->pCurrentTime()->Minutes, m_timer->pCurrentTime()->Seconds, m_timer->pCurrentTime()->MilliSeconds, elapsedTime);
	//fprintf(stderr, buf);
	
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
		
		if(collisionType == COL_PATH)
			m_snide->Move(DIRECTION_UP);
		else
			m_snide->Face(DIRECTION_UP);
		
		if(collisionType >= COL_DOOR1 && collisionType <= COL_SECRET_PASSAGE)
		{
			CDoor* pDoor = m_currentRoom->GetDoor((int)collisionType);
			
			if(pDoor != NULL)
			{
				m_currentRoom = pDoor->pRoomOut();
				
				int xRoom = pDoor->pDoorOut()->X() - 128;
				
				int xChar = 128;
				int yChar = pDoor->pDoorOut()->Y() - CHARACTER_HEIGHT;
				
				if(xRoom + 256 > m_currentRoom->Width()) xRoom = m_currentRoom->Width() - 256;
				if(xRoom < 0) xRoom = 0;
			
				if(pDoor->pDoorOut()->X() < 128) xChar = pDoor->pDoorOut()->X();
				if(pDoor->pDoorOut()->X() > m_currentRoom->Width() - 128) xChar = 256 - (m_currentRoom->Width() - pDoor->pDoorOut()->X());	
				
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
		
		if(collisionType == COL_PATH)
			m_snide->Move(DIRECTION_DOWN);
		else
			m_snide->Face(DIRECTION_DOWN);
		
		if(collisionType >= COL_DOOR1 && collisionType <= COL_SECRET_PASSAGE)
		{
			CDoor* pDoor = m_currentRoom->GetDoor((int)collisionType);
			
			if(pDoor != NULL)
			{
				m_currentRoom = pDoor->pRoomOut();
			
				int xRoom = pDoor->pDoorOut()->X() - 128;
				
				int xChar = 128;
				int yChar = pDoor->pDoorOut()->Y() - CHARACTER_HEIGHT + 16;
				
				if(xRoom + 256 > m_currentRoom->Width()) xRoom = m_currentRoom->Width() - 256;
				if(xRoom < 0) xRoom = 0;
				
				if(pDoor->pDoorOut()->X() < 128) xChar = pDoor->pDoorOut()->X();
				if(pDoor->pDoorOut()->X() > m_currentRoom->Width() - 128) xChar = 256 - (m_currentRoom->Width() - pDoor->pDoorOut()->X());
				
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
		
		if(collisionType == COL_PATH)
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
		
		if(collisionType == COL_PATH)
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
	
	m_snide->Animate(m_elapsedTime);
	//m_characterArray[CHARACTER_GABRIEL]->Animate(elapsedTime);
	
	SortSprites();
	
	m_snide->Draw();
	//m_characterArray[CHARACTER_GABRIEL]->Draw();
	
	oamUpdate(&oamSub);
}

void CGame::SortSprites()
{
	for (int i=0; i < MAX_CHARACTERS; i++)
	{
		m_characterArray[i]->Hide();
		
		for(int j=0; j < MAX_CHARACTERS; j++)
		{
			if (m_characterArray[i]->Y() + CHARACTER_HEIGHT > m_characterArray[j]->Y() + CHARACTER_HEIGHT &&
				m_characterArray[i]->Priority() > m_characterArray[j]->Priority())
			{
				int temp = m_characterArray[i]->Priority();
				m_characterArray[i]->SetPriority(m_characterArray[j]->Priority());
				m_characterArray[j]->SetPriority(temp);
			}
		}
	}
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

void CGame::UpdateVBlank()
{
	m_fxManager.UpdateVBlank();
}

void CGame::UpdateHBlank()
{
	m_fxManager.UpdateHBlank();
}

void CGame::UpdateTimer1()
{
}

void CGame::UpdateTimer2()
{
	m_timer->Update();
}
