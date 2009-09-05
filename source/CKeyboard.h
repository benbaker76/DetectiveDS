#ifndef __CKEYBOARD_H__
#define __CKEYBOARD_H__

#include <nds.h>

#define MAX_TEXT_ENTRY	30

class CKeyboard
{
public:
	CKeyboard();
	~CKeyboard();
	
	void Initialize();
	void Shutdown();
	void CheckKeyTouch(int touchX, int touchY);
	
private:

	int m_charPos;
	char m_textEntry[MAX_TEXT_ENTRY+1];
};

#endif
