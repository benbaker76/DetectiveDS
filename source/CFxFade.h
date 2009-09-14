#ifndef __CFXFADE_H__
#define __CFXFADE_H__

#include "CFx.h"

class CFxFade : public CFx
{
public:

	CFxFade(FxType fxType, CFxManager* fxManager) : CFx(fxType, fxManager) { }
	~CFxFade() {}

	void Initialize();
	void Shutdown();
	void UpdateVBlank();
	void UpdateHBlank();

private:

	u16 m_fadeValue;
	bool m_lightsEnabled;
};

class CFxLights : public CFx
{
public:

	CFxLights(FxType fxType, CFxManager* fxManager) : CFx(fxType, fxManager) {}
	~CFxLights() {}

	void Initialize();
	void Shutdown();
	void UpdateVBlank();
	void UpdateHBlank();

private:

	u16 m_map_light[SCREEN_HEIGHT];
	u16 m_map_mix[SCREEN_HEIGHT];
	u16 m_fadeValue; 
};

class CFxColourPulse : public CFx
{
public:

	CFxColourPulse(FxType fxType, CFxManager* fxManager) : CFx(fxType, fxManager) {}
	~CFxColourPulse() {}

	void Initialize();
	void Shutdown();
	void UpdateVBlank();
	void UpdateHBlank();

private:

	bool m_ping;

	u8 m_fadeValue; 
};

#endif
