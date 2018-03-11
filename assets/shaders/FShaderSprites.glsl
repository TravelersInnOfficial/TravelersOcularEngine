#version 130

uniform sampler2D myTextureSampler;

in vec2 FragTexCoords;

out vec4 color;

void main() {
	color = texture( myTextureSampler, FragTexCoords);
	if(color.a < 0.5) discard;
}
