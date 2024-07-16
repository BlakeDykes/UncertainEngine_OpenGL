#ifndef CONTROL_MAP_CHICKEN_BOT_H
#define CONTROL_MAP_CHICKEN_BOT_H

#include "ControlMap.h"

namespace Uncertain
{

	class ControlMap_ChickenBot_Default : public ControlMap
	{
	public:
		ControlMap_ChickenBot_Default() = default;
		ControlMap_ChickenBot_Default(const ControlMap_ChickenBot_Default&) = delete;
		ControlMap_ChickenBot_Default& operator=(const ControlMap_ChickenBot_Default&) = delete;
		~ControlMap_ChickenBot_Default() = default;

		virtual void HandleAction(Keyboard::Key key, PlayerController& playerController) override;
	};
}



#endif // !CONTROL_MAP_CHICKEN_BOT_H
