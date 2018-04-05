#version 130

in vec2 VertexPosition;
in vec2 TextureCoords;
in vec2 MaskCoords;
in vec4 overColor;

out vec2 MaskTexCoords;
out vec2 FragTexCoords;
out vec4 FragOverColor;

void main(){
    FragTexCoords = TextureCoords;
    MaskTexCoords = MaskCoords;
    FragOverColor = overColor;
    gl_Position = vec4(VertexPosition, 0.0,1);
}