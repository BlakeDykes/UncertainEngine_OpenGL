#ifndef ANIM_H
#define ANIM_H

#include "_Time.h"
#include "GameObjectAnimSkin.h"
#include "AnimData.h"
#include "BoneMap.h"
#include "Bone.h"
#include "Command.h"
#include "AnimNames.h"

class ShaderObject;

namespace Uncertain
{
	class SSBO;
	class AnimMixer;
	class FrameBucket;

	class Anim
	{
	public:

		enum class ANIM_SPECIAL
		{
			IDENTITY,
			BLEND
		};

		Anim(ANIM_SPECIAL specialType, unsigned int numBones);
		Anim(AnimName name);
		Anim() = delete;
		Anim(const Anim&) = delete;
		Anim& operator=(const Anim&) = delete;
		~Anim();

		void Animate(_Time tCurr, ShaderObject* _pAnimMixerSO);
		_Time FindMaxTime();

		const char* GetName() { return this->pName; }
		BoneMap* GetBoneMap() const { return this->poMap; }
		unsigned int GetBoneIndex(unsigned int nodeIndex) const; 
		Bone* GetBone() const { return this->poBoneResult; }
		SSBO* GetBoneResultSSBO() const;
		unsigned int GetNumBones() const { return this->NumBones; }
		Bone* GetFirstBone() const;

		void CustomAnimate(ShaderObject* _pAnimMixerSO, SSBO* keyA_array, SSBO* keyB_array, const float tS);

		Command* GetCallback() const { return this->pCallback; }
		void SetCallback(Command* callback);
		void SetCallbackNull() { this->pCallback = nullptr; }
		//void SetFrames(AnimData& anim);
		void SetBoneMap(AnimData& anim);

	private:
		void privAnimate(_Time tCurr, ShaderObject* _pAnimMixerSO);

		char pName[AnimData::ANIM_NAME_SIZE];
		unsigned int NumBones;
		unsigned int NumFrames;
		BoneMap* poMap;
		Bone* poBoneResult;
		_Time TotalTime;
		FrameBucket* pFrames;
		Command* pCallback;
		AnimMixer* poMixer;
	};
}

#endif