#ifndef __CFXMANAGER_H__
#define __CFXMANAGER_H__

#include "CFx.h"

class CFxManager
{
public:
	CFxManager();
	~CFxManager();
	
	void Initialize();
	void FxOff();
	void UpdateVBlank();
	void UpdateHBlank();
	
	void SetFx(int fxType, bool state) { m_fxArray[fxType]->SetEnabled(state); }
	CFx* GetFx(int fxType) { return m_fxArray[fxType]; }

private:

	CFx* m_fxArray[MAX_FX];
};

#endif
