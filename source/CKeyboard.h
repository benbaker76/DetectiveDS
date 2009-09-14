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
	
	void Initialize();
	void Shutdown();
	void CheckKeyTouch(int x, int y);
	
private:

	CCursor* m_pCursor;

	int m_charPos;
	char m_textEntry[MAX_TEXT_ENTRY+1];
};

#endif
