#include "keyboardinterface.h"


keyboardinterface::keyboardinterface()
{
	for( int i = 0; i < iMaxKeys; i++ )
	{
		m_KeyList[i] = 0;
	}
	m_iEventsAmount = 0;
}


keyboardinterface::~keyboardinterface()
{

}

void keyboardinterface::Press( unsigned int iKeyCode )
{
	if( iKeyCode > iMaxKeys || iKeyCode < 0 )
		return;
	m_KeyList[iKeyCode] = true;
}

void keyboardinterface::Release( unsigned int iKeyCode )
{
	if( iKeyCode > iMaxKeys || iKeyCode < 0 )
		return;
	m_KeyList[iKeyCode] = false;
}


bool keyboardinterface::IsPressed( unsigned int iKeyCode )
{
	return( m_KeyList[iKeyCode] );
}

KeyEvent keyboardinterface::GetNextEvent( KeyEvent& var )
{
	KeyEvent none;
	none.type = KeyEventNone;
	none.iKeyCode = 0;
	if( m_iEventsAmount < 1 )
		return none;
	if( m_KeyEventList[0].type == KeyEventNone )
	{
		for( int i = 0; i <= m_iEventsAmount - 1; ++i )
		{
			if( i != m_iEventsAmount - 1 )
				m_KeyEventList[i] = m_KeyEventList[i + 1];
			else
			{
				KeyEvent none;
				none.type = KeyEventNone;
				none.iKeyCode = 0;
				m_KeyEventList[m_iEventsAmount-1] = none;
				m_iEventsAmount--;
			}
		}
	}
	KeyEvent cur = m_KeyEventList[0];
	m_KeyEventList[0] = none;
	var = cur;
}

void keyboardinterface::InsertEvent( KeyEvent Event )
{
	if( m_iEventsAmount == iMaxEvents )
		return;
	m_KeyEventList[m_iEventsAmount] = Event;
	m_iEventsAmount++;
}

void keyboardinterface::ClearEvents()
{
	for( int i = 0; i <= m_iEventsAmount - 1; i++ )
	{
		KeyEvent none;
		none.type = KeyEventNone;
		m_KeyEventList[i] = none;
	}
}

void keyboardinterface::Clear()
{

}
