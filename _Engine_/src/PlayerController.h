#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "AnimManager.h"
#include "ControlMaps_Wrapper.h"
#include "InputManager.h"

namespace Uncertain
{
	class GameObjectAnim;
	class ControlMap;

	class PlayerController
	{
	public:
		PlayerController(GameObjectAnim& gameObject, ControlMap& map);
		PlayerController() = delete;
		PlayerController(const PlayerController&) = delete;
		PlayerController& operator=(const PlayerController&) = delete;
		virtual ~PlayerController();

		void ExecuteAction(Keyboard::Key key);

		AnimController*& GetAnimController() { return this->pAnim; }
		GameObjectAnim*& GetGameObject() { return this->pGameObject; }
		
		void AdjustDelta(DIRECTION dir, _Time change = AnimManager::DEFAULT_ANIM_TIME_ADJUST);
		void Reverse();

	private:
		GameObjectAnim* pGameObject;
		AnimController* pAnim;
		ControlMap* poMap;
	};
}

#endif // !PLAYER_CONTROLLER_H
