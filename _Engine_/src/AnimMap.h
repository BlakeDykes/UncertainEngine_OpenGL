#ifndef ANIM_MAP_H
#define ANIM_MAP_H

#include "Anim.h"
#include "TimerController.h"
#include "DLink.h"
#include "AnimNames.h"

class ShaderObject;

namespace Uncertain
{
	class AnimController;

	class AnimMap : public DLink
	{
	public:
		AnimMap();
		AnimMap(const AnimMap&) = delete;
		AnimMap& operator=(const AnimMap&) = delete;
		virtual ~AnimMap();

		void Set(AnimName name, AnimController& animController, Anim& anim, TimerController& timer);
		virtual void Update(_Time delta, ShaderObject* _pAnimMixerSO);

		void SetLoop(bool loop) { this->Loop = loop; }
		Bone* GetBone() const { return this->poAnim->GetBone(); }
		virtual SSBO* GetBoneResultSSBO() const { return this->poAnim->GetBoneResultSSBO(); }
		Bone* GetFirstBone() const { return this->poAnim->GetFirstBone(); }
		BoneMap* GetBoneMap() const { return this->poAnim->GetBoneMap(); }
		unsigned int GetNumBones() const { return this->poAnim->GetNumBones(); }
		unsigned int GetBoneIndex(unsigned int nodeIndex) const { return this->poAnim->GetBoneIndex(nodeIndex); }

		virtual const char* GetName() override;
		virtual bool Compare(NodeBase& pNode) override;
		virtual void Print() override;
		virtual void Wash() override;

		AnimName Name;
		AnimController* pController;
		Anim* poAnim;
		TimerController* poTimerController;
		bool Loop;
	};
}

#endif // !ANIM_MAP_H
