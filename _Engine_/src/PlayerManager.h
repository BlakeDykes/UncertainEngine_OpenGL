#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H

#include "ManagerBase.h"
#include "Player.h"
#include "Keyboard.h"

namespace Uncertain
{

	class AnimController;
	class GameObjectAnim;
	class ControlMap;

	class PlayerManager : public ManagerBase
	{
	public:

		PlayerManager() = delete;
		PlayerManager(const PlayerManager&) = delete;
		PlayerManager& operator =(const PlayerManager&) = delete;

		static void Create(int initialReserved = 5, int deltaGrow = 5);
		static void Destroy();

		static Player* Add(PlayerName name, GameObjectAnim& gameObject, ControlMap& controlMap);
		static Player* Find(PlayerName name);
		static Player* Find(NodeBase::Handle nodeID);
		static void Remove(Player& pNode);

		static void ExecuteAction(Keyboard::Key key, PlayerName playerName = PlayerName::UNINITIALIZED);
		
		static void PrintAll();

	protected:
		virtual NodeBase* CreateNode() override;

	private:
		PlayerManager(int initialReserved, int deltaGrow);
		static PlayerManager* GetInstance();
		virtual ~PlayerManager();
		void Clear();

		static PlayerManager* instance;
		Player* pCompNode;
		Player* pActivePlayer;
	};
}

#endif // !PLAYER_MANAGER_H
