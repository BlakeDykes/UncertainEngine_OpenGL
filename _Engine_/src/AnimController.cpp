#include "AnimController.h"
#include "Anim.h"
#include "DLinkManager.h"
#include "DLinkIterator.h"
#include "ProtoData_Wrapper.h"
#include "TimerController.h"
#include "AnimMap_Null.h"
#include "CMD_SetAnimNoBlend.h"
#include "DebugObject.h"
#include "Armature.h"
#include "ShaderObject.h"
#include "AnimMap_Blend.h"
#include "AnimMap_Null.h"

namespace Uncertain
{

	_Time AnimController::DEFAULT_BLEND_TIME = 2.0f * _Time(_Time::Duration::ONE_SECOND);

	AnimController::AnimController(int initialReserved, int deltaGrow)
		:	ManagerBase(*new DLinkManager(), *new DLinkManager()), pActiveAnim(nullptr), pIdleAnim(nullptr),
		poCompNode(nullptr), poBlendAnim(nullptr), poNullAnim(nullptr), poDebugObject(nullptr), pArmature(nullptr),
		Delta(_Time(_Time::Duration::ZERO)), bShouldDelete(true), bIsBlending(false)
	{
		this->SetReserve(initialReserved, deltaGrow);
	}

	AnimController::~AnimController()
	{
		//this->BaseClear();
		
		if (this->poCompNode)
		{
			delete this->poCompNode;
		}
		if (this->poNullAnim)
		{
			delete this->poNullAnim;
		}
		if (this->poBlendAnim)
		{
			delete this->poBlendAnim;
		}
		if (this->poDebugObject)
		{
			delete this->poDebugObject;
		}
		if (this->pArmature)
		{
			pArmature->MarkForDelete();
			this->pArmature = nullptr;
		}
	}

	void AnimController::Add(AnimName name, _Time delta)
	{
		AnimMap* pNode = (AnimMap*)this->BaseAdd();


		Anim* animation = new Anim(name);

		_Time maxTime = animation->FindMaxTime();
		_Time minTime = _Time(_Time::Duration::ZERO);

		TimerController* pTimer = new TimerController(minTime, maxTime);

		pNode->Set(name, *this, *animation, *pTimer);

		// Set fallback bone position
		if (!this->poNullAnim)
		{
			this->poNullAnim = new AnimMap_Null();
			Anim* nullAnimation = new Anim(Anim::ANIM_SPECIAL::IDENTITY, animation->GetNumBones());
			this->poNullAnim->Set(*this, *nullAnimation);

			if (!this->pActiveAnim)
			{
				this->pActiveAnim = this->poNullAnim;
			}
		}
		if (!this->poBlendAnim)
		{

			TimerController* pBlendTimer = new TimerController(minTime, DEFAULT_BLEND_TIME);
			Anim* pBlendAnim = new Anim(Anim::ANIM_SPECIAL::BLEND, animation->GetNumBones());
			this->poBlendAnim = new AnimMap_Blend(*this, *pBlendAnim, *pBlendTimer);
		}

	}

	AnimMap* AnimController::Find(AnimName name)
	{
		if (!this->poCompNode)
		{
			this->poCompNode = new AnimMap();
		}

		this->poCompNode->Name = name;

		return (AnimMap*)this->BaseFind(*this->poCompNode);
	}

	void AnimController::Remove(AnimName name)
	{
		this->poCompNode->Name = name;

		this->BaseRemove(*this->poCompNode);
	}

	void AnimController::Set(_Time delta, GameObjectFont* debugMessage)
	{
		this->bShouldDelete = false;
		this->Delta = delta;
		if (debugMessage)
		{
			this->poDebugObject = new DebugObject(*debugMessage);
		}
	}

	void AnimController::SetActive(AnimName name, bool loop, _Time blendTime)
	{
		AnimMap* pAnim = this->Find(name);

		this->BlendFromActiveAnim(*pAnim, loop, blendTime);
	}

	void AnimController::SetActive(AnimMap& animMap, bool loop, _Time blendTime)
	{
		this->BlendFromActiveAnim(animMap, loop, blendTime);
	}

	void AnimController::SetActiveNoBlend(AnimName name, bool loop)
	{
		this->bIsBlending = false;

		privSetActive(name, loop);
	}

	void AnimController::SetActiveNoBlend(AnimMap& animMap, bool loop)
	{
		this->bIsBlending = false;

		privSetActive(animMap, loop);
	}

	void AnimController::SetIdleAsActive(_Time blendTime)
	{
		AnimMap* pAnim = this->GetIdle();

		if (this->pActiveAnim->Compare(*pAnim))
		{
			this->pActiveAnim->SetLoop(true);
		}
		else
		{
			this->BlendFromActiveAnim(*pAnim, true, blendTime);
		}
	}

