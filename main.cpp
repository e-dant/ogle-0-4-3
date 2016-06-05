#include <iostream>
#include <SDL2/SDL.h>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "display_data.h"
#include "camera.h"
#include "commonData.h"

static const int DISPLAY_WIDTH = 500;
static const int DISPLAY_HEIGHT = 500;
static const bool showTracker = 0;

void loop(Display * display, Transform * transform, Mesh * mesh0, Shader * shader, Camera * camera){
    bool run = true;
    SDL_Event e;
    xyz_i mousePos;
    glm::vec3 vec3_mousePos = {0,0,0};
    
    while (run) {
        while(SDL_PollEvent(&e)) {
            Uint32 startingTicks=SDL_GetTicks();
            display->Clear(8.0f, 0.0f, 0.7f, 1.0f);
            //keyboard input
            if(e.type == SDL_QUIT) run = false;
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    run = false;
                    break;
                default:
                    break;
            }
            //mouse and trackpad input
            if (e.type == SDL_MOUSEMOTION) {
                if (e.motion.x>0) {
                    /*if (showTracker) *///std::cout << "tracking x" << std::endl;
                    /*if (showTracker)*/ std::cout << "x | " << mousePos.x << std::endl;
                    mousePos.x += 1;
                }
                if (e.motion.y<0) {
                    /*if (showTracker) *///std::cout << "tracking x" << std::endl;
                    /*if (showTracker)*/ std::cout << "x | " << mousePos.x << std::endl;
                    mousePos.x -= 1;
                }
                if (e.motion.y>=0) {
                    /*if (showTracker) *///std::cout << "tracking y" << std::endl;
                    /*if (showTracker)*/ std::cout << "y | " << mousePos.y << std::endl;
                    mousePos.y += 1;
                }
                if (e.motion.y<=0) {
                    /*if (showTracker) *///std::cout << "tracking y" << std::endl;
                    /*if (showTracker)*/ std::cout << "y | " << mousePos.y << std::endl;
                    mousePos.y -= 1;
                }
                if (e.motion.y==0) {
                    mousePos.y += 0;
                }
                if (e.motion.y==0) {
                    mousePos.y += 0;
                }
                
//                ////////////////
//                //vec3_mousePos = {e.motion.xrel, e.motion.yrel, 0};
//                //mousePos.x = e.motion.xrel;
//                //mousePos.y = e.motion.yrel;
//                vec3_mousePos.x += e.motion.xrel;
//                vec3_mousePos.y += e.motion.yrel;
//                vec3_mousePos.z = 1;
//                /*if (showTracker)*/ std::cout << "relative mouse position    x | y    " << vec3_mousePos.x << "," << vec3_mousePos.y << std::endl;
//                ////////////////
            }
            
            /*if (showTracker) *///std::cout << "ending mouse tracking" << std::endl;
            /*if (showTracker) *///std::cout << "drawing" << std::endl;
            
            vec3_mousePos = {mousePos.x/40, mousePos.y/40, mousePos.z};
            
            transform->SetPos(vec3_mousePos);
            mesh0->Draw();
            shader->Update(*transform, *camera);
            display->SwapBuffers();
            
            if (1000/60>SDL_GetTicks()-startingTicks) {
                SDL_Delay(1000/60-(SDL_GetTicks()-startingTicks));
                
            //keyboard input (again)
            if(e.type == SDL_QUIT) run = false;
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    run = false;
                    break;
                default:
                    break;
            }

            }
        }
    }
}

int main(int argc, char** argv) {
    Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "main");
    Mesh monkey("./res/monkey3.obj", 1);
    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
    Mesh teapot("./res/teapot.obj");
    Shader shader("./res/basicShader");
    Texture texture("./res/bricks.jpg");
    Transform transform;
    Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 90.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.1f, 100.0f);
    //matrix stack
    shader.Bind();
    if (showTracker) display.info();
    if (showTracker) std::cout << "done initialization" << std::endl;

    loop(&display, &transform, &mesh, &shader, &camera);
    SDL_Quit();
    
    return 0;
}
