#include "Scene_Demo1.h"
#include "GameObject.h"
#include "Manager_Wrapper.h"
#include "EngineNames.h"
#include "AnimNames.h"
#include "EngineCMDWrapper.h"
#include "Camera.h"
#include "UIStyle.h"
#include "GameObjectUIElement.h"
#include "GameObjectFont.h"
#include "ControlMaps_Wrapper.h"
#include "Font.h"
#include "FontManager.h"

namespace Azul
{
	Azul::Scene_Demo1::Scene_Demo1()
	{
	}

	void Scene_Demo1::Load()
	{
		//----------------------------------------------------------------------------------------------------
		//-- Cameras
		//----------------------------------------------------------------------------------------------------
		Camera* pAuxCam = CameraManager::Add(CameraName::AUX_3D_1);
		pAuxCam->setOrientAndPosition(Vec3(0.0f, 1.0f, 0.0f), Vec3(-1.1f, 0.0f, 0.0f), Vec3(-1.1f, 0.0f, 0.25f));

		//// ----------------------------------------------------------------------------------------------------
		//// -- Textures
		//// ----------------------------------------------------------------------------------------------------
		TextureManager::Add(TextureName::GRANDMA, TextureNode::TYPE::MULTI);
		TextureManager::Add(TextureName::MICHELLE_DIFFUSE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::MOUSE_DIFFUSE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::NINJA_DIFFUSE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::ORTIZ_DIFFUSE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::PUMPKIN_HULK_DIFFUSE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::ZOMBIE_GIRL, TextureNode::TYPE::MULTI);


		////// ----------------------------------------------------------------------------------------------------
		////// -- Protos
		////// ----------------------------------------------------------------------------------------------------
		ProtoNode* pGrandmaProto = ProtoManager::Add(ModelName::GRANDMA, TextureName::GRANDMA, ArmatureName::GRANDMA);
		ProtoNode* pMichelleProto = ProtoManager::Add(ModelName::MICHELLE, TextureName::MICHELLE_DIFFUSE, ArmatureName::MICHELLE);
		ProtoNode* pMouseProto = ProtoManager::Add(ModelName::MOUSE, TextureName::MOUSE_DIFFUSE, ArmatureName::MOUSE);
		ProtoNode* pNinjaProto = ProtoManager::Add(ModelName::NINJA, TextureName::NINJA_DIFFUSE, ArmatureName::NINJA);
		ProtoNode* pOrtizProto = ProtoManager::Add(ModelName::ORTIZ, TextureName::ORTIZ_DIFFUSE, ArmatureName::ORTIZ);
		ProtoNode* pPumpkinHulkProto = ProtoManager::Add(ModelName::PUMPKIN_HULK, TextureName::PUMPKIN_HULK_DIFFUSE, ArmatureName::PUMPKIN_HULK);
		ProtoNode* pZombieGirlProto = ProtoManager::Add(ModelName::ZOMBIE_GIRL, TextureName::ZOMBIE_GIRL, ArmatureName::ZOMBIE_GIRL);

		//////// ----------------------------------------------------------------------------------------------------
		//////// -- UI
		//////// ----------------------------------------------------------------------------------------------------

		//// ----------------------------------------------------------------------------------------------------
		//// -- Animations
		//// ----------------------------------------------------------------------------------------------------
		AnimController* pGrandmaController = AnimManager::Add(AnimManager::MASTER_DELTA);
		pGrandmaController->Add(AnimName::S_GRANDMA_IDLE);
		pGrandmaController->Add(AnimName::S_GRANDMA_IDLE_FALLEN);
		pGrandmaController->Add(AnimName::S_GRANDMA_DANCE_MACARENA);
		pGrandmaController->Add(AnimName::S_GRANDMA_DANCE_HIP_HOP);
		pGrandmaController->Add(AnimName::S_GRANDMA_DANCE_SLIDE_HH);
		pGrandmaController->Add(AnimName::S_GRANDMA_DANCE_RUNNING);
		pGrandmaController->Add(AnimName::S_GRANDMA_VICTORY);
		pGrandmaController->Add(AnimName::S_GRANDMA_THREATEN);
		pGrandmaController->Add(AnimName::S_GRANDMA_PAIN);
		pGrandmaController->Add(AnimName::S_GRANDMA_FALL_F);
		pGrandmaController->Add(AnimName::S_GRANDMA_SHAKE_IT_OFF);
		pGrandmaController->SetIdle(AnimName::S_GRANDMA_IDLE);

		AnimController* pMichelleController = AnimManager::Add(AnimManager::MASTER_DELTA);
		pMichelleController->Add(AnimName::S_MICHELLE_IDLE);
		pMichelleController->Add(AnimName::S_MICHELLE_REACT);
		pMichelleController->Add(AnimName::S_MICHELLE_TALK);
		pMichelleController->SetIdle(AnimName::S_MICHELLE_IDLE);

		AnimController* pMouseController = AnimManager::Add(AnimManager::MASTER_DELTA);
		pMouseController->Add(AnimName::S_MOUSE_IDLE);
		pMouseController->Add(AnimName::S_MOUSE_WALK);
		pMouseController->Add(AnimName::S_MOUSE_RUN_GOOFY);
		pMouseController->Add(AnimName::S_MOUSE_DANCE_SALSA);
		pMouseController->Add(AnimName::S_MOUSE_DANCE_SILLY);
		pMouseController->Add(AnimName::S_MOUSE_DANCE_JAZZ);
		pMouseController->Add(AnimName::S_MOUSE_DANCE_TWERK);
		pMouseController->Add(AnimName::S_MOUSE_JOYFUL_JUMP);
		pMouseController->Add(AnimName::S_MOUSE_SCARED);
		pMouseController->Add(AnimName::S_MOUSE_TAUNT);
		pMouseController->Add(AnimName::S_MOUSE_POINT_F);
		pMouseController->SetIdle(AnimName::S_MOUSE_IDLE);

		AnimController* pNinjaController = AnimManager::Add(AnimManager::MASTER_DELTA);
		pNinjaController->Add(AnimName::S_NINJA_IDLE);
		pNinjaController->Add(AnimName::S_NINJA_CHEER);
		pNinjaController->Add(AnimName::S_NINJA_PUSH_UP);
		pNinjaController->SetIdle(AnimName::S_NINJA_IDLE);

		AnimController* pOrtizController = AnimManager::Add(AnimManager::MASTER_DELTA);
		pOrtizController->Add(AnimName::S_ORTIZ_IDLE);
		pOrtizController->Add(AnimName::S_ORTIZ_CHEER);
		pOrtizController->Add(AnimName::S_ORTIZ_DEFEAT);
		pOrtizController->SetIdle(AnimName::S_ORTIZ_IDLE);

		AnimController* pPumpkinController = AnimManager::Add(AnimManager::MASTER_DELTA);
		pPumpkinController->Add(AnimName::S_PUMPKIN_HULK_IDLE);
		pPumpkinController->Add(AnimName::S_PUMPKIN_HULK_EXCITED);
		pPumpkinController->Add(AnimName::S_PUMPKIN_HULK_AGONIZE);
		pPumpkinController->SetIdle(AnimName::S_PUMPKIN_HULK_IDLE);

		AnimController* pZombieGirlController = AnimManager::Add(AnimManager::MASTER_DELTA);
		pZombieGirlController->Add(AnimName::S_ZOMBIE_GIRL_IDLE);
		pZombieGirlController->Add(AnimName::S_ZOMBIE_GIRL_AGONIZE);
		pZombieGirlController->Add(AnimName::S_ZOMBIE_GIRL_CHEER);
		pZombieGirlController->SetIdle(AnimName::S_ZOMBIE_GIRL_IDLE);


		CMD_SetAnimNoBlend* pSetGMA = new CMD_SetAnimNoBlend(*pGrandmaController, AnimName::S_GRANDMA_IDLE, true);
		CMD_SetAnimNoBlend* pSetMichelle = new CMD_SetAnimNoBlend(*pMichelleController, AnimName::S_MICHELLE_IDLE, true);
		CMD_SetAnimNoBlend* pSetMouse = new CMD_SetAnimNoBlend(*pMouseController, AnimName::S_MOUSE_IDLE, true);
		CMD_SetAnimNoBlend* pSetNinja = new CMD_SetAnimNoBlend(*pNinjaController, AnimName::S_NINJA_IDLE, true);
		CMD_SetAnimNoBlend* pSetOrtiz = new CMD_SetAnimNoBlend(*pOrtizController, AnimName::S_ORTIZ_IDLE, true);
		CMD_SetAnimNoBlend* pSetPumpkin = new CMD_SetAnimNoBlend(*pPumpkinController, AnimName::S_PUMPKIN_HULK_IDLE, true);
		CMD_SetAnimNoBlend* pSetZombieGirl = new CMD_SetAnimNoBlend(*pZombieGirlController, AnimName::S_ZOMBIE_GIRL_IDLE, true);

		CommandQueueManager::SendData(pSetGMA);
		CommandQueueManager::SendData(pSetMichelle);
		CommandQueueManager::SendData(pSetMouse);
		CommandQueueManager::SendData(pSetNinja);
		CommandQueueManager::SendData(pSetOrtiz);
		CommandQueueManager::SendData(pSetPumpkin);
		CommandQueueManager::SendData(pSetZombieGirl);


		////// ----------------------------------------------------------------------------------------------------
		////// -- GameObjects
		////// ----------------------------------------------------------------------------------------------------
		GameObjectAnim* pGma = GameObjectManager::Add(*pGrandmaProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pGrandmaController, TextureName::DEFAULT);
		GameObjectManager::SetScale(pGma, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pGma, Vec3(-0.1f, 0.0f, 0.0f));

		GameObjectAnim* pMichelle = GameObjectManager::Add(*pMichelleProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pMichelleController, TextureName::DEFAULT);
		GameObjectManager::SetScale(pMichelle, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pMichelle, Vec3(-0.066f, 0.0f, 0.0f));

		GameObjectAnim* pMouse = GameObjectManager::Add(*pMouseProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pMouseController, TextureName::DEFAULT);
		GameObjectManager::SetScale(pMouse, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pMouse, Vec3(-0.033f, 0.0f, 0.0f));

		GameObjectAnim* pNinja = GameObjectManager::Add(*pNinjaProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pNinjaController, TextureName::DEFAULT);
		GameObjectManager::SetScale(pNinja, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pNinja, Vec3(0.0f, 0.0f, 0.0f));

		GameObjectAnim* pOrtiz = GameObjectManager::Add(*pOrtizProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pOrtizController, TextureName::DEFAULT);
		GameObjectManager::SetScale(pOrtiz, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pOrtiz, Vec3(0.033f, 0.0f, 0.0f));

		GameObjectAnim* pPumpkin = GameObjectManager::Add(*pPumpkinHulkProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pPumpkinController, TextureName::DEFAULT);
		GameObjectManager::SetScale(pPumpkin, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pPumpkin, Vec3(0.066f, 0.00f, 0.0f));

		GameObjectAnim* pZombieGirl = GameObjectManager::Add(*pZombieGirlProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pZombieGirlController, TextureName::DEFAULT);
		GameObjectManager::SetScale(pZombieGirl, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pZombieGirl, Vec3(0.1f, 0.0f, 0.0f));

		////// ----------------------------------------------------------------------------------------------------
		////// -- Player
		////// ----------------------------------------------------------------------------------------------------
		ControlMap_Grandma_Default* pGmaMap = new ControlMap_Grandma_Default();
		ControlMap_Mouse_Default* mouseMap = new ControlMap_Mouse_Default();

		PlayerManager::Add(PlayerName::PLAYER_1, *pGma, *pGmaMap);
		PlayerManager::Add(PlayerName::PLAYER_2, *pMouse, *mouseMap);

	}

	void Scene_Demo1::Unload()
	{
	}

	void Scene_Demo1::Update()
	{
	}
}


