#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp> //Doesn't include transformation functions
#include <glm/gtx/transform.hpp> //Includes all the transformation functions


class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) : //Function to transform our object by being the interface for us to pass 
	//the Matrix transform to the Vertex Shader
	//3 different ways to transform the object -> Put the object around anywhere, 
	//rotation moves the object around its ais and scale which decide how big or small our object is
	//Those are the arguments of the function as vectors
	m_pos(pos),
	m_rot(rot),
	m_scale(scale) {}

	inline glm::mat4 GetModel() const//glm::mat4 which is a 4x4 matrix
	{
		glm::mat4 posMatrix = glm::translate(m_pos); //Generates a 4x4 matrix with the position

		glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1, 0, 0)); //Represents rotation on the x-axis
		glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0, 1, 0)); //Represents rotation on the y-axis
		glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0, 0, 1)); //Represents rotation on the z-axis

		glm::mat4 scaleMatrix = glm::scale(m_scale); //Runs functions for converting bunch of basic positions, scaling in matrices
		
		//One way to combine matrices is to multiply them. THe downside being that its not commutative
		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix; //Mulitply them in the opposite manner that you want

		return posMatrix * rotMatrix * scaleMatrix; //It first scales the object to the perfect size,
		//then roates the object around its axis
		//then it is placed in the world position
	}

	inline glm::vec3& GetPos() { return m_pos; }
	inline glm::vec3& GetRot() { return m_rot; }
	inline glm::vec3& GetScale() { return m_scale; }

	inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
	inline void SetRot(const glm::vec3& rot) { m_rot = rot; }
	inline void SetScale(const glm::vec3& scale) { m_scale = scale; }
protected:
private:
	glm::vec3 m_pos; //Member variables
	glm::vec3 m_rot;
	glm::vec3 m_scale;
};

#endif //TRANSFORM_H