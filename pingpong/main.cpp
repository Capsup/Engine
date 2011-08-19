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
#include "shadermanager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include "game.h"
#include "camera.h"
#include "keyboardinterface.h"



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

	//game game;

	camera camera;

	keyboardinterface keyboard;

};

#pragma region Globals and Prototypes
Globals g;

GLint vColorValue;
GLint mvpMatrix;
GLuint FlatShader;

LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow );
void draw();
void move();
#pragma endregion
#include <string>
#pragma region New WinMain
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow )
{
	std::string sGlobalPath = std::string(__argv[0]).substr(0, std::string(__argv[0]).rfind('\\') );
	SetCurrentDirectory( tools::StringToWString( sGlobalPath ).c_str() );
	MessageBoxA( NULL, (LPCSTR) sGlobalPath.c_str(), "test" , MB_OK );

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

	MSG msg;

	shadermanager sm; 

	FlatShader = sm.LoadFromFile( sGlobalPath+"/content/shaders/flat/FlatShader.fp", sGlobalPath+"/content/shaders/flat/FlatShader.vp" );

	vColorValue = glGetUniformLocation( FlatShader, "vColorValue" );
	mvpMatrix = glGetUniformLocation( FlatShader, "mvpMatrix" );

	

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

		KeyEvent event;

		while( g.keyboard.GetNextEvent( event ).type != KeyEventNone )
		{
			//if( event.type == KeyEventRelease && event.iKeyCode == 37 )
			switch( event.iKeyCode )
			{
				//glm::mat4 lookat = g/*.game*/.camera.GetLookAt();
				//glm::mat4 lookat = g.camera.m_m4LookAt;
				//glm::rotate( lookat, 90.f, glm::vec3( 0, 0, 1 ) );
				//lookat *= rotate;
				//g/*.game*/.camera.LookAt( lookat );
				g.camera.m_m4LookAt = glm::rotate( g.camera.m_m4LookAt, 90.f, glm::vec3( 0, 1, 0 ) );
			}
			/*glViewport(0, 0, g.width,g.height);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glClearColor( 1, 0, 0, 0 );
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );	
			glLoadIdentity();

			SwapBuffers(g.hdc);*/
		}
		
		draw();
		
	}

	AnimateWindow( g.hwnd, 200, AW_HIDE | AW_BLEND );
	
	return msg.wParam;
}
#pragma endregion

#pragma region Draw Function
void draw() 
{
	glViewport(0, 0, g.width,g.height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor( 0, 0, 0, 0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );	
	glLoadIdentity();
	

	GLfloat vColor[] = { 0.1f, 0.1f, 1.f, 1.0f };
	/*glm::mat4 projection = glm::perspective( 45.0f, (float) g.width / (float) g.height, 1.f, 1000.f );
	glm::mat4 translate = glm::translate( glm::mat4( 1.f ), glm::vec3( 1.f, 1.f, 1.f ) );
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
	glm::mat4 mvp = projection * translate * Model;
	glm::mat4 lookat = glm::lookAt( glm::vec3( 0.f, 0.f, 10.f ),
									glm::vec3( 0.f, 0.f, 0.f ),
									glm::vec3( 0.f, 1.f, 0.f ) );
	mvp *= lookat;*/

	//glm::mat4 mvp = glm::mat4(1.f) * g.camera.GetLookAt() * glm::perspective( 45.0f, (float) g.width / (float) g.height, 1.f, 1000.f );
	glm::mat4 mvp = glm::perspective( 45.0f, (float) g.width / (float) g.height, 1.f, 1000.f ) * g.camera.GetLookAt() * glm::mat4(1.f) ;

	glUseProgram( FlatShader );
		glUniform4fv(vColorValue, 1, vColor);
		glUniformMatrix4fv(mvpMatrix, 1, GL_FALSE, glm::value_ptr( mvp ) );
		glBegin (GL_QUAD_STRIP);
			glColor3f(  1, 0, 0 );
			glVertex3f( 0, 1, 0 );

			glColor3f(  0, 1, 0 );
			glVertex3f( 1, 1, 0 );

			glColor3f(  0, 0, 1 );
			glVertex3f( 0, 0, 0 );

			glColor3f(  1, 1, 1 );
			glVertex3f( 1, 0, 0 );
		glEnd();
	glUseProgram( 0 );

	SwapBuffers(g.hdc);

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

		g.keyboard.Press( KeyCode );

		KeyEvent Event;
		Event.type = KeyEventPress;
		Event.iKeyCode = KeyCode;

		g.keyboard.InsertEvent( Event );

		//return 0;
		break;
		}
	case WM_KEYUP:
		{
		unsigned int KeyCode = wparam;

		g.keyboard.Release( KeyCode );

		KeyEvent Event;
		Event.type = KeyEventRelease;
		Event.iKeyCode = KeyCode;

		g.keyboard.InsertEvent( Event );

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
			g.keyboard.InsertEvent( Event );
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