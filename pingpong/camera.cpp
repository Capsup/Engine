#include "camera.h"


camera::camera()
{
	/*m_m4LookAt = glm::lookAt( glm::vec3( 0.f, 0.f, 10.f ),
									glm::vec3( 0.f, 0.f, 0.f ),
									glm::vec3( 0.f, 1.f, 0.f ) );*/
	m_m4LookAt = glm::lookAt( glm::vec3( 0.f, 0.f, 10.f ),
									glm::vec3( 0.f, 0.f, 0.f ),
									glm::vec3( 0.f, 1.f, 0.f ) );
}

camera::camera( glm::vec3 v3Origin )
{

}

camera::camera( glm::vec3 v3Origin, glm::vec3 v3LookAt, glm::vec3 v3Up )
{
	
}

camera::~camera()
{

}

void camera::LookAt()
{
	
}

void camera::LookAt( glm::vec3 v3Origin, glm::vec3 v3LookAt, glm::vec3 v3Up )
{
	m_m4LookAt = glm::lookAt( v3Origin, v3LookAt, v3Up );
}

void camera::LookAt( glm::mat4 m4LookAt )
{
	m_m4LookAt = m4LookAt;
}

glm::mat4 camera::GetLookAt()
{
	return m_m4LookAt;
}

void camera::SetYaw( float Yaw )
{
	m_fYaw = Yaw;
}

float camera::GetYaw()
{
	return m_fYaw;
}

void camera::SetPitch( float Pitch )
{
	m_fPitch = Pitch;
}

float camera::GetPitch()
{
	return m_fPitch;
}

void camera::SetOrigin( glm::vec3& v3Origin )
{
	m_v3Origin = v3Origin;
}

void camera::AttachTo()
{

}