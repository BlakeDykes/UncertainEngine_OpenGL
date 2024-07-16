#include "AnimCMD.h"
#include "CMD_SetMessage.h"
#include "CommandQueueManager.h"

AnimCMD::AnimCMD(CommandName name, AnimController& controller)
	: Command(name, CommandQueueNames::QueueName::ANIM), pController(&controller)
{
}
