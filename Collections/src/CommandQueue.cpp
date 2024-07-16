#include "CommandQueue.h"

namespace Uncertain
{
	CommandQueue::CommandQueue()
		: ID(-1),
		QName(QueueName::UNINITIALIZED),
		front(Command_DATA_SIZE),
		back(Command_DATA_SIZE),
		empty(true),
		full(false)
	{
		for (int i = 0; i < Command_DATA_SIZE; i++)
		{
			this->data[i] = 0;
		}
	}

	CommandQueue::~CommandQueue()
	{
	}

	bool CommandQueue::PushBack(Command* val)
	{
		this->mtx.lock();

		bool status = true;

		if (this->front != this->back || this->empty == true)
		{
			this->data[this->back.GetIndex()] = val;
			this->back++;

			this->empty = false;

			if (this->front == this->back)
			{
				this->full = true;
			}
		}
		else
		{
			status = false;
		}

		this->mtx.unlock();

		return status;
	}

	bool CommandQueue::PopFront(Command*& val)
	{
		this->mtx.lock();

		bool status = true;

		if (this->front != this->back || this->full == true)
		{
			val = this->data[this->front.GetIndex()];

			this->front++;

			this->full = false;

			if (this->front == this->back)
			{
				this->empty = true;
			}
		}
		else
		{
			status = false;
		}

		this->mtx.unlock();

		return status;
	}

	void CommandQueue::Set(QueueName threadName, COMMAND_QUEUE_ID id)
	{
		this->QName = threadName;
		this->ID = id;
	}

	void CommandQueue::SetID(COMMAND_QUEUE_ID id)
	{
		this->ID = id;
	}

	void CommandQueue::Wash()
	{
		this->mtx.lock();

		this->ID = -1;
		this->QName = QueueName::UNINITIALIZED;
		front.SetIndex(0);
		back.SetIndex(0);
		empty = true;
		full = false;

		for (int i = 0; i < Command_DATA_SIZE; i++)
		{
			this->data[i] = 0;
		}

		this->mtx.unlock();
	}

	bool CommandQueue::Compare(NodeBase& pNode)
	{
		CommandQueue* pComp = (CommandQueue*)&pNode;

		return this->ID == pComp->ID;
	}
}
