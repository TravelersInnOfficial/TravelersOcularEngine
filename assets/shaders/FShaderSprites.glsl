#version 130

uniform sampler2D myTextureSampler;

in vec2 FragTexCoords;
in vec4 FragOverColor;

out vec4 color;

void main() {
	color = texture(myTextureSampler, FragTexCoords) * FragOverColor;
	if(color.a < 0.5) discard;
}
