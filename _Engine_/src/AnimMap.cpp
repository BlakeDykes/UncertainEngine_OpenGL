#include "AnimMap.h"
#include "CommandQueueManager.h"
#include "AnimController.h"
#include "EngineCMDWrapper.h"
#include "ShaderObject.h"

AnimMap::AnimMap()
	: Name(AnimName::UNINITIALIZED), pController(nullptr), poAnim(nullptr), poTimerController(nullptr), Loop(false)
{
}

AnimMap::~AnimMap()
{
	if (this->poTimerController)
	{
		delete this->poTimerController;
		this->poTimerController = nullptr;
	}
	if (this->poAnim)
	{
		delete this->poAnim;
		this->poAnim = nullptr;
	}
}

void AnimMap::Set(AnimName name, AnimController& animController, Anim& anim, TimerController& timer)
{
	this->Name = name;
	this->pController = &animController;

	if (this->poAnim)
	{
		delete this->poAnim;
	}
	this->poAnim = &anim;
	
	if (this->poTimerController)
	{
		delete this->poTimerController;
	}
	this->poTimerController = &timer;
}

void AnimMap::Update(_Time delta, ShaderObject* _pAnimMixerSO)
{
	// if finished
	if (this->poTimerController->Update(delta))
	{
		// if loop is true
		if (this->Loop)
		{
			this->poTimerController->SetCurrTime(this->poTimerController->GetMinTime());
		}
		// if the animation has a callback
		else if (this->poAnim->GetCallback())
		{
			CommandQueueManager::SendData(this->poAnim->GetCallback());
		}
		// set idle
		else
		{
			CMD_SetIdleAsActive* pSetIdle = new CMD_SetIdleAsActive(*this->pController);
			CommandQueueManager::SendData(pSetIdle);
		}
	}
	// if not finished
	else
	{
		this->poAnim->Animate(this->poTimerController->GetCurrTime(), _pAnimMixerSO);
	}
}

const char* AnimMap::GetName()
{
	return Stringify(this->Name);
}

bool AnimMap::Compare(NodeBase& pNode)
{
	AnimMap* pComp = (AnimMap*)&pNode;

	return (this->Name == pComp->Name);
}

void AnimMap::Print()
{

}

void AnimMap::Wash()
{

	this->Name = AnimName::UNINITIALIZED;
	this->pController = nullptr;

	if (this->poTimerController)
	{
		delete this->poTimerController;
		this->poTimerController = nullptr;
	}
	if (this->poAnim)
	{
		delete this->poAnim;
		this->poAnim = nullptr;
	}
}