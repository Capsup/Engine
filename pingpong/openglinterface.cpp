#include "openglinterface.h"


openglinterface::openglinterface()
{
}


openglinterface::~openglinterface()
{
}

bool openglinterface::CreateOGLWindow( int iWidth, int iHeight, bool bIsFullscreen, HINSTANCE hInstance )
{
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;

	m_WindowRect.left = 0;
	m_WindowRect.right = iWidth;
	m_WindowRect.top = 0;
	m_WindowRect.bottom = iHeight;

	AdjustWindowRectEx( &m_WindowRect, dwStyle, false, dwExStyle );

	m_WindowHandle = CreateWindowEx(
									dwExStyle,
									TEXT("OGLClass"),
									TEXT("Opengl Window"),
									dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
									0,
									0,
									m_WindowRect.right - m_WindowRect.left,
									m_WindowRect.bottom - m_WindowRect.top,
									NULL,
									NULL,
									hInstance,
									NULL
									);
	if( m_WindowHandle == NULL )
		return false;

	m_HandleDeviceContext = GetDC( m_WindowHandle );
	if( m_HandleDeviceContext == NULL )
		return false;

	PIXELFORMATDESCRIPTOR pfd;

	SetPixelFormat( m_HandleDeviceContext, 1, &pfd );

	m_hOpenGL = wglCreateContext( m_HandleDeviceContext );
	if( m_hOpenGL == NULL )
		return false;

	wglMakeCurrent( m_HandleDeviceContext, m_hOpenGL );

	/*LPSTR errorStr;

	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), 0, errorStr, 255, NULL);

	WCHAR pWideString[80];
	MultiByteToWideChar(CP_ACP,0,errorStr,-1,pWideString,80);

	MessageBoxW(NULL, pWideString, TEXT(""), MB_OK);  */

	//MessageBox( NULL, (LPCTSTR) tools::StringToWString(errorStr).c_str(), NULL, MB_OK );
	
	if( m_ExtMan.InitAPI() != true )
		return false;

	int pixAttribs[] = { WGL_SUPPORT_OPENGL_ARB, 1, // Must support OGL rendering
						 WGL_DRAW_TO_WINDOW_ARB, 1, // pf that can run a window
						 WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB, // must be HW accelerated
						 WGL_COLOR_BITS_ARB,     24, // 8 bits of each R, G and B
						 WGL_DEPTH_BITS_ARB,     16, // 16 bits of depth precision for window
						 WGL_DOUBLE_BUFFER_ARB,	 GL_TRUE, // Double buffered context
						 WGL_SAMPLE_BUFFERS_ARB, GL_TRUE, // MSAA on
						 WGL_SAMPLES_ARB,        8, // 8x MSAA 
						 WGL_PIXEL_TYPE_ARB,      WGL_TYPE_RGBA_ARB, // pf should be RGBA type
						 0}; // NULL termination
	int nPixCount = 0;
	int nPixelFormat  = -1;

	wglChoosePixelFormatARB( m_HandleDeviceContext, &pixAttribs[0], NULL, 1, &nPixelFormat, (UINT*) &nPixCount );
	
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( m_hOpenGL );
	ReleaseDC( m_WindowHandle, m_HandleDeviceContext );
	DestroyWindow( m_WindowHandle );

	if( bIsFullscreen )
	{
		DEVMODE dmSettings;

		memset( &dmSettings, 0, sizeof( dmSettings ) );
		dmSettings.dmSize = sizeof( dmSettings );

		dmSettings.dmPelsWidth = iWidth;         // screen width
		dmSettings.dmPelsHeight = iHeight;           // screen height
		dmSettings.dmBitsPerPel = 32;             // bits per pixel
		dmSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if( ChangeDisplaySettings( &dmSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
		{
			MessageBox(NULL, L"Display mode failed", NULL, MB_OK);
			return false;
			//m_isFullscreen = false;
		}
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor( false );
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	m_WindowHandle = CreateWindowEx(
									dwExStyle,
									TEXT("OGLClass"),
									TEXT("Opengl Window"),
									dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
									0,
									0,
									m_WindowRect.right - m_WindowRect.left,
									m_WindowRect.bottom - m_WindowRect.top,
									NULL,
									NULL,
									hInstance,
									NULL
									);
	if( m_WindowHandle == NULL )
		return false;

	ShowWindow( m_WindowHandle, SW_SHOW );

	m_HandleDeviceContext = GetDC( m_WindowHandle );
	
	int result = SetPixelFormat( m_HandleDeviceContext, nPixelFormat, &pfd );

	if( result == NULL )
	{
		return false;
	}

	m_hOpenGL = wglCreateContext( m_HandleDeviceContext );

	wglMakeCurrent( m_HandleDeviceContext, m_hOpenGL );

	return true;
}

bool openglinterface::Initialise()
{
	return true;
}

void openglinterface::GetError()
{
	return;
}

HDC openglinterface::GetHDC()
{
	if( m_HandleDeviceContext != NULL )
		return m_HandleDeviceContext;
}

HWND openglinterface::GetHWND()
{
	if( m_WindowHandle != NULL )
		return m_WindowHandle;
}

RECT openglinterface::GetRect()
{
		return m_WindowRect;
}