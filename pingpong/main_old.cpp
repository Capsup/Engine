#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <GL/glext.h>
#include <GL/wglext.h>
//#include "extensions.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

struct Globals
{
	HINSTANCE hInstance;    // window app instance

	HWND hWnd;      // handle for the window

	HDC   hdc;      // handle to device context

	HGLRC hglrc;    // handle to OpenGL rendering context
	
	int width, height;      // the desired width and
	// height of the CLIENT AREA
	// (DRAWABLE REGION in Window)
};

Globals g;

bool SetupWindow( int iWidth, int iHeight, bool bFS );
bool ChoosePFWindow( HWND hWnd );
LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow );
void draw(); 

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow )
{
	g.hInstance = hInstance;
	SetupWindow( g.width, g.height, false );
	ChoosePFWindow( g.hWnd );

	MSG msg;

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

		//6.  DRAW USING OPENGL.
		// This region right here is the
		// heart of our application.  THE MOST
		// execution time is spent just repeating
		// this draw() function.
		draw();
		
	}

	return 0;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam ) 
{
	switch( message )
	{
	case WM_CREATE:
		//Beep( 50, 10 );
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
		return 0;
		break;

	case WM_KEYDOWN:
		switch( wparam )
		{
		case VK_ESCAPE:
			PostQuitMessage( 0 );
			break;
		default:
			break;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage( 0 ) ;
		return 0;
		break;
	}
 
	return DefWindowProc( hwnd, message, wparam, lparam );
}

/*bool SetupWindow( int iWidth, int iHeight, bool bFS )
{
	int nWindowX = 0;
	int nWindowY = 0;

	DWORD dwExtStyle;
	DWORD dwWindStyle;

	//g.hInstance = GetModuleHandle(NULL);

	WNDCLASS wc;
	wc.cbClsExtra = 0; 
	wc.cbWndExtra = 0; 
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );         
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );     
	wc.hInstance = g.hInstance;         
	wc.lpfnWndProc = WndProc;         
	wc.lpszClassName = TEXT("OGLClas");
	wc.lpszMenuName = 0; 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	if( !RegisterClass(&wc) )
		FatalAppExit( NULL, TEXT("Failed to register class!" ) );

	dwExtStyle  = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	dwWindStyle = WS_OVERLAPPEDWINDOW;
	ShowCursor(TRUE);

	RECT rect;

	SetRect( &rect, 50,  // left
					50,  // top
					850, // right
					650 ); // bottom
	/*rect.left   = nWindowX;
	rect.right  = nWindowX + iWidth;
	rect.top    = nWindowY;
	rect.bottom = nWindowY + iHeight;

	// Setup window width and height
	//AdjustWindowRectEx(&rect, dwWindStyle, FALSE, dwExtStyle);

	//Adjust for adornments
	int nWindowWidth = rect.right   - rect.left;
	int nWindowHeight = rect.bottom - rect.top;

	AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false);

	// Create window
	g.hWnd = CreateWindowEx(dwExtStyle,     // Extended style
							TEXT("OGL_CLASS"),    // class name
							TEXT("PingPong"),   // window name
							dwWindStyle |        
							WS_CLIPSIBLINGS | 
							WS_CLIPCHILDREN,// window stlye
							nWindowX,       // window position, x
							nWindowY,       // window position, y
							nWindowWidth,   // height
							nWindowHeight,  // width
							NULL,           // Parent window
							NULL,           // menu
							g.hInstance,    // instance
							NULL);          // pass this to WM_CREATE

	if( g.hWnd == NULL )
	{
		FatalAppExit( NULL, TEXT("Application fuck up - CreateWindow() failed!") );
	}

	g.hdc = GetDC( g.hWnd );

	return 0;
}*/
bool SetupWindow( int iWidth, int iHeight, bool bUseFS )
{

	#pragma region part 1 - create a window
	// The next few lines you should already
	// be used to:  create a WNDCLASS
	// that describes the properties of
	// the window we're going to soon create.
	// A.  Create the WNDCLASS
	WNDCLASS wc;
	wc.cbClsExtra = 0; 
	wc.cbWndExtra = 0; 
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );         
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );     
	wc.hInstance = g.hInstance;         
	wc.lpfnWndProc = WndProc;         
	wc.lpszClassName = TEXT("Philip");
	wc.lpszMenuName = 0; 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	// Register that class with the Windows O/S..
	RegisterClass(&wc);
	
	/////////////////
	// Ok, AT THIS POINT, we'd normally
	// just go ahead and call CreateWindow().
	// And we WILL call CreateWindow(), but
	// there is something I must explain to
	// you first.  That thing is the RECT structure.

	/////////////////
	// RECT:
	//
	// A RECT is just a C struct meant to represent
	// a rectangle.
	// 
	// The RECT structure WILL DESCRIBE EXACTLY WHERE
	// AND HOW WE WANT OUR WINDOW TO APPEAR WHEN WE
	// CREATE IT.
	//
	//         TOP
	//       --------
	//       |      |
	// LEFT  |      | RIGHT
	//       --------
	//        BOTTOM
	//
	// So, what we do is, we create the RECT
	// struct for our window as follows:
	RECT rect;
	SetRect( &rect, 50,  // left
					50,  // top
					850, // right
					650 ); // bottom
	
	// Save width and height off.
	g.width = rect.right - rect.left;
	g.height = rect.bottom - rect.top;
	
	// Adjust it.
	AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false);

	// AdjustWindowRect() expands the RECT
	// so that the CLIENT AREA (drawable region)
	// has EXACTLY the dimensions we specify
	// in the incoming RECT.

	// If you didn't just understand that, understand
	// this:  "you have to call AdjustWindowRect()",
	// and move on.  Its not THAT important, but its
	// good for the performance of your app.

	///////////////////
	// NOW we call CreateWindow, using
	// that adjusted RECT structure to
	// specify the width and height of the window.
	g.hWnd = CreateWindow(TEXT("Philip"),
						  TEXT("GL WINDOW!"),
						  WS_OVERLAPPEDWINDOW,
						  rect.left, rect.top,
						  rect.right - rect.left, rect.bottom - rect.top,
						  NULL, NULL,
						  g.hInstance, NULL);

	// check to see that the window
	// was created successfully!
	if( g.hWnd == NULL )
	{
		FatalAppExit( NULL, TEXT("Application fuck up - CreateWindow() failed!") );
	}
	return 0;
}
//bool ChoosePFWindow( HWND hWnd, HGLRC& r_hRC )
bool ChoosePFWindow( HWND hWnd )
{
	int nPixelFormat  = -1;
	PIXELFORMATDESCRIPTOR pfd;

	HDC hDC = GetDC( hWnd );

	SetPixelFormat( hDC, 1, &pfd );

	HGLRC r_hRC = wglCreateContext( hDC );

	wglMakeCurrent( hDC, r_hRC );

	int nPixCount = 0;

	// Specify the important attributes we care about
	int pixAttribs[] = { WGL_SUPPORT_OPENGL_ARB, 1, // Must support OGL rendering
						 WGL_DRAW_TO_WINDOW_ARB, 1, // pf that can run a window
						 WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB, // must be HW accelerated
						 WGL_COLOR_BITS_ARB,     24, // 8 bits of each R, G and B
						 WGL_DEPTH_BITS_ARB,     16, // 16 bits of depth precision for window
						 WGL_DOUBLE_BUFFER_ARB,	 GL_TRUE, // Double buffered contexs
						 WGL_SAMPLE_BUFFERS_ARB, GL_TRUE, // MSAA on
						 WGL_SAMPLES_ARB,        8, // 8x MSAA 
						 WGL_PIXEL_TYPE_ARB,      WGL_TYPE_RGBA_ARB, // pf should be RGBA type
						 0}; // NULL termination

	extern PFNWGLCHOOSEPIXELFORMATARBPROC;
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");

	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( r_hRC );
	ReleaseDC( hWnd, hDC );
	DestroyWindow( hWnd );

	SetupWindow( g.width, g.height, false );

	hDC = GetDC( g.hWnd );

	wglChoosePixelFormatARB( hDC, &pixAttribs[0], NULL, 1, &nPixelFormat, (UINT*)&nPixCount );

	/*char b[100];
	sprintf(b, "You got ID# %d as your pixelformat!\n", nPixelFormat);
	MessageBoxA( NULL, b, "Your pixelformat", MB_OK );*/

	extern PFNWGLGETPIXELFORMATATTRIBIVARBPROC;
	PFNWGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)wglGetProcAddress("wglGetPixelFormatAttribivARB");

	int attrib[] = { WGL_SAMPLES_ARB };
	int nResults = 0;
	wglGetPixelFormatAttribivARB( hDC, nPixelFormat, 0, 1, attrib, &nResults );

	SetPixelFormat( hDC, nPixelFormat, &pfd );

	/*GLint attribs[] = { WGL_CONTEXT_MAJOR_VERSION_ARB,  3,
						WGL_CONTEXT_MINOR_VERSION_ARB,  3,
						0 };
		
		g_hRC = wglCreateContextAttribsARB(g_hDC, 0, attribs);
		*/
	return 0;
}

