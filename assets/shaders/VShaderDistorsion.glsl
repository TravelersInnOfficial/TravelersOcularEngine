#version 130

in vec3 VertexPosition;  // VERTICE EN COORDENADAS LOCALES
in vec3 VertexNormal;    // NORMAL EL COORDENADAS LOCALES
in vec2 TextureCoords;   // COORDENADAS DE TEXTURA

out vec3 Position;    // VERTICES EN COORDENADAS DE VISTA
out vec3 Normal;      // NORMAL EN COORDENADAS DE VISTA
out vec2 TexCoords;   // COORDENADAS DE TEXTURA
out mat4 FragViewMatrix;

uniform float frameTime;	// Time from start
uniform mat4 ModelViewMatrix;
uniform mat4 ModelMatrix;		//|
uniform mat4 ViewMatrix;		//|
uniform mat4 ProjectionMatrix;	//| MVP -- Model * View * Projection

void main() {
    vec4 finalPosition = ModelMatrix * vec4(VertexPosition, 1.0);
	
    float offset = (finalPosition.x + finalPosition.z) * 0.5;
    float scale  = 0.7;
    finalPosition.x += cos(frameTime + offset) * scale;
    finalPosition.z += sin(frameTime + offset) * scale;

	Position = vec3 (ViewMatrix * finalPosition);
	Normal = normalize (ModelViewMatrix * vec4(VertexNormal,0)).xyz;

    gl_Position = ProjectionMatrix * ViewMatrix  * finalPosition;
    TexCoords = TextureCoords;
	FragViewMatrix = ViewMatrix;
} 
