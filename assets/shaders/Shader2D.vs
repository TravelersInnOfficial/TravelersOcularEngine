#version 130

in vec2 position;
in vec4 color;
in vec2 MaskCoords;

out vec4 FragmentColor;
out vec2 MaskTexCoords;

void main(){
    FragmentColor = color;
    MaskTexCoords = MaskCoords;
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
}