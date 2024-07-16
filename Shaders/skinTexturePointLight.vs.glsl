
#version 430 core

#define MAX_INVBIND 100

uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform mat4 invBind_matrix[MAX_INVBIND];
uniform mat4 world_matrix;
uniform vec4 vBaseColorFactor;
uniform vec3 vLightPos;
uniform vec4 vColor;


// Atrributes
layout (location = 0) in vec4	vVert;
layout (location = 1) in vec3	vNormal;
layout (location = 2) in vec2	vTexCoord0;
layout (location = 4) in vec4	vWeight;
layout (location = 5) in ivec4	vJoint;

layout (std430, binding = 2) buffer BoneResult
{
	mat4 BoneResult_array[];
};

out VS_OUT
{	
	vec4 vFragColor;
	vec2 vTex;
	vec4 vBaseColor;
} vs_out;


void main(void)
{
	mat4 skin_matrix =	vWeight.x * BoneResult_array[vJoint.x] * invBind_matrix[vJoint.x] +
						vWeight.y * BoneResult_array[vJoint.y] * invBind_matrix[vJoint.y] +
						vWeight.z * BoneResult_array[vJoint.z] * invBind_matrix[vJoint.z] +
						vWeight.w * BoneResult_array[vJoint.w] * invBind_matrix[vJoint.w] ;

	// Get vNorm
		mat4 mvsMatrix = view_matrix * world_matrix * skin_matrix;
		mat3 mNormalMatrix;
		mNormalMatrix[0] = normalize(mvsMatrix[0].xyz);
		mNormalMatrix[1] = normalize(mvsMatrix[1].xyz);
		mNormalMatrix[2] = normalize(mvsMatrix[2].xyz);
		vec3 vNorm = normalize(mNormalMatrix * vNormal);

	// Get vLightDir
		vec4 ecPosition;
		vec3 ecPosition3;
		ecPosition = mvsMatrix * vVert;
		ecPosition3 = ecPosition.xyz /ecPosition.w;
		vec3 vLightDir = normalize(vLightPos - ecPosition3);

	// Get vFragColor
		float fDot = max(0.0, dot(vNorm, vLightDir)); 
		vs_out.vFragColor.rgb = vColor.rgb * fDot;
		vs_out.vFragColor.a = vColor.a;

	vs_out.vTex = vTexCoord0;
	vs_out.vBaseColor = vBaseColorFactor;


	gl_Position = proj_matrix * view_matrix * world_matrix * skin_matrix * vVert;
}