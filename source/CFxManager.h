#ifndef __CFXMANAGER_H__
#define __CFXMANAGER_H__

#include "CFx.h"
#include "CFxFade.h"
#include "CFxTextScroller.h"

class CFxManager
{
public:
	CFxManager();
	~CFxManager();
	
	void Initialize();
	void FxOff();
	void UpdateVBlank();
	void UpdateHBlank();
	
	void SetFx(FxType fxType, FxMode fxMode, bool state) { m_fxArray[fxType]->SetEnabled(fxMode, state); }
	CFx* GetFx(FxType fxType) { return m_fxArray[fxType]; }

private:

	CFx* m_fxArray[MAX_FX];
};

#endif
