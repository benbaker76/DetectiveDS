#ifndef __CSPRITE_H__
#define __CSPRITE_H__

#include <nds.h>

#define MAX_SPRITES		24

enum FrameType
{
	FRAME_NONE = 0,
	FRAME_SPEAK = BIT(0),
	FRAME_LEFT = BIT(1),
	FRAME_RIGHT = BIT(2),
	FRAME_UP = BIT(3),
	FRAME_DOWN = BIT(4),
	FRAME_DEAD = BIT(5)
};

enum SpriteType
{
	SPRITE_SNIDE_HEAD,
	SPRITE_SNIDE_BODY,
	SPRITE_REVEREND_HEAD,
	SPRITE_REVEREND_BODY,
	SPRITE_BENTLEY_HEAD,
	SPRITE_BENTLEY_BODY,
	SPRITE_COOK_HEAD,
	SPRITE_COOK_BODY,
	SPRITE_GABRIEL_HEAD,
	SPRITE_GABRIEL_BODY,
	SPRITE_CYNTHIA_HEAD,
	SPRITE_CYNTHIA_BODY,
	SPRITE_PROFESSOR_HEAD,
	SPRITE_PROFESSOR_BODY,
	SPRITE_DOCTOR_HEAD,
	SPRITE_DOCTOR_BODY,
	SPRITE_MAJOR_HEAD,
	SPRITE_MAJOR_BODY,
	SPRITE_DINGLE_HEAD,
	SPRITE_DINGLE_BODY,
	SPRITE_ANGUS_HEAD,
	SPRITE_ANGUS_BODY,
	SPRITE_COL1,
	SPRITE_COL2
};

class CSprite
{
public:
	CSprite(SpriteType spriteType, const u32* pBmp, const int* frameArray, int frameCount);
	//CSprite(SpriteType spriteType, const u32* pTiles, int tilesLen, const u16* pPalette, int paletteLen, const int* frameArray, int frameCount);
	~CSprite();
	
	void SetPosition(float x, float y);
	void Animate(int elapsedTime);
	void Hide();
	void Draw();
	void SetFrameType(FrameType frameType);
	
	void SetOamIndex(int oamIndex) { m_oamIndex = oamIndex; }
	int OamIndex() const { return m_oamIndex; }
	
	void SetAlpha(int alpha) { m_alpha = alpha; }
	
	float X() const { return m_x; }
	float Y() const { return m_y; }

private:
	SpriteType m_spriteType;
	const u32* m_pBmp;
	//const u32* m_pTiles;
	//const u16* m_pPalette;
	
	//int m_tilesLen;
	//int m_paletteLen;
	
	const int* m_frameArray;
	FrameType m_frameType;
	int m_frameNum;
	int m_frameCount;
	int m_lastUpdate;
	
	int m_oamIndex;
	
	u16* m_gfxSub;
	
	float m_x;
	float m_y;
	
	int m_alpha;
};

#endif
