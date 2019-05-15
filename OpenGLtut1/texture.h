#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& fileName);

	void Bind(unsigned int unit); //It will set OpenGL to use the texture we bind

	virtual ~Texture();
protected:
private:
	Texture(const Texture& other) {}
	Texture& operator=(const Texture& other) {}

	//Astual data in the texture class
	GLuint m_texture; //Refers to the handle that OpenGL has given us to refer to the texture file
};

#endif //TEXTURE_H