#ifndef __CWATCH_H__
#define __CWATCH_H__

#include <nds.h>

class CWatch
{
public:
	CWatch(int x, int y);
	~CWatch();
	
	void SetPosition(float x, float y);
	void Hide();
	void Draw(CTime* pTime);

private:
	u16* m_gfxHours;
	u16* m_gfxMinutes;
	u16* m_gfxSeconds;
	
	CWatch* m_pSprite;
	
	float m_x;
	float m_y;
};

#endif
