#ifndef __CKEYBOARD_H__
#define __CKEYBOARD_H__

#include <nds.h>
#include "CCursor.h"

#define MAX_TEXT_ENTRY	30

class CKeyboard
{
public:
	CKeyboard(CCursor* pCursor);
	~CKeyboard();
	
	void Show(const char* string);
	void Hide();
	char CheckKeyTouch(int x, int y);
	
	const char* GetText() const { return m_textEntry; }
	
private:

	CCursor* m_pCursor;

	int m_charPos;
	char m_textEntry[MAX_TEXT_ENTRY+1];
};

#endif
