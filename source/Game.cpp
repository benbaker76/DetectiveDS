#include <stdio.h>
#include "Game.h"
#include "TDG.h"

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
		
		m_mapArray[MAP_CELLAR] = new CMap(400, 120, map_cellarTiles, map_cellarTilesLen, map_cellarMap, map_cellarMapLen, map_cellarPal, map_cellarPalLen);
		m_mapArray[MAP_CLOCK] = new CMap(304, 120, map_clockTiles, map_clockTilesLen, map_clockMap, map_clockMapLen, map_clockPal, map_clockPalLen);
		m_mapArray[MAP_DRAWING] = new CMap(640, 120, map_drawingTiles, map_drawingTilesLen, map_drawingMap, map_drawingMapLen, map_drawingPal, map_drawingPalLen);
		m_mapArray[MAP_HALL1] = new CMap(832, 120, map_hall1Tiles, map_hall1TilesLen, map_hall1Map, map_hall1MapLen, map_hall1Pal, map_hall1PalLen);
		m_mapArray[MAP_HALL2] = new CMap(832, 120, map_hall2Tiles, map_hall2TilesLen, map_hall2Map, map_hall2MapLen, map_hall2Pal, map_hall2PalLen);
		m_mapArray[MAP_HALL3] = new CMap(832, 120, map_hall3Tiles, map_hall3TilesLen, map_hall3Map, map_hall3MapLen, map_hall3Pal, map_hall3PalLen);
		m_mapArray[MAP_HALL4] = new CMap(544, 120, map_hall4Tiles, map_hall4TilesLen, map_hall4Map, map_hall4MapLen, map_hall4Pal, map_hall4PalLen);
		m_mapArray[MAP_KITCHEN] = new CMap(536, 120, map_kitchenTiles, map_kitchenTilesLen, map_kitchenMap, map_kitchenMapLen, map_kitchenPal, map_kitchenPalLen);
		m_mapArray[MAP_LANDING] = new CMap(400, 120, map_landingTiles, map_landingTilesLen, map_landingMap, map_landingMapLen, map_landingPal, map_landingPalLen);
		m_mapArray[MAP_LIBRARY] = new CMap(416, 120, map_libraryTiles, map_libraryTilesLen, map_libraryMap, map_libraryMapLen, map_libraryPal, map_libraryPalLen);
		m_mapArray[MAP_OUTSIDE1] = new CMap(400, 120, map_outside1Tiles, map_outside1TilesLen, map_outside1Map, map_outside1MapLen, map_outside1Pal, map_outside1PalLen);
		m_mapArray[MAP_OUTSIDE2] = new CMap(544, 120, map_outside2Tiles, map_outside2TilesLen, map_outside2Map, map_outside2MapLen, map_outside2Pal, map_outside2PalLen);
		m_mapArray[MAP_PASSAGE1] = new CMap(240, 120, map_passage1Tiles, map_passage1TilesLen, map_passage1Map, map_passage1MapLen, map_passage1Pal, map_passage1PalLen);
		m_mapArray[MAP_PASSAGE2] = new CMap(240, 120, map_passage2Tiles, map_passage2TilesLen, map_passage2Map, map_passage2MapLen, map_passage2Pal, map_passage2PalLen);
		m_mapArray[MAP_ROOM1] = new CMap(400, 120, map_room1Tiles, map_room1TilesLen, map_room1Map, map_room1MapLen, map_room1Pal, map_room1PalLen);
		m_mapArray[MAP_ROOM2] = new CMap(344, 120, map_room2Tiles, map_room2TilesLen, map_room2Map, map_room2MapLen, map_room2Pal, map_room2PalLen);
		m_mapArray[MAP_STAIRS] = new CMap(336, 120, map_stairsTiles, map_stairsTilesLen, map_stairsMap, map_stairsMapLen, map_stairsPal, map_stairsPalLen);
		m_mapArray[MAP_STUDY] = new CMap(320, 120, map_studyTiles, map_studyTilesLen, map_studyMap, map_studyMapLen, map_studyPal, map_studyPalLen);
		
		m_roomArray[ROOM_SNIDE] = new CRoom(ROOM_SNIDE, m_mapArray[MAP_ROOM1]);
		m_roomArray[ROOM_REVEREND] = new CRoom(ROOM_REVEREND, m_mapArray[MAP_ROOM1]);
		m_roomArray[ROOM_BENTLEY] = new CRoom(ROOM_BENTLEY, m_mapArray[MAP_ROOM1]);
		m_roomArray[ROOM_COOK] = new CRoom(ROOM_COOK, m_mapArray[MAP_ROOM1]);
		m_roomArray[ROOM_GABRIEL] = new CRoom(ROOM_GABRIEL, m_mapArray[MAP_ROOM1]);
		m_roomArray[ROOM_CYNTHIA] = new CRoom(ROOM_CYNTHIA, m_mapArray[MAP_ROOM1]);
		m_roomArray[ROOM_PROFESSOR] = new CRoom(ROOM_PROFESSOR, m_mapArray[MAP_ROOM1]);
		m_roomArray[ROOM_DOCTOR] = new CRoom(ROOM_DOCTOR, m_mapArray[MAP_ROOM1]);		
		m_roomArray[ROOM_MAJOR] = new CRoom(ROOM_MAJOR, m_mapArray[MAP_ROOM1]);
		m_roomArray[ROOM_DINGLE] = new CRoom(ROOM_DINGLE, m_mapArray[MAP_ROOM1]);
		m_roomArray[ROOM_OUTSIDE1] = new CRoom(ROOM_OUTSIDE1, m_mapArray[MAP_OUTSIDE1]);
		m_roomArray[ROOM_OUTSIDE2] = new CRoom(ROOM_OUTSIDE2, m_mapArray[MAP_OUTSIDE2]);
		m_roomArray[ROOM_OUTSIDE3] = new CRoom(ROOM_OUTSIDE3, m_mapArray[MAP_OUTSIDE1]);
		m_roomArray[ROOM_OUTSIDE4] = new CRoom(ROOM_OUTSIDE4, m_mapArray[MAP_OUTSIDE2]);
		m_roomArray[ROOM_OUTSIDE5] = new CRoom(ROOM_OUTSIDE5, m_mapArray[MAP_OUTSIDE1]);
		m_roomArray[ROOM_PASSAGE1] = new CRoom(ROOM_PASSAGE1, m_mapArray[MAP_PASSAGE1]);
		m_roomArray[ROOM_PASSAGE2] = new CRoom(ROOM_PASSAGE2, m_mapArray[MAP_PASSAGE2]);
		m_roomArray[ROOM_PASSAGE3] = new CRoom(ROOM_PASSAGE3, m_mapArray[MAP_PASSAGE1]);
		m_roomArray[ROOM_HALL1] = new CRoom(ROOM_HALL1, m_mapArray[MAP_HALL1]);
		m_roomArray[ROOM_HALL2] = new CRoom(ROOM_HALL1, m_mapArray[MAP_HALL2]);
		m_roomArray[ROOM_HALL3] = new CRoom(ROOM_HALL1, m_mapArray[MAP_HALL3]);
		m_roomArray[ROOM_HALL4] = new CRoom(ROOM_HALL1, m_mapArray[MAP_HALL4]);
		m_roomArray[ROOM_LANDING] = new CRoom(ROOM_LANDING, m_mapArray[MAP_LANDING]);
		m_roomArray[ROOM_KITCHEN] = new CRoom(ROOM_KITCHEN, m_mapArray[MAP_KITCHEN]);
		m_roomArray[ROOM_STAIRS] = new CRoom(ROOM_STAIRS, m_mapArray[MAP_STAIRS]);
		m_roomArray[ROOM_STUDY] = new CRoom(ROOM_STUDY, m_mapArray[MAP_STUDY]);
		m_roomArray[ROOM_CLOCK] = new CRoom(ROOM_CLOCK, m_mapArray[MAP_CLOCK]);
		m_roomArray[ROOM_CELLAR] = new CRoom(ROOM_CELLAR, m_mapArray[MAP_CELLAR]);
		m_roomArray[ROOM_DRAWING] = new CRoom(ROOM_DRAWING, m_mapArray[MAP_DRAWING]);
		m_roomArray[ROOM_LIBRARY] = new CRoom(ROOM_LIBRARY, m_mapArray[MAP_LIBRARY]);
		
		m_eventArray[EVENT_SHOW_ROOM] = new CEvent(EVENT_SHOW_ROOM, new CTime(0, 0, 5, 0));
		break;
	}
	
	m_mapArray[MAP_HALL1]->Draw();
	
	m_characterArray[CHARACTER_SNIDE]->SetPosition(128, 64);
	m_characterArray[CHARACTER_GABRIEL]->SetPosition(64, 64);
	
	m_characterArray[CHARACTER_GABRIEL]->SetFrameType(FRAME_SPEAK);
}

