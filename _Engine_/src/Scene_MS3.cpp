#include "Scene_MS3.h"
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

namespace Uncertain
{
	Scene_MS3::Scene_MS3()
		: DebugTime(), DebugTimer(), pCountFont(nullptr), pCountPreMessage("Time Elapsed: "), CounterMessageBuffer{0}
	{
	}

	void Scene_MS3::Load()
	{
		//----------------------------------------------------------------------------------------------------
		//-- Cameras
		//----------------------------------------------------------------------------------------------------
		Camera* pAuxCam = CameraManager::Add(CameraName::AUX_3D_1);
		pAuxCam->setOrientAndPosition(Vec3(0.0f, 1.0f, 0.0f), Vec3(-1.1f, 0.0f, 0.0f), Vec3(-1.1f, 0.0f, 0.25f));

		//// ----------------------------------------------------------------------------------------------------
		//// -- Textures
		//// ----------------------------------------------------------------------------------------------------
		TextureManager::Add(TextureName::MOUSE_DIFFUSE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::CHICKENBOT_DIFFUSE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::R2D2_BASE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::SPACEFRIG_BASE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::WOODEN_CRATE_BASE, TextureNode::TYPE::SINGLE);

		////// ----------------------------------------------------------------------------------------------------
		////// -- Protos
		////// ----------------------------------------------------------------------------------------------------
		ProtoNode* pMouseProto = ProtoManager::Add(ModelName::MOUSE, TextureName::MOUSE_DIFFUSE, ArmatureName::MOUSE);
		ProtoNode* pChickenProto = ProtoManager::Add(ModelName::CHICKEN_BOT, TextureName::CHICKENBOT_DIFFUSE, ArmatureName::CHICKEN_BOT);
		ProtoNode* pR2Proto = ProtoManager::Add(ModelName::R2D2, TextureName::R2D2_BASE);
		ProtoNode* pSpaceFrigProto = ProtoManager::Add(ModelName::SPACE_FRIG, TextureName::SPACEFRIG_BASE);
		ProtoNode* pCrateProto = ProtoManager::Add(ModelName::WOODEN_CRATE, TextureName::WOODEN_CRATE_BASE);


		////// ----------------------------------------------------------------------------------------------------
		////// -- UI
		////// ----------------------------------------------------------------------------------------------------

		Font* pFont = FontManager::Find(SpriteSheetName::VERDANA_FONT);
		Image* pRedAlien = ImageManager::Find(SpriteSheetName::ALIENS, "octo_red");
		Image* pGreenAlien = ImageManager::Find(SpriteSheetName::ALIENS, "crab_green");

		UIStyle* pStyle = new UIStyle(CameraManager::GetActive2D(), UIStyle::X_AREA::CENTER, UIStyle::Y_AREA::BOTTOM, 0.5f, 0.25f, 0.0f, 1, true);
		UINode* pUINode = UIManager::AddNode(UIName::PAUSE, pStyle);
		GameObjectUIElement* pRedAlienGO = UIManager::AddElement(*pUINode, *pRedAlien);
		GameObjectUIElement* pGreenAlienGO = UIManager::AddElement(*pUINode, *pGreenAlien);
		GameObjectFont* pAnimDebugMessage_Left = UIManager::AddFont(*pUINode, *pFont);
		GameObjectFont* pAnimDebugMessage_Right = UIManager::AddFont(*pUINode, *pFont);

		UIStyle* pTopStyle = new UIStyle(CameraManager::GetActive2D(), UIStyle::X_AREA::CENTER, UIStyle::Y_AREA::TOP, 0.5f, 0.25f, 0.0f, 1, true);
		UINode* pCounterNode = UIManager::AddNode(UIName::DEBUG_1, pTopStyle);
		pCountFont = UIManager::AddFont(*pCounterNode, *pFont, pCountPreMessage);

		pRedAlienGO->SetWidth_AR(150.0f);
		pRedAlienGO->SetPos(-125.0f, 0.0f);

		pGreenAlienGO->SetWidth_AR(150.0f);
		pGreenAlienGO->SetPos(125.0f, 0.0f);

		pAnimDebugMessage_Left->SetPos(-125.0f, 200.0f);
		pAnimDebugMessage_Right->SetPos(125.0f, 200.0f);
		pAnimDebugMessage_Right->SetScale(Vec3(0.75f, 0.75f, 0.75f));
		pAnimDebugMessage_Left->SetScale(Vec3(0.75f, 0.75f, 0.75f));

		//// ----------------------------------------------------------------------------------------------------
		//// -- Animations
		//// ----------------------------------------------------------------------------------------------------
		AnimController* pMouseController = AnimManager::Add(AnimManager::MASTER_DELTA, pAnimDebugMessage_Right);
		pMouseController->Add(AnimName::S_MOUSE_IDLE);
		pMouseController->Add(AnimName::S_MOUSE_WALK);
		pMouseController->Add(AnimName::S_MOUSE_RUN_GOOFY);
		pMouseController->Add(AnimName::S_MOUSE_DANCE_SALSA);
		pMouseController->Add(AnimName::S_MOUSE_DANCE_SILLY);
		pMouseController->Add(AnimName::S_MOUSE_JOYFUL_JUMP);
		pMouseController->SetIdle(AnimName::S_MOUSE_IDLE);

		AnimController* chickenController = AnimManager::Add(AnimManager::MASTER_DELTA);
		chickenController->Add(AnimName::S_CHICKENBOT_IDLE);
		chickenController->Add(AnimName::S_CHICKENBOT_RUN);
		chickenController->Add(AnimName::S_CHICKENBOT_WALK);
		chickenController->Add(AnimName::S_CHICKENBOT_SHOT_F);
		chickenController->Add(AnimName::S_CHICKENBOT_SHOT_D);
		chickenController->Add(AnimName::S_CHICKENBOT_SHOT_U);
		chickenController->Add(AnimName::S_CHICKENBOT_HIT_F);
		chickenController->Add(AnimName::S_CHICKENBOT_HIT_L);
		chickenController->Add(AnimName::S_CHICKENBOT_HIT_R);
		chickenController->Add(AnimName::S_CHICKENBOT_SIDESTEP_L);
		chickenController->Add(AnimName::S_CHICKENBOT_SIDESTEP_R);

		chickenController->SetIdle(AnimName::S_CHICKENBOT_IDLE);

		CMD_SetAnimNoBlend* setChickenAnimController = new CMD_SetAnimNoBlend(*chickenController, AnimName::S_CHICKENBOT_IDLE, true);
		CMD_SetAnimNoBlend* setMouseController = new CMD_SetAnimNoBlend(*pMouseController, AnimName::S_MOUSE_IDLE, true);

		CommandQueueManager::SendData(setMouseController);
		CommandQueueManager::SendData(setChickenAnimController);

		////// ----------------------------------------------------------------------------------------------------
		////// -- GameObjects
		////// ----------------------------------------------------------------------------------------------------
		GameObjectAnim* pMouse = GameObjectManager::Add(*pMouseProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pMouseController, nullptr, TextureName::DEFAULT);
		GameObjectManager::SetScale(pMouse, Vec3(0.09f, 0.09f, 0.09f));
		GameObjectManager::SetPos(pMouse, Vec3(0.045f, -0.032f, 0.0f));

		GameObjectAnim* pChickenLeft = GameObjectManager::Add(*pChickenProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, * chickenController, nullptr, TextureName::DEFAULT);
		GameObjectManager::SetScale(pChickenLeft, Vec3(2.0f, 2.0f, 2.0f));
		GameObjectManager::SetLightColor(pChickenLeft, Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		GameObjectManager::SetPos(pChickenLeft, Vec3(.04f, -0.02f, 0.0f));
		GameObjectManager::SetRot(pChickenLeft, Quat(Quat::Rot3::XYZ, -MATH_PI2, 0.0f, MATH_PI2));

		GameObject* pR2Left = GameObjectManager::Add(*pR2Proto, ShaderName::TEXTURE_POINT_LIGHT, MaterialName::TEXT_POINT_LIGHT, nullptr, TextureName::DEFAULT);
		GameObjectManager::SetRot(pR2Left, Quat(Quat::Rot3::XYZ, MATH_PI2, MATH_PI, MATH_PI));
		GameObjectManager::SetPos(pR2Left, Vec3(-0.105f, 0.05f, 0.0f));
		GameObjectManager::SetLightColor(pR2Left, Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		GameObjectManager::SetScale(pR2Left, Vec3(2.5f, 2.5f, 2.5f));

		GameObject* pR2Right = GameObjectManager::Add(*pR2Proto, ShaderName::COLOR_CONST, MaterialName::WIREFRAME);
		GameObjectManager::SetRot(pR2Right, Quat(Quat::Rot3::XYZ, MATH_PI2, MATH_PI, MATH_PI));
		GameObjectManager::SetPos(pR2Right, Vec3(0.115f, 0.05f, 0.0f));
		GameObjectManager::SetLightColor(pR2Right, Vec4(0.0f, 0.0f, 1.0f, 1.0f));
		GameObjectManager::SetScale(pR2Right, Vec3(2.5f, 2.5f, 2.5f));

		GameObject* pSpaceFrig = GameObjectManager::Add(*pSpaceFrigProto, ShaderName::TEXTURE_POINT_LIGHT, MaterialName::TEXT_POINT_LIGHT, nullptr, TextureName::DEFAULT);
		GameObjectManager::SetPos(pSpaceFrig, Vec3(0.09f, -0.075f, 0.0f));
		GameObjectManager::SetScale(pSpaceFrig, Vec3(0.00125f, 0.00125f, 0.00125f));
		GameObjectManager::SetLightColor(pSpaceFrig, Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		GameObjectManager::SetDeltaRot(pSpaceFrig, Vec3(0.01f, -0.009f, 0.03f));

		GameObject* pWoodenCrate = GameObjectManager::Add(*pCrateProto, ShaderName::TEXTURE_POINT_LIGHT, MaterialName::TEXT_POINT_LIGHT, nullptr, TextureName::DEFAULT);
		GameObjectManager::SetPos(pWoodenCrate, Vec3(-0.115f, -0.075f, 0.0f));
		GameObjectManager::SetScale(pWoodenCrate, Vec3(0.020f, 0.020f, 0.020f));
		GameObjectManager::SetLightColor(pWoodenCrate, Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		GameObjectManager::SetDeltaRot(pWoodenCrate, Vec3(-0.02f, -0.01f, 0.009f));

		////// ----------------------------------------------------------------------------------------------------
		////// -- Player
		////// ----------------------------------------------------------------------------------------------------
		ControlMap_ChickenBot_Default* pCBMap = new ControlMap_ChickenBot_Default();
		ControlMap_Mouse_Default* mouseMap = new ControlMap_Mouse_Default();

		PlayerManager::Add(PlayerName::PLAYER_1, *pChickenLeft, *pCBMap);
		PlayerManager::Add(PlayerName::PLAYER_2, *pMouse, *mouseMap);

	}

	void Scene_MS3::Unload()
	{
	}

	void Scene_MS3::Update()
	{
		DebugTime += DebugTimer.Toc();
		// Update string
		int seconds = _Time::Quotient(DebugTime, _Time(_Time::Duration::ONE_SECOND));
		_Time ms = _Time::Remainder(DebugTime, _Time(_Time::Duration::ONE_SECOND));
		int milliseconds = _Time::Quotient(ms, _Time(_Time::Duration::ONE_MILLISECOND));

		sprintf_s(CounterMessageBuffer, 64, "%s %d.%ds", pCountPreMessage, seconds, milliseconds);
		GameObjectManager::SetMessage(pCountFont, CounterMessageBuffer);

		DebugTimer.Tic();
	}
}

