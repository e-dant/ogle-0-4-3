#include "display.h"
//#include <GL/glew.h>
#include <OpenGL/GL.h>
#include <iostream>

Display::Display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

Display::~Display()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::info(){
    std::cout						<<"OpenGL info\n";
    std::cout<<"Vendor: "			<<glGetString(GL_VENDOR)<<std::endl;
    std::cout<<"Renderer: "			<<glGetString(GL_RENDERER)<<std::endl;
    std::cout<<"GL ver.: "			<<glGetString(GL_VERSION)<<std::endl;
    std::cout<<"GLSL ver.: "		<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
}

void Display::SwapBuffers()
{
	SDL_GL_SwapWindow(window);
}
