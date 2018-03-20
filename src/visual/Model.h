//
// Created by zakrent on 3/18/18.
//

#ifndef GL_SURFACE_MODEL_H
#define GL_SURFACE_MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"

using glm::vec3;

struct Vertex{
    vec3 position;
    vec3 color;
    vec3 normal;
};

class Model {
    uint m_vertexArray;
    uint m_elementBuffer;
    uint m_vertexBuffer;
    std::vector<Vertex> m_vertices;
    std::vector<uint> m_indices;
    int m_numberOfIndices;

public:
    Shader* shader;
    bool isBuffered;
    void bufferModel();
    void deleteBuffers();
    void bindVertexArray();

    int getNumberOfIndices() const;

    void setVertices(const std::vector<Vertex> &m_vertices);
    void setIndices(const std::vector<uint> &m_indices);

    Model(Shader* shader);
    Model(Shader* shader, std::vector<Vertex> vertices, std::vector<uint> indices);
    ~Model();
};


#endif //GL_SURFACE_MODEL_H
