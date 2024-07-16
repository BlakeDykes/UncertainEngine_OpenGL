#pragma once

#include <mutex>
#include "CommandIndex.h"
#include "DLink.h"
#include "Names_CommandQueue.h"

namespace Uncertain
{
	class Command;

	class CommandQueue : public DLink
	{
	public:

		static const int Command_DATA_SIZE = 1 << 10; // 32

		CommandQueue();

		CommandQueue(const CommandQueue&) = delete;
		const CommandQueue& operator =(const CommandQueue&) = delete;

		~CommandQueue();

		bool PushBack(Command* val);
		bool PopFront(Command*& val);

		void Set(QueueName queueName, COMMAND_QUEUE_ID id);
		void SetID(COMMAND_QUEUE_ID id);
		COMMAND_QUEUE_ID GetID() const { return this->ID; }
		QueueName GetQueueName() const { return this->QName; }

		virtual void Wash() override;
		virtual bool Compare(NodeBase& pNode) override;

	private:
		Command* data[Command_DATA_SIZE];

		COMMAND_QUEUE_ID ID;
		QueueName QName;

		CommandIndex front;
		CommandIndex back;

		bool empty;
		bool full;

		std::mutex mtx;
	};
}
