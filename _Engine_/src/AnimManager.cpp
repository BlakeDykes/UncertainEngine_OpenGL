#include "AnimManager.h"
#include "DLinkManager.h"
#include "ProtoData_Wrapper.h"
#include "DLinkIterator.h"
#include "AnimController.h"
#include "CommandQueueManager.h"
#include "Command.h"
#include "GameObjectFont.h"
#include "ShaderObject.h"
#include "ShaderManager.h"
#include "TimerManager.h"

namespace Uncertain
{

	AnimManager* AnimManager::instance = nullptr;
	_Time AnimManager::DEFAULT_ANIM_TIME_ADJUST = 0.05f * _Time(_Time::Duration::FILM_24_FRAME);
	_Time AnimManager::MASTER_DELTA = 0.4f * _Time(_Time::Duration::FILM_24_FRAME);


	AnimManager::AnimManager(int initialReserved, int deltaGrow)
		:ManagerBase(*new DLinkManager(), *new DLinkManager()), Delta(MASTER_DELTA), MasterPlay(true), 
		poTimedEventManager( new TimerManager())
	{
		this->SetReserve(initialReserved, deltaGrow);
		this->pAnimMixerSO = ShaderManager::Find(ShaderName::COMPUTE_ANIM_MIXER);
		this->pCompNode = new AnimController();
	}

	AnimManager::~AnimManager()
	{
		this->BaseClear();
		delete this->poTimedEventManager;
		delete this->pCompNode;
	}


	void AnimManager::Create(int initialReserved, int deltaGrow)
	{
		assert(initialReserved >= 0);
		assert(deltaGrow > 0);
		assert(!instance);

		if (!instance)
		{
			instance = new AnimManager(initialReserved, deltaGrow);

			instance->pCommandQueue = CommandQueueManager::Add(QueueName::ANIM);
		}
	}

	void AnimManager::Destroy()
	{
		AnimManager* inst = AnimManager::GetInstance();

		delete inst;

		instance = nullptr;
	}

	void AnimManager::AdjustAll(DIRECTION dir, _Time delta)
	{
		AnimManager* inst = AnimManager::GetInstance();

		DLinkIterator* pIt = (DLinkIterator*)inst->poActive->GetIterator();
		AnimController* pCur = (AnimController*)pIt->First();

		while (!pIt->IsDone())
		{
			pCur->AdjustDelta(dir, delta);
			pCur = (AnimController*)pIt->Next();
		}
	}

	void AnimManager::ReverseAll()
	{
		AnimManager* inst = AnimManager::GetInstance();

		DLinkIterator* pIt = (DLinkIterator*)inst->poActive->GetIterator();
		AnimController* pCur = (AnimController*)pIt->First();

		while (!pIt->IsDone())
		{
			pCur->Reverse();
			pCur = (AnimController*)pIt->Next();
		}
	}

	void AnimManager::TogglePlayAll()
	{
		AnimManager* inst = AnimManager::GetInstance();

		inst->MasterPlay = !inst->MasterPlay;
	}

	void AnimManager::AddTimedEvent(Command& command, _Time timeInitiated, int timeTillTrigger, _Time::Duration triggerTimeUnit)
	{
		AnimManager* inst = AnimManager::GetInstance();
		assert(inst->poTimedEventManager);

		inst->poTimedEventManager->Add(command, timeInitiated, timeTillTrigger, triggerTimeUnit);
	}

	_Time AnimManager::GetTime()
	{
		AnimManager* inst = AnimManager::GetInstance();
		assert(inst->poTimedEventManager);


		return inst->poTimedEventManager->GetTime();
	}


	void AnimManager::Update()
	{
		AnimManager* inst = AnimManager::GetInstance();

		Command* pCommand;

		if (inst->MasterPlay)
		{

			// 1. Update and execute timed events
			inst->poTimedEventManager->Update();
			
			// 2. Execute commands
			while(inst->pCommandQueue->PopFront(pCommand) == true)
			{
				pCommand->Execute();
			}

			// 3. Update and animate all controllers
			DLinkIterator* pIt = (DLinkIterator*)inst->poActive->GetIterator();
			AnimController* pCur = (AnimController*)pIt->First();

			while (!pIt->IsDone())
			{
				if (pCur->ShouldDelete())
				{
					inst->BaseRemove(*pCur);
				}
				else
				{
					pCur->Update(inst->pAnimMixerSO);
				}
				pCur = (AnimController*)pIt->Next();
			}
		}
	}

	AnimController* AnimManager::Add(_Time delta, GameObjectFont* debugMessage)
	{
		AnimManager* inst = AnimManager::GetInstance();

		AnimController* pNode = (AnimController*)inst->BaseAdd();

		pNode->Set(delta, debugMessage);

		return pNode;
	}


	AnimController* AnimManager::Find(NodeBase::Handle nodeID)
	{
		AnimManager* inst = AnimManager::GetInstance();

		return (AnimController*)inst->BaseFindByHandle(nodeID);
	}

	void AnimManager::Remove(AnimController& pNode)
	{
		AnimManager* inst = AnimManager::GetInstance();

		inst->BaseRemove(pNode);
	}

	void AnimManager::PrintAll()
	{
		AnimManager* inst = AnimManager::GetInstance();

		Trace::out("\n");
		Trace::out("----------------------------\n");
		Trace::out("----- Active Animations ----\n");
		Trace::out("----------------------------\n");

		inst->BasePrintAll();
	}

	NodeBase* AnimManager::CreateNode()
	{
		return new AnimController();
	}

	AnimManager* AnimManager::GetInstance()
	{
		assert(instance);
		return instance;
	}

	void AnimManager::Clear()
	{
		this->BaseClear();
	}
}
