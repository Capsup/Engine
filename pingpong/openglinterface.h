#pragma once

#include <Windows.h>

class openglinterface
{
public:
	openglinterface();
	~openglinterface();
	bool CreateOGLWindow();
	bool Initialise();
	void GetError();
private:

};

