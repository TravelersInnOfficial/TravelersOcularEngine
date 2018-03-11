#version 130

uniform vec3 LineColor;
out vec4 color;

void main(){
	color = vec4(LineColor, 1.0f);
}
