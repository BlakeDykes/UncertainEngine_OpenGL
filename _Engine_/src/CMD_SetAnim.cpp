#include "CMD_SetAnim.h"

CMD_SetAnim::CMD_SetAnim(AnimController& controller, AnimNames::AnimName animName, bool loop, _Time blendTime)
	:AnimCMD(CommandName::Anim_Set, controller), AnimationMap(nullptr), 
	Name(animName), BlendTime(blendTime), Loop(loop)
{
}

CMD_SetAnim::CMD_SetAnim(AnimController& controller, AnimMap& animMap, bool loop, _Time blendTime)
	: AnimCMD(CommandName::Anim_Set, controller), AnimationMap(&animMap), 
		Name(AnimName::UNINITIALIZED), BlendTime(blendTime), Loop(loop)
{
}

void CMD_SetAnim::Execute()
{
	this->pController->SetCallbackNullIfCurrent(*this);

	if (AnimationMap)
	{
		this->pController->SetActive(*this->AnimationMap, this->Loop, BlendTime);
	}
	else
	{
		this->pController->SetActive(this->Name, this->Loop, BlendTime);
	}

	delete this;
}

