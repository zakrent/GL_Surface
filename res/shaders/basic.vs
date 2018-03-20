#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;

uniform mat4 combinedMatrix;

out vec3 RGBColor;
out vec3 normal;

void main(){
    gl_Position = combinedMatrix*position;
    normal = inNormal;
    RGBColor = inColor;
}
