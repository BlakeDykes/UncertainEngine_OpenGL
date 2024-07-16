#ifndef CMD_SET_IDLE_AS_ACTIVE_H
#define CMD_SET_IDLE_AS_ACTIVE_H

#include "AnimCMD.h"
#include "AnimController.h"

class CMD_SetIdleAsActive : public AnimCMD
{
public:

	CMD_SetIdleAsActive() = delete;
	CMD_SetIdleAsActive(const CMD_SetIdleAsActive&) = delete;
	CMD_SetIdleAsActive& operator=(const CMD_SetIdleAsActive&) = delete;
	virtual ~CMD_SetIdleAsActive() = default;

	CMD_SetIdleAsActive(AnimController& controller, _Time blendTime = AnimController::DEFAULT_BLEND_TIME);

	virtual void Execute() override;

private:
	_Time BlendTime;
	
};


#endif // !CMD_SET_ANIM_H
