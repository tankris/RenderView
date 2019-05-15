#include <iostream>
#include "display.h"
#include <GL/glew.h>

Display::Display(int width, int height, const std::string& title)
{
	//constructor

	SDL_Init(SDL_INIT_EVERYTHING); //Initializing everything in SDL

	//Attributes to be set since we create a window using SDL_WINDOW_OPENGL

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Setting No of bits used to display Red colors
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); //Setting No of bits used to display Green colors
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); //Setting No of bits used to display Blue colors
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); //Setting No of bits used to determine transparency
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //Data in bits that SDL will allocate for a single pixel
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); //Allocating space for z-buffer/depth-buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //SDL allocates space for 2 windows but creates only 1 that is displayed

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
		//SDL is a C API so we convert title string to c eqivalent string and use SDL_WINDOWPOS_CENTERED for (x,y) 
		//to create the window in the centre SDL_WINDOW_OPENGL indicates that we are in fact 
		//using OpenGL to create the window and not SDL functions
	m_glContext = SDL_GL_CreateContext(m_window); //Created context to allow GPU to draw in the window
	
	GLenum status = glewInit(); //Finds all the functions that our OS supports

	if (status != GLEW_OK) //If status isn't okay
	{
		std::cerr << "Glew failed to initialize" << std::endl; //Print error message
	}

	m_isClosed = false; //Currently in the window, so can't be closed

	//Z-Buffer method: At every single pixel of the image, store how far the pixel is from the camera. 
	//When drawing, you compare if the pixel is closer than the pixel already drawn. If further away, don't draw it.	
	glEnable(GL_DEPTH_TEST); //Enables the use of Z-buffer

	glEnable(GL_CULL_FACE); //Back-culling -> If the face is facing away from the camera, we're not going to draw it
	glCullFace(GL_BACK);

}

Display::~Display()
{
	//destructor
	SDL_GL_DeleteContext(m_glContext); //Delete the glContext
	SDL_DestroyWindow(m_window); //Delete the window
	SDL_Quit(); //De-initializes everything related to SDL
}

void Display::Clear(float r, float g, float b, float a) //Function to clear the window
{
	glClearColor(r, g, b, a); //Fill the window with a color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the color buffer in other words it will fill our color buffer with the color as defined above
}

bool Display::isCLosed() //Function returns status of the Windows as closed or not
{
	return m_isClosed; //returns boolean value
}

void Display::Update() //Used to handle events and swapping of buffers 
{
	SDL_GL_SwapWindow(m_window); //Swaps the buffers

	//Used for handling events

	SDL_Event e; //Stores OS events

	while (SDL_PollEvent(&e)) //Looks for OS events we found and we pass the address of the event
	{
		if (e.type == SDL_QUIT) //Checks if we closed the window
			m_isClosed = true; //Sets the bol value to true
	}
}