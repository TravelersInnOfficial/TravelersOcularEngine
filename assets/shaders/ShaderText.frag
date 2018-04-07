#version 130

// TEMPORAL TEXTURE WITHOUT MATERIALS
uniform sampler2D uvMap;

in vec2 TexCoords;      // UV COORDENADAS DE TEXTURA

out vec4 color;

void main() {
	color = texture( uvMap, TexCoords);
	if(color.a < 0.5) discard;
}
