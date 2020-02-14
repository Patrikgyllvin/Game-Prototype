#version 330 core

layout(location = 0) in vec2 Pos;
layout(location = 1) in vec2 vertUV;
layout(location = 2) in vec4 in_Color;

uniform MVP;

out vec4 fragCol;
out vec2 UV;

void main()
{
	gl_Position = vec4(Pos, 0.0, 1.0);
	fragCol = in_Color;
	UV = vertUV;
}