#include "CMD_TimedEvent_Anim.h"
#include "AnimManager.h"

CMD_TimedEvent_Anim::CMD_TimedEvent_Anim(Command& command, _Time timeInitiated,
										 int timeTillTrigger, _Time::Duration triggerTimeUnit)
	:Command(CommandName::TimedEvent_Anim, QueueName::ANIM), 
	pCMD(&command), InitTime(timeInitiated), TimeTillTrigger(timeTillTrigger), TriggerTimeUnit(triggerTimeUnit)
{
}

void CMD_TimedEvent_Anim::Execute()
{
	AnimManager::AddTimedEvent(*pCMD, InitTime, TimeTillTrigger, TriggerTimeUnit);

	delete this;
}
