#ifndef __CFXTEXTSCROLLER_H__
#define __CFXTEXTSCROLLER_H__

#include "CFx.h"

#define MAX_TEXT_SCROLLER	8

class CFxTextScroller : public CFx
{
public:

	CFxTextScroller(FxType fxType, CFxManager* fxManager) : CFx(fxType, fxManager) { }
	~CFxTextScroller() {}

	void Initialize();
	void Shutdown();
	void UpdateVBlank();
	void UpdateHBlank();
	
	void ClearText();
	bool AddText(const char* text);
	void SetLoop(bool loop) { m_loop = loop; }
	
	bool ScrollerEmpty() const { return (m_textArray[m_textPos] == NULL); }

private:

	//u16 m_scrollPos;
	u8 m_scrollPos;
	const char* m_charPos;
	u32 m_textPos;
	const char* m_textArray[MAX_TEXT_SCROLLER];
	
	u32 m_loop;
};

#endif
