#pragma once

#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <GL/glext.h>
#include <GL/wglext.h>

//#pragma comment(lib, "opengl32.lib")


/*

extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
*/
extern PFNWGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB;
extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
extern PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
extern PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
extern PFNGLGETINFOLOGARBPROC glGetInfoLogARB;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLUNIFORM4FVPROC glUniform4fv;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;

class ExtensionManager
{
public:
	ExtensionManager( bool bInitAPI = true );
	~ExtensionManager();
	bool isExtSupported( int ext );
	bool InitAPI();
private:
	const char* extensions;
};