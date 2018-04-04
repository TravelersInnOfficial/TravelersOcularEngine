#version 130

in vec2 TexCoords;
in vec3 FinalColor;

// TEMPORAL TEXTURE WITHOUT MATERIALS
uniform sampler2D uvMap;

out vec4 color;

void main() {
	color = texture( uvMap, TexCoords) * vec4(FinalColor, 1);
	if(color.a < 0.5) discard;
}
