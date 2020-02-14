#version 330 core

in vec4 fragCol;
in vec2 UV;

out vec4 color;

uniform sampler2D tex;

void main()
{
	vec4 Color = texture2D( tex, UV ) * fragCol;

	color = Color;
}
