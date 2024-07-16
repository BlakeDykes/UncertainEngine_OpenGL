#ifndef CMD_TIME_EVENT_H
#define CMD_TIME_EVENT_H

#include "Command.h"
#include "_Time.h"

using namespace Uncertain;

class CMD_TimedEvent_Anim : public Command
{
public:

	CMD_TimedEvent_Anim() = delete;
	CMD_TimedEvent_Anim(const CMD_TimedEvent_Anim&) = delete;
	CMD_TimedEvent_Anim& operator=(const CMD_TimedEvent_Anim&) = delete;
	virtual ~CMD_TimedEvent_Anim() = default;

	CMD_TimedEvent_Anim(Command& command, _Time timeInitiated, 
						int timeTillTrigger, _Time::Duration triggerTimeUnit);

	virtual void Execute() override;

private:
	Command* pCMD;
	_Time InitTime;
	int TimeTillTrigger;
	_Time::Duration TriggerTimeUnit;
};

#endif
