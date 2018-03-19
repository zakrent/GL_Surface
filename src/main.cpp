//
// Created by zakrent on 3/18/18.
//

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "visual/Window.h"
#include "visual/Model.h"
#include "visual/Shader.h"
#include "visual/Renderer.h"

using glm::vec3;

void MessageCallback( GLenum source,
                      GLenum type,
                      GLuint id,
                      GLenum severity,
                      GLsizei length,
                      const GLchar* message,
                      const void* userParam )
{
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
             ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
             type, severity, message );
}

int main(){
    Window window;
    Renderer renderer;

    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( (GLDEBUGPROC) MessageCallback, 0 );

    Shader basicShader("basic");

    std::vector<Vertex> vertices = {
            Vertex{vec3(-1.0f, 0.0f, -1.0f),vec3(1.0f, 0.0f, 0.0f)},
            Vertex{vec3(1.0f, 0.0f, -1.0f),vec3(0.0f, 1.0f, 0.0f)},
            Vertex{vec3(0.0f, 0.0f, 1.0f),vec3(0.0f, 0.0f, 1.0f)},
            Vertex{vec3(0.0f, 1.0f, 0.0f),vec3(1.0f, 1.0f, 1.0f)},
    };
    std::vector<uint> indices = {
            0,1,2,
            0,2,3,
            0,1,3,
            1,2,3
    };
    Model test(&basicShader, vertices, indices);

    bool running = true;
    float rot = -180;
    while(running) {
        Uint32 updateStart = SDL_GetTicks();

        rot += 0.01;
        if(rot > 180){
            rot = -180;
        }

        renderer.startRendering();
        renderer.renderModel(test, vec3(0.0f, 0.0f, -6.0f), rot, vec3(0.2f, 1.0f, 0.0f));
        window.update();

        SDL_Event event{};
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        if (SDL_GetTicks() < updateStart + 10) {
            SDL_Delay((updateStart + 10) - SDL_GetTicks());
        }
    }

}

