#version 130

uniform sampler2D uvMap;

in vec2 FragTexCoords;

out vec4 color;

void main() {
	vec4 outColor = texture(uvMap, FragTexCoords);
	
	color = outColor;
	if(color.a < 0.5) discard;
}
