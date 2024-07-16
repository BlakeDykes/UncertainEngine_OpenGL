
#version 430 core

// Uniforms
	uniform vec3 vLightPos;
	uniform vec3 viewPosition;
	uniform float keySpecularIntensity;
	uniform float keyHighlightSize;
	uniform float ambientStrength;

	// Varrying
	in VS_OUT
	{
		vec3 vFragPos;
		vec3 vFragColor;
		vec3 vFragNormal;
	} fs_in;


	// Out
	out vec4 FragColorOut;

	void main(void)
	{
		// Generate ambient, diffuse, and specular
		
		//Ambient
		vec3 ambient = ambientStrength * fs_in.vFragColor;

		// Key light - diffuse
		// Diffuse
		vec3 LightDir = normalize(vLightPos - fs_in.vFragPos);											// distance from light source to object
		vec3 diffNormal = normalize(fs_in.vFragNormal);
		float keyImpact = max(dot(LightDir, diffNormal), 0.0);											// diffuse impact
		vec3 keyDiffuse = keyImpact * fs_in.vFragColor;													// diffuse light

		// Specular
		vec3 viewDir = normalize(viewPosition - fs_in.vFragPos);
		vec3 keyReflectDir = reflect(-LightDir, diffNormal);											// reflection vector
		float keySpecularComponent = pow(max(dot(viewDir, keyReflectDir), 0.0), keyHighlightSize);
		vec3 keySpecular = keySpecularIntensity * keySpecularComponent * fs_in.vFragColor;

		FragColorOut = vec4(ambient + keyDiffuse + keySpecular, 1.0f);
	}


// Varrying