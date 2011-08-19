#pragma once

const int iMaxEvents = 128;
const int iMaxKeys = 512;

enum EnumKeyEventType
{
	KeyEventNone = 0,
	KeyEventPress = 1,
	KeyEventRelease = 2,
	KeyEventChar = 4,
	KeyEventAny = 8
};

struct KeyEvent
{
	EnumKeyEventType type;

	union
	{
		unsigned int iKeyCode;
		char asciiCode;
	};
};

class keyboardinterface
{
public:
	keyboardinterface();
	~keyboardinterface();
	void Press( unsigned int iKeyCode );
	void Release( unsigned int iKeyCode );
	bool IsPressed( unsigned int iKeyCode );
	KeyEvent GetNextEvent( KeyEvent& var );
	void InsertEvent( KeyEvent Event );
	void ClearEvents();
	void Clear();
private:

	int m_KeyList[iMaxKeys];
	int m_iEventsAmount;
	KeyEvent m_KeyEventList[iMaxEvents];
};

