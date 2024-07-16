#include "Player.h"
#include "PlayerController.h"
#include "ControlMap.h"

namespace Uncertain
{
	Player::Player()
		:Name(PlayerName::UNINITIALIZED), pController(nullptr)
	{
	}

	Player::~Player()
	{
		if (this->pController)
		{
			delete this->pController;
			this->pController = nullptr;
		}
	}

	void Player::Set(PlayerName name, GameObjectAnim& gameObject, ControlMap& map)
	{
		this->Name = name;

		this->pController = new PlayerController(gameObject, map);
	}

	void Player::ExecuteAction(Keyboard::Key key)
	{
		this->pController->ExecuteAction(key);
	}

	const char* Player::GetName()
	{
		return Stringify(this->Name);
	}

	bool Player::Compare(NodeBase& pNode)
	{
		Player* pComp = (Player*)&pNode;

		return (this->Name == pComp->Name);
	}

	void Player::Print()
	{
		Trace::out("-- %s", Stringify(this->Name));
	}

	void Player::Wash()
	{
		this->Name = PlayerName::UNINITIALIZED;

		if (this->pController)
		{
			delete this->pController;
			this->pController = nullptr;
		}
	}

}
