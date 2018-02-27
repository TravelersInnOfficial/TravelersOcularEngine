#version 130
// FRAGMENT SHADER LIGHTING MAPS

// ENTRADA, PROVENIENTE DEL VERTEX SHADER
in vec3 Position;  		// VERTICES EN COORDENADAS DE VISTA
in vec3 Normal;  		// NORMAL EN COORDENADAS DE VISTA
in vec2 TexCoords;
  
// SALIDA PARA COMUNICAR CON EL RESTO DEL PIPELINE
Layout (location = 0) out vec4 FragColor;	// COLOR FINAL DEL FRAGMENTO

// ESTRUCTURA PARA GUARDAR EL MATERIAL. AHORA UTILIZAMOS TEXTURAS PARA GUARDAR LAS PROPIEDADES DIFUSAS Y ESPECULARES DEL MATERIAL 
struct TMaterial {
    sampler2D Diffuse;
    sampler2D Specular;
    float     Shininess;
};  

// ESTRUCTURA PARA GUARDAR LAS LUCES (POSICION, Y PROPIEDADES AMBIENTAL, DIFUSA Y ESPECULAR DE LA LUZ)
struct TLight {
    vec3 Position;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

// ESTADO DE OPENGL: MATERIAL Y LUZ (DEL TIPO DE LAS ESTRUCTURAS ANTERIORES)
uniform TMaterial Material;
uniform TLight Light;

// FUNCION QUE CALCULA EL MODELO DE REFLEXION DE PHONG
vec3  Phong () 
{
    // CALCULAR LOS DIFERENTES VECTORES	 
	vec3 n = normalize(Normal);
    vec3 s = normalize(Light.Position - Position);
	vec3 v = normalize(-Position);
	vec3 r = reflect(-s, n);

	// COMPONENTE AMBIENTAL
    vec3 Ambient = Light.Ambient * vec3(texture(Material.Diffuse, TexCoords));
  	
    // COMPONENTE DIFUSA 
    vec3 Diffuse = Light.Diffuse * max(dot(s, n), 0.0) * vec3(texture(Material.Diffuse, TexCoords));  
    
    // COMPONENTE ESPECULAR  
    vec3 Specular = Light.Specular * pow(max(dot(r, v), 0.0), Material.Shininess) * vec3(texture(Material.Specular, TexCoords));
        
    return Ambient + Diffuse + Specular;  
} 

void main()
{
	FragColor = vec3 (Phong(), 0.0);
}
