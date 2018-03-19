//
// Created by zakrent on 3/18/18.
//

#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <cstring>


void Shader::loadFromFile(const std::string &filename) {
    const std::string vsFilename = filename+".vs";
    const std::string fsFilename = filename+".fs";
    std::ifstream vsFile("res/shaders/"+vsFilename);
    std::ifstream fsFile("res/shaders/"+fsFilename);
    std::string tmpString;
    while(!(vsFile.eof() && fsFile.eof())){
        if(!vsFile.eof() && !vsFile.fail()){
            std::getline(vsFile, tmpString);
            vertexShaderSource.append(tmpString+"\n");
        }
        if(!fsFile.eof() && !fsFile.fail()){
            std::getline(fsFile, tmpString);
            fragmentShaderSource.append(tmpString+"\n");
        }
    }

}

uint Shader::compileShader(const std::string& source, uint type){
    uint id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(!result){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cerr<<message<<"\n";
        glDeleteShader(id);
        return 0;
    }

    return id;
}

void Shader::createShader() {
    uint program = glCreateProgram();
    uint vs = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    uint fs = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    m_programID = program;
}

void Shader::use() {
    glUseProgram(m_programID);
}

Shader::Shader(const std::string &filename) {
    loadFromFile(filename);
    createShader();
}
