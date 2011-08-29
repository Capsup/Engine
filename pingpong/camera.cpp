#include "camera.h"


camera::camera()
{
	/*m_m4LookAt = glm::lookAt( glm::vec3( 0.f, 0.f, 10.f ),
									glm::vec3( 0.f, 0.f, 0.f ),
									glm::vec3( 0.f, 1.f, 0.f ) );*/
	m_m4LookAt = glm::lookAt( glm::vec3( 0.f, 0.f, 10.f ),
									glm::vec3( 0.f, 0.f, 0.f ),
									glm::vec3( 0.f, 1.f, 0.f ) );
	m_v3Origin = glm::vec3( 0.f, 0.f, 10.f );
	m_v3EyePos = glm::vec3( 0.f, 0.f, 0.f );
	m_v3Up = glm::vec3( 0.f, 1.f, 0.f );
	m_fYaw = 0.f;
	m_fPitch = 0.f;
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

void camera::AddYaw( float fYaw )
{
	m_fYaw += fYaw;

	if( m_fYaw > 360.f ) 
		m_fYaw -= 360.f;
	if( m_fYaw < 0.f )
		m_fYaw += 360.f;

}

float camera::GetYaw()
{
	return m_fYaw;
}

void camera::SetPitch( float Pitch )
{
	m_fPitch = Pitch;
}

void camera::AddPitch( float fAmount )
{
	m_fPitch += fAmount;

	if( m_fPitch > 45.f )
		m_fPitch = 45.f;
	if( m_fPitch < -45.f )
		m_fPitch = -45.f;

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

void camera::MoveForward( float fAmount )
{
	//m_v3Origin.z += fAmount;

	m_v3Origin.x += glm::cos( glm::radians( m_fYaw ) ) * fAmount;
	m_v3Origin.z += glm::sin( glm::radians( m_fYaw ) ) * fAmount;

}

void camera::Apply()
{
	float cosyaw = glm::cos( glm::radians( m_fYaw ) );
	float sinyaw = glm::sin( glm::radians( m_fYaw ) );
	float sinpitch = glm::sin( glm::radians( m_fPitch ) );

	m_v3EyePos.x = m_v3Origin.x + cosyaw;
	m_v3EyePos.y = m_v3Origin.y + sinpitch;
	m_v3EyePos.z = m_v3Origin.z + sinyaw;

	m_m4LookAt = glm::lookAt(	m_v3Origin,
								m_v3EyePos,
								m_v3Up 
								);
}