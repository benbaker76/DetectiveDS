#ifndef __CSELECTOR_H__
#define __CSELECTOR_H__

#include <nds.h>

class CSelector
{
public:
	CSelector();
	~CSelector();
	
	void SetPosition(float x, float y);
	void Hide();
	void Draw();
		
private:
	u16* m_gfxLeft;
	u16* m_gfxMiddle1;
	u16* m_gfxMiddle2;
	u16* m_gfxMiddle3;
	u16* m_gfxRight;
	
	float m_x;
	float m_y;
};

#endif
