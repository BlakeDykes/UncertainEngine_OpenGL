#ifndef CONTROL_MAP_H
#define CONTROL_MAP_H

#include "CommandQueueManager.h"
#include "EngineCMDWrapper.h"
#include "Keyboard.h"

namespace Uncertain
{
	class PlayerController;

	class ControlMap
	{
	public:
		ControlMap() = default;
		ControlMap(const ControlMap&) = delete;
		ControlMap& operator=(const ControlMap&) = delete;
		~ControlMap() = default;

		virtual void HandleAction(Keyboard::Key key, PlayerController& playerController);
	};
}


#endif