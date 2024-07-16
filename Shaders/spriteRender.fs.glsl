#version 430 core

uniform sampler2D tex_object;

in VS_OUT
{
	vec2 vTex;
	mat4 uvMat;
} fs_in;

out vec4 color;

void main(void)
{
	vec4 uv_vec;
	uv_vec.xy = fs_in.vTex.xy;
	uv_vec.z = 0.0f;
	uv_vec.w = 1.0f;

	vec4 uv_corrected = fs_in.uvMat * uv_vec;

	color = texture(tex_object, uv_corrected.xy);
}