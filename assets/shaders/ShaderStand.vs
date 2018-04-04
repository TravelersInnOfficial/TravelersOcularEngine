#version 130

// ##################################################################################################
// IN VARIABLES
in vec3 VertexPosition;     // VERTICE EN COORDENADAS LOCALES
in vec3 VertexNormal;       // NORMAL EL COORDENADAS LOCALES
in vec2 TextureCoords;      // COORDENADAS DE TEXTURA
// OUT VARIABLES TO FRAGMENT
out vec3 Position;    	    // VERTICES EN COORDENADAS DE VISTA
out vec3 Normal;      	    // NORMAL EN COORDENADAS DE VISTA
out vec2 TexCoords;   	    // COORDENADAS DE TEXTURA
out mat4 FragViewMatrix;    // VIEW MATRIX
out vec4 ShadowCoord;       // VERTICES DESDE LA LUZ
// IN UNIFORMS
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform mat4 ViewMatrix;
// ############  DON'T CHANGE ABOVE THIS LINE  ######################################################
uniform mat4 DepthBiasMVP;


void main() {
	// TRANSFORMAR VERTICE Y NORMAL A COORDENADAS DE VISTA
	Position = vec3 (ModelViewMatrix * vec4(VertexPosition, 1.0));
	Normal = normalize (ModelViewMatrix * vec4(VertexNormal,0)).xyz;
	ShadowCoord = DepthBiasMVP * vec4(VertexPosition,1.0);

	// LAS COORDENADAS DE TEXTURA NO SUFREN TRANSFORMACION
	TexCoords = TextureCoords;
	FragViewMatrix = ViewMatrix;

	// TRANSFORMAR Y PROYECTAR EL VERTICE (POSICION DEL FRAGMENTO)
	gl_Position = MVP * vec4(VertexPosition, 1.0);
}