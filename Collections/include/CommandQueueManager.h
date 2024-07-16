#pragma once

#include "ManagerBase.h"
#include "CommandQueue.h"

namespace Uncertain
{
	class Command;

	class CommandQueueManager : public ManagerBase
	{
	public:
		CommandQueueManager() = delete;
		CommandQueueManager(const CommandQueueManager&) = delete;
		CommandQueueManager& operator =(const CommandQueueManager&) = delete;
		virtual ~CommandQueueManager();

		static void Create(int initialNumReserved = 5, int deltaGrow = 2);
		static void Destroy();

		static CommandQueue* Add(QueueName queueName);
		static CommandQueue* Find(COMMAND_QUEUE_ID id);
		static CommandQueue* Find(QueueName queueName);
		static void Remove(CommandQueue& pQueue);

		static bool SendData(Command* pCommand);
		static bool SendData(COMMAND_QUEUE_ID id, Command* pCommand);

		virtual NodeBase* CreateNode() override;

	private:
		CommandQueueManager(int initialReserved, int deltaGrow);
		static CommandQueueManager* GetInstance();
		void Clear();

		static CommandQueueManager* instance;
		CommandQueue* pCompNode;

		COMMAND_QUEUE_ID CurrentID;
	};
}
