#version 130

// TEMPORAL TEXTURE WITHOUT MATERIALS
uniform sampler2D myTextureSampler;
uniform sampler2DShadow shadowMap;

// ENTRADA, PROVENIENTE DEL VERTEX SHADER
in vec3 Position;  		// VERTICES EN COORDENADAS DE VISTA
in vec3 Normal;  		// NORMAL EN COORDENADAS DE VISTA
in vec4 ShadowCoord;
in vec2 TexCoords;      // UV COORDENADAS DE TEXTURA
in mat4 FragViewMatrix;

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

// FUNCION QUE CALCULA EL MODELO DE REFLEXION DE PHONG
vec3  Phong (int num) {
	// CALCULAR LOS DIFERENTES VECTORES	 
	vec3 eyeDir = -Position;
	vec3 n = normalize(Normal); 
	vec3 lightPos = (FragViewMatrix * vec4(Light[num].Position, 1)).xyz;
	vec3 objToToLight = lightPos + eyeDir;
	vec3 s = normalize(objToToLight);
	vec3 r = reflect(-s, n);
  	
	// COMPONENTE DIFUSA
	vec3 Diffuse = vec3(0);
	Diffuse = Light[num].Diffuse * clamp(dot(n,s), 0, 1) * vec3(texture(myTextureSampler, TexCoords)) * Material.Diffuse;

	// COMPONENTE ESPECULAR  
	vec3 Specular = vec3(0);
	vec3 R = reflect(-s, n);
	vec3 E = normalize(eyeDir);
	if(dot(s, n) > 0) Specular = Light[num].Specular * pow(clamp(dot(E,R),0,1), Material.Shininess) * Material.Specular;

	// CALCULAMOS ATENUACION
	float Attenuation = 1.0 / (1.0 + Light[num].Attenuation * pow(length(objToToLight), 2));

	// ENVIAMOS EL RESULTADO
	return Attenuation * (Diffuse + Specular);
} 

// POISSON SAMPLING
vec2 poissonDisk[4] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 )
);

void main() {
	// Check alpha and discard fragments
	vec4 texValue = texture(myTextureSampler, TexCoords);
	if(texValue.a < 0.5) discard;

	// CALCULAMOS DIFFUSE + SPECULAR
	vec4 result = vec4(0.0);
	for(int i = 0; i < nlights; i++) result += vec4(Phong(i), 0.0);

	/// CHECK SHADOWS
	float bias = 0.005;
	float visibility = 1.0;
	
	// Sample the shadow map 4 times
	for (int i=0;i<4;i++){
		int index = i;
		// being fully in the shadow will eat up 4*0.2 = 0.8
		// 0.2 potentially remain, which is quite dark.
		visibility -= 0.2*(1.0-texture( shadowMap, vec3(ShadowCoord.xy + poissonDisk[index]/700.0,  (ShadowCoord.z-bias)/ShadowCoord.w) ));
	}
	// ADD shadow
	result *= visibility;	

	// SUMAMOS AMBIENTAL
	vec3 Ambient = SpecialLight.AmbientLight * vec3(texValue) * Material.Ambient;
	result += vec4(Ambient, 1.0);

	// SPOTLIGHT
	///if ( textureProj( shadowMap, ShadowCoord.xyw ).z  <  (ShadowCoord.z-bias)/ShadowCoord.w )
	///if ( texture( shadowMap, (ShadowCoord.xy/ShadowCoord.w) ).z  <  (ShadowCoord.z-bias)/ShadowCoord.w )
	FragColor = result;
}