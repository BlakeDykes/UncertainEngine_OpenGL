#include "AnimMap_Blend.h"
#include "CommandQueueManager.h"

Uncertain::AnimMap_Blend::AnimMap_Blend(AnimController& animController, Anim& anim, TimerController& timer)
{
	this->Name = AnimName::BLEND_ANIM;
	pController = &animController;
	poAnim = &anim;
	poTimerController = &timer;

	Loop = false;
}

void Uncertain::AnimMap_Blend::Update(_Time delta, ShaderObject* _pAnimMixerSO)
{
	// If blend is over, set current anim to pTo
	if (this->poTimerController->Update(delta))
	{
		pFrom->poTimerController->SetCurrTime(_Time(_Time::Duration::ZERO));
		CommandQueueManager::SendData(this->poAnim->GetCallback());
	}
	else
	{
		// Update From and To timers and loop if they finish before blending
		if (pFrom->poTimerController->Update(delta))
		{
			pFrom->poTimerController->SetCurrTime(pFrom->poTimerController->GetMinTime());
		}
		if (pTo->poTimerController->Update(delta))
		{
			pTo->poTimerController->SetCurrTime(pTo->poTimerController->GetMinTime());
		}

		// Animate From and To
		pFrom->poAnim->Animate(pFrom->poTimerController->GetCurrTime(), _pAnimMixerSO);
		pTo->poAnim->Animate(pTo->poTimerController->GetCurrTime(), _pAnimMixerSO);

		float tS = this->poTimerController->GetCurrTime() / this->poTimerController->GetMaxTime();

		this->poAnim->CustomAnimate(_pAnimMixerSO, pFrom->GetBoneResultSSBO(), pTo->GetBoneResultSSBO(), tS);
	}
}

void Uncertain::AnimMap_Blend::Set(AnimMap& from, AnimMap& to, _Time blendTime)
{
	this->poTimerController->SetCurrTime(_Time(_Time::Duration::ZERO));
	this->poTimerController->SetMaxTime(blendTime);
	this->pFrom = &from;
	this->pTo = &to;
}
