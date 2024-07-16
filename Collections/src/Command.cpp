#include "Command.h"
#include "CommandQueueManager.h"

namespace Uncertain
{
	Command::Command(CommandName name, QueueName exeQueue)
		:CName(name), ExeQueue(exeQueue), pCallback(nullptr), bPreventCallback(false)
	{
	}

	Command::Command(CommandName name, QueueName exeQueue, Command* _pCallback)
		: CName(name), ExeQueue(exeQueue), pCallback(_pCallback), bPreventCallback(false)
	{
	}

	Command::~Command()
	{

		if (!this->bPreventCallback && this->pCallback != nullptr)
		{
			if (this->ExeQueue == this->pCallback->ExeQueue)
			{
				this->pCallback->Execute();
			}
			else
			{
				CommandQueueManager::SendData(this->pCallback);
			}
		}
	}

	void Command::SetCallback(Command* _pCallback)
	{
		this->pCallback = _pCallback;
	}

	void Command::PreventCallback()
	{
		this->bPreventCallback = true;
	}

}
