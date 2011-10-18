#pragma once

#include "tools.h"
#include "ExtensionManager.h"
#include <Windows.h>

class openglinterface
{
public:
	openglinterface();
	~openglinterface();
	bool CreateOGLWindow( int iWidth, int iHeight, bool bIsFullscreen, HINSTANCE hInstance );
	bool Initialise();
	void GetError();
	HDC GetHDC();
	HWND GetHWND();
	RECT GetRect();
private:
	/*int m_iWindowWidth;
	int m_iWindowHeight;*/
	RECT m_WindowRect;
	HWND m_WindowHandle;
	HDC m_HandleDeviceContext;
	HGLRC m_hOpenGL;
	ExtensionManager m_ExtMan;
};

