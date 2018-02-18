#version 130

in vec3 VertexPosition;	// VERTICE EN COORDENADAS LOCALES
in vec2 inUV;			// UV IN FOR THE FRAGMENT

out vec2 outUV;			// UV OUT TO THE FRAGMENT

//uniform mat4 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main(){
	gl_Position = ProjectionMatrix *  ViewMatrix * ModelViewMatrix * vec4(VertexPosition, 1.0);
	outUV = inUV; // Pass UV to the fragment
}