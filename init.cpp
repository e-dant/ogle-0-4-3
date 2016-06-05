//
//  init.cpp
//  opengl tutorial
//
//  Created by Edmond Dantes on 5/16/16.
//  Copyright © 2016 Edmond Dantes. All rights reserved.
//

#include "init.h"

void checkSDLError(int line) {
    std::string error = SDL_GetError();
    
    if (error != "")
    {
        std::cout << "SDL Error : " << error << std::endl;
        
        if (line != -1)
            std::cout << "\nLine : " << line << std::endl;
        
        SDL_ClearError();
    }
}

bool setOpenGLAttributes() {
    ////
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    ////
    
    // Set our OpenGL version.
    // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it (3.1 is what we're on)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    //depth and stencil size
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
    
    // Turn on double buffering with a 24bit Z buffer; if 24 doesn't work, try 16 or 32
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); //<---non-standard
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    return true;
}

void init(SDL_Window *window, SDL_GLContext context, int width, int height, std::string title) {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    //mainContext = SDL_GL_CreateContext(window);
    setOpenGLAttributes();
    context = SDL_GL_CreateContext(window);
    //SDL_GL_SetSwapInterval(1);  // buffer swap syncronized with the monitor's vertical refresh
    if (!window) {std::cout << "Unable to create window\n"; checkSDLError(__LINE__);}     // check for context and window errorserror
    if (!context) {std::cout << "Unable to create context\n"; checkSDLError(__LINE__);}
    
    //info
    std::cout						<<"OpenGL info\n";
    std::cout<<"Vendor: "			<<glGetString(GL_VENDOR)<<std::endl;
    std::cout<<"Renderer: "			<<glGetString(GL_RENDERER)<<std::endl;
    std::cout<<"GL ver.: "			<<glGetString(GL_VERSION)<<std::endl;
    std::cout<<"GLSL ver.: "		<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
}