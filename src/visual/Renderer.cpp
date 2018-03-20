//
// Created by zakrent on 3/19/18.
//

#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

void Renderer::renderModel(Model &model, vec3 position, float rotVal, vec3 rotVec) {
    Shader* shader = model.shader;
    shader->use();
    if(!model.isBuffered){
        model.bufferModel();
    }

    glm::mat4 translationMatrix = glm::translate(glm::mat4(), position);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), rotVal, rotVec);
    glm::mat4 perspectiveMatrix = glm::perspective(120.0f, 1.0f, 0.01f, 500.0f);
    glm::mat4 combinedMatrix =
            perspectiveMatrix*translationMatrix*rotationMatrix;

    model.bindVertexArray();
    GLint combinedMatLocation = glGetUniformLocation(shader->m_programID, "combinedMatrix");
    glUniformMatrix4fv(combinedMatLocation, 1, GL_FALSE, &combinedMatrix[0][0]);
    glDrawElements(GL_TRIANGLES, model.getNumberOfIndices(), GL_UNSIGNED_INT, 0);
}

void Renderer::startRendering() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
}

const vec3 &Renderer::getCameraPos() const {
    return m_cameraPos;
}

void Renderer::setCameraPos(const vec3 &cameraPos) {
    Renderer::m_cameraPos = cameraPos;
}
