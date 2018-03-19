//
// Created by zakrent on 3/18/18.
//

#ifndef GL_SURFACE_SHADER_H
#define GL_SURFACE_SHADER_H

#include <string>

class Shader {
    uint m_programID;
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    uint compileShader(const std::string& source, uint type);
    void createShader();
    void loadFromFile(const std::string& filename);
public:
    void use();
    Shader(const std::string& filename);
};


#endif //GL_SURFACE_SHADER_H
