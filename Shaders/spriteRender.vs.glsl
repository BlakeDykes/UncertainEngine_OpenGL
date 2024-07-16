#version 430 core

// Uniforms
	uniform mat4 world_matrix;
	uniform mat4 view_matrix;
	uniform mat4 proj_matrix;
	uniform mat4 uv_matrix;
	
// Attributes
	layout (location = 0) in vec4 vVert;
	layout (location = 2) in vec2 vTexCoord0;

// Varying
	out VS_OUT
	{
		vec2 vTex;
		mat4 uvMat;
	} vs_out;

void main(void)
{
	vs_out.vTex = vTexCoord0;
	vs_out.uvMat = uv_matrix;

	gl_Position = proj_matrix * view_matrix * world_matrix * vVert;
}