/*#include <GL/glext.h>
#include <GL/wglext.h>
extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB_real;
inline PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats)
{
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB_real = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	return wglChoosePixelFormatARB_real;
}


extern PFNWGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB;
PFNWGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)wglGetProcAddress("wglGetPixelFormatAttribivARB");*/
