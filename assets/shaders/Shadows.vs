#version 330 core

// Input vertex data, different for all executions of this shader.
in vec3 Position;

// Values that stay constant for the whole mesh.
uniform mat4 DepthMVP;

void main(){
    gl_Position =  DepthMVP * vec4(Position, 1);
}