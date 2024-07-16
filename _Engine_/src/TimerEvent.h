#ifndef TIMER_EVENT_H
#define TIMER_EVENT_H

#include "DLink.h"
#include "_Time.h"


namespace Uncertain
{
	class Command;

	class TimerEvent : public DLink
	{
	public:

		TimerEvent();
		TimerEvent(Command& command, _Time triggerTime, int Priority);
		TimerEvent(const TimerEvent&) = delete;
		TimerEvent operator=(const TimerEvent&) = delete;
		virtual ~TimerEvent();

		void Set(Command& command, _Time triggerTime, int Priority);
		bool UpdateAndTrigger(_Time delta);

		virtual bool Compare(NodeBase& pNode) override;
		virtual void Wash() override;
		virtual PriorityCompResult ComparePriority(int priority) override;

		_Time GetTriggerTime() const { return this->TriggerTime; }
		bool GetDeleteMark() const { return this->DeleteMark; }

		static _Time INVALID_TIME;

	private:
		void Trigger();

		Command* pCMD;
		_Time TriggerTime;
		int Priority;
		bool DeleteMark;

	};

}


#endif