#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include "ManagerBase.h"
#include "Command.h"
#include "_Time.h"
#include "_Timer.h"
#include "TimerEvent.h"

namespace Uncertain
{
	class TimerManager : public ManagerBase
	{
	public:
	
	TimerManager(int initialNumReserved = 5, int deltaGrow = 2);
		TimerManager& operator = (const TimerManager&) = delete;
		TimerManager(const TimerManager&) = delete;
		virtual ~TimerManager();

		void Update();
		_Time GetTotalTime();
		_Time GetTime();

		// Todo:: add sort
		TimerEvent* Add(Command& pCMD, _Time timeInitiated, int timeToTrigger, _Time::Duration triggerTimeUnit);
		void Remove(TimerEvent& pEvent);
		void RemoveTriggered();

		virtual NodeBase* CreateNode() override;


	private:
		_Timer mTimer;
		_Time FirstRequest;
		_Time CurTime;
		bool ZeroSet;
	};

}

#endif