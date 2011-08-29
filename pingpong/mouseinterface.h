#pragma once

#include <glm/glm.hpp>
#include <Windows.h>

class mouseinterface
{
public:
	mouseinterface(void);
	~mouseinterface(void);
	glm::vec2 GetMousePos();
	void SetMousePos( glm::vec2 v2Pos );
};

