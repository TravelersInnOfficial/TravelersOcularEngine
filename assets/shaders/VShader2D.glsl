#version 130

in vec2 position;
in vec4 color;

out vec4 FragmentColor;

void main(){
    FragmentColor = color;
    gl_Position = vec4(position.x, position.y, 0.0f, 1.0);
}