#ifndef ANIM_MIXER_H
#define ANIM_MIXER_H

#include "_Timer.h"
#include "Bone.h"

class ShaderObject;

namespace Uncertain
{
	class Anim;
	class SSBO;

	class AnimMixer
	{
	public:
		AnimMixer(Anim& anim);

		AnimMixer() = delete;
		AnimMixer(const AnimMixer&) = delete;
		const AnimMixer& operator =(const AnimMixer&) = delete;
		~AnimMixer();

		void Blend(ShaderObject* pAnimMixerSO, SSBO* keyA_array, SSBO* keyB_array, const float tS);

		unsigned int NumBones;
		SSBO* poSSBO_Result;
	};
}

#endif // !ANIM_MIXER_H
