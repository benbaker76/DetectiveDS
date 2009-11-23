#ifndef __CFXRAT_H__
#define __CFXRAT_H__

#include "CFx.h"

#define MAX_POINTS 		4

class CFxRat : public CFx
{
public:

	CFxRat(FxType fxType, CFxManager* fxManager) : CFx(fxType, fxManager) { }
	~CFxRat() {}

	void Initialize();
	void Shutdown();
	void Reset();
	void UpdateVBlank();
	void UpdateHBlank();

	void SetXOffset(int xOffset) { m_xOffset = xOffset; }
	void SetPoints(Point* p1, Point* p2, Point* p3, Point* p4);

private:

	u16* m_gfx;
	
	DirectionType m_direction;
	
	PointF m_location;

	int m_frameNum;
	int m_frameCount;
	
	bool m_waiting;
	
	int m_pointPos;
	
	Point* m_pointArray[MAX_POINTS];

	int m_xOffset;

};

#endif