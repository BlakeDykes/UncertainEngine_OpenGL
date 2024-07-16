#pragma once

#include "Names_CommandQueue.h"

namespace Uncertain
{
	class UCallback;

	class Command
	{
	public:

		Command() = delete;
		Command(CommandName name, QueueName exeQueue);
		Command(CommandName name, QueueName exeQueue, Command* _pCallback);
		Command(const Command&) = default;
		Command& operator =(const Command&) = default;
		virtual ~Command();

		CommandName GetName() const { return this->CName; }
		QueueName GetExeQueue() const { return this->ExeQueue; }
		void SetCallback(Command* _pCallback);

		virtual void Execute() = 0;

	protected:
		virtual void PreventCallback();

		CommandName CName;
		QueueName ExeQueue;
		Command* pCallback;
		bool bPreventCallback;
	};

}
