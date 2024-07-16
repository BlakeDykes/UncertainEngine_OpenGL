#include "Manager_Wrapper.h"

using namespace Uncertain;

void ManagerWrapper::InitManagers(Game* pGame)
{
	CommandQueueManager::Create();
	PlayerManager::Create();
	ProtoManager::Create();
	MeshNodeManager::Create();
	ShaderManager::Create(true);
	ArmatureManager::Create();
	TextureManager::Create();
	ImageManager::Create(true);
	FontManager::Create(true);
	GraphicsObjectManager::Create();
	GameObjectManager::Create();
	CameraManager::Create(*pGame);
	UIManager::Create();
	InputManager::Create();
	FrameManager::Create();
	AnimManager::Create();
}

void ManagerWrapper::DestroyManagers()
{
	PlayerManager::Destroy();
	ProtoManager::Destroy();
	InputManager::Destroy();
	UIManager::Destroy();
	FrameManager::Destroy();
	GameObjectManager::Destroy();
	AnimManager::Destroy();
	MeshNodeManager::Destroy();
	ImageManager::Destroy();
	FontManager::Destroy();
	TextureManager::Destroy();
	ArmatureManager::Destroy();
	ShaderManager::Destroy();
	GraphicsObjectManager::Destroy();
	CameraManager::Destroy();
	CommandQueueManager::Destroy();
}