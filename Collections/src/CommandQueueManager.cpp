#include "CommandQueueManager.h"
#include "DLinkManager.h"
#include "Command.h"

namespace Uncertain
{
	CommandQueueManager* CommandQueueManager::instance = nullptr;

	CommandQueueManager::CommandQueueManager(int initialReserved, int deltaGrow)
		: ManagerBase(*new DLinkManager(), *new DLinkManager()), CurrentID(0)
	{
		this->pCompNode = new CommandQueue();

		this->SetReserve(initialReserved, deltaGrow);
	}

	CommandQueueManager::~CommandQueueManager()
	{
		this->Clear();

		this->pCompNode->Wash();
		delete this->pCompNode;
	}

	void CommandQueueManager::Destroy()
	{
		CommandQueueManager* inst = CommandQueueManager::GetInstance();

		delete inst;
	}

	void CommandQueueManager::Create(int initialNumReserved, int deltaGrow)
	{
		assert(instance == nullptr);
		assert(deltaGrow != 0);

		if (instance == nullptr)
		{
			instance = new CommandQueueManager(initialNumReserved, deltaGrow);
		}
	}

	CommandQueue* CommandQueueManager::Add(QueueName threadName)
	{
		CommandQueueManager* inst = CommandQueueManager::GetInstance();

		CommandQueue* pNode = (CommandQueue*)inst->BaseAdd();

		pNode->Set(threadName, ++inst->CurrentID);

		return pNode;
	}

	CommandQueue* CommandQueueManager::Find(COMMAND_QUEUE_ID id)
	{
		CommandQueueManager* inst = CommandQueueManager::GetInstance();

		inst->pCompNode->SetID(id);

		CommandQueue* pNode = (CommandQueue*)inst->BaseFind(*inst->pCompNode);

		return pNode;
	}

	CommandQueue* CommandQueueManager::Find(QueueName threadName)
	{
		CommandQueueManager* inst = CommandQueueManager::GetInstance();

		CommandQueue* pCur = (CommandQueue*)inst->poActive->GetFirst();

		while (pCur)
		{
			if (pCur->GetQueueName() == threadName)
			{
				break;
			}

			pCur = (CommandQueue*)pCur->GetNext();
		}

		return pCur;
	}

	void CommandQueueManager::Remove(CommandQueue& pQueue)
	{
		CommandQueueManager* inst = CommandQueueManager::GetInstance();

		inst->BaseRemove(pQueue);
	}

	bool CommandQueueManager::SendData(Command* pCommand)
	{
		assert(pCommand);
		CommandQueueManager* inst = CommandQueueManager::GetInstance();

		CommandQueue* pQueue = inst->Find(pCommand->GetExeQueue());
		if (!pQueue)
		{
			return false;
		}

		return pQueue->PushBack(pCommand);
	}

	bool CommandQueueManager::SendData(COMMAND_QUEUE_ID id, Command* pCommand)
	{
		assert(pCommand);
		CommandQueueManager* inst = CommandQueueManager::GetInstance();

		CommandQueue* pQueue = inst->Find(id);
		if (!pQueue)
		{
			return false;
		}

		return pQueue->PushBack(pCommand);
	}

	void CommandQueueManager::Clear()
	{
		CommandQueueManager* inst = CommandQueueManager::GetInstance();

		inst->BaseClear();
	}

	NodeBase* CommandQueueManager::CreateNode()
	{
		return new CommandQueue();
	}

	CommandQueueManager* CommandQueueManager::GetInstance()
	{
		assert(instance != nullptr);
		return instance;
	}
}


