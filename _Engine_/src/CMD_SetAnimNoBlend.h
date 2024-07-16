#ifndef CMD_SET_ANIM_NO_BLEND_H
#define CMD_SET_ANIM_NO_BLEND_H

#include "AnimCMD.h"
#include "AnimController.h"

class CMD_SetAnimNoBlend : public AnimCMD
{
public:

	CMD_SetAnimNoBlend() = delete;
	CMD_SetAnimNoBlend(const CMD_SetAnimNoBlend&) = delete;
	CMD_SetAnimNoBlend& operator=(const CMD_SetAnimNoBlend&) = delete;
	virtual ~CMD_SetAnimNoBlend() = default;

	CMD_SetAnimNoBlend(AnimController& controller, AnimNames::AnimName animName, bool loop);
	CMD_SetAnimNoBlend(AnimController& controller, AnimMap& animMap, bool loop);


	virtual void Execute() override;

private:
	AnimMap* AnimationMap;
	AnimNames::AnimName Name;
	bool Loop;
};


#endif // !CMD_SET_ANIM_H
