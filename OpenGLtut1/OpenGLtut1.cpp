#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "Camera.h"
#undef main //overcomes LNK2019 error

#define WIDTH 800
#define HEIGHT 620

int main(int argc, char* argv[]) {

	Display display(WIDTH, HEIGHT, "Hello World!");

	//Mesh - Act of taking 3D data and sending it to the GPU

	//Shaders - prgorams for the GPU which will do processing on the 3D data

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
						  Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
						  Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0)) }; //OpenGL co-ordinates are from -1(x=left & y=bottom) to 1(x=right & y=top)
	
	unsigned int indices[] = {0, 1, 2};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0])); //sizeof(vertices) / sizeof(vertices[0]) gives the number of 
	//elements in the array. Sizeof returns the number of bytes.
	Mesh mesh2("./res/trex.obj"); //Create another mesh

	Shader shader("./res/basicShader"); //Loads the path to our shader file
	Texture texture("./res/fluid.jpg");
	Camera camera(glm::vec3(0,0,-2), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f, glm::vec3(0,0,1), glm::vec3(0,1,0)); //70.0f is approcimately the field of view of the human eye
	Transform transform;

	float counter = 0.0f;

	while (!display.isCLosed()) //As long as window is not closed
	{
		display.Clear(0.0f, 0.0f, 0.0f, 0.0f); //Passing the values as actual arguments to the Clear function
		
		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);
		float tanCounter = tanf(counter);

		//transform.GetPos().x = cosCounter; //We are able to assign since GetPos returns reference
		//transform.GetPos().y = -1;
		//transform.GetPos().z = sinCounter;
		//transform.GetRot().x = sinCounter;// cosf(counter * 50);
		transform.GetRot().y = counter*3;
		//transform.GetRot().z = sinCounter;
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind(); //Uses the shader when we draw something
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh2.Draw(); //Uses the Mesh to draw something
		
		display.Update(); //Calls the update function
		counter += 0.0005f;
	}

	
	
	return 0;
	
}