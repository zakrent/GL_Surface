//
// Created by zakrent on 3/18/18.
//

#ifndef GL_SURFACE_SHADER_H
#define GL_SURFACE_SHADER_H

#include <string>

class Shader {
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    uint compileShader(const std::string& source, uint type);
    void createShader();
    void loadFromFile(const std::string& filename);
public:
    uint m_programID;
    void use();
    Shader(const std::string& filename);
};


#endif //GL_SURFACE_SHADER_H
