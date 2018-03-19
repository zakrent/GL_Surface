//
// Created by zakrent on 3/18/18.
//

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "visual/Window.h"
#include "visual/Model.h"
#include "visual/Shader.h"

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

    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( (GLDEBUGPROC) MessageCallback, 0 );

    Shader basicShader("basic");
    basicShader.use();

    std::vector<Vertex> vertices = {
            Vertex{vec3(-0.5f, -0.5f, 0.0f),vec3(1.0f, 0.0f, 0.0f)},
            Vertex{vec3(0.5f, -0.5f, 0.0f),vec3(0.0f, 1.0f, 0.0f)},
            Vertex{vec3(0.0f, 0.5f, 0.0f),vec3(0.0f, 0.0f, 1.0f)},
    };
    std::vector<uint> indices = {
            0,1,2
    };
    Model test(vertices, indices);
    test.bufferModel();
    test.bindVertexArray();

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    window.update();

    SDL_Delay(50000);

}

