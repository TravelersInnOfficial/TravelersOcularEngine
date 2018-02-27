#version 130

// TEMPORAL TEXTURE WITHOUT MATERIALS
uniform sampler2D myTextureSampler;

// FRAGMENT SHADER LIGHTING MAPS

// ENTRADA, PROVENIENTE DEL VERTEX SHADER
in vec3 Position;  		// VERTICES EN COORDENADAS DE VISTA
in vec3 Normal;  		// NORMAL EN COORDENADAS DE VISTA
in vec2 TexCoords;
  
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
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

uniform TLight Light[20];
uniform int nlights;

// FUNCION QUE CALCULA EL MODELO DE REFLEXION DE PHONG
vec3  Phong (int num) {
    // CALCULAR LOS DIFERENTES VECTORES	 
	vec3 n = normalize(Normal);
    vec3 s = normalize(Light[num].Position - Position);
	vec3 v = normalize(-Position);
	vec3 r = reflect(-s, n);

	// COMPONENTE AMBIENTAL
    vec3 Ambient = Light[num].Ambient * vec3(texture(myTextureSampler, TexCoords)) * Material.Ambient;
  	
    // COMPONENTE DIFUSA 
    vec3 Diffuse = Light[num].Diffuse * max(dot(s, n), 0.0) * vec3(texture(myTextureSampler, TexCoords)) * Material.Diffuse;  
    
    // COMPONENTE ESPECULAR  
    vec3 Specular = Light[num].Specular * pow(max(dot(r, v), 0.0), Material.Shininess) * Material.Specular;
        
    return Ambient + Diffuse + Specular;
    //return Ambient;
} 

void main() {
    vec4 result = vec4(0.0f);
    
    for(int i = 0; i<nlights; i++){
        result += vec4(Phong(i), 0.0);
    }

	FragColor = result;
}
