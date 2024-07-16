#include "TimerManager.h"
#include "DLinkManager.h"

namespace Uncertain
{

	TimerManager::TimerManager(int initialNumReserved, int deltaGrow)
		:ManagerBase(*new DLinkManager(), *new DLinkManager()), FirstRequest(_Time(_Time::Duration::ZERO)), ZeroSet(false)
	{
		this->SetReserve(initialNumReserved, deltaGrow);
		this->mTimer.Tic();
	}

	TimerManager::~TimerManager()
	{
		this->BaseClear();
	}

	void TimerManager::Update()
	{
		this->CurTime = this->mTimer.Toc();

		TimerEvent* pCur = (TimerEvent*)this->poActive->GetFirst();

		while (pCur != nullptr)
		{
			pCur->UpdateAndTrigger(CurTime);

			pCur = (TimerEvent*)pCur->GetNext();
		}

		this->RemoveTriggered();
	}

	_Time TimerManager::GetTime()
	{
		if (ZeroSet)
		{
			return this->mTimer.Toc() - FirstRequest;
		}
		else
		{
			this->ZeroSet = true;
			this->FirstRequest = mTimer.Toc();
			return _Time(_Time::Duration::ZERO);
		}
	}

	_Time TimerManager::GetTotalTime()
	{
		return this->mTimer.Toc();
	}

	TimerEvent* TimerManager::Add(Command& pCMD, _Time timeInitiated, int timeToTrigger, _Time::Duration triggerTimeUnit)
	{
		_Time currentTime = mTimer.Toc();
		
		_Time triggerTime = (currentTime + (currentTime - timeInitiated)) + (_Time(triggerTimeUnit) * timeToTrigger);

		// Convert time till trigger to milliseconds to determine priority in queue
		int priority = _Time::Quotient(triggerTime - currentTime, _Time(_Time::Duration::ONE_MILLISECOND));

		TimerEvent* pNode = (TimerEvent*)this->BaseAdd(priority);

		pNode->Set(pCMD, triggerTime, priority);

		return pNode;
	}

	void TimerManager::Remove(TimerEvent& pEvent)
	{
		this->BaseRemove(pEvent);
	}

	void TimerManager::RemoveTriggered()
	{
		TimerEvent* pCur = (TimerEvent*)this->poActive->GetFirst();
		TimerEvent* pTemp;

		while (pCur != nullptr && pCur->GetDeleteMark() == true)
		{
			pTemp = (TimerEvent*)pCur->GetNext();
			BaseRemove(*pCur);
			pCur = pTemp;
		}
	}

	NodeBase* TimerManager::CreateNode()
	{
		return new TimerEvent();
	}

}