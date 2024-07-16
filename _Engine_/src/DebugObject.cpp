#include "DebugObject.h"
#include "GameObjectFont.h"
#include "CommandQueueManager.h"
#include "CMD_SetMessage.h"

DebugObject::DebugObject(GameObjectFont& debugFont)
	: pGameObjectFont(&debugFont)
{
	memset(&MessageBuffer, '\0', MESSAGE_BUFFER_SIZE);
}

DebugObject::~DebugObject()
{
	if (this->pGameObjectFont)
	{
		pGameObjectFont->RemoveDebugObject();
	}
}

void DebugObject::Display(const char* pMessage)
{
	if (this->pGameObjectFont)
	{
		
		if (pMessage)
		{
			strcpy_s(MessageBuffer, MESSAGE_BUFFER_SIZE, pMessage);
		}

		CMD_SetMessage* pCMD = new CMD_SetMessage(*pGameObjectFont, MessageBuffer);
		CommandQueueManager::SendData(pCMD);
	}
}

void DebugObject::SetMessage(const char* message, const char* pre, const char* post)
{
	if (pre)
	{
		strcpy_s(MessageBuffer, MESSAGE_BUFFER_SIZE, pre);
		strcat_s(MessageBuffer, MESSAGE_BUFFER_SIZE, message);
	}
	else
	{
		strcpy_s(MessageBuffer, MESSAGE_BUFFER_SIZE, message);
	}

	if (post)
	{
		strcat_s(MessageBuffer, MESSAGE_BUFFER_SIZE, post);
	}

	
}

