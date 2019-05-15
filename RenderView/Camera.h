#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar, const glm::vec3& forward, const glm::vec3& up)
		//pos - position of camera, fov - field of view, aspect - aspect of the project, 
		//zNear - closest distance that we can see, zFar - Farthest distance we can see
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = forward; //001
		m_up = up;//010
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up); //Used to apply camera rotation
	}

protected:
private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward; //Represents forward direction	
	glm::vec3 m_up; //Represents the user's up
};

#endif //CAMERA_H_INCLUDED