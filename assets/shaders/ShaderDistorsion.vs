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
uniform float TextureScale;
// ############  DON'T CHANGE ABOVE THIS LINE  ######################################################

// IN UNIFORM FOR ONLY THIS SHADER 
uniform float frameTime;	// Time from start
uniform mat4 ModelMatrix;		//|
//uniform mat4 ViewMatrix;		//|
uniform mat4 ProjectionMatrix;	//| MVP -- Model * View * Projection

void main() {
    // ##################################################################################################
	// TRANSFORM VERTEX AND NORMAL TO VIEW COORDINATES
	Position = vec3 (ModelViewMatrix * vec4(VertexPosition, 1.0));
	Normal = normalize (ModelViewMatrix * vec4(VertexNormal,0)).xyz;
	// PASS COORDS AND VIEW MATRIX
	TexCoords = TextureCoords * TextureScale;
	FragViewMatrix = ViewMatrix;
    ShadowCoord = vec4(0.0);
    // ############  DON'T CHANGE ABOVE THIS LINE  ######################################################

    vec4 finalPosition = ModelMatrix * vec4(VertexPosition, 1.0);
	
    float offset = (finalPosition.x + finalPosition.z) * 0.5;
    float scale  = 0.7;
    finalPosition.x += cos(frameTime + offset) * scale;
    finalPosition.z += sin(frameTime + offset) * scale;

    gl_Position = ProjectionMatrix * ViewMatrix  * finalPosition;
}