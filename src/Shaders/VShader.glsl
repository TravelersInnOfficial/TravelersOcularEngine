#version 150 core

    in vec2 position;
    in float vertexColor;

    out float color;

    void main()
    {
        color = vertexColor;
        gl_Position = vec4(position, 0.0, 1.0);
    }