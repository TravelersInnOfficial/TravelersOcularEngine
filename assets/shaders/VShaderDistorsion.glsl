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
    vec4 worldPos = ModelMatrix * vec4(VertexPosition, 1.0);
	
    float wobbleOffset = (worldPos.x + worldPos.z) * 0.5;
    float wobbleScale  = 0.7;
    worldPos.x += cos(uTime + wobbleOffset) * wobbleScale;
    worldPos.z += sin(uTime + wobbleOffset) * wobbleScale;

	Position = vec3 (ViewMatrix * worldPos);
	Normal = normalize (ModelViewMatrix * vec4(VertexNormal,0)).xyz;

    gl_Position = ProjectionMatrix * ViewMatrix  * worldPos;
    TexCoords = TextureCoords;
	FragViewMatrix = ViewMatrix;
} 
