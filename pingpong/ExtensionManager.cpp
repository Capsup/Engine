#include "ExtensionManager.h"

//Proc defines:
PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNWGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB = NULL;
PFNGLCOMPILESHADERARBPROC glCompileShaderARB = NULL;
PFNGLSHADERSOURCEARBPROC glShaderSourceARB = NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB = NULL;
PFNGLGETINFOLOGARBPROC glGetInfoLogARB = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLUNIFORM4FVPROC glUniform4fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
//End proc defines.

ExtensionManager::ExtensionManager( bool bInitAPI )
{
	if( !wglGetCurrentContext() ) 
		return;

	extensions = (char*) glGetString( GL_EXTENSIONS );

	if( bInitAPI )
		InitAPI();
}


ExtensionManager::~ExtensionManager(void)
{
}

bool ExtensionManager::isExtSupported( int ext )
{
	if( (*extensions) != ( NULL || "" ) )
	{
		return( strchr( extensions, ext ) != NULL ? true : false );
	}
	else
	{
		FatalAppExit( NULL, TEXT("Failed to load extensions.") );
		return false;
	}
}

bool ExtensionManager::InitAPI()
{
	if( !wglGetCurrentContext() ) 
		return false;
	
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC) wglGetProcAddress("wglChoosePixelFormatARB");
	wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC) wglGetProcAddress( "wglGetPixelFormatAttribivARB" );
	
	/*
	wglCreateContextAttribsARB = NULL;
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress( "wglCreateContextAttribsARB" );*/

	glCreateShader = (PFNGLCREATESHADERPROC) wglGetProcAddress( "glCreateShader" );
	glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC) wglGetProcAddress( "glShaderSourceARB" );
	glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC) wglGetProcAddress( "glCompileShaderARB" );
	glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC) wglGetProcAddress( "glGetObjectParameterivARB" );
	glGetShaderiv = (PFNGLGETSHADERIVPROC) wglGetProcAddress( "glGetShaderiv" );
	glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC) wglGetProcAddress( "glGetInfoLogARB" );
	glCreateProgram = (PFNGLCREATEPROGRAMPROC) wglGetProcAddress( "glCreateProgram" );
	glAttachShader = (PFNGLATTACHSHADERPROC) wglGetProcAddress( "glAttachShader" );
	glLinkProgram = (PFNGLLINKPROGRAMPROC) wglGetProcAddress( "glLinkProgram" );
	glUseProgram = (PFNGLUSEPROGRAMPROC) wglGetProcAddress( "glUseProgram" );
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress( "glGetUniformLocation" );
	glUniform4fv = (PFNGLUNIFORM4FVPROC) wglGetProcAddress( "glUniform4fv" );
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) wglGetProcAddress( "glUniformMatrix4fv" );
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC) wglGetProcAddress( "glGetProgramiv" );
	return true;

}