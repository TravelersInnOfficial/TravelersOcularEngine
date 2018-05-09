#version 130

uniform sampler2D uvMap;
uniform sampler2D myMask;

in vec2 MaskTexCoords;
in vec2 FragTexCoords;
in vec4 FragOverColor;

out vec4 color;

void main() {
	vec4 mask = texture(myMask, MaskTexCoords);
	vec4 outColor = texture(uvMap, FragTexCoords) * FragOverColor;
	if(mask.r>0.5) mask.r = 1;
	color = vec4(outColor.rgb, outColor.a * mask.r);
	//if(color.a < 0.5) discard;
}
