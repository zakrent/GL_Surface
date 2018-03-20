//
// Created by zakrent on 3/19/18.
//

#ifndef GL_SURFACE_RENDERER_H
#define GL_SURFACE_RENDERER_H

#include "Model.h"

class Renderer {
    vec3 m_cameraPos;
public:
    void startRendering();
    void renderModel(Model& model, vec3 position, float rotVal, vec3 rotVec);

    const vec3 &getCameraPos() const;
    void setCameraPos(const vec3 &cameraPos);
};


#endif //GL_SURFACE_RENDERER_H
