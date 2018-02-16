#version 130

in vec3 VertexPosition;   // VERTICE EN COORDENADAS LOCALES
in vec3 VertexColor;      // COLOR PROVISIONAL

//layout (location = 0) in vec3 VertexPosition; // VERTICE EN COORDENADAS LOCALES
//layout (location = 1) in vec3 VertexNormal;   // NORMAL EL COORDENADAS LOCALES
//layout (location = 2) in vec2 TextureCoords;  // COORDENADAS DE TEXTURA

//uniform mat4 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

out vec3 color;

void main(){
    color = VertexColor;
    gl_Position = ProjectionMatrix *  ViewMatrix * ModelViewMatrix * vec4(VertexPosition, 1.0);
}