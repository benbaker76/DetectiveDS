#ifndef __CFX_H__
#define __CFX_H__

#define MAX_FX		32

enum FxType
{
	FX_FADE_BLACK_IN = 0,
	FX_FADE_BLACK_OUT = 1,
	FX_FADE_WHITE_IN = 2,
	FX_FADE_WHITE_OUT = 3,
	FX_LIGHTS = 4
};

class CFxManager;

class CFx
{
public:
	CFx(FxType fxType, CFxManager* fxManager);
	~CFx();
	
	virtual void Initialize();
	virtual void Shutdown();
	virtual void UpdateVBlank();
	virtual void UpdateHBlank();
	
	FxType GetFxType() const { return m_fxType; };
	bool Enabled() const { return m_enabled; };
	CFxManager* FxManager() const { return m_fxManager; };
	
	void SetEnabled(bool state) { (state ? Initialize() : Shutdown()); m_enabled = state; }

private:

	FxType m_fxType;
	CFxManager* m_fxManager;
	bool m_enabled;
};

#endif
