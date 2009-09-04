#ifndef __CFX_H__
#define __CFX_H__

#define MAX_FX		32

enum FxType
{
	FX_FADE_BLACK_IN,
	FX_FADE_BLACK_OUT,
	FX_FADE_WHITE_IN,
	FX_FADE_WHITE_OUT,
	FX_LIGHTS_BLACK,
	FX_LIGHTS_BLACK_IN,
	FX_LIGHTS_BLACK_OUT,
	FX_LIGHTS_WHITE,
	FX_LIGHTS_WHITE_IN,
	FX_LIGHTS_WHITE_OUT,
	FX_TEXT_SCROLLER
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
