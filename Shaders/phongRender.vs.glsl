
#version 430 core


// Uniforms
	uniform mat4 world_matrix;
	uniform mat4 view_matrix;
	uniform mat4 proj_matrix;
	uniform vec3 vColor;

// Attributes
	layout (location = 0) in vec4 vVert;
	layout (location = 1) in vec3 vNormal;


// Varrying
	out VS_OUT
	{
		vec3 vFragPos;
		vec3 vFragColor;
		vec3 vFragNormal;
	} vs_out;

	void main(void)
	{
		gl_Position = proj_matrix * view_matrix * world_matrix * vVert;
		
		vs_out.vFragColor = vColor;

		vs_out.vFragNormal = vNormal;

		vs_out.vFragPos = vec3(vVert);
	}