#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;

uniform mat4 MWMatrix;
uniform mat4 PVMatrix;
uniform mat4 shadowPVMatrix;

out vec3 RGBColor;
out vec3 normal;
out vec4 lightPos;

void main(){
    mat4 combinedMatrix = PVMatrix*MWMatrix;
    gl_Position = combinedMatrix*position;
    mat4 shadowMatrix = shadowPVMatrix*MWMatrix;
    lightPos = shadowMatrix*position;
    normal = inNormal;
    RGBColor = inColor;
}
