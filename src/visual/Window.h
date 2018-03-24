//
// Created by zakrent on 3/18/18.
//

#ifndef GL_SURFACE_WINDOW_H
#define GL_SURFACE_WINDOW_H

#include <SDL.h>

class Window {
public:
    static const int WIDTH = 1000;
    static const int HEIGHT = 600;
    SDL_Window* m_window;
    SDL_GLContext m_context;

    void update();

    Window();
    ~Window();
};


#endif //GL_SURFACE_WINDOW_H
