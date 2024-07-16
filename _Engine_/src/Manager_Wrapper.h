#ifndef MANAGER_WRAPPER_H
#define MANAGER_WRAPPER_H

#include "CommandQueueManager.h"
#include "MeshNodeManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "GraphicsObjectManager.h"
#include "GameObjectManager.h"
#include "InputManager.h"
#include "CameraManager.h"
#include "ProtoManager.h"
#include "AnimManager.h"
#include "PlayerManager.h"
#include "ImageManager.h"
#include "UIManager.h"
#include "FontManager.h"
#include "ArmatureManager.h"
#include "FrameManager.h"

class Game;

class ManagerWrapper
{
public:
	static void InitManagers(Game* pGame);
	static void DestroyManagers();
};

#endif // !MANAGER_WRAPPER_H
