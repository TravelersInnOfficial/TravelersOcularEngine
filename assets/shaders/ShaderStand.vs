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

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
out vec4 ShadowCoord;       // VERTICES DESDE LA LUZ
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

//bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
out vec4 ShadowCoordArray[40];       // VERTICES DESDE LA LUZ
//bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb

// IN UNIFORMS
uniform mat4 ModelMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;
uniform mat4 ViewMatrix;
uniform vec2 TextureScale;
// ############  DON'T CHANGE ABOVE THIS LINE  ######################################################

// IN UNIFORM FOR ONLY THIS SHADER
//bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
uniform mat4 DepthBiasMVPArray[40];		// Son las MVP de cada luz
uniform int nshadowlights;				// NUMBER OF CURRENT SHADOW LIGHTS
//bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
uniform mat4 DepthBiasMVP;				// Son las MVP de cada luz, habria que enviar un array del MVP de cada luz con sombra
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

void main() {
	// TRANSFORMAR VERTICE Y NORMAL A COORDENADAS DE VISTA
	Position = vec3 (ModelViewMatrix * vec4(VertexPosition, 1.0));
	
	//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
	ShadowCoord = DepthBiasMVP * vec4(VertexPosition,1.0);		// En realidad deberia haber un array de ShadowCoord, uno por cada luz con sombra
	//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

	//bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
	for (int i = 0; i < 0/*nshadowlights*/; i++){
		ShadowCoordArray[i] = DepthBiasMVPArray[i] * vec4(VertexPosition,1.0);
	}
	//bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb

	// LAS COORDENADAS DE TEXTURA NO SUFREN TRANSFORMACION
	TexCoords.x = TextureCoords.x * TextureScale.x;
	TexCoords.y = TextureCoords.y * TextureScale.y;

	FragViewMatrix = ViewMatrix;

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

	// TRANSFORMAR Y PROYECTAR EL VERTICE (POSICION DEL FRAGMENTO)
	gl_Position = MVP * vec4(VertexPosition, 1.0);
}