#version 430 core

// Uniforms
uniform mat4 world_matrix;
uniform mat4 proj_matrix;
uniform mat4 view_matrix;
uniform vec4 vColor;

// Attributes
layout (location = 0) in vec2 vVert;
layout (location = 2) in vec2 tc;

// Varying
out VS_OUT
{
	vec2 textCoordinate;
	vec4 vFragColor;
} vs_out;


void main(void) 
{ 
	// Set vFragColor
	vs_out.vFragColor = vColor;

	// Set tc
	vs_out.textCoordinate = tc;

	// Set Gl_position
	gl_Position = proj_matrix * view_matrix * world_matrix * vec4(vVert.xy, 0.0f, 1.0f);
}

// --- End of File ---
