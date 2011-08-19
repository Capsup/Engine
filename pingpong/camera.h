#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class camera
{
public:
	camera();
	camera( glm::vec3 v3Origin );
	camera( glm::vec3 v3Origin, glm::vec3 v3LookAt, glm::vec3 v3Up );
	~camera();
	void LookAt( glm::vec3 v3Origin, glm::vec3 v3LookAt, glm::vec3 v3Up );
	void LookAt( glm::mat4 v3LookAt );
	void LookAt();
	glm::mat4 GetLookAt();
	void SetYaw( float Yaw );
	float GetYaw();
	void SetPitch( float Pitch );
	float GetPitch();
	void SetOrigin( glm::vec3& v3Origin );
	void AttachTo();
	glm::mat4 m_m4LookAt;

private:
	glm::vec3 m_v3Origin;
	glm::vec3 m_v3Up;
	glm::vec3 m_v3Right;
	glm::vec3 m_v3Forward;
	

	float m_fPitch;
	float m_fYaw;

	glm::mat3 m_m3ViewMatrix;
};

