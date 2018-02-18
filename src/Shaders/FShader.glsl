#version 130

in vec2 UV;

out vec3 outColor;

uniform sampler2D myTextureSampler;

void main(){
    outColor = texture(myTextureSampler, UV).rgb;
}