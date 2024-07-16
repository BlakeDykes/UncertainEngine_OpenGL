#ifndef ANIM_MAP_BLEND_H
#define ANIM_MAP_BLEND_H

#include "AnimMap.h"

namespace Uncertain
{
	class AnimMixer;

	class AnimMap_Blend : public AnimMap
	{
	public:
		AnimMap_Blend(AnimController& animController, Anim& anim, TimerController& timer);
		AnimMap_Blend() = delete;
		AnimMap_Blend(const AnimMap_Blend&) = delete;
		AnimMap_Blend& operator=(const AnimMap_Blend&) = delete;
		virtual ~AnimMap_Blend() = default;

		virtual void Update(_Time delta, ShaderObject* _pAnimMixerSO) override;

		void Set(AnimMap& from, AnimMap& to, _Time blendTime);

		AnimMap* pFrom;
		AnimMap* pTo;
	};

}
#endif // !ANIM_MAP_BLEND_H