	void AnimController::BlendFromActiveAnim(AnimMap& toAnim, bool loop, _Time blendTime)
	{
		// Do nothing if ActiveAnim == toAnim
		if (this->pActiveAnim->Compare(toAnim))
		{
			return;
		}

		CMD_SetAnimNoBlend* animCallback = new CMD_SetAnimNoBlend(*this, toAnim, loop);
		this->poBlendAnim->poAnim->SetCallback(animCallback);

		if (bIsBlending)
		{
			this->poBlendAnim->pFrom->poTimerController->SetCurrTime(_Time(_Time::Duration::ZERO));
			this->poBlendAnim->pFrom->SetLoop(false);
			this->poBlendAnim->Set(*this->poBlendAnim->pTo, toAnim, blendTime);
		}
		else
		{
			this->poBlendAnim->Set(*this->pActiveAnim, toAnim, blendTime);
		}
		
		this->bIsBlending = true;

		privSetActive(*this->poBlendAnim, false);
	}

	void AnimController::SetCallbackNullIfCurrent(Command& pCallback) 
	{ 
		if (this->pActiveAnim->poAnim->GetCallback() == &pCallback)
		{
			this->pActiveAnim->poAnim->SetCallbackNull();
		}
	}


	void AnimController::SetIdle(AnimName name)
	{
		this->pIdleAnim = this->Find(name);
	}

	void AnimController::Update(ShaderObject* _pAnimMixerSO)
	{
		this->pActiveAnim->Update(this->Delta, _pAnimMixerSO);
	}

	void AnimController::SetArmature(Armature& armature)
	{
		this->pArmature = &armature;
	}

	void AnimController::AdjustDelta(DIRECTION dir, _Time change)
	{
		switch (dir)
		{
		case DIRECTION::UP:
			this->Delta += change;
			break;
		case DIRECTION::DOWN:
			this->Delta -= change;
			if (this->Delta <= _Time(_Time::Duration::ZERO))
			{
				this->Delta = _Time(_Time::Duration::ZERO);
			}
		case EngineNames::DIRECTION::LEFT:
		case EngineNames::DIRECTION::RIGHT:
		case EngineNames::DIRECTION::FORWARD:
		case EngineNames::DIRECTION::BACKWARD:
		default:
			break;
		}
	}

	void AnimController::Reverse()
	{
		this->Delta *= -1.0f;
	}

	const char* AnimController::GetName()
	{
		return "Anim Controller";
	}

	bool AnimController::Compare(NodeBase& pNode)
	{
		AnimController* pComp = (AnimController*)&pNode;

		return(this->GetHandle() == pComp->GetHandle());

	}

	unsigned int AnimController::GetBoneIndex(unsigned int nodeIndex)
	{
		return this->pActiveAnim->GetBoneIndex(nodeIndex);
	}


	void AnimController::Wash()
	{
		this->BaseClear();
		this->Delta = _Time(_Time::Duration::ZERO);
		this->pActiveAnim = nullptr;

		if (this->poCompNode)
		{
			delete this->poCompNode;
			this->poCompNode = nullptr;
		}
		if (this->poNullAnim)
		{
			delete this->poNullAnim;
			this->poNullAnim = nullptr;
		}
		if (this->poBlendAnim)
		{
			delete this->poBlendAnim;
			this->poBlendAnim = nullptr;
		}
		if (this->poDebugObject)
		{
			delete this->poDebugObject;
			this->poDebugObject = nullptr;
		}
		if (this->pArmature)
		{
			pArmature->MarkForDelete();
			this->pArmature = nullptr;
		}
	}

	NodeBase* AnimController::CreateNode()
	{
		return new AnimMap();
	}

	void AnimController::privSetActive(AnimMap& animMap, bool loop)
	{
		this->pActiveAnim = &animMap;
		this->pActiveAnim->SetLoop(loop);

		if (this->poDebugObject)
		{
			this->poDebugObject->SetMessage(this->pArmature->GetName(), nullptr, this->GetActiveName());
			this->poDebugObject->Display();
		}
	}

	void AnimController::privSetActive(AnimName name, bool loop)
	{
		AnimMap* pAnim = this->Find(name);
		if (pAnim)
		{
			//if (this->pActiveAnim)
			//{
			//	this->pActiveAnim->SetLoop(false);
			//	this->pActiveAnim->poTimerController->SetCurrTime(_Time(_Time::Duration::ZERO));
			//}

			this->pActiveAnim = pAnim;
			this->pActiveAnim->SetLoop(loop);

			if (this->poDebugObject)
			{
				this->poDebugObject->SetMessage(this->pArmature->GetName(), nullptr, this->GetActiveName());
				this->poDebugObject->Display();
			}
		}
	}

}