void CGame::Update(int elapsedTime, CTime* pCurrentTime)
{
	touchPosition touch;
	int key;
	
	touchRead(&touch);
	scanKeys();
	key = keysHeld();
	
	//char buf[256];
	//sprintf(buf, "%02d:%02d:%02d:%02d Elapsed: %08d", pCurrentTime->Hours, pCurrentTime->Minutes, pCurrentTime->Seconds, pCurrentTime->MilliSeconds, elapsedTime);
	//fprintf(stderr, buf);
	
	for(int i=0; i<MAX_EVENTS; i++)
	{
		if(m_eventArray[i] != NULL)
		{
			if(m_eventArray[i]->Update(pCurrentTime))
			{
				m_eventArray[i] = NULL;
				//fprintf(stderr,"Event!");
			}
		}
	}
	
	m_bg2VScroll--;
	BACKGROUND.scroll[2].y = m_bg2VScroll;
	
	if(keysHeld() & KEY_UP)
	{
		if(m_characterArray[CHARACTER_SNIDE]->Y() > 76 - CHARACTER_HEIGHT)
			m_characterArray[CHARACTER_SNIDE]->Move(DIRECTION_UP);
		else
			m_characterArray[CHARACTER_SNIDE]->Face(DIRECTION_UP);
	}
	else if(keysHeld() & KEY_DOWN)
	{
		if(m_characterArray[CHARACTER_SNIDE]->Y() < 112 - CHARACTER_HEIGHT)
			m_characterArray[CHARACTER_SNIDE]->Move(DIRECTION_DOWN);
		else
			m_characterArray[CHARACTER_SNIDE]->Face(DIRECTION_DOWN);
	}
	else if(keysHeld() & KEY_LEFT)
	{
		// Unfortunately this doesn't seem to work after I added back the "scroll to the edge" code from last night
		// So we will have to come up with a new way of dealing with the angle
		// Right now though I'm concentrating on getting the level to scroll properly
		// Believe it or not it's a total pain in the arse reminiciant of the double screen
		// vertical scrolling in Warhawk.
		
		//if(m_characterArray[CHARACTER_SNIDE]->X() > (128-(m_characterArray[CHARACTER_SNIDE]->Y()-(112 - CHARACTER_HEIGHT))))
		
		if(m_characterArray[CHARACTER_SNIDE]->X() > 128)
			m_characterArray[CHARACTER_SNIDE]->Move(DIRECTION_LEFT);
		else
		{
			m_characterArray[CHARACTER_SNIDE]->Face(DIRECTION_LEFT);
			
			if(!m_mapArray[MAP_HALL1]->Scroll(DIRECTION_LEFT) && m_characterArray[CHARACTER_SNIDE]->X() > 0)
				m_characterArray[CHARACTER_SNIDE]->Move(DIRECTION_LEFT);
		}
	}
	else if(keysHeld() & KEY_RIGHT)
	{
		//if(m_characterArray[CHARACTER_SNIDE]->X() < (128+(m_characterArray[CHARACTER_SNIDE]->Y()-(112 - CHARACTER_HEIGHT))))
		
		if(m_characterArray[CHARACTER_SNIDE]->X() < 128)
			m_characterArray[CHARACTER_SNIDE]->Move(DIRECTION_RIGHT);
		else
		{
			m_characterArray[CHARACTER_SNIDE]->Face(DIRECTION_RIGHT);
			
			if(!m_mapArray[MAP_HALL1]->Scroll(DIRECTION_RIGHT) && m_characterArray[CHARACTER_SNIDE]->X() < 256 - CHARACTER_WIDTH)
				m_characterArray[CHARACTER_SNIDE]->Move(DIRECTION_RIGHT);
		}
	}
	else if(keysHeld() & KEY_A)
	{
		m_characterArray[CHARACTER_SNIDE]->SetFrameType(FRAME_SPEAK);
	}
	else
	{
		m_characterArray[CHARACTER_SNIDE]->SetFrameType(FRAME_NONE);
	}
	
	m_characterArray[CHARACTER_SNIDE]->Animate(elapsedTime);
	m_characterArray[CHARACTER_GABRIEL]->Animate(elapsedTime);
	
	SortSprites();
	
	m_characterArray[CHARACTER_SNIDE]->Draw();
	m_characterArray[CHARACTER_GABRIEL]->Draw();
	
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
