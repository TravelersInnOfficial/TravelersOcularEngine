#version 130

in vec3 VertexPosition;  // VERTICE EN COORDENADAS LOCALES
in vec4 ParticleCenter;	 // CENTRO DE LA PARTICULA Y SIZE
in vec3 ParticleColor;	 // COLOR DE LA PARTICULA

uniform mat4 MVP;		 // MATRIZ MODELO*VISTA*PROYECCION

out vec2 TexCoords;   	// COORDENADAS DE TEXTURA
out vec3 FinalColor;	// COLOR DE LA PARTICULA

void main(){
	//vec3 Position = ParticleCenter.xyz + VertexPosition * ParticleCenter.w;
	vec3 Position = VertexPosition.xyz * ParticleCenter.w + ParticleCenter.xyz;

    gl_Position =  MVP * vec4(Position,1);

    TexCoords = VertexPosition.xy + vec2(0.5, 0.5);
    FinalColor = ParticleColor;
}