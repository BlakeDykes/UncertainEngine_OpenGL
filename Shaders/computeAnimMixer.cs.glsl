#version 430 core

layout(local_size_x = 10) in;

struct Bone
{
	vec3 t;
	vec4 q;
	vec3 s;
};

layout (std430, binding = 0 ) buffer KeyFrameA
{
	Bone KeyA_array[];
};

layout (std430, binding = 1) buffer KeyFrameB
{
	Bone KeyB_array[];
};

layout (std430, binding = 2) buffer Result
{
	Bone Result_array[];
};

uniform float ts;
uniform uint boneCount;

vec4 slerp(vec4 src, vec4 tar, float t);

void main()
{
	uint boneIndex = gl_GlobalInvocationID.x;

	Result_array[boneIndex] = KeyA_array[boneIndex];

	if( gl_GlobalInvocationID.x < boneCount)
	{

		vec3 trans = mix( KeyA_array[boneIndex].t, KeyB_array[boneIndex].t, ts );
		vec4 quat = slerp( KeyA_array[boneIndex].q, KeyB_array[boneIndex].q, ts );
		vec3 scale = mix( KeyA_array[boneIndex].s, KeyB_array[boneIndex].s, ts );

		Result_array[boneIndex].t = trans;
		Result_array[boneIndex].q = quat;
		Result_array[boneIndex].s = scale;
	}

}

vec4 slerp( vec4 src, vec4 tar, float t)
{
	vec4 result;
	vec4 target;
	float QUAT_EPSILON = 0.001f;

	float cosom = src.x * tar.x + 
				  src.y * tar.y + 
				  src.z * tar.z + 
				  src.w * tar.w;

	if(cosom >= 1.0f)
	{
		result = tar;
	}
	else
	{

		if(cosom < 0.0f)
		{
			cosom = -cosom;
			target = -tar;
		}
		else
		{
			target = tar;
		}

		float tarFactor = t;
		float srcFactor = 1.0f - t;

		
		if (cosom < (1.0f - QUAT_EPSILON))
		{
			const float omega = acos(cosom);
			const float sinom = 1.0f / sin(omega);

			srcFactor = sin(srcFactor * omega) * sinom;
			tarFactor = sin(tarFactor * omega) * sinom;
		}

		result.x = src.x * srcFactor + target.x * tarFactor;
		result.y = src.y * srcFactor + target.y * tarFactor;
		result.z = src.z * srcFactor + target.z * tarFactor;
		result.w = src.w * srcFactor + target.w * tarFactor;
	}

	return result;

}