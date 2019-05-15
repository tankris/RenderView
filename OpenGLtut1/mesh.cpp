#include "mesh.h"
#include "obj_loader.h" //Benny Box's library to load obj files
#include <vector>

Mesh::Mesh(const std::string& fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();//We use it to load into its intermediate representation and obj_loader.h we're going to load position, texture Co-ordinates and normals. A nice list very easy to send to GPU
	InitMesh(model); //OBJ model-loading based construcor
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	//Constructor

	IndexedModel model; 

	//Loading the positions & texture Coordinates from Model

	for (unsigned int i = 0; i < numVertices; i++) //converts all positions and texcoords as a list of positions and texcoords
	{
		model.positions.push_back(*vertices[i].getPos());
		model.texCoords.push_back(*vertices[i].getTexCoord());
		model.normals.push_back(*vertices[i].getNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++) //converts all positions and texcoords as a list of positions and texcoords
	{
		model.indices.push_back(indices[i]);
	}

	InitMesh(model);
}

Mesh::~Mesh()
{
	//Destructor

	glDeleteVertexArrays(1, &m_vertexArrayObject); //Delete vertexArrayObject
}

void Mesh::InitMesh(const IndexedModel& model) //OpenGL initialization
{
	m_drawCount = model.indices.size();

	glGenVertexArrays(1, &m_vertexArrayObject); //1 is not number of vertexArraysObjects you want to write
	glBindVertexArray(m_vertexArrayObject); //By binding, any operation that would affect vertexArrayObject 
	//will affect m_vertexArrayObject

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffer); //Gets buffers(Blocks of data) on GPU that we can write to

	//Setting up buffer for Position

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[POSITION_VB]); //Any OpenGL function that would affect a buffer would 
	//now affect the buffer in our possession
	//GL_ARRAY_BUFFER tell it to interpret the buffer of data as an Array
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); //Taking some data from RAM to GPU memory
	//GL_STATIC_DRAW casues OpenGL to find some location in memory where it doesn't expect data to be changed. Fast to access
	//not so fast to write to initially though

	glEnableVertexAttribArray(0); //Tells OpenGL that the data is sequential in order
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //Tells OpenGl how to read one our attribute as an array
	//glm stores data as floating point

	//Setting up buffer for texCoords

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[TEXCOORD_VB]); //Any OpenGL function that would affect a buffer would 
	//now affect the buffer in our possession
	//GL_ARRAY_BUFFER tell it to interpret the buffer of data as an Array
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); //Taking some data from RAM to GPU memory
	//GL_STATIC_DRAW casues OpenGL to find some location in memory where it doesn't expect data to be changed. Fast to access
	//not so fast to write to initially though

	glEnableVertexAttribArray(1); //Tells OpenGL that the data is sequential in order
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); //Tells OpenGl how to read one our attribute as an array
	//glm stores data as floating point

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer[NORMAL_VB]); //Any OpenGL function that would affect a buffer would 
	//now affect the buffer in our possession
	//GL_ARRAY_BUFFER tell it to interpret the buffer of data as an Array
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW); //Taking some data from RAM to GPU memory
	//GL_STATIC_DRAW casues OpenGL to find some location in memory where it doesn't expect data to be changed. Fast to access
	//not so fast to write to initially though

	glEnableVertexAttribArray(2); //Tells OpenGL that the data is sequential in order
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0); //Tells OpenGl how to read one our attribute as an array
	//glm stores data as floating point

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffer[INDEX_VB]); //Any OpenGL function that would affect a buffer would 
	//now affect the buffer in our possession
	//GL_ELEMENT_ARRAY_BUFFER tell it to interpret the buffer of data as an Array referencing elements in another array
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); //Taking some data from RAM to GPU memory
	//GL_STATIC_DRAW casues OpenGL to find some location in memory where it doesn't expect data to be changed. Fast to access
	//not so fast to write to initially though

	glBindVertexArray(0); //Operations on vertexArrayObject will no more affect m_vertexArrayObject
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0); 
	//GL_TRIANGLES suggests that we want to draw Triangles
	//NOT glDrawArrays(GL_TRIANGLES, 0, m_drawCount); //Tells OpenGL to draw an array of data as Triangles
	//m_drawCount gives the draw count which is numIndices
	//GL_UNSIGNED_INT tells that the value passe, indices in this case, is of unsigned int type
	glBindVertexArray(0);
}