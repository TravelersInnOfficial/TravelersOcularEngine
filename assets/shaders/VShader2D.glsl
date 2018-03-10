#version 130

in vec3 position;
in vec3 color;

out vec3 FragmentColor;

void main(){
    FragmentColor = color;
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}