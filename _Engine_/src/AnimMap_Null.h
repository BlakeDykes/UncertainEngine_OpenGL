#ifndef ANIM_MAP_NULL_H
#define ANIM_MAP_NULL_H

#include "AnimMap.h"

namespace Uncertain
{

	class AnimMap_Null : public AnimMap
	{
	public:
		AnimMap_Null();
		AnimMap_Null(const AnimMap_Null&) = delete;
		AnimMap_Null& operator=(const AnimMap_Null&) = delete;
		virtual ~AnimMap_Null();

		virtual void Update(_Time delta, ShaderObject* _pAnimMixerSO) override;

		void Set(AnimController& animController, Anim& anim);

	};

}
#endif // !ANIM_MAP_NULL_H
