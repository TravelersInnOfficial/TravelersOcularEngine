#version 130
// VERTEX SHADER LIGHTING MAPS
in vec3 VertexPosition;  // VERTICE EN COORDENADAS LOCALES
in vec3 VertexNormal;    // NORMAL EL COORDENADAS LOCALES
in vec2 TextureCoords;   // COORDENADAS DE TEXTURA

out vec3 Position;    // VERTICES EN COORDENADAS DE VISTA
out vec3 Normal;      // NORMAL EN COORDENADAS DE VISTA
out vec2 TexCoords;   // COORDENADAS DE TEXTURA
out vec3 WorldPosition;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;
uniform mat4 ModelMatrix;

void main() {
	// TRANSFORMAR VERTICE Y NORMAL A COORDENADAS DE VISTA
	Position = vec3 (ModelViewMatrix * vec4(VertexPosition, 1.0f));
	WorldPosition = vec3 (ModelMatrix * vec4(VertexPosition, 1.0f));
	Normal = normalize (ModelViewMatrix * vec4(VertexNormal,0)).xyz;

	// LAS COORDENADAS DE TEXTURA NO SUFREN TRANSFORMACION
	TexCoords = TextureCoords;    

	// TRANSFORMAR Y PROYECTAR EL VERTICE (POSICION DEL FRAGMENTO)
	gl_Position = MVP * vec4(VertexPosition, 1.0f);
} 
