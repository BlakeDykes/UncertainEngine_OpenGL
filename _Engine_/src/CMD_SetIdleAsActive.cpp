#include "CMD_SetIdleAsActive.h"

CMD_SetIdleAsActive::CMD_SetIdleAsActive(AnimController& controller, _Time blendTime)
	:AnimCMD(CommandName::Anim_SetIdleAsActive, controller), BlendTime(blendTime)
{
}

void CMD_SetIdleAsActive::Execute()
{
	this->pController->SetCallbackNullIfCurrent(*this);

	this->pController->SetIdleAsActive(BlendTime);

	delete this;
}
