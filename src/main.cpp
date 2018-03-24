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
#include "world/World.h"

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
    renderer.setCameraPos(vec3(0.0f, 0.0f, 7.0f));

    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( (GLDEBUGPROC) MessageCallback, 0 );

    World world(vec3(0.0f,0.0f,0.0f));

    bool running = true;
    float offset = 0;
    while(running) {
        Uint32 updateStart = SDL_GetTicks();

        offset += 2;
        renderer.setCameraPos(vec3(offset, 0.0f, 0.0f));
        world.generateWorld(renderer.getCameraPos()-vec3(-50.0f, 0.0f, 5.0f));
        world.generateWorld(vec3(offset, 0.0f, 0.0f)-vec3(-50.0f, 0.0f, 5.0f));
        world.updateModel();

        renderer.registerModel(&world.m_model, world.m_position);
        renderer.renderAll();
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