void draw() 
{
	// 1. set up the viewport
	glViewport(0, 0, g.width,g.height);

	// 2. projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(float)g.width/(float)g.height, 1, 1000);

	// 3. viewing transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor( 0.5, 0, 0, 0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	
	glLoadIdentity();
	
	gluLookAt(  0, 0, 10,
				0, 0, 0,
				0, 1, 0);

	// 4. modelling transformation and drawing
	static float i = 0.01f;
	// Notice that 'i' is a STATIC variable.
	// That's very important. (imagine me saying
	// that like Conchords in "Business Time")
	// http://youtube.com/watch?v=WGOohBytKTU

	// A 'static' variable is created ONCE
	// when the function in which it sits first runs.
	
	// The static variable will "LIVE ON"
	// between seperate calls to the function
	// in which it lives UNTIL THE PROGRAM ENDS.

	i+= 0.001f;     // increase i by 0.001 from its
	// it had on the LAST FUNCTION CALL to the draw() function

	float c = cos( i );
	float s = sin( i );

	glBegin (GL_TRIANGLES);
		glColor3f(  c, 0, 0 );      // red
		glVertex3f( 1+c, 0+s, 0 );

		glColor3f(  c, s, 0 );      // yellow
		glVertex3f( 0+c, 1+s, 0 );

		glColor3f(  s, 0.1f, s );   // magenta
		glVertex3f(-1+c, 0+s, 0 );
	glEnd();

	//7.  SWAP BUFFERS.
	SwapBuffers(g.hdc);
	// Its important to realize that the backbuffer
	// is intelligently managed by the HDC ON ITS OWN,
	// so all's you gots to do is call SwapBuffers
	// on the HDC of your window.
}

