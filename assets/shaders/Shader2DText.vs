#version 130

in vec2 VertexPosition;
in vec2 TextureCoords;

out vec2 FragTexCoords;

void main(){
    FragTexCoords = TextureCoords;
    
    gl_Position = vec4(VertexPosition, 0.0f,1.0f);
}