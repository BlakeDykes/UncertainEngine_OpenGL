#ifndef CMD_CB_DONE_H
#define CMD_CB_DONE_H

#include "Command.h"

class CMD_CB_Done : public Command
{
public:

	CMD_CB_Done() = delete;
	CMD_CB_Done(const CMD_CB_Done&) = delete;
	CMD_CB_Done& operator=(const CMD_CB_Done&) = delete;
	virtual ~CMD_CB_Done() = default;

	CMD_CB_Done(std::atomic<bool>& doneFlag, QueueName queueName);

	virtual void Execute() override;

private:
	std::atomic_bool& DoneFlag;
};

#endif
