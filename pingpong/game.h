#pragma once

#include "keyboardinterface.h"
#include "camera.h"

class game
{
public:
	game(void);
	~game(void);
	keyboardinterface keyboard;
	camera camera;
};

