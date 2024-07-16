#ifndef ANIM_CMD_H
#define ANIM_CMD_H

#include "Command.h"
#include "AnimController.h"
#include "GameObjectFont.h"

class CMD_SetMessage;

class AnimCMD : public Command
{
public:

	AnimCMD() = delete;
	AnimCMD(const AnimCMD&) = delete;
	AnimCMD& operator=(const AnimCMD&) = delete;
	virtual ~AnimCMD() = default;

	AnimCMD(CommandName name, AnimController& controller);

	virtual void Execute() override = 0;

protected:
	AnimController* pController;
};


#endif // !ANIM_CMD_H
