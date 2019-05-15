#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp> //Header for OpenGL Math Library
#include <GL/glew.h> //To access glew functions
#include"obj_loader.h"

class Vertex
{
	//Adding another class to represent the data to be sent to GPU

	//The GPU needs the data to be of the format x,y,z co-ordinates, between -1 to 1 and expects 3 of them in sequence 
	//to represent each triangle. Vertex is one of the 3 points
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,0,0))
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	inline glm::vec3* getPos() { return &pos; }
	inline glm::vec2* getTexCoord() { return &texCoord; }
	inline glm::vec3* getNormal() { return &normal; }

protected:
private:
	glm::vec3 pos; //Vertex data
	glm::vec2 texCoord; //Position on the texture that we are mapping to the vertex
	glm::vec3 normal; //The up direction on a surface
};

class Mesh {
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices); //Takes parameter as list of vertices
	Mesh(const std::string& fileName);

	void Draw(); //Its going to take the mesh and draw it with Graphics card

	virtual ~Mesh();

protected:

private:
	Mesh(const Mesh& other) {}
	void operator=(const Mesh& other) {}

	void InitMesh(const IndexedModel& model);

	enum //we use this to refer to every item of vertexArrayBuffer
	{
		POSITION_VB,
		TEXCOORD_VB, //Buffer for texture co-ordinates
		NORMAL_VB, //Used to store all normals

		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject; //GLuint refers to all data it has on the GPU
	GLuint m_vertexArrayBuffer[NUM_BUFFERS];
	unsigned int m_drawCount; //Tells OpenGL how much of vertexArrayObject do we want to draw by keeping track of that
};

#endif //MESH_H