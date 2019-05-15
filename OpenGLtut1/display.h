#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h> //To access SDL functions within Display
#include<string> //Importing string as it is used in the parameters of Display

class Display {
public:
	Display(int width, int height, const std::string& title); //Input parameters include Width, Height & String input of title
	
	void Clear(float r, float g, float b, float a);
	void Update(); //Here is where Double Buffers comes to play
	bool isCLosed();

	virtual ~Display();

protected:
	
private:
	Display(const Display& other) {}
	void operator=(const Display& other) {}

	SDL_Window* m_window; //A window pointer

	SDL_GLContext m_glContext; //Removes iron hold of OS's control of the windowing system and allows GPU to take control of it
	bool m_isClosed; //Boolean determining if the window is closed
};

#endif //DISPLAY_H