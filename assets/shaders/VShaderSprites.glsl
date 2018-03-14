#version 130

in vec2 VertexPosition;
in vec2 TextureCoords;
in vec4 overColor;

out vec2 FragTexCoords;
out vec4 FragOverColor;

void main(){
    FragTexCoords = TextureCoords;
    FragOverColor = overColor;
    gl_Position = vec4(VertexPosition, 0.0f,1);
}