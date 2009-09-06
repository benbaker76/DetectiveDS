#ifndef __CTEXTCONSOLE_H__
#define __CTEXTCONSOLE_H__

#include <nds.h>
#include "CCursor.h"

#define CONSOLE_X		1
#define CONSOLE_Y		15
#define CONSOLE_WIDTH	19
#define CONSOLE_HEIGHT	8

#define MAX_TEXT_CONSOLE	CONSOLE_HEIGHT

class CTextConsole
{
public:
	CTextConsole(CCursor* pCursor);
	~CTextConsole();
	
	void ClearText();
	bool AddText(const char* text);
	void Update(int elapsedTime);
	
private:
	CCursor* m_pCursor;
	
	int m_x;
	int m_y;

	int m_lastUpdate;
	
	const char* m_charPos;
	u32 m_textPos;
	const char* m_textArray[MAX_TEXT_CONSOLE];
};

#endif
