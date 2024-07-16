#ifndef CONTROL_MAP_CHICKEN_BOT_ALT_ONE_H
#define CONTROL_MAP_CHICKEN_BOT_ALT_ONE_H

#include "ControlMap.h"

namespace Uncertain
{

	class ControlMap_ChickenBot_AltOne : public ControlMap
	{
	public:
		ControlMap_ChickenBot_AltOne() = default;
		ControlMap_ChickenBot_AltOne(const ControlMap_ChickenBot_AltOne&) = delete;
		ControlMap_ChickenBot_AltOne& operator=(const ControlMap_ChickenBot_AltOne&) = delete;
		~ControlMap_ChickenBot_AltOne() = default;

		virtual void HandleAction(Keyboard::Key key, PlayerController& playerController) override;
	};
}



#endif // !CONTROL_MAP_CHICKEN_BOT_ALT_ONE_H
