#ifndef PLAYER_H
#define PLAYER_H

#include "DLink.h"
#include "EngineNames.h"
#include "Keyboard.h"

namespace Uncertain
{
	class AnimController;
	class GameObjectAnim;
	class PlayerController;
	class ControlMap;

	class Player : public DLink
	{
	public:
		
		Player();
		Player(const Player&) = delete;
		Player& operator=(const Player&) = delete;
		virtual ~Player();

		void Set(PlayerName name, GameObjectAnim& gameObject, ControlMap& map);
		void SetName(PlayerName name) { this->Name = name; }
		void ExecuteAction(Keyboard::Key key);

		virtual const char* GetName() override;
		virtual bool Compare(NodeBase& pNode) override;
		virtual void Print() override;
		virtual void Wash() override;

	private:
		PlayerName Name;
		PlayerController* pController;
	};
}

#endif