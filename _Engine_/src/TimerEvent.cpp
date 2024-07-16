#include "TimerEvent.h"
#include "Command.h"

namespace Uncertain
{
	_Time TimerEvent::INVALID_TIME = _Time(_Time::Duration::MIN);

	TimerEvent::TimerEvent()
		: pCMD(nullptr), TriggerTime(INVALID_TIME), Priority(-1), DeleteMark(false)
	{
	}

	TimerEvent::TimerEvent(Command& command, _Time triggerTime, int priority)
		: pCMD(&command), TriggerTime(triggerTime), Priority(priority), DeleteMark(false)
	{
	}

	TimerEvent::~TimerEvent()
	{
		if (pCMD)
		{
			delete pCMD;
		}
	}

	void TimerEvent::Set(Command& command, _Time triggerTime, int priority)
	{
		this->pCMD = &command;
		this->TriggerTime = triggerTime;
		this->Priority = priority;
		this->DeleteMark = false;
	}

	bool TimerEvent::UpdateAndTrigger(_Time currentTime)
	{
		if (currentTime > TriggerTime)
		{
			Trigger();
			return true;
		}

		Priority = _Time::Quotient(TriggerTime - currentTime, _Time(_Time::Duration::ONE_MILLISECOND));

		return false;
	}

	void TimerEvent::Trigger()
	{
		this->pCMD->Execute();
		this->pCMD = nullptr;
		Priority = 0;

		this->DeleteMark = true;
	}

	bool TimerEvent::Compare(NodeBase& pNode)
	{
		TimerEvent* pComp = (TimerEvent*)&pNode;

		return (this->pCMD->GetName() == pComp->pCMD->GetName()
				&& this->TriggerTime == pComp->TriggerTime);
	}

	void TimerEvent::Wash()
	{
		if (this->pCMD)
		{
			delete this->pCMD;
			this->pCMD = nullptr;
		}

		this->TriggerTime = INVALID_TIME;
		this->DeleteMark = false;
	}

	DLink::PriorityCompResult TimerEvent::ComparePriority(int priority)
	{
		if (this->Priority > priority)
		{
			return DLink::PriorityCompResult::THIS_IS_GREATER_THAN;
		}
		else
		{
			return DLink::PriorityCompResult::THIS_IS_LESS_THAN;
		}
	}
}
