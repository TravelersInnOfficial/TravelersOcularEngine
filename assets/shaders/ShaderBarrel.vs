#version 130
// ##################################################################################################
// IN VARIABLES
in vec3 VertexPosition;     // VERTICE EN COORDENADAS LOCALES
in vec3 VertexNormal;       // NORMAL EL COORDENADAS LOCALES
in vec2 TextureCoords;      // COORDENADAS DE TEXTURA
// OUT VARIABLES TO FRAGMENT
out vec3 Position;    	    // VERTICES EN COORDENADAS DE VISTA
out vec2 TexCoords;   	    // COORDENADAS DE TEXTURA
out mat4 FragViewMatrix;    // VIEW MATRIX
out mat4 RotationNormal;
out vec4 ShadowCoordArray[20];	// VERTICES DESDE LA LUZ
// IN UNIFORMS
uniform mat4 ModelMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform mat4 ViewMatrix;
uniform vec2 TextureScale;
// ############  DON'T CHANGE ABOVE THIS LINE  ######################################################

uniform mat4 DepthBiasMVPArray[20];		// Son las MVP de cada luz
uniform int nshadowlights;				// NUMBER OF CURRENT SHADOW LIGHTS

#define DIST_VALUE 1.25 // DISTORSION VALUE < 0

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
	// LAS COORDENADAS DE TEXTURA NO SUFREN TRANSFORMACION
	TexCoords.x = TextureCoords.x * TextureScale.x;
	TexCoords.y = TextureCoords.y * TextureScale.y;
	FragViewMatrix = ViewMatrix;
    // ############  DON'T CHANGE ABOVE THIS LINE  ######################################################

	for (int i = 0; i < nshadowlights; i++){
		ShadowCoordArray[i] = (DepthBiasMVPArray[i] * ModelMatrix) * vec4(VertexPosition,1.0);
	}

    // FISH EYE DISTORTION
	vec4 P = MVP * vec4(VertexPosition, 1.0);
	gl_Position = ApplyFishEye(P);

    // CALCULAR LA MATRIZ DE ROTACION DE LA NORMAL

    vec3 B =  normalize (vec4(0,0,1,0)).xyz;
    vec3 A = normalize (ModelViewMatrix * vec4(VertexNormal,0)).xyz;

    vec3 v = cross(A,B);

    mat3 ssc;
    ssc[0] = vec3(0, -v[2], v[1]);
    ssc[1] = vec3(v[2], 0, -v[0]);
    ssc[2] = vec3(-v[1], v[0], 0);

    mat3 R = mat3(1) + ssc + (ssc*ssc)*(1-dot(A,B))/(length(v*v));

    RotationNormal =  mat4(R);
}