#version 130

// TEMPORAL TEXTURE WITHOUT MATERIALS
uniform sampler2D myTextureSampler;

in vec2 TexCoords;      // UV COORDENADAS DE TEXTURA

out vec4 color;

void main() {
	color = texture( myTextureSampler, TexCoords);
}
