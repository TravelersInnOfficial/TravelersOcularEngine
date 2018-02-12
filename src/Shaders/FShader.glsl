#version 130

in float color;
out vec4 outColor;

void main(){
    outColor = vec4(vec3(color), 1.0);
}