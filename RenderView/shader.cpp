#include "shader.h"
#include <iostream>
#include <fstream> //Class used to operate on files
#include <glm/glm.hpp>

static std::string LoadShader(const std::string& fileName);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static GLuint CreateShader(const std::string& text, GLenum shaderType); //OpenGL refers to shaders as GLuint

Shader::Shader(const std::string& fileName)
{
	//Constructor
	m_program = glCreateProgram(); //Create a program & a space in the GPU for the program and returns a number to refer it by
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER); //Assigning 0 as a Vertex shader
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER); //Assigning 1 as a Fragment shader
	//.vs & .fs is just a convention used to differentiate between the files for vertex & fragment shaders

	//Adding shaders to the program
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]); //Takes a program and adds a shader to it
	
	glBindAttribLocation(m_program, 0, "position"); 
	//It tells OpenGL what part of the data to read and as what variable in the shader program
	glBindAttribLocation(m_program, 1, "texCoord");
	//Sends texture coordinates data in the mesh to texCoord attribute in the basicShader
	glBindAttribLocation(m_program, 2, "normal");
	//Sends normals in the mesh to normal attribute in the basicShader

	glLinkProgram(m_program); //Link the shaders so during compilation everything gets linked to the final program
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed!:"); //Checks if the Program Linking has been
		//established successfully

	glValidateProgram(m_program);//Check if we ended up with a valid shader after linking
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is Invalid!:"); //Checks for Program Validation				  
	
	//Figuring out where the GPU is storing the different uniforms
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

Shader::~Shader()
{
	//Destructor
	
	//Delete the shaders as deleting program doesn't delete indiidual shaders
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]); //Detachs the shader from the program
		glDeleteShader(m_shaders[i]); //Deletes the shader
	}

	glDeleteProgram(m_program); //Tells OpenGL to free space in the GPU by deleting the program
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	//Updating the uniform
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel(); //Retreving data to be assigned to uniform

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]); //Matrix 4x4 of floating values
}

static GLuint CreateShader(const std::string& text, GLenum shaderType) //Used for Shader creation
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0) //Checks for error. If 0, OpenGL hasn't given the shader yet
		std::cerr << "Error: Shader creation failed!" << std::endl;

	const GLchar* shaderSourceStrings[1]; //Using GLchar to ensure char size compatability with OpenGL
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str(); //Converts text to C compliant standard and stores it
	shaderSourceStringLengths[0] = text.length();//Give us the length of the text string

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths); //Send our source code to OpenGL
	//1 indicates number of source strings

	glCompileShader(shader); //Now we compile the shader
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader Compilation failed!:"); 
	//False cause its for checking one component and not the entire program
	//Checks if the shader compilation is successfull

	return shader; //Returns the shader
}

static std::string LoadShader(const std::string& fileName) //Loads a textFile from the Hard-drive
{
	std::ifstream file; //Input stream variable used to operate on files
	file.open((fileName).c_str()); //Opening the file contents

	std::string output;
	std::string line;

	if (file.is_open()) //Checks if the file is opened
	{
		while (file.good()) //Checks for end of file and file errors
		{
			getline(file, line); //Used to read a string or a line from input stream
			output.append(line + "\n"); //Appends the string with \n
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl; //Prints error message
	}

	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
//Handles the error messages by informing us
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram) //Checks the bool value is true
		glGetProgramiv(shader, flag, &success); //Returns in params the value of a parameter for a specific program object
	else
		glGetShaderiv(shader, flag, &success);//Returns in params the value of a parameter for a specific program object

	if (success == GL_FALSE) //Checks if value of success is 0
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error); //Grabs Link Log of entire Shader program object
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl; //Prints message into Error Console stream
	}
}
