#include "mouseinterface.h"


mouseinterface::mouseinterface(void)
{

}


mouseinterface::~mouseinterface(void)
{

}

glm::vec2 mouseinterface::GetMousePos()
{
	POINT point;
    GetCursorPos(&point);
	return( glm::vec2( point.x, point.y ) );
}

void mouseinterface::SetMousePos( glm::vec2 v2Pos )
{
	SetCursorPos( v2Pos.x, v2Pos.y );
}