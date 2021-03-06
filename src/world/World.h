//
// Created by zakrent on 3/20/18.
//

#ifndef GL_SURFACE_WORLD_H
#define GL_SURFACE_WORLD_H

#include <glm/glm.hpp>
#include "../visual/Model.h"
using glm::vec2;

class World {
    bool indicesCalculated;
    static const int worldSize = 48;
    static constexpr float sideLength = 100.0f;
    float m_heightMap[worldSize][worldSize];
    void centerWorld(vec3 center);
    float getPerlinNoise(vec2 offset, float seed);
    vec3 getPerlinNoiseNormal(vec2 offset, float seed);
public:
    vec3 m_position;
    Model m_model;
    bool hasChanged;
    void generateWorld(vec3 center);
    void updateModel();
    explicit World(vec3 center);
};


#endif //GL_SURFACE_WORLD_H
