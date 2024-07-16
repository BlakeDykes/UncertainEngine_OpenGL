#version 430 core

// Uniforms
	uniform sampler2D textureUnit0;

// Varying
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
	//color.a = fs_in.vFragColor.a;

	color = fs_in.vFragColor * vec4(fs_in.vBaseColor.xyz, 1.0f) * texture(textureUnit0, fs_in.vTex);
}


// --- End of File ---
