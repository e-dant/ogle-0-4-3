#ifndef DISPLAY_INCLUDED_H
#define DISPLAY_INCLUDED_H

#include "init.h"
#include <string>
#include <SDL2/SDL.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Clear(float r, float g, float b, float a);
	void SwapBuffers();
    void info();

	virtual ~Display();
//protected:
//private:
	void operator=(const Display& display) {}
	Display(const Display& display) {}

	SDL_Window* window;
	SDL_GLContext context;
};

#endif
