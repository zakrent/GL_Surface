#version 330 core

out vec4 color;
in vec3 RGBColor;
in vec3 normal;

void main(){
    float lightMag = dot(normal, vec3(0.0f, 0.0f, 1.0f));
    color = vec4(RGBColor*lightMag, 1.0f);
}