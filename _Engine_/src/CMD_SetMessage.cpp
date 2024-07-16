#include "CMD_SetMessage.h"
#include "GameObjectFont.h"

CMD_SetMessage::CMD_SetMessage(GameObjectFont& messageGameObject, const char* message)
	: Command(CommandName::SetMessage, QueueName::GAME), pMessageGameObject(&messageGameObject), pMessage(message)
{
}

void CMD_SetMessage::Execute()
{
	if (this->pMessageGameObject && pMessage)
	{
		this->pMessageGameObject->SetMessage(pMessage);
	}

	delete this;
}
