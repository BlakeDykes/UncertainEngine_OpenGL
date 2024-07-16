#include "CMD_SetAnimNoBlend.h"

CMD_SetAnimNoBlend::CMD_SetAnimNoBlend(AnimController& controller, AnimNames::AnimName animName, bool loop)
	:AnimCMD(CommandName::Anim_Set, controller), AnimationMap(nullptr), Name(animName), Loop(loop)
{
}

CMD_SetAnimNoBlend::CMD_SetAnimNoBlend(AnimController& controller, AnimMap& animMap, bool loop)
	: AnimCMD(CommandName::Anim_Set, controller), AnimationMap(&animMap), Name(AnimName::UNINITIALIZED), Loop(loop)
{
}

void CMD_SetAnimNoBlend::Execute()
{
	this->pController->SetCallbackNullIfCurrent(*this);

	if (AnimationMap)
	{
		this->pController->SetActiveNoBlend(*this->AnimationMap, this->Loop);
	}
	else
	{
		this->pController->SetActiveNoBlend(this->Name, this->Loop);
	}

	delete this;
}