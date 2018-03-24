#version 330 core

out vec4 color;
in vec3 RGBColor;
in vec3 normal;
in vec4 lightPos;

uniform vec3 sunVector;
uniform sampler2D shadowZMap;

void main(){
    float lightMag = 0.1f;
    lightMag += clamp(dot(normal, sunVector), 0.0f, 1.0f);

    vec2 UV;
    UV.x = 0.5*lightPos.x+0.5;
    UV.y = 0.5*lightPos.y+0.5;
    float depth = texture(shadowZMap, UV).x;
    float curDepth = lightPos.z*0.5+0.5;
    if (depth < curDepth-0.01){
       lightMag *= 0.2f;
    }

    //color = texture(shadowZMap, UV)+vec4(vec3(0.25f),1.0f);
    color = vec4(RGBColor*lightMag, 1.0f);
}