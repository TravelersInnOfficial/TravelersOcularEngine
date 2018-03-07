#version 130

// TEMPORAL TEXTURE WITHOUT MATERIALS
uniform sampler2D myTextureSampler;

// ENTRADA, PROVENIENTE DEL VERTEX SHADER
in vec3 Position;  		// VERTICES EN COORDENADAS DE VISTA
in vec3 Normal;  		// NORMAL EN COORDENADAS DE VISTA
in vec2 TexCoords;      // UV COORDENADAS DE TEXTURA
  
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
	vec3 n = normalize(Normal);
    vec3 vecToLight = Light[num].Position - Position;
    vec3 s = normalize(vecToLight);
	vec3 v = normalize(-Position);
	vec3 r = reflect(-s, n);
  	
    // COMPONENTE DIFUSA 
    vec3 Diffuse = Light[num].Diffuse * max(dot(s, n), 0.0) * vec3(texture(myTextureSampler, TexCoords)) * Material.Diffuse;  
    
    // COMPONENTE ESPECULAR  
    vec3 Specular = Light[num].Specular * pow(max(dot(r, v), 0.0), Material.Shininess) * Material.Specular;
    
    // CALCULAMOS ATENUACION
    float Attenuation = 1.0 / (1.0 + Light[num].Attenuation * pow(length(vecToLight), 2));

    // ENVIAMOS EL RESULTADO
    return Attenuation * (Diffuse + Specular);
} 

void main() {
    vec4 result = vec4(0.0f);
    
    // CALCULAMOS DIFFUSE + SPECULAR
    for(int i = 0; i < nlights; i++) result += vec4(Phong(i), 0.0);

    // SUMAMOS AMBIENTAL
    vec3 Ambient = SpecialLight.AmbientLight * vec3(texture(myTextureSampler, TexCoords)) * Material.Ambient;
    result += vec4(Ambient, 1.0);

	FragColor = result;
}
