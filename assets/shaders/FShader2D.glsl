#version 130

in vec3 FragmentColor;

out vec4 color;


void main(){
	color = vec4(FragmentColor, 1.0f);
}
