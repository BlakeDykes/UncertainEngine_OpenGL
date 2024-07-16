#ifndef ANIM_CONTROLLER_H
#define ANIM_CONTROLLER_H

#include "DLink.h"
#include "AnimManager.h"
#include "AnimMap.h"
#include "AnimNames.h"
#include "Bone.h"
#include "AnimMap_Null.h"
#include "AnimMap_Blend.h"

class GameObjectFont;
class DebugObject;
class ShaderObject;


namespace Uncertain
{
	class Armature;
	class AnimMap_Null;
	class AnimMap_Blend;

	class AnimController : public DLink, public ManagerBase 
	{
	public: 

		const static int DEFAULT_RESERVE = 5;
		const static int DEFAULT_DELTA_GROW = 5;
		static _Time DEFAULT_BLEND_TIME;

		AnimController(int initialReserved = DEFAULT_RESERVE, int deltaGrow = DEFAULT_DELTA_GROW);

		AnimController(const AnimController&) = delete;
		AnimController& operator=(const AnimController&) = delete;
		virtual ~AnimController();

		void Add(AnimName name, _Time delta = AnimManager::MASTER_DELTA);
		AnimMap* Find(AnimName name);
		void Remove(AnimName name);

		void Set(_Time delta, GameObjectFont* debugMessage);
		void SetActive(AnimMap& animMap, bool loop, _Time blendTime);
		void SetActive(AnimName name, bool loop, _Time blendTime);
		void SetActiveNoBlend(AnimName name, bool loop);
		void SetActiveNoBlend(AnimMap& animMap, bool loop);
		void SetIdleAsActive(_Time blendTime);

		bool CompareCallback(Command& callback) const { return this->pActiveAnim->poAnim->GetCallback() == &callback; }
		void SetCallbackNullIfCurrent(Command& pCallback);

		void SetIdle(AnimName name);
		AnimMap* GetIdle() const { return this->pIdleAnim != nullptr ? this->pIdleAnim : this->poNullAnim; }
		const char* GetActiveName() const { return Stringify(this->pActiveAnim->Name); }

		void AdjustDelta(DIRECTION dir, _Time change = AnimManager::DEFAULT_ANIM_TIME_ADJUST);
		void Reverse();

		unsigned int GetBoneIndex(unsigned int nodeIndex);
		Bone* GetBone() const { return this->pActiveAnim->GetBone(); }
		SSBO* GetBoneResultSSBO() const { return this->pActiveAnim->GetBoneResultSSBO(); }
		BoneMap* GetBoneMap() const { return this->pActiveAnim->GetBoneMap(); }
		unsigned int GetNumBones() const { return this->pActiveAnim->GetNumBones(); }

		void Update(ShaderObject* _pAnimMixerSO);

		void SetArmature(Armature& armature);

		void MarkForDelete() { bShouldDelete = true; }
		bool ShouldDelete() const { return this->bShouldDelete; }

		virtual const char* GetName() override;
		virtual bool Compare(NodeBase& pNode) override;
		virtual void Wash() override;

	protected:
		virtual NodeBase* CreateNode() override;

	private:
		void BlendFromActiveAnim(AnimMap& toAnim, bool loop, _Time blendTime);
		void privSetActive(AnimMap& animMap, bool loop);
		void privSetActive(AnimName name, bool loop);

		AnimMap* pActiveAnim;
		AnimMap* pIdleAnim;

		AnimMap* poCompNode;
		AnimMap_Blend* poBlendAnim;
		AnimMap_Null* poNullAnim;
		
		DebugObject* poDebugObject;

		Armature* pArmature;

		_Time Delta;

		bool bShouldDelete;
		bool bIsBlending;
	};
}

#endif