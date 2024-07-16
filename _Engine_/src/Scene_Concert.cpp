#include "Scene_Concert.h"
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
	Scene_Concert::Scene_Concert()
		: DebugTime(), DebugTimer(), pCountFont(nullptr), pCountPreMessage("Time Elapsed: "), CounterMessageBuffer{ 0 },
		BandUpdateTime(_Time(_Time::Duration::ONE_SECOND) * 30), CurBandTime(), BandTimer(),
		AudienceUpdateTime(_Time(_Time::Duration::ONE_SECOND) * 30), CurAudienceTime(), AudienceTimer()
	{
	}

	void Scene_Concert::Load()
	{
		//----------------------------------------------------------------------------------------------------
		//-- Cameras
		//----------------------------------------------------------------------------------------------------
		Camera3D* pActiveCam = CameraManager::GetActive3D();
		pActiveCam->setOrientAndPosition(Vec3(0.017265f, 0.982421f, -0.185877f), Vec3(-0.062034f, 0.060128f, -0.172152f), Vec3(-0.140550f, 0.105584f, 0.060804f));
		//pActiveCam->setFieldOfView(23.0f);

		Camera3D* pAuxCam = (Camera3D*)CameraManager::Add(CameraName::AUX_3D_1);
		pAuxCam->setOrientAndPosition(Vec3(-0.143549f, 0.955487f, -0.257756f), Vec3(-0.515802f, -0.275738f, -1.082174f), Vec3(0.277253f, 0.124515f, -0.040127f));

		Camera3D* pEditNegY = (Camera3D*)CameraManager::Add(CameraName::EDIT_NEG_Y);
		pEditNegY->setOrientAndPosition(Vec3(-0.001599f, 0.991556f, -0.129666f), Vec3(-0.032469f, 0.067060f, 0.050484f), Vec3(-0.042459f, 0.099435f, 0.298177f));
		pEditNegY->setFieldOfView(30.0f);

		//// ----------------------------------------------------------------------------------------------------
		//// -- Textures
		//// ----------------------------------------------------------------------------------------------------
		TextureManager::Add(TextureName::CLAIRE, TextureNode::TYPE::MULTI);
		TextureManager::Add(TextureName::GRANDMA, TextureNode::TYPE::MULTI);
		TextureManager::Add(TextureName::KNIGHT_DIFFUSE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::MICHELLE_DIFFUSE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::MOUSE_DIFFUSE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::NINJA_DIFFUSE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::ORTIZ_DIFFUSE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::PALADIN_DIFFUSE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::PUMPKIN_HULK_DIFFUSE, TextureNode::TYPE::SINGLE);
		TextureManager::Add(TextureName::VANGUARD, TextureNode::TYPE::MULTI);
		TextureManager::Add(TextureName::ZOMBIE_GIRL, TextureNode::TYPE::MULTI);

		TextureManager::Add(TextureName::WOODEN_CRATE_BASE, TextureNode::TYPE::SINGLE);


		////// ----------------------------------------------------------------------------------------------------
		////// -- Protos
		////// ----------------------------------------------------------------------------------------------------
		ProtoNode* pClaireProto = ProtoManager::Add(ModelName::CLAIRE, TextureName::CLAIRE, ArmatureName::CLAIRE);
		ProtoNode* pGrandmaProto = ProtoManager::Add(ModelName::GRANDMA, TextureName::GRANDMA, ArmatureName::GRANDMA);
		ProtoNode* pKnightProto = ProtoManager::Add(ModelName::KNIGHT, TextureName::KNIGHT_DIFFUSE, ArmatureName::KNIGHT);
		ProtoNode* pMouseProto = ProtoManager::Add(ModelName::MOUSE, TextureName::MOUSE_DIFFUSE, ArmatureName::MOUSE);
		ProtoNode* pPumpkinHulkProto = ProtoManager::Add(ModelName::PUMPKIN_HULK, TextureName::PUMPKIN_HULK_DIFFUSE, ArmatureName::PUMPKIN_HULK);
		ProtoNode* pVanguardProto = ProtoManager::Add(ModelName::VANGUARD, TextureName::VANGUARD, ArmatureName::VANGUARD);
		
		ProtoNode* pCrateProto = ProtoManager::Add(ModelName::WOODEN_CRATE, TextureName::WOODEN_CRATE_BASE);

		ProtoNode* pPaladinProto = ProtoManager::Add(ModelName::PALADIN, TextureName::PALADIN_DIFFUSE, ArmatureName::PALADIN);
		ProtoNode* pMichelleProto = ProtoManager::Add(ModelName::MICHELLE, TextureName::MICHELLE_DIFFUSE, ArmatureName::MICHELLE);
		ProtoNode* pNinjaProto = ProtoManager::Add(ModelName::NINJA, TextureName::NINJA_DIFFUSE, ArmatureName::NINJA);
		ProtoNode* pOrtizProto = ProtoManager::Add(ModelName::ORTIZ, TextureName::ORTIZ_DIFFUSE, ArmatureName::ORTIZ);
		ProtoNode* pZombieGirlProto = ProtoManager::Add(ModelName::ZOMBIE_GIRL, TextureName::ZOMBIE_GIRL, ArmatureName::ZOMBIE_GIRL);

		////// ----------------------------------------------------------------------------------------------------
		////// -- UI
		////// ----------------------------------------------------------------------------------------------------
		Font* pFont = FontManager::Find(SpriteSheetName::VERDANA_FONT);

		UIStyle* pStyle = new UIStyle(CameraManager::GetActive2D(), UIStyle::X_AREA::LEFT, UIStyle::Y_AREA::TOP, 0.025f, 0.25f, 0.0f, 1, true);
		UINode* pUINode = UIManager::AddNode(UIName::DEBUG_1, pStyle);
		this->pCountFont = UIManager::AddFont(*pUINode, *pFont, pCountPreMessage);
		GameObjectFont* pAnimDebugMessage_Claire = UIManager::AddFont(*pUINode, *pFont);
		GameObjectFont* pAnimDebugMessage_Grandma = UIManager::AddFont(*pUINode, *pFont);
		GameObjectFont* pAnimDebugMessage_Knight = UIManager::AddFont(*pUINode, *pFont);
		GameObjectFont* pAnimDebugMessage_Mouse = UIManager::AddFont(*pUINode, *pFont);
		GameObjectFont* pAnimDebugMessage_Pumpkin = UIManager::AddFont(*pUINode, *pFont);
		GameObjectFont* pAnimDebugMessage_Vanguard = UIManager::AddFont(*pUINode, *pFont);

		pCountFont->SetPos(0.0f, 90.0f);
		pAnimDebugMessage_Claire->SetPos(0.0f, 50.0f);
		pAnimDebugMessage_Grandma->SetPos(0.0f, 25.0f);
		pAnimDebugMessage_Knight->SetPos(0.0f, 0.0f);
		pAnimDebugMessage_Mouse->SetPos(0.0f, -25.0f);
		pAnimDebugMessage_Pumpkin->SetPos(0.0f, -50.0f);
		pAnimDebugMessage_Vanguard->SetPos(0.0f, -75.0f);

		pCountFont->SetScale(Vec3(0.75f, 0.75f, 0.75f));
		pAnimDebugMessage_Claire->SetScale(Vec3(0.65f, 0.65f, 0.65f));
		pAnimDebugMessage_Grandma->SetScale(Vec3(0.65f, 0.65f, 0.65f));
		pAnimDebugMessage_Knight->SetScale(Vec3(0.65f, 0.65f, 0.65f));
		pAnimDebugMessage_Mouse->SetScale(Vec3(0.65f, 0.65f, 0.65f));
		pAnimDebugMessage_Pumpkin->SetScale(Vec3(0.65f, 0.65f, 0.65f));
		pAnimDebugMessage_Vanguard->SetScale(Vec3(0.65f, 0.65f, 0.65f));

		//// ----------------------------------------------------------------------------------------------------
		//// -- Animations
		//// ----------------------------------------------------------------------------------------------------
		
		//	-----------------------------------------------------------------------------------------------------
		//  ---------------------------------------------------------------------------- Band -------------------
		//	-----------------------------------------------------------------------------------------------------
		this->pClaireController = AnimManager::Add(AnimManager::MASTER_DELTA, pAnimDebugMessage_Claire);
		pClaireController->Add(AnimName::S_CLAIRE_IDLE_HAPPY_SWAY);
		pClaireController->Add(AnimName::S_CLAIRE_BASS);
		pClaireController->Add(AnimName::S_CLAIRE_DANCE_HIGH_KICK);
		pClaireController->SetIdle(AnimName::S_CLAIRE_FIST_PUMP);
		CMD_SetAnimNoBlend* pSetClaire = new CMD_SetAnimNoBlend(*pClaireController, AnimName::S_CLAIRE_IDLE_HAPPY_SWAY, true);

		this->pGrandmaController = AnimManager::Add(AnimManager::MASTER_DELTA, pAnimDebugMessage_Grandma);
		pGrandmaController->Add(AnimName::S_GRANDMA_IDLE);
		pGrandmaController->Add(AnimName::S_GRANDMA_DANCE_BBOY_HH);
		pGrandmaController->Add(AnimName::S_GRANDMA_VICTORY);
		pGrandmaController->SetIdle(AnimName::S_GRANDMA_IDLE);
		CMD_SetAnimNoBlend* pSetGMA = new CMD_SetAnimNoBlend(*pGrandmaController, AnimName::S_GRANDMA_DANCE_BBOY_HH, true);

		this->pKnightController = AnimManager::Add(AnimManager::MASTER_DELTA, pAnimDebugMessage_Knight);
		pKnightController->Add(AnimName::S_KNIGHT_CLAP_SIT);
		pKnightController->Add(AnimName::S_KNIGHT_PIANO);
		pKnightController->Add(AnimName::S_KNIGHT_IDLE_SIT);
		pKnightController->SetIdle(AnimName::S_KNIGHT_IDLE_SIT);
		CMD_SetAnimNoBlend* pSetKnight = new CMD_SetAnimNoBlend(*pKnightController, AnimName::S_KNIGHT_IDLE_SIT, true);

		this->pMouseController = AnimManager::Add(AnimManager::MASTER_DELTA, pAnimDebugMessage_Mouse);
		pMouseController->Add(AnimName::S_MOUSE_IDLE);
		pMouseController->Add(AnimName::S_MOUSE_GUITAR);
		pMouseController->Add(AnimName::S_MOUSE_DANCE_SILLY);
		pMouseController->Add(AnimName::S_MOUSE_DANCE_TWERK);
		pMouseController->Add(AnimName::S_MOUSE_JOYFUL_JUMP);
		pMouseController->SetIdle(AnimName::S_MOUSE_IDLE);
		CMD_SetAnimNoBlend* pSetMouse = new CMD_SetAnimNoBlend(*pMouseController, AnimName::S_MOUSE_IDLE, true);

		this->pPumpkinController = AnimManager::Add(AnimManager::MASTER_DELTA, pAnimDebugMessage_Pumpkin);
		pPumpkinController->Add(AnimName::S_PUMPKIN_HULK_IDLE_SIT);
		pPumpkinController->Add(AnimName::S_PUMPKIN_HULK_DRUMS);
		pPumpkinController->Add(AnimName::S_PUMPKIN_HULK_FIST_PUMP_SITTING);
		pPumpkinController->SetIdle(AnimName::S_PUMPKIN_HULK_IDLE_SIT);
		CMD_SetAnimNoBlend* pSetPumpkin = new CMD_SetAnimNoBlend(*pPumpkinController, AnimName::S_PUMPKIN_HULK_IDLE_SIT, true);
		
		this->pVanguardController = AnimManager::Add(AnimManager::MASTER_DELTA, pAnimDebugMessage_Vanguard);
		pVanguardController->Add(AnimName::S_VANGUARD_IDLE_HAPPY);
		pVanguardController->Add(AnimName::S_VANGUARD_SING);
		pVanguardController->Add(AnimName::S_VANGUARD_DANCE_SALSA_1);
		pVanguardController->Add(AnimName::S_VANGUARD_DANCE_SALSA_2);
		pVanguardController->Add(AnimName::S_VANGUARD_JAM);
		pVanguardController->SetIdle(AnimName::S_VANGUARD_IDLE_HAPPY);
		CMD_SetAnimNoBlend* pSetVanguard = new CMD_SetAnimNoBlend(*pVanguardController, AnimName::S_VANGUARD_IDLE_HAPPY, true);
		
		CommandQueueManager::SendData(pSetClaire);
		CommandQueueManager::SendData(pSetGMA);
		CommandQueueManager::SendData(pSetKnight);
		CommandQueueManager::SendData(pSetMouse);
		CommandQueueManager::SendData(pSetPumpkin);
		CommandQueueManager::SendData(pSetVanguard);


		//	-------------------------------------------------------------------------------------------------------
		//  ------------------------------------------------------------------------ Audience ---------------------
		//	-------------------------------------------------------------------------------------------------------

		this->pPaladinController_Cheer_1 = AnimManager::Add(AnimManager::MASTER_DELTA);
		pPaladinController_Cheer_1->Add(AnimName::S_PALADIN_IDLE_HAPPY);
		pPaladinController_Cheer_1->Add(AnimName::S_PALADIN_CHEER);
		pPaladinController_Cheer_1->Add(AnimName::S_PALADIN_DANCE_SILLY);
		pPaladinController_Cheer_1->SetIdle(AnimName::S_PALADIN_IDLE_HAPPY);
		CMD_SetAnimNoBlend* pSetPaladin_Cheer_1 = new CMD_SetAnimNoBlend(*pPaladinController_Cheer_1, AnimName::S_PALADIN_CHEER, true);
		CommandQueueManager::SendData(pSetPaladin_Cheer_1);

		this->pPaladinController_Cheer_2 = AnimManager::Add(AnimManager::MASTER_DELTA);
		pPaladinController_Cheer_2->Add(AnimName::S_PALADIN_IDLE_HAPPY);
		pPaladinController_Cheer_2->Add(AnimName::S_PALADIN_CHEER);
		pPaladinController_Cheer_2->Add(AnimName::S_PALADIN_DANCE_SILLY);
		pPaladinController_Cheer_2->SetIdle(AnimName::S_PALADIN_IDLE_HAPPY);
		CMD_SetAnimNoBlend* pSetPaladin_Cheer_2 = new CMD_SetAnimNoBlend(*pPaladinController_Cheer_2, AnimName::S_PALADIN_IDLE_HAPPY, true);
		CommandQueueManager::SendData(pSetPaladin_Cheer_2);

		this->pPaladinController_Dance = AnimManager::Add(AnimManager::MASTER_DELTA);
		pPaladinController_Dance->Add(AnimName::S_PALADIN_IDLE_HAPPY);
		pPaladinController_Dance->Add(AnimName::S_PALADIN_DANCE_SILLY);
		pPaladinController_Dance->Add(AnimName::S_PALADIN_DANCE_HOKEY_POKEY);
		pPaladinController_Dance->SetIdle(AnimName::S_PALADIN_IDLE_HAPPY);
		CMD_SetAnimNoBlend* pSetPaladin_Dance = new CMD_SetAnimNoBlend(*pPaladinController_Dance, AnimName::S_PALADIN_DANCE_HOKEY_POKEY, true);
		CommandQueueManager::SendData(pSetPaladin_Dance);

		this->pPaladinController_Static = AnimManager::Add(AnimManager::MASTER_DELTA);
		pPaladinController_Static->Add(AnimName::S_PALADIN_IDLE_HAPPY);
		pPaladinController_Static->Add(AnimName::S_PALADIN_DANCE_SILLY);
		pPaladinController_Static->SetIdle(AnimName::S_PALADIN_IDLE_HAPPY);
		CMD_SetAnimNoBlend* pSetPaladin_Static = new CMD_SetAnimNoBlend(*pPaladinController_Static, AnimName::S_PALADIN_DANCE_SILLY, true);
		CommandQueueManager::SendData(pSetPaladin_Static);

		this->pMichelleController_Cheer_1 = AnimManager::Add(AnimManager::MASTER_DELTA);
		pMichelleController_Cheer_1->Add(AnimName::S_MICHELLE_IDLE);
		pMichelleController_Cheer_1->Add(AnimName::S_MICHELLE_REACT);
		pMichelleController_Cheer_1->Add(AnimName::S_MICHELLE_TALK);
		pMichelleController_Cheer_1->Add(AnimName::S_MICHELLE_CHEER);
		pMichelleController_Cheer_1->SetIdle(AnimName::S_MICHELLE_IDLE);
		CMD_SetAnimNoBlend* pSetMichelle_Cheer_1 = new CMD_SetAnimNoBlend(*pMichelleController_Cheer_1, AnimName::S_MICHELLE_CHEER, true);
		CommandQueueManager::SendData(pSetMichelle_Cheer_1);

		this->pMichelleController_Cheer_2 = AnimManager::Add(AnimManager::MASTER_DELTA);
		pMichelleController_Cheer_2->Add(AnimName::S_MICHELLE_IDLE);
		pMichelleController_Cheer_2->Add(AnimName::S_MICHELLE_REACT);
		pMichelleController_Cheer_2->Add(AnimName::S_MICHELLE_TALK);
		pMichelleController_Cheer_2->Add(AnimName::S_MICHELLE_CHEER);
		pMichelleController_Cheer_2->SetIdle(AnimName::S_MICHELLE_IDLE);
		CMD_SetAnimNoBlend* pSetMichelle_Cheer_2 = new CMD_SetAnimNoBlend(*pMichelleController_Cheer_2, AnimName::S_MICHELLE_TALK, true);
		CommandQueueManager::SendData(pSetMichelle_Cheer_2);

		this->pMichelleController_Dance = AnimManager::Add(AnimManager::MASTER_DELTA);
		pMichelleController_Dance->Add(AnimName::S_MICHELLE_IDLE);
		pMichelleController_Dance->Add(AnimName::S_MICHELLE_DANCE_MARA_STEP);
		pMichelleController_Dance->Add(AnimName::S_MICHELLE_DANCE_NSS_COMBO);
		pMichelleController_Dance->SetIdle(AnimName::S_MICHELLE_IDLE);
		CMD_SetAnimNoBlend* pSetMichelle_Dance = new CMD_SetAnimNoBlend(*pMichelleController_Dance, AnimName::S_MICHELLE_DANCE_MARA_STEP, true);
		CommandQueueManager::SendData(pSetMichelle_Dance);

		this->pNinjaController_Cheer_1 = AnimManager::Add(AnimManager::MASTER_DELTA);
		pNinjaController_Cheer_1->Add(AnimName::S_NINJA_IDLE);
		pNinjaController_Cheer_1->Add(AnimName::S_NINJA_CHEER);
		pNinjaController_Cheer_1->Add(AnimName::S_NINJA_JAM);
		pNinjaController_Cheer_1->SetIdle(AnimName::S_NINJA_IDLE);
		CMD_SetAnimNoBlend* pSetNinja_Cheer_1 = new CMD_SetAnimNoBlend(*pNinjaController_Cheer_1, AnimName::S_NINJA_CHEER, true);
		CommandQueueManager::SendData(pSetNinja_Cheer_1);

		this->pNinjaController_Cheer_2 = AnimManager::Add(AnimManager::MASTER_DELTA);
		pNinjaController_Cheer_2->Add(AnimName::S_NINJA_IDLE);
		pNinjaController_Cheer_2->Add(AnimName::S_NINJA_CHEER);
		pNinjaController_Cheer_2->Add(AnimName::S_NINJA_JAM);
		pNinjaController_Cheer_2->SetIdle(AnimName::S_NINJA_IDLE);
		CMD_SetAnimNoBlend* pSetNinja_Cheer_2 = new CMD_SetAnimNoBlend(*pNinjaController_Cheer_2, AnimName::S_NINJA_JAM, true);
		CommandQueueManager::SendData(pSetNinja_Cheer_2);

		this->pNinjaController_Dance = AnimManager::Add(AnimManager::MASTER_DELTA);
		pNinjaController_Dance->Add(AnimName::S_NINJA_IDLE);
		pNinjaController_Dance->Add(AnimName::S_NINJA_DANCE_FLAIR);
		pNinjaController_Dance->Add(AnimName::S_NINJA_DANCE_HOUSE);
		pNinjaController_Dance->SetIdle(AnimName::S_NINJA_IDLE);
		CMD_SetAnimNoBlend* pSetNinja_Dance = new CMD_SetAnimNoBlend(*pNinjaController_Dance, AnimName::S_NINJA_DANCE_HOUSE, true);
		CommandQueueManager::SendData(pSetNinja_Dance);

		this->pNinjaController_Static = AnimManager::Add(AnimManager::MASTER_DELTA);
		pNinjaController_Static->Add(AnimName::S_NINJA_PUSH_UP);
		pNinjaController_Static->SetIdle(AnimName::S_NINJA_PUSH_UP);
		CMD_SetAnimNoBlend* pSetNinja_Static = new CMD_SetAnimNoBlend(*pNinjaController_Static, AnimName::S_NINJA_PUSH_UP, true);
		CommandQueueManager::SendData(pSetNinja_Static);

		this->pOrtizController_Cheer_1 = AnimManager::Add(AnimManager::MASTER_DELTA);
		pOrtizController_Cheer_1->Add(AnimName::S_ORTIZ_IDLE);
		pOrtizController_Cheer_1->Add(AnimName::S_ORTIZ_CHEER);
		pOrtizController_Cheer_1->Add(AnimName::S_ORTIZ_JAM);
		pOrtizController_Cheer_1->SetIdle(AnimName::S_ORTIZ_IDLE);
		CMD_SetAnimNoBlend* pSetOrtiz_Cheer_1 = new CMD_SetAnimNoBlend(*pOrtizController_Cheer_1, AnimName::S_ORTIZ_JAM, true);
		CommandQueueManager::SendData(pSetOrtiz_Cheer_1);

		this->pOrtizController_Cheer_2 = AnimManager::Add(AnimManager::MASTER_DELTA);
		pOrtizController_Cheer_2->Add(AnimName::S_ORTIZ_IDLE);
		pOrtizController_Cheer_2->Add(AnimName::S_ORTIZ_CHEER);
		pOrtizController_Cheer_2->Add(AnimName::S_ORTIZ_JAM);
		pOrtizController_Cheer_2->SetIdle(AnimName::S_ORTIZ_IDLE);
		CMD_SetAnimNoBlend* pSetOrtiz_Cheer_2 = new CMD_SetAnimNoBlend(*pOrtizController_Cheer_2, AnimName::S_ORTIZ_JAM, true);
		CommandQueueManager::SendData(pSetOrtiz_Cheer_2);

		this->pOrtizController_Dance = AnimManager::Add(AnimManager::MASTER_DELTA);
		pOrtizController_Dance->Add(AnimName::S_ORTIZ_IDLE);
		pOrtizController_Dance->Add(AnimName::S_ORTIZ_DANCE);
		pOrtizController_Dance->Add(AnimName::S_ORTIZ_JAM);
		pOrtizController_Dance->Add(AnimName::S_ORTIZ_DANCE_SWING);
		pOrtizController_Dance->SetIdle(AnimName::S_ORTIZ_IDLE);
		CMD_SetAnimNoBlend* pSetOrtiz_Dance = new CMD_SetAnimNoBlend(*pOrtizController_Dance, AnimName::S_ORTIZ_DANCE, true);
		CommandQueueManager::SendData(pSetOrtiz_Dance);

		this->pZombieGirlController_Cheer_1 = AnimManager::Add(AnimManager::MASTER_DELTA);
		pZombieGirlController_Cheer_1->Add(AnimName::S_ZOMBIE_GIRL_CHEER);
		pZombieGirlController_Cheer_1->Add(AnimName::S_ZOMBIE_GIRL_AGONIZE);
		pZombieGirlController_Cheer_1->Add(AnimName::S_ZOMBIE_GIRL_IDLE_THRILLER);
		pZombieGirlController_Cheer_1->SetIdle(AnimName::S_ZOMBIE_GIRL_DANCE_YMCA);
		CMD_SetAnimNoBlend* pSetZombieGirl_Cheer_1 = new CMD_SetAnimNoBlend(*pZombieGirlController_Cheer_1, AnimName::S_ZOMBIE_GIRL_CHEER, true);
		CommandQueueManager::SendData(pSetZombieGirl_Cheer_1);

		this->pZombieGirlController_Cheer_2 = AnimManager::Add(AnimManager::MASTER_DELTA);
		pZombieGirlController_Cheer_2->Add(AnimName::S_ZOMBIE_GIRL_CHEER);
		pZombieGirlController_Cheer_2->Add(AnimName::S_ZOMBIE_GIRL_AGONIZE);
		pZombieGirlController_Cheer_2->Add(AnimName::S_ZOMBIE_GIRL_IDLE_THRILLER);
		pZombieGirlController_Cheer_2->SetIdle(AnimName::S_ZOMBIE_GIRL_DANCE_YMCA);
		CMD_SetAnimNoBlend* pSetZombieGirl_Cheer_2 = new CMD_SetAnimNoBlend(*pZombieGirlController_Cheer_2, AnimName::S_ZOMBIE_GIRL_AGONIZE, true);
		CommandQueueManager::SendData(pSetZombieGirl_Cheer_2);

		this->pZombieGirlController_Dance = AnimManager::Add(AnimManager::MASTER_DELTA);
		pZombieGirlController_Dance->Add(AnimName::S_ZOMBIE_GIRL_DANCE_MARA_STEP);
		pZombieGirlController_Dance->Add(AnimName::S_ZOMBIE_GIRL_DANCE_YMCA);
		pZombieGirlController_Dance->Add(AnimName::S_ZOMBIE_GIRL_IDLE_THRILLER);
		pZombieGirlController_Dance->SetIdle(AnimName::S_ZOMBIE_GIRL_IDLE_THRILLER);
		CMD_SetAnimNoBlend* pSetZombieGirl_Dance = new CMD_SetAnimNoBlend(*pZombieGirlController_Dance, AnimName::S_ZOMBIE_GIRL_DANCE_YMCA, true);
		CommandQueueManager::SendData(pSetZombieGirl_Dance);

		GenerateBandTimedEvents();
		GenerateAudienceTimedEvents();



		////// ----------------------------------------------------------------------------------------------------
		////// -- GameObjects
		////// ----------------------------------------------------------------------------------------------------
		//	-------------------------------------------------------------------------------------------------------
		//  ---------------------------------------------------------------------------- Band ---------------------
		//	-------------------------------------------------------------------------------------------------------

		GameObjectAnim* pClaire = GameObjectManager::Add(*pClaireProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pClaireController, "Claire on bass", TextureName::DEFAULT);
		GameObjectManager::SetScale(pClaire, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pClaire, Vec3(0.197000f, 0.001000f, -0.452003f));
		GameObjectManager::SetRot(pClaire, Quat(Quat::Rot3::XYZ, 0.0f, MATH_PI8 * 0.75f, 0.0f));

		GameObjectAnim* pGma = GameObjectManager::Add(*pGrandmaProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pGrandmaController, "Grandma rapper", TextureName::DEFAULT);
		GameObjectManager::SetScale(pGma, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pGma, Vec3(0.133000f, 0.000000f, -0.440001f));

		GameObjectAnim* pKnight = GameObjectManager::Add(*pKnightProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pKnightController, "Knight pianist", TextureName::DEFAULT);
		GameObjectManager::SetScale(pKnight, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pKnight, Vec3(-0.106000f, -0.002000f, -0.518001f));

		GameObjectAnim* pMouse = GameObjectManager::Add(*pMouseProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pMouseController, "Mouse on guitar", TextureName::DEFAULT);
		GameObjectManager::SetScale(pMouse, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pMouse, Vec3(-0.163000f, 0.000000f, -0.455001f));
		GameObjectManager::SetRot(pMouse, Quat(Quat::Rot3::XYZ, 0.0f, -MATH_PI8 * 0.75f, 0.0f));

		GameObjectAnim* pPumpkin = GameObjectManager::Add(*pPumpkinHulkProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pPumpkinController, "Pumpkin Head on drums", TextureName::DEFAULT);
		GameObjectManager::SetScale(pPumpkin, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pPumpkin, Vec3(0.000000f, 0.054000f, -0.487002f));

		GameObjectAnim* pVanguard = GameObjectManager::Add(*pVanguardProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pVanguardController, "Vanguard singer", TextureName::DEFAULT);
		GameObjectManager::SetScale(pVanguard, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pVanguard, Vec3(-0.030000f, -0.005000f, -0.324002f));
		GameObjectManager::SetLightColor(pVanguard, Vec4(0.84f, 0.83f, 0.18f));
		GameObjectManager::SetRot(pVanguard, Quat(Quat::Rot3::XYZ, 0.0f, MATH_PI8, 0.0f));

		//	-------------------------------------------------------------------------------------------------------
		//  ---------------------------------------------------------------------------- Audience -----------------
		//	-------------------------------------------------------------------------------------------------------

		// -----------
		// Group 1
		// -----------
		GameObjectAnim* pPaladin_1 = GameObjectManager::Add(*pPaladinProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pPaladinController_Cheer_1, "Paladin", TextureName::DEFAULT);
		GameObjectManager::SetScale(pPaladin_1, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pPaladin_1, Vec3(0.213000f, -0.062000f, -0.357999f));
		GameObjectManager::SetRot(pPaladin_1, Quat(Quat::Rot1::Y, MATH_PI2 * 2));

		GameObjectAnim* pMichelle_1 = GameObjectManager::Add(*pMichelleProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pMichelleController_Cheer_1, "Michelle", TextureName::DEFAULT);
		GameObjectManager::SetScale(pMichelle_1, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pMichelle_1, Vec3(-0.088000f, -0.062000f, -0.294000f));
		GameObjectManager::SetRot(pMichelle_1, Quat(Quat::Rot1::Y, MATH_PI2));

		GameObjectAnim* pNinja_1 = GameObjectManager::Add(*pNinjaProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pNinjaController_Cheer_1, "Ninja", TextureName::DEFAULT);
		GameObjectManager::SetScale(pNinja_1, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pNinja_1, Vec3(0.160000f, -0.062000f, -0.339999f));
		GameObjectManager::SetRot(pNinja_1, Quat(Quat::Rot1::Y, MATH_PI2 * 2.5f));

		GameObjectAnim* pOrtiz_1 = GameObjectManager::Add(*pOrtizProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pOrtizController_Cheer_1, "Ortiz", TextureName::DEFAULT);
		GameObjectManager::SetScale(pOrtiz_1, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pOrtiz_1, Vec3(-0.143000f, -0.062000f, -0.362999f));
		GameObjectManager::SetRot(pOrtiz_1, Quat(Quat::Rot1::Y, MATH_PI2 * 2));

		GameObjectAnim* pZombie_1 = GameObjectManager::Add(*pZombieGirlProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pZombieGirlController_Cheer_1, "Zombie", TextureName::DEFAULT);
		GameObjectManager::SetScale(pZombie_1, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pZombie_1, Vec3(-0.209000f, -0.062000f, -0.368999f));
		GameObjectManager::SetRot(pZombie_1, Quat(Quat::Rot1::Y, MATH_PI2 * 2));

		// -----------
		// Group 2
		// -----------
		GameObjectAnim* pPaladin_2 = GameObjectManager::Add(*pPaladinProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pPaladinController_Cheer_2, "Paladin", TextureName::DEFAULT);
		GameObjectManager::SetScale(pPaladin_2, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pPaladin_2, Vec3(-0.090000f, -0.062000f, -0.357999f));
		GameObjectManager::SetRot(pPaladin_2, Quat(Quat::Rot1::Y, MATH_PI2 * 2));

		GameObjectAnim* pMichelle_2 = GameObjectManager::Add(*pMichelleProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pMichelleController_Cheer_2, "Michelle", TextureName::DEFAULT);
		GameObjectManager::SetScale(pMichelle_2, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pMichelle_2, Vec3(0.027000f, -0.062000f, -0.229000f));
		GameObjectManager::SetRot(pMichelle_2, Quat(Quat::Rot1::Y, MATH_PI2 * 2));

		GameObjectAnim* pNinja_2 = GameObjectManager::Add(*pNinjaProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pNinjaController_Cheer_2, "Ninja", TextureName::DEFAULT);
		GameObjectManager::SetScale(pNinja_2, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pNinja_2, Vec3(-0.175000f, -0.062000f, -0.326999f));
		GameObjectManager::SetRot(pNinja_2, Quat(Quat::Rot1::Y, MATH_PI2 * 2));

		GameObjectAnim* pOrtiz_2 = GameObjectManager::Add(*pOrtizProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pOrtizController_Cheer_2, "Ortiz", TextureName::DEFAULT);
		GameObjectManager::SetScale(pOrtiz_2, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pOrtiz_2, Vec3(0.118000f, -0.062000f, -0.278000f));
		GameObjectManager::SetRot(pOrtiz_2, Quat(Quat::Rot1::Y, -MATH_PI2));

		GameObjectAnim* pZombie_2 = GameObjectManager::Add(*pZombieGirlProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pZombieGirlController_Cheer_2, "Zombie", TextureName::DEFAULT);
		GameObjectManager::SetScale(pZombie_2, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pZombie_2, Vec3(0.123000f, -0.062000f, -0.357999f));
		GameObjectManager::SetRot(pZombie_2, Quat(Quat::Rot1::Y, MATH_PI2 * 2));

		// -----------
		// Group 3
		// -----------
		GameObjectAnim* pPaladin_3 = GameObjectManager::Add(*pPaladinProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pPaladinController_Dance, "Paladin", TextureName::DEFAULT);
		GameObjectManager::SetScale(pPaladin_3, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pPaladin_3, Vec3(-0.087000f, -0.062000f, -0.204000f));
		GameObjectManager::SetRot(pPaladin_3, Quat(Quat::Rot1::Y, MATH_PI2 * 1.85f));

		GameObjectAnim* pMichelle_3 = GameObjectManager::Add(*pMichelleProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pMichelleController_Dance, "Michelle", TextureName::DEFAULT);
		GameObjectManager::SetScale(pMichelle_3, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pMichelle_3, Vec3(0.194000f, -0.062000f, -0.294000f));
		GameObjectManager::SetRot(pMichelle_3, Quat(Quat::Rot1::Y, MATH_PI2 * 2));

		GameObjectAnim* pNinja_3 = GameObjectManager::Add(*pNinjaProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pNinjaController_Dance, "Ninja", TextureName::DEFAULT);
		GameObjectManager::SetScale(pNinja_3, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pNinja_3, Vec3(0.012000f, -0.065000f, -0.172000f));
		GameObjectManager::SetRot(pNinja_3, Quat(Quat::Rot1::Y, -MATH_PI2 * 2));

		GameObjectAnim* pOrtiz_3 = GameObjectManager::Add(*pOrtizProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pOrtizController_Dance, "Ortiz", TextureName::DEFAULT);
		GameObjectManager::SetScale(pOrtiz_3, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pOrtiz_3, Vec3(-0.157000f, -0.062000f, -0.270000f));
		GameObjectManager::SetRot(pOrtiz_3, Quat(Quat::Rot1::Y, MATH_PI2 * 1.56f));

		GameObjectAnim* pZombie_3 = GameObjectManager::Add(*pZombieGirlProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pZombieGirlController_Dance, "Zombie", TextureName::DEFAULT);
		GameObjectManager::SetScale(pZombie_3, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pZombie_3, Vec3(-0.041000f, -0.062000f, -0.223000f));
		GameObjectManager::SetRot(pZombie_3, Quat(Quat::Rot1::Y, MATH_PI2 * 1.85f));

		// -----------
		// Group 4
		// -----------
		GameObjectAnim* pPaladin_4 = GameObjectManager::Add(*pPaladinProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pPaladinController_Static, "Paladin", TextureName::DEFAULT);
		GameObjectManager::SetScale(pPaladin_4, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pPaladin_4, Vec3(0.079000f, -0.057000f, -0.206000f));
		GameObjectManager::SetRot(pPaladin_4, Quat(Quat::Rot1::Y, MATH_PI2 * 1.25f));

		GameObjectAnim* pPaladin_5 = GameObjectManager::Add(*pPaladinProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pPaladinController_Static, "Paladin", TextureName::DEFAULT);
		GameObjectManager::SetScale(pPaladin_5, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pPaladin_5, Vec3(0.119000f, -0.062000f, -0.201000f));
		GameObjectManager::SetRot(pPaladin_5, Quat(Quat::Rot1::Y, -MATH_PI2 * 1.25f));

		GameObjectAnim* pNinja_4 = GameObjectManager::Add(*pNinjaProto, ShaderName::SKIN_TEXT_POINT_LIGHT, MaterialName::SKIN_TEXT_POINT_LIGHT, *pNinjaController_Static, "Ninja", TextureName::DEFAULT);
		GameObjectManager::SetScale(pNinja_4, Vec3(0.045f, 0.045f, 0.045f));
		GameObjectManager::SetPos(pNinja_4, Vec3(0.177000f, -0.065000f, -0.245000f));
		GameObjectManager::SetRot(pNinja_4, Quat(Quat::Rot1::Y, -MATH_PI2 * 1.5f));


		//	-------------------------------------------------------------------------------------------------------
		//  ---------------------------------------------------------------------------- Environment --------------
		//	-------------------------------------------------------------------------------------------------------
		GameObject* pStageRoot = GameObjectManager::AddRoot3D("Stage Root");
		
		GameObject* pStage_1 = GameObjectManager::Add(*pCrateProto, ShaderName::TEXTURE_POINT_LIGHT, MaterialName::TEXT_POINT_LIGHT, "Stage Left", TextureName::DEFAULT, pStageRoot);
		GameObjectManager::SetScale(pStage_1, Vec3(0.084000f, 0.034000f, 0.072000f));
		GameObjectManager::SetPos(pStage_1, Vec3(-0.144000f, -0.032000f, -0.473001f));
		GameObjectManager::SetLightColor(pStage_1, Vec4(0.60f, 0.60f, 0.60f, 1.0f));

		GameObject* pStage_2 = GameObjectManager::Add(*pCrateProto, ShaderName::TEXTURE_POINT_LIGHT, MaterialName::TEXT_POINT_LIGHT, "Stage Center", TextureName::DEFAULT, pStageRoot);
		GameObjectManager::SetScale(pStage_2, Vec3(0.071000f, 0.034000f, 0.146000f));
		GameObjectManager::SetPos(pStage_2, Vec3(0.009000f, -0.032000f, -0.399002f));
		GameObjectManager::SetLightColor(pStage_2, Vec4(0.60f, 0.60f, 0.60f, 1.0f));

		GameObject* pStage_3 = GameObjectManager::Add(*pCrateProto, ShaderName::TEXTURE_POINT_LIGHT, MaterialName::TEXT_POINT_LIGHT, "Stage Right", TextureName::DEFAULT, pStageRoot);
		GameObjectManager::SetScale(pStage_3, Vec3(0.084000f, 0.034000f, 0.072000f));
		GameObjectManager::SetPos(pStage_3, Vec3(0.160999f, -0.032000f, -0.473001f));
		GameObjectManager::SetLightColor(pStage_3, Vec4(0.60f, 0.60f, 0.60f, 1.0f));

		GameObject* pStage_DrumPlatform = GameObjectManager::Add(*pCrateProto, ShaderName::TEXTURE_POINT_LIGHT, MaterialName::TEXT_POINT_LIGHT, "Stage Drum Platform", TextureName::DEFAULT, pStageRoot);
		GameObjectManager::SetScale(pStage_DrumPlatform, Vec3(0.054000f, 0.032000f, 0.056000f));
		GameObjectManager::SetPos(pStage_DrumPlatform, Vec3(0.010000f, 0.028000f, -0.456003f));
		GameObjectManager::SetLightColor(pStage_DrumPlatform, Vec4(0.60f, 0.60f, 0.60f, 1.0f));


		////// ----------------------------------------------------------------------------------------------------
		////// -- Player
		////// ----------------------------------------------------------------------------------------------------


		////// ----------------------------------------------------------------------------------------------------
		////// -- Editable Objects
		////// ----------------------------------------------------------------------------------------------------
		InputManager::SetEditObject(*pMichelle_2, Keyboard::KEY_LEFT_SHIFT);
		InputManager::SetEditObject(*pNinja_1, Keyboard::KEY_LEFT_CONTROL);
		InputManager::SetEditObject(*pPaladin_5, Keyboard::KEY_LEFT_ALT);
		InputManager::SetEditObject(*pNinja_3, Keyboard::KEY_RIGHT_SHIFT);
	}

	void Scene_Concert::Unload()
	{
	}

	void Scene_Concert::Update()
	{
		DebugTime += DebugTimer.Toc();
		CurAudienceTime += AudienceTimer.Toc();
		CurBandTime += BandTimer.Toc();

		// Update string
		int seconds = _Time::Quotient(DebugTime, _Time(_Time::Duration::ONE_SECOND));
		_Time ms = _Time::Remainder(DebugTime, _Time(_Time::Duration::ONE_SECOND));
		int milliseconds = _Time::Quotient(ms, _Time(_Time::Duration::ONE_MILLISECOND));

		sprintf_s(CounterMessageBuffer, 64, "%s - %d:%ds", pCountPreMessage, seconds, milliseconds);
		GameObjectManager::SetMessage(pCountFont, CounterMessageBuffer);


		if (CurAudienceTime >= AudienceUpdateTime)
		{
			GenerateAudienceTimedEvents();
			CurAudienceTime = _Time(_Time::Duration::ZERO);
		}

		if (CurBandTime >= BandUpdateTime)
		{
			GenerateBandTimedEvents();
			CurBandTime = _Time(_Time::Duration::ZERO);
		}

		AudienceTimer.Tic();
		BandTimer.Tic();
		DebugTimer.Tic();
	}

	void Scene_Concert::GenerateBandTimedEvents()
	{
		_Time initTime = AnimManager::GetTime();

		CMD_SetAnim* pClaire_PlayGuitar = new CMD_SetAnim(*pClaireController, AnimName::S_CLAIRE_BASS, true);
		CMD_SetAnim* pClaire_Dance = new CMD_SetAnim(*pClaireController, AnimName::S_CLAIRE_DANCE_HIGH_KICK, true);
		CMD_SetAnim* pClaire_PlayGuitar_2 = new CMD_SetAnim(*pClaireController, AnimName::S_CLAIRE_BASS, true);
		
		CMD_TimedEvent_Anim* pTimedClaire1 = new CMD_TimedEvent_Anim(*pClaire_PlayGuitar, initTime, 1, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedClaire2 = new CMD_TimedEvent_Anim(*pClaire_Dance, initTime, 6, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedClaire3 = new CMD_TimedEvent_Anim(*pClaire_PlayGuitar_2, initTime, 13, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pGrandma_Dance = new CMD_SetAnim(*pGrandmaController, AnimName::S_GRANDMA_DANCE_BBOY_HH, true);
		CMD_SetAnim* pGrandma_Victory = new CMD_SetAnim(*pGrandmaController, AnimName::S_GRANDMA_VICTORY, true);

		CMD_TimedEvent_Anim* pTimedGrandma1 = new CMD_TimedEvent_Anim(*pGrandma_Dance, initTime, 1, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedGrandma2 = new CMD_TimedEvent_Anim(*pGrandma_Victory, initTime, 10, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pMouse_PlayGuitar = new CMD_SetAnim(*pMouseController, AnimName::S_MOUSE_GUITAR, true);
		CMD_SetAnim* pMouse_Silly = new CMD_SetAnim(*pMouseController, AnimName::S_MOUSE_DANCE_SILLY, true);
		CMD_SetAnim* pMouse_Twerk = new CMD_SetAnim(*pMouseController, AnimName::S_MOUSE_DANCE_TWERK, true);
		CMD_SetAnim* pMouse_Jump = new CMD_SetAnim(*pMouseController, AnimName::S_MOUSE_JOYFUL_JUMP, true);

		CMD_TimedEvent_Anim* pTimedMouse1 = new CMD_TimedEvent_Anim(*pMouse_PlayGuitar, initTime, 1, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedMouse2 = new CMD_TimedEvent_Anim(*pMouse_Silly, initTime, 6, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedMouse3 = new CMD_TimedEvent_Anim(*pMouse_Twerk, initTime, 15, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedMouse4 = new CMD_TimedEvent_Anim(*pMouse_Jump, initTime, 25, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pKnight_PlayPiano = new CMD_SetAnim(*pKnightController, AnimName::S_KNIGHT_PIANO, true);
		CMD_SetAnim* pKnight_Clap = new CMD_SetAnim(*pKnightController, AnimName::S_KNIGHT_CLAP_SIT, true);

		CMD_TimedEvent_Anim* pTimedKnight1 = new CMD_TimedEvent_Anim(*pKnight_PlayPiano, initTime, 2, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedKnight2 = new CMD_TimedEvent_Anim(*pKnight_Clap, initTime, 12, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pPumpkin_PlayDrums = new CMD_SetAnim(*pPumpkinController, AnimName::S_PUMPKIN_HULK_DRUMS, true);
		CMD_SetAnim* pPumpkin_Fist = new CMD_SetAnim(*pPumpkinController, AnimName::S_PUMPKIN_HULK_FIST_PUMP_SITTING, true);

		CMD_TimedEvent_Anim* pTimedPumpkin1 = new CMD_TimedEvent_Anim(*pPumpkin_PlayDrums, initTime, 5, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedPumpkin2 = new CMD_TimedEvent_Anim(*pPumpkin_Fist, initTime, 15, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pVanguard_Sing = new CMD_SetAnim(*pVanguardController, AnimName::S_VANGUARD_SING, true);
		CMD_SetAnim* pVanguard_Dance_1 = new CMD_SetAnim(*pVanguardController, AnimName::S_VANGUARD_DANCE_SALSA_1, true);
		CMD_SetAnim* pVanguard_Dance_2 = new CMD_SetAnim(*pVanguardController, AnimName::S_VANGUARD_DANCE_SALSA_2, true);
		CMD_SetAnim* pVanguard_Jam = new CMD_SetAnim(*pVanguardController, AnimName::S_VANGUARD_JAM, true);

		CMD_TimedEvent_Anim* pTimedVanguard1 = new CMD_TimedEvent_Anim(*pVanguard_Sing, initTime, 2, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedVanguard2 = new CMD_TimedEvent_Anim(*pVanguard_Dance_1, initTime, 8, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedVanguard3 = new CMD_TimedEvent_Anim(*pVanguard_Dance_2, initTime, 15, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedVanguard4 = new CMD_TimedEvent_Anim(*pVanguard_Jam, initTime, 23, _Time::Duration::ONE_SECOND);


		CommandQueueManager::SendData(pTimedClaire1);
		CommandQueueManager::SendData(pTimedClaire2);
		CommandQueueManager::SendData(pTimedClaire3);

		CommandQueueManager::SendData(pTimedGrandma1);
		CommandQueueManager::SendData(pTimedGrandma2);

		CommandQueueManager::SendData(pTimedMouse1);
		CommandQueueManager::SendData(pTimedMouse2);
		CommandQueueManager::SendData(pTimedMouse3);
		CommandQueueManager::SendData(pTimedMouse4);

		CommandQueueManager::SendData(pTimedKnight1);
		CommandQueueManager::SendData(pTimedKnight2);

		CommandQueueManager::SendData(pTimedPumpkin1);
		CommandQueueManager::SendData(pTimedPumpkin2);

		CommandQueueManager::SendData(pTimedVanguard1);
		CommandQueueManager::SendData(pTimedVanguard2);
		CommandQueueManager::SendData(pTimedVanguard3);
		CommandQueueManager::SendData(pTimedVanguard4);


	}

	void Scene_Concert::GenerateAudienceTimedEvents()
	{
		_Time initTime = AnimManager::GetTime();

		// -------------------------------------------------------------------------
		//  Paladin ----------------------------------------------------------------
		// -------------------------------------------------------------------------

		CMD_SetAnim* pPaladin_Cheer1_Cheer1 = new CMD_SetAnim(*pPaladinController_Cheer_1, AnimName::S_PALADIN_CHEER, false);
		CMD_SetAnim* pPaladin_Cheer1_Cheer2 = new CMD_SetAnim(*pPaladinController_Cheer_1, AnimName::S_PALADIN_CHEER, true);
		CMD_SetAnim* pPaladin_Cheer1_Dance = new CMD_SetAnim(*pPaladinController_Cheer_1, AnimName::S_PALADIN_DANCE_SILLY, true);

		CMD_TimedEvent_Anim* pTimedPaladin_Cheer1_1 = new CMD_TimedEvent_Anim(*pPaladin_Cheer1_Cheer1, initTime, 5, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedPaladin_Cheer1_2 = new CMD_TimedEvent_Anim(*pPaladin_Cheer1_Dance, initTime, 10, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedPaladin_Cheer1_3 = new CMD_TimedEvent_Anim(*pPaladin_Cheer1_Cheer2, initTime, 15, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pPaladin_Cheer2_Cheer1 = new CMD_SetAnim(*pPaladinController_Cheer_2, AnimName::S_PALADIN_CHEER, true);
		CMD_SetAnim* pPaladin_Cheer2_Dance = new CMD_SetAnim(*pPaladinController_Cheer_2, AnimName::S_PALADIN_DANCE_SILLY, true);
		CMD_SetAnim* pPaladin_Cheer2_Cheer2 = new CMD_SetAnim(*pPaladinController_Cheer_2, AnimName::S_PALADIN_CHEER, true);

		CMD_TimedEvent_Anim* pTimedPaladin_Cheer2_1 = new CMD_TimedEvent_Anim(*pPaladin_Cheer2_Cheer1, initTime, 3, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedPaladin_Cheer2_2 = new CMD_TimedEvent_Anim(*pPaladin_Cheer2_Dance, initTime, 17, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedPaladin_Cheer2_3 = new CMD_TimedEvent_Anim(*pPaladin_Cheer2_Cheer2, initTime, 20, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pPaladin_Dance_2 = new CMD_SetAnim(*pPaladinController_Dance, AnimName::S_PALADIN_DANCE_HOKEY_POKEY, true);

		CMD_TimedEvent_Anim* pTimedPaladin_Dance_1 = new CMD_TimedEvent_Anim(*pPaladin_Dance_2, initTime, 10, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pPaladin_Static = new CMD_SetAnim(*pPaladinController_Static, AnimName::S_PALADIN_DANCE_SILLY, true);

		CMD_TimedEvent_Anim* pTimedPaladin_Dance_2 = new CMD_TimedEvent_Anim(*pPaladin_Static, initTime, 10, _Time::Duration::ONE_SECOND);

		CommandQueueManager::SendData(pTimedPaladin_Cheer1_1);
		CommandQueueManager::SendData(pTimedPaladin_Cheer1_2);
		CommandQueueManager::SendData(pTimedPaladin_Cheer1_3);
		CommandQueueManager::SendData(pTimedPaladin_Cheer2_1);
		CommandQueueManager::SendData(pTimedPaladin_Cheer2_2);
		CommandQueueManager::SendData(pTimedPaladin_Cheer2_3);
		CommandQueueManager::SendData(pTimedPaladin_Dance_1);
		CommandQueueManager::SendData(pTimedPaladin_Dance_2);


		// -------------------------------------------------------------------------
		//  Michelle ---------------------------------------------------------------
		// -------------------------------------------------------------------------

		CMD_SetAnim* pMichelle_Cheer1_React = new CMD_SetAnim(*pMichelleController_Cheer_1, AnimName::S_MICHELLE_REACT, true);
		CMD_SetAnim* pMichelle_Cheer1_Talk = new CMD_SetAnim(*pMichelleController_Cheer_1, AnimName::S_MICHELLE_TALK, true);
		CMD_SetAnim* pMichelle_Cheer1_Cheer = new CMD_SetAnim(*pMichelleController_Cheer_1, AnimName::S_MICHELLE_CHEER, true);

		CMD_TimedEvent_Anim* pTimedMichelle_Cheer1_1 = new CMD_TimedEvent_Anim(*pMichelle_Cheer1_React, initTime, 2, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedMichelle_Cheer1_2 = new CMD_TimedEvent_Anim(*pMichelle_Cheer1_Talk, initTime, 5, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedMichelle_Cheer1_3 = new CMD_TimedEvent_Anim(*pMichelle_Cheer1_Cheer, initTime, 18, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pMichelle_Cheer2_React = new CMD_SetAnim(*pMichelleController_Cheer_2, AnimName::S_MICHELLE_REACT, true);
		CMD_SetAnim* pMichelle_Cheer2_Talk = new CMD_SetAnim(*pMichelleController_Cheer_2, AnimName::S_MICHELLE_TALK, true);
		CMD_SetAnim* pMichelle_Cheer2_Cheer = new CMD_SetAnim(*pMichelleController_Cheer_2, AnimName::S_MICHELLE_CHEER, true);

		CMD_TimedEvent_Anim* pTimedMichelle_Cheer2_1 = new CMD_TimedEvent_Anim(*pMichelle_Cheer2_Talk, initTime, 2, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedMichelle_Cheer2_2 = new CMD_TimedEvent_Anim(*pMichelle_Cheer2_React, initTime, 8, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedMichelle_Cheer2_3 = new CMD_TimedEvent_Anim(*pMichelle_Cheer2_Cheer, initTime, 19, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pMichelle_Dance_Mara1 = new CMD_SetAnim(*pMichelleController_Dance, AnimName::S_MICHELLE_DANCE_MARA_STEP, true);
		CMD_SetAnim* pMichelle_Dance_NSS1 = new CMD_SetAnim(*pMichelleController_Dance, AnimName::S_MICHELLE_DANCE_NSS_COMBO, true);
		CMD_SetAnim* pMichelle_Dance_Mara2 = new CMD_SetAnim(*pMichelleController_Dance, AnimName::S_MICHELLE_DANCE_MARA_STEP, true);

		CMD_TimedEvent_Anim* pTimedMichelle_Dance_1 = new CMD_TimedEvent_Anim(*pMichelle_Dance_Mara1, initTime, 5, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedMichelle_Dance_2 = new CMD_TimedEvent_Anim(*pMichelle_Dance_NSS1, initTime, 15, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedMichelle_Dance_3 = new CMD_TimedEvent_Anim(*pMichelle_Dance_Mara2, initTime, 25, _Time::Duration::ONE_SECOND);

		CommandQueueManager::SendData(pTimedMichelle_Cheer1_1);
		CommandQueueManager::SendData(pTimedMichelle_Cheer1_2);
		CommandQueueManager::SendData(pTimedMichelle_Cheer1_3);
		CommandQueueManager::SendData(pTimedMichelle_Cheer2_1);
		CommandQueueManager::SendData(pTimedMichelle_Cheer2_2);
		CommandQueueManager::SendData(pTimedMichelle_Cheer2_3);
		CommandQueueManager::SendData(pTimedMichelle_Dance_1);
		CommandQueueManager::SendData(pTimedMichelle_Dance_2);
		CommandQueueManager::SendData(pTimedMichelle_Dance_3);


		// -------------------------------------------------------------------------
		//  Ninja ------------------------------------------------------------------
		// -------------------------------------------------------------------------

		CMD_SetAnim* pNinja_Cheer1_Cheer1 = new CMD_SetAnim(*pNinjaController_Cheer_1, AnimName::S_NINJA_CHEER, true);
		CMD_SetAnim* pNinja_Cheer1_Jam1 = new CMD_SetAnim(*pNinjaController_Cheer_1, AnimName::S_NINJA_JAM, true);

		CMD_TimedEvent_Anim* pTimedNinja_Cheer1_1 = new CMD_TimedEvent_Anim(*pNinja_Cheer1_Cheer1, initTime, 3, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedNinja_Cheer1_2 = new CMD_TimedEvent_Anim(*pNinja_Cheer1_Jam1, initTime, 17, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pNinja_Cheer2_Cheer1 = new CMD_SetAnim(*pNinjaController_Cheer_2, AnimName::S_NINJA_CHEER, true);
		CMD_SetAnim* pNinja_Cheer2_Jam1 = new CMD_SetAnim(*pNinjaController_Cheer_2, AnimName::S_NINJA_JAM, true);

		CMD_TimedEvent_Anim* pTimedNinja_Cheer2_1 = new CMD_TimedEvent_Anim(*pNinja_Cheer2_Cheer1, initTime, 8, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedNinja_Cheer2_2 = new CMD_TimedEvent_Anim(*pNinja_Cheer2_Jam1, initTime, 18, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pNinja_Dance_Flair1 = new CMD_SetAnim(*pNinjaController_Dance, AnimName::S_NINJA_DANCE_FLAIR, true);
		CMD_SetAnim* pNinja_Dance_House1 = new CMD_SetAnim(*pNinjaController_Dance, AnimName::S_NINJA_DANCE_HOUSE, true);

		CMD_TimedEvent_Anim* pTimedNinja_Dance_1 = new CMD_TimedEvent_Anim(*pNinja_Dance_Flair1, initTime, 10, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedNinja_Dance_2 = new CMD_TimedEvent_Anim(*pNinja_Dance_House1, initTime, 20, _Time::Duration::ONE_SECOND);

		CommandQueueManager::SendData(pTimedNinja_Cheer1_1);
		CommandQueueManager::SendData(pTimedNinja_Cheer1_2);
		CommandQueueManager::SendData(pTimedNinja_Cheer2_1);
		CommandQueueManager::SendData(pTimedNinja_Cheer2_2);
		CommandQueueManager::SendData(pTimedNinja_Dance_1);
		CommandQueueManager::SendData(pTimedNinja_Dance_2);

		// -------------------------------------------------------------------------
		//  Ortiz ------------------------------------------------------------------
		// -------------------------------------------------------------------------

		CMD_SetAnim* pOrtiz_Cheer1_Cheer1 = new CMD_SetAnim(*pOrtizController_Cheer_1, AnimName::S_ORTIZ_CHEER, true);
		CMD_SetAnim* pOrtiz_Cheer1_Jam1 = new CMD_SetAnim(*pOrtizController_Cheer_1, AnimName::S_ORTIZ_JAM, true);

		CMD_TimedEvent_Anim* pTimedOrtiz_Cheer1_1 = new CMD_TimedEvent_Anim(*pOrtiz_Cheer1_Cheer1, initTime, 2, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedOrtiz_Cheer1_2 = new CMD_TimedEvent_Anim(*pOrtiz_Cheer1_Jam1, initTime, 17, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pOrtiz_Cheer2_Jam1 = new CMD_SetAnim(*pOrtizController_Cheer_2, AnimName::S_ORTIZ_JAM, true);
		CMD_SetAnim* pOrtiz_Cheer2_Cheer = new CMD_SetAnim(*pOrtizController_Cheer_2, AnimName::S_ORTIZ_CHEER, true);

		CMD_TimedEvent_Anim* pTimedOrtiz_Cheer2_1 = new CMD_TimedEvent_Anim(*pOrtiz_Cheer2_Jam1, initTime, 10, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedOrtiz_Cheer2_2 = new CMD_TimedEvent_Anim(*pOrtiz_Cheer2_Cheer, initTime, 20, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pOrtiz_Dance_Dance = new CMD_SetAnim(*pOrtizController_Dance, AnimName::S_ORTIZ_DANCE, true);
		CMD_SetAnim* pOrtiz_Dance_Swing = new CMD_SetAnim(*pOrtizController_Dance, AnimName::S_ORTIZ_DANCE_SWING, true);

		CMD_TimedEvent_Anim* pTimedOrtiz_Dance_1 = new CMD_TimedEvent_Anim(*pOrtiz_Dance_Dance, initTime, 8, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedOrtiz_Dance_2 = new CMD_TimedEvent_Anim(*pOrtiz_Dance_Swing, initTime, 15, _Time::Duration::ONE_SECOND);

		CommandQueueManager::SendData(pTimedOrtiz_Cheer1_1);
		CommandQueueManager::SendData(pTimedOrtiz_Cheer1_2);
		CommandQueueManager::SendData(pTimedOrtiz_Cheer2_1);
		CommandQueueManager::SendData(pTimedOrtiz_Cheer2_2);
		CommandQueueManager::SendData(pTimedOrtiz_Dance_1);
		CommandQueueManager::SendData(pTimedOrtiz_Dance_2);


		// -------------------------------------------------------------------------
		//  Zombie Girl ------------------------------------------------------------
		// -------------------------------------------------------------------------

		CMD_SetAnim* pZombieGirl_Cheer1_Cheer = new CMD_SetAnim(*pZombieGirlController_Cheer_1, AnimName::S_ZOMBIE_GIRL_CHEER, true);
		CMD_SetAnim* pZombieGirl_Cheer1_Agonize = new CMD_SetAnim(*pZombieGirlController_Cheer_1, AnimName::S_ZOMBIE_GIRL_AGONIZE, true);

		CMD_TimedEvent_Anim* pTimedZombieGirl_Cheer1_1 = new CMD_TimedEvent_Anim(*pZombieGirl_Cheer1_Agonize, initTime, 5, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedZombieGirl_Cheer1_2 = new CMD_TimedEvent_Anim(*pZombieGirl_Cheer1_Cheer, initTime, 20, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pZombieGirl_Cheer2_Cheer = new CMD_SetAnim(*pZombieGirlController_Cheer_2, AnimName::S_ZOMBIE_GIRL_CHEER, true);
		CMD_SetAnim* pZombieGirl_Cheer2_Agonize = new CMD_SetAnim(*pZombieGirlController_Cheer_2, AnimName::S_ZOMBIE_GIRL_AGONIZE, true);

		CMD_TimedEvent_Anim* pTimedZombieGirl_Cheer2_1 = new CMD_TimedEvent_Anim(*pZombieGirl_Cheer2_Agonize, initTime, 6, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedZombieGirl_Cheer2_2 = new CMD_TimedEvent_Anim(*pZombieGirl_Cheer2_Cheer, initTime, 15, _Time::Duration::ONE_SECOND);

		CMD_SetAnim* pZombieGirl_Dance_Mara1 = new CMD_SetAnim(*pZombieGirlController_Dance, AnimName::S_ZOMBIE_GIRL_DANCE_MARA_STEP, true);
		CMD_SetAnim* pZombieGirl_Dance_YMCA1 = new CMD_SetAnim(*pZombieGirlController_Dance, AnimName::S_ZOMBIE_GIRL_DANCE_YMCA, true);

		CMD_TimedEvent_Anim* pTimedZombieGirl_Dance_1 = new CMD_TimedEvent_Anim(*pZombieGirl_Dance_Mara1, initTime, 10, _Time::Duration::ONE_SECOND);
		CMD_TimedEvent_Anim* pTimedZombieGirl_Dance_2 = new CMD_TimedEvent_Anim(*pZombieGirl_Dance_YMCA1, initTime, 20, _Time::Duration::ONE_SECOND);

		CommandQueueManager::SendData(pTimedZombieGirl_Cheer1_1);
		CommandQueueManager::SendData(pTimedZombieGirl_Cheer1_2);
		CommandQueueManager::SendData(pTimedZombieGirl_Cheer2_1);
		CommandQueueManager::SendData(pTimedZombieGirl_Cheer2_2);
		CommandQueueManager::SendData(pTimedZombieGirl_Dance_1);
		CommandQueueManager::SendData(pTimedZombieGirl_Dance_2);


	}
}


