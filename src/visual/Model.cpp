//
// Created by zakrent on 3/18/18.
//

#include "Model.h"

Model::Model() {
    isBuffered = false;
    glGenVertexArrays(1, &m_vertexArray);
    m_elementBuffer = 0;
    m_vertexBuffer = 0;
}

Model::Model(std::vector<Vertex> vertices, std::vector<uint> indices)
        : Model() {
    setVertices(vertices);
    setIndices(indices);
}

void Model::bindVertexArray() {
    glBindVertexArray(m_vertexArray);
}


Model::~Model() {
    deleteBuffers();
    glDeleteVertexArrays(1, &m_vertexArray);
}

void Model::bufferModel() {
    deleteBuffers();
    bindVertexArray();

    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(Vertex), m_vertices.data(), GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glGenBuffers(1, &m_elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size()*sizeof(uint), m_indices.data(), GL_STATIC_DRAW);

    isBuffered = true;
    m_numberOfIndices = static_cast<int>(m_indices.size());
}

void Model::deleteBuffers() {
    if(m_elementBuffer != 0)
        glDeleteBuffers(1, &m_elementBuffer);
    if(m_vertexBuffer != 0)
        glDeleteBuffers(1, &m_vertexBuffer);
}

void Model::setVertices(const std::vector<Vertex> &vertices) {
    isBuffered = false;
    Model::m_vertices = vertices;
}

void Model::setIndices(const std::vector<uint> &indices) {
    isBuffered = false;
    Model::m_indices = indices;
}

int Model::getNumberOfIndices() const {
    return m_numberOfIndices;
}

