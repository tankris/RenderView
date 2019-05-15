#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

//We will be using stb_image for texture loading since it is simple and also cause it can be statically linked

Texture::Texture(const std::string& fileName) //We're going to be loading a texture from a file
{
	//Constructor

	int width, height, numComponents; //These are the 3 non-texture data that stbi will give us
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4); //Loads the texture data

	if (imageData == NULL) //Checking if the texture loading is unsuccessful
		std::cerr << "Texture Loading Failed for texture: " << fileName <<std::endl;

	glGenTextures(1, &m_texture); //Generates space for 1 texture in the buffer
	glBindTexture(GL_TEXTURE_2D, m_texture); //Specifying the data as 2D texture data

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	//GL_TEXTURE_WRAP_S controls reading location outside texture boundary width 
	//GL_REPEAT specifies to go back to beginning in such a case
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//GL_TEXTURE_WRAP_S controls reading location outside texture boundary height

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//GL_TEXTURE_MIN_FILTER how to handle interpolation when texture takes up fewer pixels than its resolution
	//GL_LINEAR it will Linearly interpolate between existing pixels to produce accurate image
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//GL_TEXTURE_MAG_FILTER how to handle extrapolation when texture takes up more pixels than its resolution

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); //Sending texture data

	stbi_image_free(imageData); //Delete the texture data from the CPU
}

Texture::~Texture()
{
	//Destructor

	glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <=31); //Ensure that the units don't go out of range since OpenGL has only 32 textures

	glActiveTexture(GL_TEXTURE0 + unit); //Specifies which texture OpenGl is working with
	glBindTexture(GL_TEXTURE_2D, m_texture); //All future texture operations will use m_texture
}