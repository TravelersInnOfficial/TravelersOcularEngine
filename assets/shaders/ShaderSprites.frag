#version 130

uniform sampler2D uvMap;

in vec2 FragTexCoords;
in vec4 FragOverColor;

out vec4 color;

void main() {
	color = texture(uvMap, FragTexCoords) * FragOverColor;
	if(color.a < 0.5) discard;
}
