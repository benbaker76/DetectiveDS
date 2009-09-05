#ifndef __CTEXTCONSOLE_H__
#define __CTEXTCONSOLE_H__

#include <nds.h>

#define CONSOLE_X		1
#define CONSOLE_Y		15
#define CONSOLE_WIDTH	19
#define CONSOLE_HEIGHT	8

#define MAX_TEXT_CONSOLE	CONSOLE_HEIGHT

#define CURSOR_FRAMES	4

class CTextConsole
{
public:
	CTextConsole();
	~CTextConsole();
	
	void ClearText();
	bool AddText(const char* text);
	void Update(int elapsedTime);
	
private:

	int m_lastUpdate;
	
	int m_cursorX;
	int m_cursorY;
	int m_cursorFrame;
	bool m_cursorPing;
	
	const char* m_charPos;
	u32 m_textPos;
	const char* m_textArray[MAX_TEXT_CONSOLE];
	
	void DrawCursor();
};

#endif
