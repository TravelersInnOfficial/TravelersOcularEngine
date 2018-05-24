#version 130

in vec4 VertexPosition;  // VERTICE EN COORDENADAS LOCALES
uniform mat4 MVP;		 // MATRIZ MODELO*VISTA*PROYECCION

void main(){
    gl_Position =  MVP * VertexPosition;
}