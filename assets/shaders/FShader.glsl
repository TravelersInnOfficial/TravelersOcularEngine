#version 130

// TEMPORAL TEXTURE WITHOUT MATERIALS
uniform sampler2D myTextureSampler;

// ENTRADA, PROVENIENTE DEL VERTEX SHADER
in vec3 Position;  		// VERTICES EN COORDENADAS DE VISTA
in vec3 Normal;  		// NORMAL EN COORDENADAS DE VISTA
in vec2 TexCoords;      // UV COORDENADAS DE TEXTURA
in vec3 WorldPosition;  // VERTICES EN COORDENADAS DE MUNDO
  
// SALIDA PARA COMUNICAR CON EL RESTO DEL PIPELINE
out vec4 FragColor;	// COLOR FINAL DEL FRAGMENTO

// ESTRUCTURA PARA GUARDAR EL MATERIAL.
struct TMaterial {
	vec3  Diffuse;
	vec3  Specular;
	vec3  Ambient;
	float Shininess;
};
uniform TMaterial Material;

// ESTRUCTURA PARA GUARDAR LAS LUCES (POSICION, Y PROPIEDADES AMBIENTAL, DIFUSA Y ESPECULAR DE LA LUZ)
struct TLight {
	vec3 Position;
	vec3 Diffuse;
	vec3 Specular;
	float Attenuation;
};

uniform TLight Light[20];
uniform int nlights;

// LUZ AMBIENTE
struct SLight{ vec3 AmbientLight; };
uniform SLight SpecialLight;

uniform mat4 ViewMatrix;

// FUNCION QUE CALCULA EL MODELO DE REFLEXION DE PHONG
vec3  Phong (int num) {
	vec3 eyeDir = -Position;
	// CALCULAR LOS DIFERENTES VECTORES	 
	vec3 cameraPos = vec3(ViewMatrix[3][0], ViewMatrix[3][1], ViewMatrix[3][2]);
	vec3 n = normalize(Normal); 
	vec3 lightPos = (ViewMatrix * vec4(Light[num].Position, 1)).xyz;
	vec3 objToToLight = lightPos + eyeDir;
	vec3 s = normalize(objToToLight);
	vec3 v = normalize(cameraPos - WorldPosition);
	vec3 r = reflect(-s, n);
  	

	// COMPONENTE DIFUSA
	vec3 Diffuse = vec3(0);
	Diffuse = Light[num].Diffuse * clamp(dot(n,s), 0, 1) * vec3(texture(myTextureSampler, TexCoords)) * Material.Diffuse;

	// COMPONENTE ESPECULAR  
	vec3 Specular = vec3(0);
	vec3 R = reflect(-s, n);
	vec3 E = normalize(eyeDir);
	if(dot(s, n) > 0) Specular = Light[num].Specular * pow(clamp(dot(E,R),0,1), 100) * 1;

	// CALCULAMOS ATENUACION
	float Attenuation = 1.0 / (1.0 + Light[num].Attenuation * pow(length(objToToLight), 2));

	// ENVIAMOS EL RESULTADO
	return Attenuation * (Diffuse + Specular);
} 

void main() {
	vec4 texValue = texture(myTextureSampler, TexCoords);
	if(texValue.a < 0.5) discard;

	vec4 result = vec4(0.0f);
	
	// CALCULAMOS DIFFUSE + SPECULAR
	for(int i = 0; i < nlights; i++) result += vec4(Phong(i), 0.0);

	// SUMAMOS AMBIENTAL
	vec3 Ambient = SpecialLight.AmbientLight * vec3(texValue) * Material.Ambient;
	result += vec4(Ambient, 1.0);

	FragColor = result;
}
