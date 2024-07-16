#include "CMD_CB_Done.h"

CMD_CB_Done::CMD_CB_Done(std::atomic<bool>& doneFlag, QueueName queueName)
	:Command(CommandName::CB_Done, queueName), DoneFlag(doneFlag)
{
}

void CMD_CB_Done::Execute()
{
	this->DoneFlag.store(true);

	Trace::out("Done - %d\n", DoneFlag.load());

	delete this;
}