#include "PlayerManager.h"
#include "DLinkManager.h"
#include "DLinkIterator.h"
#include "AnimController.h"
#include "ControlMap.h"

namespace Uncertain
{
	PlayerManager* PlayerManager::instance = nullptr;

	PlayerManager::PlayerManager(int initialReserved, int deltaGrow)
		:ManagerBase(*new DLinkManager(), *new DLinkManager()), pActivePlayer(nullptr)
	{
		this->SetReserve(initialReserved, deltaGrow);
	}

	PlayerManager::~PlayerManager()
	{
		this->BaseClear();
		delete this->pCompNode;
	}


	void PlayerManager::Create(int initialReserved, int deltaGrow)
	{
		assert(initialReserved >= 0);
		assert(deltaGrow > 0);
		assert(!instance);

		if (!instance)
		{
			instance = new PlayerManager(initialReserved, deltaGrow);

			instance->pCompNode = new Player();
		}
	}

	void PlayerManager::Destroy()
	{
		PlayerManager* inst = PlayerManager::GetInstance();

		delete inst;

		instance = nullptr;
	}

	Player* PlayerManager::Add(PlayerName name, GameObjectAnim& gameObject, ControlMap& map)
	{
		PlayerManager* inst = PlayerManager::GetInstance();

		Player* pNode = (Player*)inst->BaseAdd();

		pNode->Set(name, gameObject, map);

		if (!inst->pActivePlayer)
		{
			inst->pActivePlayer = pNode;
		}

		return pNode;
	}

	void PlayerManager::ExecuteAction(Keyboard::Key key, PlayerName playerName)
	{
		PlayerManager* inst = PlayerManager::GetInstance();

		Player* pPlayer = nullptr;

		if(playerName == PlayerName::UNINITIALIZED)
		{
			pPlayer = (Player*)inst->poActive->GetFirst();
			while (pPlayer)
			{
				pPlayer->ExecuteAction(key);
				pPlayer = (Player*)pPlayer->GetNext();
			}
			
		}
		else
		{
			pPlayer = inst->Find(playerName);

			if(pPlayer)
			{
				pPlayer->ExecuteAction(key);

			}
		}
	}


	Player* PlayerManager::Find(NodeBase::Handle nodeID)
	{
		PlayerManager* inst = PlayerManager::GetInstance();

		return (Player*)inst->BaseFindByHandle(nodeID);
	}

	Player* PlayerManager::Find(PlayerName name)
	{
		PlayerManager* inst = PlayerManager::GetInstance();

		inst->pCompNode->SetName(name);

		return (Player*)inst->BaseFind(*inst->pCompNode);
	}

	void PlayerManager::Remove(Player& pNode)
	{
		PlayerManager* inst = PlayerManager::GetInstance();

		inst->BaseRemove(pNode);
	}

	void PlayerManager::PrintAll()
	{
		PlayerManager* inst = PlayerManager::GetInstance();

		Trace::out("\n");
		Trace::out("----------------------------\n");
		Trace::out("----- Active Animations ----\n");
		Trace::out("----------------------------\n");

		inst->BasePrintAll();
	}

	NodeBase* PlayerManager::CreateNode()
	{
		return new Player();
	}

	PlayerManager* PlayerManager::GetInstance()
	{
		assert(instance);
		return instance;
	}

	void PlayerManager::Clear()
	{
		this->BaseClear();
	}
}
