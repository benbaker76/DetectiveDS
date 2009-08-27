#ifndef __CSPRITE_H__
#define __CSPRITE_H__

#include <nds.h>

#define MAX_SPRITES		64

enum AnimationType
{
	ANIMATION_NONE,
	ANIMATION_WALKING,
	ANIMATION_TALKING,
	ANIMATION_DEAD
};

enum FrameType
{
	FRAME_NONE = 0,
	FRAME_SPEAK = 0x1,
	FRAME_LEFT = 0x2,
	FRAME_RIGHT = 0x4,
	FRAME_UP = 0x8,
	FRAME_DOWN = 0x10,
	FRAME_DEAD = 0x20
};

enum SpriteType
{
	SPRITE_HEAD_SNIDE = 2,
	SPRITE_BODY_SNIDE,
	SPRITE_HEAD_REVEREND,
	SPRITE_BODY_REVEREND,
	SPRITE_HEAD_BENTLEY,
	SPRITE_BODY_BENTLEY,
	SPRITE_HEAD_COOK,
	SPRITE_BODY_COOK,
	SPRITE_HEAD_GABRIEL,
	SPRITE_BODY_GABRIEL,
	SPRITE_HEAD_CYNTHIA,
	SPRITE_BODY_CYNTHIA,
	SPRITE_HEAD_PROFESSOR,
	SPRITE_BODY_PROFESSOR,
	SPRITE_HEAD_DOCTOR,
	SPRITE_BODY_DOCTOR,
	SPRITE_HEAD_MAJOR,
	SPRITE_BODY_MAJOR,
	SPRITE_HEAD_DINGLE,
	SPRITE_BODY_DINGLE,
	SPRITE_COL1,
	SPRITE_COL2
};

class CSprite
{
public:
	CSprite(SpriteType spriteType, const u32* pTiles, int tilesLen, const u16* pPalette, int paletteLen, const int* frameArray, int frameCount);
	~CSprite();
	
	void SetPosition(int x, int y);
	void Animate(int elapsedTime);
	void Hide();
	void Draw();
	void SetFrameType(FrameType frameType);
	
	void SetOamIndex(int oamIndex) { m_oamIndex = oamIndex; }
	int OamIndex() const { return m_oamIndex; }
	
	int X() const { return m_x; }
	int Y() const { return m_y; }

private:
	SpriteType m_spriteType;
	const u32* m_pTiles;
	const u16* m_pPalette;
	
	int m_tilesLen;
	int m_paletteLen;
	
	const int* m_frameArray;
	FrameType m_frameType;
	int m_frameNum;
	int m_frameCount;
	int m_lastUpdate;
	
	int m_oamIndex;
	
	u16* m_gfx;
	u16* m_gfxSub;
	
	CSprite* m_pSprite;
	
	int m_x;
	int m_y;
};

#endif
