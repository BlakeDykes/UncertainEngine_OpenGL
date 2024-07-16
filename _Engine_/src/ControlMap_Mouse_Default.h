#ifndef CONTROL_MAP_MOUSE_DEFAULT_H
#define CONTROL_MAP_MOUSE_DEFAULT_H

#include "ControlMap.h"

namespace Uncertain
{

	class ControlMap_Mouse_Default : public ControlMap
	{
	public:
		ControlMap_Mouse_Default() = default;
		ControlMap_Mouse_Default(const ControlMap_Mouse_Default&) = delete;
		ControlMap_Mouse_Default& operator=(const ControlMap_Mouse_Default&) = delete;
		~ControlMap_Mouse_Default() = default;

		virtual void HandleAction(Keyboard::Key key, PlayerController& playerController) override;
	};
}



#endif // !CONTROL_MAP_MOUSE_DEFAULT_H
