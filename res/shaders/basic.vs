#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 RGBcolor;

out vec4 RGBAcolor;

void main(){
    gl_Position = position;
    RGBAcolor = vec4(RGBcolor, 1.0);
}
