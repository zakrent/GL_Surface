//
// Created by zakrent on 3/19/18.
//

#include "Renderer.h"
#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>

void Renderer::renderAll() {

    uint shadowFB;
    glGenFramebuffers(1, &shadowFB);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFB);
    glViewport(0, 0, 1024, 1024);

    uint shadowTexture;
    glGenTextures(1, &shadowTexture);
    glBindTexture(GL_TEXTURE_2D, shadowTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D, shadowTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        exit(-1);

    vec3 sunPos = sunVector*100.0f+m_cameraPos;
    glm::mat4 shadowProjectionMat = glm::ortho<float>(0, 100, -30, 30, 0.1, 200);
    glm::mat4 shadowViewMat = glm::lookAt(sunPos, sunPos-sunVector, glm::cross(sunVector, vec3(1.0f, 0.0f, 0.0f)));
    glm::mat4 shadowPVMat = shadowProjectionMat*shadowViewMat;

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    depthShader.use();
    renderScene(shadowPVMat, &depthShader);


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Window::WIDTH, Window::HEIGHT);

    glDrawBuffer(GL_BACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float aspect = Window::WIDTH*1.0f/Window::HEIGHT;
    glm::mat4 cameraProjectionMat = glm::perspective(120.0f, aspect, 0.1f, 100.0f);
    glm::mat4 cameraViewMat = glm::lookAt(m_cameraPos, m_cameraPos+vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 cameraPVMat = cameraProjectionMat*cameraViewMat;

    glActiveTexture(GL_TEXTURE0);

    basicShader.use();
    GLint sunVectorLocation = glGetUniformLocation(basicShader.m_programID, "sunVector");
    GLint shadowPVMatLocation = glGetUniformLocation(basicShader.m_programID, "shadowPVMatrix");
    GLint shadowZMapLocation = glGetUniformLocation(basicShader.m_programID, "shadowZMap");
    glUniform3fv(sunVectorLocation, 1, &sunVector[0]);
    glUniformMatrix4fv(shadowPVMatLocation, 1, GL_FALSE, &shadowPVMat[0][0]);
    glUniform1i(shadowZMapLocation, 0);
    renderScene(cameraPVMat, &basicShader);

    glDeleteTextures(1, &shadowTexture);
    glDeleteFramebuffers(1, &shadowFB);

    renderables.clear();
}

void Renderer::renderScene(glm::mat4 PVMat, Shader* shader) const {
    for(Renderable renderable : renderables){
        if(!renderable.m_model->isBuffered)
            renderable.m_model->bufferModel();

        renderable.m_model->bindVertexArray();

        glm::mat4 MWMat = translate(glm::mat4(), renderable.m_pos);

        GLint PVMatrixLocation = glGetUniformLocation(shader->m_programID, "PVMatrix");
        GLint MWMatrixLocation = glGetUniformLocation(shader->m_programID, "MWMatrix");
        glUniformMatrix4fv(PVMatrixLocation, 1, GL_FALSE, &PVMat[0][0]);
        glUniformMatrix4fv(MWMatrixLocation, 1, GL_FALSE, &MWMat[0][0]);

        glDrawElements(GL_TRIANGLES, renderable.m_model->getNumberOfIndices(), GL_UNSIGNED_INT, 0);
    }
}

const vec3 &Renderer::getCameraPos() const {
    return m_cameraPos;
}

void Renderer::setCameraPos(const vec3 &cameraPos) {
    m_cameraPos = cameraPos;
}

void Renderer::registerModel(Model *model, vec3 position) {
    renderables.push_back(Renderable{model, position});
}

Renderer::Renderer() : depthShader("depthShader"), basicShader("basic"){
    sunVector = vec3(0.0f, 0.8f, 0.2f);
}
