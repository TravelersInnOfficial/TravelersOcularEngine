#version 130

in vec2 position;
in float vertexColor;

uniform mat4 transform;

out float color;

void main(){
    color = vertexColor;
    gl_Position = transform * vec4(position, 0.0, 1.0);
}