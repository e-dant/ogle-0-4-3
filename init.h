//
//  init.hpp
//  opengl tutorial
//
//  Created by Edmond Dantes on 5/16/16.
//  Copyright © 2016 Edmond Dantes. All rights reserved.
//

#ifndef init_hpp
#define init_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <OpenGL/GL.h>

void init(SDL_Window *window, SDL_GLContext context, int width, int height, std::string title);
bool setOpenGLAttributes();
void checkSDLError(int line);

#endif /* init_hpp */
