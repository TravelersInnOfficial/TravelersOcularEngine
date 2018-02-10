// VERTEX SHADER LIGHTING MAPS
layout (location = 0) in vec4 VertexPosition;  // VERTICE EN COORDENADAS LOCALES
layout (location = 1) in vec3 VertexNormal;    // NORMAL EL COORDENADAS LOCALES
layout (location = 2) in vec2 TextureCoords;   // COORDENADAS DE TEXTURA

out vec3 Position;    // VERTICES EN COORDENADAS DE VISTA
out vec3 Normal;      // NORMAL EN COORDENADAS DE VISTA
out vec2 TexCoords;   // COORDENADAS DE TEXTURA

uniform mat4 ModelViewMatrix;
uniform mat4 NormalMatrix;
uniform mat4 MVP;

void main()
{
	// TRANSFORMAR VERTICE Y NORMAL A COORDENADAS DE VISTA
	Position = vec3 (ModelViewMatrix * VertexPosition);
	Normal = normalize (NormalMatrix * VertexNormal);

	// LAS COORDENADAS DE TEXTURA NO SUFREN TRANSFORMACION
	TexCoords = TextureCoords;    

	// TRANSFORMAR Y PROYECTAR EL VERTICE (POSICION DEL FRAGMENTO)
	gl_Position = MVP * VertexPosition;
} 
