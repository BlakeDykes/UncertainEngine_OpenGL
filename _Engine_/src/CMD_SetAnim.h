#ifndef CMD_SET_ANIM_H
#define CMD_SET_ANIM_H

#include "AnimCMD.h"
#include "AnimController.h"

class CMD_SetAnim : public AnimCMD
{
public:

	CMD_SetAnim() = delete;
	CMD_SetAnim(const CMD_SetAnim&) = delete;
	CMD_SetAnim& operator=(const CMD_SetAnim&) = delete;
	virtual ~CMD_SetAnim() = default;

	CMD_SetAnim(AnimController& controller, AnimNames::AnimName animName, bool loop, _Time blendTime = AnimController::DEFAULT_BLEND_TIME);
	CMD_SetAnim(AnimController& controller, AnimMap& animMap, bool loop, _Time blendTime = AnimController::DEFAULT_BLEND_TIME);

	virtual void Execute() override;

private:
	AnimMap* AnimationMap;
	AnimNames::AnimName Name;
	_Time BlendTime;
	bool Loop;
};


#endif // !CMD_SET_ANIM_H
