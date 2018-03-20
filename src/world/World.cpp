//
// Created by zakrent on 3/20/18.
//

#include "World.h"
#include <glm/gtc/noise.hpp>

World::World(vec3 center, Shader *shader) : m_model(shader){
    indicesCalculated = false;
    generateWorld(center);
    updateModel();
}

void World::generateWorld(vec3 center) {
    centerWorld(center);
    float unitSize = sideLength/worldSize;
    for(int x = 0; x < worldSize; x++) {
        for (int y = 0; y < worldSize; y++) {
            m_heightMap[x][y] = getPerlinNoise(vec2(unitSize*x, unitSize*y), 1.0f);
        }
    }
}

void World::updateModel() {
    float unitSize = sideLength/worldSize;
    std::vector<Vertex> vertices;
    std::vector<uint> indices;
    for(int x = 0; x < worldSize; x++){
        for(int y = 0; y < worldSize; y++){
            //vec3 color = vec3(2*m_heightMap[x][y], 0.6f, m_heightMap[x][y]);
            vec3 color = vec3(0.0f, 1.0f, 0.0f);
            vec3 normal = getPerlinNoiseNormal(vec2(x*unitSize, y*unitSize), 0.5f);
            vertices.push_back(Vertex{vec3(x*unitSize, y*unitSize, m_heightMap[x][y]),
                                      color, normal});
            if(!indicesCalculated && x != worldSize-1 && y != worldSize-1) {
                indices.push_back(static_cast<unsigned int &&>(x + y * worldSize));
                indices.push_back(static_cast<unsigned int &&>(x + y * worldSize + 1));
                indices.push_back(static_cast<unsigned int &&>(x + (y + 1) * worldSize));
                indices.push_back(static_cast<unsigned int &&>(x + y * worldSize + 1));
                indices.push_back(static_cast<unsigned int &&>(x + (y + 1) * worldSize + 1));
                indices.push_back(static_cast<unsigned int &&>(x + (y + 1) * worldSize));
            }
        }
    }
    m_model.setVertices(vertices);
    if(!indicesCalculated){
        m_model.setIndices(indices);
        indicesCalculated = true;
    }
    m_model.bufferModel();
}

void World::centerWorld(vec3 center) {
    m_position = center - vec3(0.5*sideLength, 0.5*sideLength, 0);
}

float World::getPerlinNoise(vec2 pos, float seed) {
    return glm::perlin(vec3(pos.x, pos.y, seed)*0.1f)*5.0f;
}

vec3 World::getPerlinNoiseNormal(vec2 pos, float seed) {
    float dX = 0.1f;
    float dY = 0.1f;
    float XDiff = (-getPerlinNoise(pos, seed)
                       +getPerlinNoise(pos+vec2(dX, 0), seed));
    float YDiff = (-getPerlinNoise(pos, seed)
                       +getPerlinNoise(pos+vec2(0, dY), seed));
    vec3 XGrad = vec3(dX, 0, XDiff);
    vec3 YGrad = vec3(0, dY, YDiff);
    vec3 normal = glm::normalize(glm::cross(XGrad, YGrad));
    return normal;
}

