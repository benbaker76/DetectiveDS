#ifndef __CCURSOR_H__
#define __CCURSOR_H__

#include "CAnimation.h"

#define CURSOR_FRAMES	4

class CCursor
{
public:
	CCursor();
	~CCursor();
	
	void SetPosition(int x, int y) { m_x = x; m_y = y; }
	void SetX(int x) { m_x = x; }
	void SetY(int y) { m_y = y; }
	
	float X() const { return m_x; }
	float Y() const { return m_y; }
	
	void Draw();
	void Update();
	
private:
	int m_x;
	int m_y;
	
	CAnimation* m_anim;
};

#endif
