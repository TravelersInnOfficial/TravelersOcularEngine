#version 130

in vec3 VertexPosition;  // VERTICE EN COORDENADAS LOCALES
in vec3 ParticleCenter;	 // CENTRO DE LA PARTICULA Y SIZE
in vec3 ParticleColor;	 // COLOR DE LA PARTICULA
in vec2 ParticleExtra;	 // SIZE Y ROTATION DE LA PARTICULA

uniform mat4 MVP;		 // MATRIZ MODELO*VISTA*PROYECCION

out vec2 TexCoords;   	// COORDENADAS DE TEXTURA
out vec3 FinalColor;	// COLOR DE LA PARTICULA

void main(){
	float cosine = cos(ParticleExtra.y);
	float sine = sin(ParticleExtra.y);
	mat3 A;
	A[0] = vec3(cosine	, sine 		, 0.0);
	A[1] = vec3(-sine	, cosine	, 0.0);
	A[2] = vec3(0.0 	, 0.0 		, 0.0);

	vec3 Vertex = VertexPosition * A;
	vec3 Position = Vertex * ParticleExtra.x + ParticleCenter;

    gl_Position =  MVP * vec4(Position,1);

    TexCoords = VertexPosition.xy + vec2(0.5, 0.5);
    FinalColor = ParticleColor;
}