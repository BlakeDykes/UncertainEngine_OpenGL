#include "Command.h"

class GameObjectFont;

class CMD_SetMessage : public Command
{
public:

	CMD_SetMessage() = delete;
	CMD_SetMessage(const CMD_SetMessage&) = delete;
	CMD_SetMessage& operator=(const CMD_SetMessage&) = delete;
	virtual ~CMD_SetMessage() = default;

	CMD_SetMessage(GameObjectFont& messageGameObject, const char* message = nullptr);

	void SetMessage(const char* message) { this->pMessage = message;}

	virtual void Execute() override;

private:
	GameObjectFont* pMessageGameObject;
	const char* pMessage;

};
#pragma once
