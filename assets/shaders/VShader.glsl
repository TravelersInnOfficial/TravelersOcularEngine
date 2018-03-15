#version 130

in vec3 VertexPosition;  // VERTICE EN COORDENADAS LOCALES
in vec3 VertexNormal;    // NORMAL EL COORDENADAS LOCALES
in vec2 TextureCoords;   // COORDENADAS DE TEXTURA

out vec3 Position;    // VERTICES EN COORDENADAS DE VISTA
out vec3 Normal;      // NORMAL EN COORDENADAS DE VISTA
out vec2 TexCoords;   // COORDENADAS DE TEXTURA
out mat4 FragViewMatrix;

uniform float uTime;	// Time from start

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;

uniform mat4 MVP;				//|
uniform mat4 ModelMatrix;		//|
uniform mat4 ViewMatrix;		//|
uniform mat4 ProjectionMatrix;	//| MVP -- Model * View * Projection

void main() {
	// TRANSFORMAR VERTICE Y NORMAL A COORDENADAS DE VISTA
	Position = vec3 (ModelViewMatrix * vec4(VertexPosition, 1.0f));		// VIEW * MODEL * VERTEXPOS
	Normal = normalize (ModelViewMatrix * vec4(VertexNormal,0)).xyz;

	// LAS COORDENADAS DE TEXTURA NO SUFREN TRANSFORMACION
	TexCoords = TextureCoords;
	FragViewMatrix = ViewMatrix;

	// TRANSFORMAR Y PROYECTAR EL VERTICE (POSICION DEL FRAGMENTO)
	gl_Position = MVP * vec4(VertexPosition, 1.0f);
} 
