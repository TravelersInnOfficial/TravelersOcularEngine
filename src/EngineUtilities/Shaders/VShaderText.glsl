#version 130

in vec3 VertexPosition;  // VERTICE EN COORDENADAS LOCALES
in vec2 TextureCoords;   // COORDENADAS DE TEXTURA

uniform mat4 MVP;		 // MATRIZ MODELO*VISTA*PROYECCION

out vec2 TexCoords;   // COORDENADAS DE TEXTURA

void main(){
    gl_Position =  MVP * vec4(VertexPosition,1);
    TexCoords = TextureCoords;
}