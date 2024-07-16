#version 430 core

uniform sampler2D text;

// Varying
in VS_OUT
{
	vec2 textCoordinate;
	vec4 vFragColor;
} fs_in;

out vec4 color;

void main(void)
{
	color = fs_in.vFragColor * texture(text, fs_in.textCoordinate);
}
