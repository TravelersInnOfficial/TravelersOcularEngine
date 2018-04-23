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
uniform vec2 TextureScale;
// ############  DON'T CHANGE ABOVE THIS LINE  ######################################################

#define DIST_VALUE 0.75 // DISTORSION VALUE < 0

// Distorse view
vec4 ApplyFishEye(vec4 p){
    vec2 v = p.xy / p.w;
    float radius = length(v);
    if (radius > 0){
        float theta = atan(v.y,v.x);
        radius = pow(radius, DIST_VALUE);
        v.x = radius * cos(theta);
        v.y = radius * sin(theta);
        p.xy = v.xy * p.w;
    }
    return p;
}

void main() {
    // ##################################################################################################
	// TRANSFORM VERTEX AND NORMAL TO VIEW COORDINATES
	Position = vec3 (ModelViewMatrix * vec4(VertexPosition, 1.0));
	Normal = normalize (ModelViewMatrix * vec4(VertexNormal,0)).xyz;
	// LAS COORDENADAS DE TEXTURA NO SUFREN TRANSFORMACION
	TexCoords.x = TextureCoords.x * TextureScale.x;
	TexCoords.y = TextureCoords.y * TextureScale.y;
	FragViewMatrix = ViewMatrix;
    ShadowCoord = vec4(0.0);
    // ############  DON'T CHANGE ABOVE THIS LINE  ######################################################

    // FISH EYE DISTORTION
	vec4 P = MVP * vec4(VertexPosition, 1.0);
	gl_Position = ApplyFishEye(P);
}