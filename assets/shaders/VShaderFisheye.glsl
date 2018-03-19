#version 130
#define fisheyeEffect 0.75 // fisheyeEffect < 0

in vec3 VertexPosition;  // VERTICE EN COORDENADAS LOCALES
in vec3 VertexNormal;    // NORMAL EL COORDENADAS LOCALES
in vec2 TextureCoords;   // COORDENADAS DE TEXTURA

out vec3 Position;    	// VERTICES EN COORDENADAS DE VISTA
out vec3 Normal;      	// NORMAL EN COORDENADAS DE VISTA
out vec2 TexCoords;   	// COORDENADAS DE TEXTURA
out mat4 FragViewMatrix;

uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform mat4 ViewMatrix;

vec4 ApplyFishEye(vec4 p){
    vec2 v = p.xy / p.w;
    float radius = length(v);
    if (radius > 0){
        float theta = atan(v.y,v.x);
        radius = pow(radius, fisheyeEffect);
        v.x = radius * cos(theta);
        v.y = radius * sin(theta);
        p.xy = v.xy * p.w;
    }
    return p;
}

void main() {
	// TRANSFORMAR VERTICE Y NORMAL A COORDENADAS DE VISTA
	Position = vec3 (ModelViewMatrix * vec4(VertexPosition, 1.0f));
	Normal = normalize (ModelViewMatrix * vec4(VertexNormal,0)).xyz;

	// LAS COORDENADAS DE TEXTURA NO SUFREN TRANSFORMACION
	TexCoords = TextureCoords;
	FragViewMatrix = ViewMatrix;
    
    // FISH EYE DISTORTION
	vec4 P = MVP * vec4(VertexPosition, 1.0f);
	gl_Position = ApplyFishEye(P);
} 