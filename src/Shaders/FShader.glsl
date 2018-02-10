#version 150

in float color;
out vec4 outColor;

void main()
{
    //outColor = vec4(color, 1.0);
    outColor = vec4(vec3(color), 1.0);
    //outColor = vec4(1.0, 1.0, 1.0, 1.0);
}