#version 430

out vec4 fragColor;
in vec4 vertexColor;

void main()	{
    fragColor = vertexColor.xyzw;
}