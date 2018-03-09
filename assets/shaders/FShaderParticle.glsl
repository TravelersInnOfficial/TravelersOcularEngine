#version 130

in vec2 TexCoords;
in vec4 FinalColor;

// TEMPORAL TEXTURE WITHOUT MATERIALS
uniform sampler2D myTextureSampler;

out vec4 color;

void main() {
	color = texture( myTextureSampler, TexCoords) * FinalColor;
}
