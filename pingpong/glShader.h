#pragma once
#include <iostream>
#include <fstream>
#include "tools.h"

#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#include "ExtensionManager.h"

class glShader
{
	public:
		glShader(void);
		virtual ~glShader(void);
		int Load( char* path );
		int Load( std::string path );
		GLuint GetObject();
	private:
		GLuint shader;
};

