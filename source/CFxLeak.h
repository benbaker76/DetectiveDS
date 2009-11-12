#ifndef __CFXLEAK_H__
#define __CFXLEAK_H__

#include "CFx.h"

class CFxLeak : public CFx
{
public:

	CFxLeak(FxType fxType, CFxManager* fxManager) : CFx(fxType, fxManager) { }
	~CFxLeak() {}

	void Initialize();
	void Shutdown();
	void Reset();
	void UpdateVBlank();
	void UpdateHBlank();

	void SetXOffset(int xOffset) { m_xOffset = xOffset; }
	void SetLocation(int xStart, int yStart, int xEnd, int yEnd);

private:

	u16* m_gfx;
	
	Point m_location;
	
	Point m_startPoint;
	Point m_endPoint;
	
	int m_frameNum;
	int m_frameRate;
	int m_frameCount;
	
	bool m_waiting;

	int m_xOffset;
};

#endif