#version 430 core

uniform sampler2D textureUnit0;

in VS_OUT
{
	vec4 vFragColor;
	vec2 vTex;
	vec4 vBaseColor;
} fs_in;


out vec4 color;

void main(void)
{
	//color = fs_in.vFragColor * texture(textureUnit0, fs_in.vTex);

	color = fs_in.vFragColor * vec4(fs_in.vBaseColor.xyz, 1.0f) * texture(textureUnit0, fs_in.vTex);
}