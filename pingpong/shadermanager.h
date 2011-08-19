#pragma once
#include "glShader.h"
#include <string>

class shadermanager
{
public:
	shadermanager(void);
	~shadermanager(void);
	GLuint LoadFromFile( char* fpPath, char* vpPath );
	GLuint LoadFromFile( std::string& fpPath, std::string& vpPath );
};
