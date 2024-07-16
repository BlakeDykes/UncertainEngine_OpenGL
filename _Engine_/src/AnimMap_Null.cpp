#include "AnimMap_Null.h"


AnimMap_Null::AnimMap_Null()
{
}

AnimMap_Null::~AnimMap_Null()
{
	if (this->poAnim)
	{
		delete this->poAnim;
		this->poAnim = nullptr;
	}
	if (this->poTimerController)
	{
		delete this->poTimerController;
		this->poTimerController = nullptr;
	}
}

void AnimMap_Null::Update(_Time delta, ShaderObject* _pAnimMixerSO)
{
	AZUL_UNUSED_VAR(delta);
	AZUL_UNUSED_VAR(_pAnimMixerSO);
}

void AnimMap_Null::Set(AnimController& animController, Anim& anim)
{
	this->Name = AnimName::NULL_ANIM;
	this->pController = &animController;
	this->poAnim = &anim;
	this->poTimerController = new TimerController(_Time(_Time::Duration::ZERO), _Time(_Time::Duration::ZERO));
}