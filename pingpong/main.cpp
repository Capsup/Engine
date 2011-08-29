#pragma region Includes
#include "tools.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <GL/glext.h>
#include <GL/wglext.h>
//#include <cml/cml.h>
#include "ExtensionManager.h"
#include "keyboardinterface.h"
#include "game.h"
#include <string>
#include <time.h>



#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma endregion
/// Define a structure to hold all
/// of the global variables of this app.
struct Globals
{
	HINSTANCE hInstance;    // window app instance

	HWND hwnd;      // handle for the window

	HDC   hdc;      // handle to device context

	HGLRC hglrc;    // handle to OpenGL rendering context
	
	int width, height;      // the desired width and
	// height of the CLIENT AREA
	// (DRAWABLE REGION in Window)

	game game;

	/*camera camera;

	keyboardinterface keyboard;

	mouseinterface mouse;*/

};

#pragma region Globals and Prototypes
Globals g;

LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow );

#pragma endregion

#pragma region New WinMain
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow )
{
	std::string sGlobalPath = std::string(__argv[0]).substr(0, std::string(__argv[0]).rfind('\\') );
	SetCurrentDirectory( tools::StringToWString( sGlobalPath ).c_str() );
	//MessageBoxA( NULL, (LPCSTR) sGlobalPath.c_str(), "test" , MB_OK );

	g.hInstance = hInstance;

	WNDCLASS wc;
	wc.cbClsExtra = 0; 
	wc.cbWndExtra = 0; 
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );         
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );     
	wc.hInstance = hInstance;         
	wc.lpfnWndProc = WndProc;         
	wc.lpszClassName = TEXT("OGLClass");
	wc.lpszMenuName = 0; 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	RegisterClass(&wc);
	
	RECT rect;
	SetRect( &rect, 50,  // left
					50,  // top
					850, // right
					650 ); // bottom
	
	g.width = rect.right - rect.left;
	g.height = rect.bottom - rect.top;
	
	AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false);

	g.hwnd = CreateWindow(TEXT("OGLClass"),
						  TEXT("PingPong"),
						  WS_OVERLAPPEDWINDOW,
						  rect.left, rect.top,
						  rect.right - rect.left, rect.bottom - rect.top,
						  NULL, NULL,
						  hInstance, NULL);

	if( g.hwnd == NULL )
	{
		Err( TEXT("CreateWindow") );
	}

	g.hdc = GetDC( g.hwnd );

	PIXELFORMATDESCRIPTOR pfd;

	SetPixelFormat( g.hdc, 1, &pfd );

	g.hglrc = wglCreateContext( g.hdc );

	wglMakeCurrent( g.hdc, g.hglrc );

	ExtensionManager ExtMan;	

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

	wglChoosePixelFormatARB(g.hdc, &pixAttribs[0], NULL, 1, &nPixelFormat, (UINT*)&nPixCount);
	
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(g.hglrc);
	ReleaseDC(g.hwnd, g.hdc);
	DestroyWindow(g.hwnd);

	g.hwnd = CreateWindow(TEXT("OGLClass"),
						  TEXT("PingPong"),
						  WS_OVERLAPPEDWINDOW,
						  rect.left, 
						  rect.top,
						  rect.right - rect.left, 
						  rect.bottom - rect.top,
						  NULL, NULL,
						  hInstance, NULL);

	if( g.hwnd == NULL )
	{
		Err( TEXT("CreateWindow") );
	}

	ShowWindow( g.hwnd, iCmdShow );

	g.hdc = GetDC( g.hwnd );
	
	/*char b[100];
	sprintf(b, "ID# %d as pixelformat!\n", nPixelFormat);
	MessageBoxA( NULL, b, "Pixelformat", MB_OK );*/
	
	
	int result = SetPixelFormat( g.hdc, nPixelFormat, &pfd );

	if (result == NULL)
	{
		Err( TEXT("SetPixelFormat") );
	}
	
	g.hglrc = wglCreateContext( g.hdc );
	
	wglMakeCurrent( g.hdc, g.hglrc );

	if( ExtMan.InitAPI() != true )
		Err( TEXT("InitAPI") );
	
	/*char b[100];
	int attrib[] = { WGL_SAMPLES_ARB };
	int nResults = 0;
	wglGetPixelFormatAttribivARB( g.hdc, nPixelFormat, 0, 1, attrib, &nResults );
	sprintf(b, "Chosen pixel format is MSAA with %d samples.\n", nResults );
	MessageBoxA( NULL, b, "Chosen MSAA", MB_OK );*/

	g.game = game( g.hdc );

	MSG msg;

	DWORD current, last;

	

	while( true )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			if( msg.message == WM_QUIT )
			{
				break;
			}
			
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		last = current;
		current = GetTickCount();

		DWORD dt = current - last;
		
		g.game.Update( dt );
		g.game.Render();
		
	}

	AnimateWindow( g.hwnd, 200, AW_HIDE | AW_BLEND );
	
	return msg.wParam;
}
#pragma endregion



#pragma region WndProc Callback
LRESULT CALLBACK WndProc(   HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam ) 
{
	switch( message )
	{
	case WM_CREATE:
		return 0;
		break;

	case WM_PAINT:
		{
			HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint( hwnd, &ps );
				// don't draw here.  draw in the draw() function.
			EndPaint( hwnd, &ps );
		}
		//return 0;
		break;

	case WM_KEYDOWN:
		{
		unsigned int KeyCode = wparam;

		g.game.keyboard.Press( KeyCode );

		KeyEvent Event;
		Event.type = KeyEventPress;
		Event.iKeyCode = KeyCode;

		g.game.keyboard.InsertEvent( Event );

		//return 0;
		break;
		}
	case WM_KEYUP:
		{
		unsigned int KeyCode = wparam;

		g.game.keyboard.Release( KeyCode );

		KeyEvent Event;
		Event.type = KeyEventRelease;
		Event.iKeyCode = KeyCode;

		g.game.keyboard.InsertEvent( Event );

		//return 0;
		break;
		}
	case WM_CHAR:
		{
		KeyEvent Event;
		Event.type = KeyEventChar;
		Event.asciiCode = (char) wparam;

		if( Event.asciiCode != 0) 
		{
			g.game.keyboard.InsertEvent( Event );
		}
		break;
		}
	case WM_CLOSE:
		{
		PostQuitMessage( 0 ) ;
		return 0;
		break;
		}
	}
 
	return DefWindowProc( hwnd, message, wparam, lparam );
}
#pragma endregion