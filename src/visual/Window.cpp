//
// Created by zakrent on 3/18/18.
//

#include "Window.h"
#include "Shader.h"
#include <GL/glew.h>
#include <iostream>


Window::Window() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow((char*)"OpenGL test!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    m_context = SDL_GL_CreateContext(m_window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr<<"GLEW Error: " << glewGetErrorString(err) << "\n";
        exit(1);
    }
    glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Window::update() {
    SDL_GL_SwapWindow(m_window);
}
