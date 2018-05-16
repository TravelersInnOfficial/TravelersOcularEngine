#version 130

uniform sampler2D myMask;
in vec4 FragmentColor;
in vec2 MaskTexCoords;

out vec4 color;

void main(){
	vec4 mask = texture(myMask, MaskTexCoords);
	if(mask.r>0.5) mask.r = 1;
	color = vec4(FragmentColor.rgb, FragmentColor.a * mask.r);
	//if(color.a < 0.5) discard;
}
