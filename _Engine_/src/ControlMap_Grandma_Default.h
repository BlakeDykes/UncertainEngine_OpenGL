#ifndef CONTROL_MAP_GRANDMA_DEFAULT_H
#define CONTROL_MAP_GRANDMA_DEFAULT_H

#include "ControlMap.h"

namespace Uncertain
{

	class ControlMap_Grandma_Default : public ControlMap
	{
	public:
		ControlMap_Grandma_Default() = default;
		ControlMap_Grandma_Default(const ControlMap_Grandma_Default&) = delete;
		ControlMap_Grandma_Default& operator=(const ControlMap_Grandma_Default&) = delete;
		~ControlMap_Grandma_Default() = default;

		virtual void HandleAction(Keyboard::Key key, PlayerController& playerController) override;
	};
}



#endif // !CONTROL_MAP_GRANDMA_DEFAULT_H
