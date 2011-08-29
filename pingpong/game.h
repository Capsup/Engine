#pragma once

#include "ExtensionManager.h"
#include "shadermanager.h"
#include "keyboardinterface.h"
#include "mouseinterface.h"
#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Windows.h>
#include "tools.h"

class game
{
public:
	game();
	game( HDC hdc );
	~game(void);
	void Update( float dt );
	void Render();
	keyboardinterface keyboard;
	mouseinterface mouse;
	camera Camera;
	shadermanager sm;
private:
	std::string sGlobalPath;
	HDC m_hdc;
};

