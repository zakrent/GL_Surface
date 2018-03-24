//
// Created by zakrent on 3/19/18.
//

#ifndef GL_SURFACE_RENDERER_H
#define GL_SURFACE_RENDERER_H

#include "Model.h"

struct Renderable{
    Model* m_model;
    vec3 m_pos;
};

class Renderer {
    vec3 m_cameraPos;
    vec3 sunVector;
    Shader depthShader;
    Shader basicShader;
    std::vector<Renderable> renderables;
    void renderScene(glm::mat4 PVMat, Shader *shader) const;
public:
    void renderAll();
    void registerModel(Model* model, vec3 position);

    const vec3 &getCameraPos() const;
    void setCameraPos(const vec3 &cameraPos);
    Renderer();

};


#endif //GL_SURFACE_RENDERER_H
