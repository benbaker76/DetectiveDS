#ifndef __CFxC64_H__
#define __CFxC64_H__

#include "CFx.h"

class CFxC64 : public CFx
{
public:

	CFxC64(FxType fxType, CFxManager* fxManager) : CFx(fxType, fxManager) { }
	~CFxC64() {}

	void Initialize();
	void Shutdown();
	void Reset();
	void UpdateVBlank();
	void UpdateHBlank();

private:

	u32 m_colorWait;
	u32 m_colorOffset;
};

#endif
