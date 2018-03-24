#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 MWMatrix;
uniform mat4 PVMatrix;

void main(){
    mat4 combinedMatrix = PVMatrix*MWMatrix;
    gl_Position = combinedMatrix*position;
}
