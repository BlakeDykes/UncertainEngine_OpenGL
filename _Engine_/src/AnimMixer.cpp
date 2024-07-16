#include "AnimMixer.h"
#include "MathApp.h"
#include "Anim.h"
#include "SSBO.h"
#include "ShaderObject.h"

namespace Uncertain
{
	
	AnimMixer::AnimMixer(Anim& anim)
		: NumBones(anim.GetNumBones()), poSSBO_Result(new SSBO())
	{
		poSSBO_Result->Set(NumBones + 1, sizeof(Bone), anim.GetBone(), GL_STATIC_DRAW);
	}

	AnimMixer::~AnimMixer()
	{
		if (this->poSSBO_Result)
		{
			delete poSSBO_Result;
		}
	}

	void AnimMixer::Blend(ShaderObject* pAnimMixerSO, SSBO* keyA_array, SSBO* keyB_array, const float tS)
	{
		assert(pAnimMixerSO);
		assert(keyA_array);
		assert(keyB_array);

		glBindVertexArray(0);

		pAnimMixerSO->SetActive();

		keyA_array->Bind(0);
		keyB_array->Bind(1);
		this->poSSBO_Result->Bind(2);

		glUniform1f(pAnimMixerSO->GetLocation("ts"), (GLfloat)tS);
		glUniform1ui(pAnimMixerSO->GetLocation("boneCount"), (GLuint)NumBones);

		pAnimMixerSO->Dispatch(1 + (NumBones / 10), 1, 1);

		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	}
}
