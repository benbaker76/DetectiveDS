#ifndef __CPOINTER_H__
#define __CPOINTER_H__

#include <nds.h>

#define POINTER_X		13
#define POINTER_Y		3
#define POINTER_WIDTH	23
#define POINTER_HEIGHT	17

#define POINTER_SPEED	0.05

class CPointer
{
public:
	CPointer();
	~CPointer();
	
	void Move(int keys_held);
	void Hide();
	void Update();
	
	void SetRect(int x, int y, int width, int height) { m_x = x; m_y = y + 4; m_rect.X = x; m_rect.Y = y; m_rect.Width = width; m_rect.Height = height; SetPoint(m_x, m_y); }
	PRECT pRect() { return (PRECT) &m_rect; }
	
	void SetPoint(int x, int y) { m_point.X = x; m_point.Y = y; }
	PPOINT pPoint() { SetPoint(m_x + POINTER_X, m_y + POINTER_Y); return (PPOINT) &m_point; }
		
private:
	u16* m_gfx;
	
	float m_x;
	float m_y;
	
	POINT m_point;
	RECT m_rect;
	
	float m_speed[4];
};

#endif
