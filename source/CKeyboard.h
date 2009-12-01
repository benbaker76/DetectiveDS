#ifndef __CKEYBOARD_H__
#define __CKEYBOARD_H__

#include <nds.h>
#include "CCursor.h"

#define MAX_TEXT_ENTRY			30

#define KEYBOARD_LEFT		4
#define KEYBOARD_RIGHT		27
#define KEYBOARD_TOP		16
#define KEYBOARD_BOTTOM		23

class CKeyboard
{
public:
	CKeyboard(CCursor* pCursor);
	~CKeyboard();
	
	void Show(const char* string);
	void Hide();
	void DrawBox();
	char CheckKeyPress(int keys_released);
	char CheckKeyTouch(int x, int y);
	
	const char* GetText() const { return m_textEntry; }
	
private:

	CCursor* m_pCursor;
	
	int m_x;
	int m_y;
	
	u16* m_gfxBox;
	u16* m_gfxBoxLeft;
	u16* m_gfxBoxRight;

	int m_charPos;
	char m_textEntry[MAX_TEXT_ENTRY+1];
	
	void HideBox();
	char ProcessKey();
};

#endif
