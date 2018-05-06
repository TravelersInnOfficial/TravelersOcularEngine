#version 130

// https://blender.stackexchange.com/questions/52865/creating-normal-maps-from-a-texture

// ENTRADA, PROVENIENTE DEL VERTEX SHADER
in vec3 Position;    		// VERTICES EN COORDENADAS DE VISTA
in vec2 TexCoords;   		// COORDENADAS DE TEXTURA
in mat4 FragViewMatrix;   	// VIEW MATRIX
in mat4 RotationNormal;		// MODELVIEW MATRIX

in vec4 ShadowCoordArray[20];       // POSICION DE VERTICES EN LA TEXTURA DE SOMBRAS (VERTICE VISTO DESDE LA LUZ)

// SALIDA PARA COMUNICAR CON EL RESTO DEL PIPELINE
out vec4 FragColor;	// COLOR FINAL DEL FRAGMENTO

// ESTRUCTURA PARA GUARDAR EL MATERIAL.
struct TMaterial {
	vec3  Diffuse;
	vec3  Specular;
	vec3  Ambient;
	float Shininess;
};

// ESTRUCTURA PARA GUARDAR LAS LUCES
struct TLight {
	vec3 Position;				// Position of the light source
	vec3 Diffuse;				// Color of the light
	vec3 Specular;				// Highlight color
	
	// For POINT
	float Attenuation;			// Attenuation factor
	
	// For DIRECTIONAL
	bool Directional;			// Is it directiona?
	vec3 Direction;				// Direction of the light

	// For SHADOW
	bool ShadowLight;			// Does it has shadow?
	sampler2DShadow ShadowMap;	// Shadow texture of the light
};

// IN UNIFORMS
uniform TMaterial Material;		// MODEL MATERIAL
uniform TLight Light[40];		// LIGHTS
uniform int nlights;			// NUMBER OF CURRENT LIGHTS
uniform vec3 AmbientLight;		// AMBIENT LIGHT

// TEMPORAL TEXTURE WITHOUT MATERIALS
uniform sampler2D uvMap;
uniform sampler2D specularMap;
uniform sampler2D bumpMap;

// POISSON SAMPLING
vec2 poissonDisk[4] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 )
);

float RandomNumber(vec4 seed4){
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

// FUNCION QUE CALCULA EL MODELO DE REFLEXION DE PHONG
vec3  Phong (int num) {

	// CALCULAR LOS DIFERENTES VECTORES	 
	vec3 eyeDir = -Position;
	vec3 normalTexture = normalize(2.0 * texture2D (bumpMap, TexCoords).rgb - 1.0);

	vec3 n = normalize (RotationNormal * vec4(normalTexture,1.0)).xyz;

	vec3 lightPos = (FragViewMatrix * vec4(Light[num].Position, 1)).xyz;
	

	// Vector from SURFACE to LIGHT
	vec3 objToToLight = lightPos + eyeDir;

	if(Light[num].Directional){
		vec3 pointA = vec3(0,0,0);						// Ponemos el principio en el centro
		vec3 pointB = -Light[num].Direction;			// Calculamos el punto final
		pointA = (FragViewMatrix * vec4(pointA,1)).xyz;	//|
		pointB = (FragViewMatrix * vec4(pointB,1)).xyz;	//| Calculamos ambos en el espacio de vision
		objToToLight = normalize(pointB - pointA);		// Calculamos el vector en espacio de vision
	}
	
	vec3 specTexure = texture(specularMap, TexCoords).rgb;

	vec3 s = normalize(objToToLight);
	vec3 r = reflect(-s, n);
  	
	// COMPONENTE DIFUSA
	vec3 Diffuse = vec3(0);
	Diffuse = Light[num].Diffuse * clamp(dot(n,s), 0, 1)  * Material.Diffuse;

	// COMPONENTE ESPECULAR  
	vec3 Specular = vec3(0);
	vec3 R = reflect(-s, n);
	vec3 E = normalize(eyeDir);
	if(dot(s, n) > 0) Specular = Light[num].Specular * pow(clamp(dot(E,R),0,1), Material.Shininess) * Material.Specular;

	// CALCULAMOS ATENUACION
	float Attenuation = 1.0 / (1.0 + Light[num].Attenuation * pow(length(objToToLight), 2));
	if(Light[num].Directional) Attenuation = 1;
	

	// ENVIAMOS EL RESULTADO
	return (Attenuation * (Diffuse + Specular) * specTexure);
}

void main() {
	// Check alpha and discard fragments
	vec4 texValue = texture(uvMap, TexCoords);
	if(texValue.a < 0.5) discard;

	// CALCULAMOS DIFFUSE + SPECULAR
	vec4 result = vec4(0.0);
	for(int i = 0; i < nlights; i++) result += vec4(Phong(i), 0.0);

	/// CHECK SHADOWS
	float bias = 0.005;
	float visibility = 1.0;
	
	int shadowindex = 0;
	for(int i = 0; i < nlights; i++){
		if(Light[i].ShadowLight == true){
			for (int j = 0; j < 4; j++){
				int index = int(16.0*RandomNumber(vec4(gl_FragCoord.xyy, i)))%16;
				visibility -= 0.2*(1.0-texture(Light[i].ShadowMap, vec3(ShadowCoordArray[shadowindex].xy + poissonDisk[index]/700.0, (ShadowCoordArray[shadowindex].z-bias)/ShadowCoordArray[shadowindex].w)));
			}
			shadowindex = shadowindex + 1;
		}
	}
	
	// ADD shadow
	result *= visibility;	

	// SUMAMOS AMBIENTAL
	vec3 Ambient = AmbientLight * vec3(texValue) * Material.Ambient;
	result += vec4(Ambient, 1.0);
	FragColor = result;
}