#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h> //To access glew functions
#include <string> //Importing string as it is used in the parameters of Shader
#include "Transform.h"
#include "Camera.h"

class Shader {
public:
	Shader(const std::string& fileName); 

	void Bind(); //Set the GPU in a state to use our Vertex Shader & Fragment Shader
	void Update(const Transform& transform, const Camera& camera); //Updates all uniforms in the arry to some new set of values
	
	virtual ~Shader();

protected:

private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}

	enum //Making it easier to add uniforms
	{
		//Have number that refer to our different uniforms
		TRANSFORM_U,

		NUM_UNIFORMS //to know how big our uniform list is
	};

	GLuint m_program; //GL unsigned integer used to keep track of where the program is
	GLuint m_shaders[NUM_SHADERS]; //Array of GL unsigned ints used for Vertex and Fragment Shaders
	GLuint m_uniforms[NUM_UNIFORMS]; //Array of GL unsigned ints used for Uniforms
};

#endif //SHADER_H