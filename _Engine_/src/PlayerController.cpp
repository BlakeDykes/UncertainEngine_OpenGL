#include "PlayerController.h"
#include "GameObjectAnim.h"
#include "ControlMap.h"

PlayerController::PlayerController(GameObjectAnim& gameObject, ControlMap& map)
{
	this->pGameObject = &gameObject;
	this->pAnim = this->pGameObject->pAnimController;
	this->poMap = &map;
}

PlayerController::~PlayerController()
{
	delete this->poMap;
}

void PlayerController::ExecuteAction(Keyboard::Key key)
{
	this->poMap->HandleAction(key, *this);
}

void PlayerController::AdjustDelta(DIRECTION dir, _Time change)
{
	AZUL_UNUSED_VAR(dir);
	AZUL_UNUSED_VAR(change);
}

void PlayerController::Reverse()
{

}