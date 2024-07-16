#include "GameObjectManager.h"	
#include "GameObject.h"
#include "CommandQueue.h"
#include "CommandQueueManager.h"
#include "PCSNode.h"
#include "PCSTreeReverseIterator.h"
#include "NullMesh.h"
#include "GraphicsObjectManager.h"
#include "TextureManager.h"
#include "AnimManager.h"
#include "ProtoManager.h"
#include "CameraManager.h"
#include "ImageManager.h"
#include "GameObjectUIRoot.h"
#include "GameObjectUI.h"
#include "GameObjectUIElement.h"
#include "UINode.h"
#include "BoundingObjectWrapper.h"
#include "ArmatureManager.h"
#include "Armature.h"

#define FRUSTUM_CULLING 0

namespace Uncertain
{
	GameObjectManager* GameObjectManager::instance = nullptr;

	GameObjectManager::GameObjectManager()
		: DrawBoundingObjects(DRAW_BOUNDING_GRAPHICS)
	{

		GraphicsObjectNode* pNullGraphObj = GraphicsObjectManager::Add(MeshName::NULL_MESH, ShaderName::NULL_SHADER, MaterialName::NULL_MAT, false);

		GameObject* pGameRoot = new GameObject(pNullGraphObj, GameObject::TYPE::GO_TREE_ROOT, "GameObject_Root", new BoundingNull());

		this->poRootTree = new PCSTree();
		assert(this->poRootTree);

		this->poRootTree->Insert(pGameRoot, nullptr);

		this->pCommandQueue = CommandQueueManager::Add(QueueName::GAME);
	}

	GameObjectManager::~GameObjectManager()
	{
		delete this->poRootTree;
	}

	void GameObjectManager::Create()
	{
		assert(!instance);

		if (!instance)
		{
			instance = new GameObjectManager();
		}
	}

	void GameObjectManager::Destroy()
	{
		GameObjectManager* inst = GameObjectManager::GetInstance();

		delete inst;

		GameObjectManager::instance = nullptr;
	}

	void GameObjectManager::Update(_Time currentTime)
	{
		GameObjectManager* inst = GameObjectManager::GetInstance();

		PCSTreeForwardIterator* pIt = inst->poRootTree->GetForwardIT();

		GameObject* pCur = (GameObject*)pIt->CurrentItem();
		GameObject* pTemp;


		// Handle command queue
		Command* pCommand;

		while (inst->pCommandQueue->PopFront(pCommand) == true)
		{
			pCommand->Execute();
		}

		while (!pIt->IsDone())
		{
			pTemp = (GameObject*)pIt->Next();
			pCur->Update(currentTime);
			pCur = pTemp;
		}
	}

	void GameObjectManager::Draw(void)
	{
		GameObjectManager* inst = GameObjectManager::GetInstance();

		PCSTreeForwardIterator* pIt = inst->poRootTree->GetForwardIT();

		GameObject* pCur = (GameObject*)pIt->CurrentItem();
		GameObject* pTemp;

#if FRUSTUM_CULLING
		// vars for culling
		bool is3d;
		Camera::CullResult cullResult;
		Camera* p2DCam = CameraManager::GetActive2D();
		Camera* p3DCam = CameraManager::GetActive3D();
#endif

		while (!pIt->IsDone())
		{
			pTemp = (GameObject*)pIt->Next();

#if FRUSTUM_CULLING

			is3d = pCur->Is3D();
			cullResult = is3d ? p3DCam->CullTest(pCur) : p2DCam->CullTest(pCur);

			if (cullResult == Camera::CullResult::CULL_INSIDE)
			{
				pCur->Draw(inst->DrawBoundingSpheres);
			}
#else
			pCur->Draw(inst->DrawBoundingObjects);
#endif

			pCur = pTemp;
		}
	}

	//GameObject* GameObjectManager::Add(MeshName meshName, ShaderName shaderName, TextureName textureName, 
	//	MaterialName materialName, const char* const objName, GameObject* pParent, bool generateBoundingGraphics)
	//{
	//	GameObjectManager* inst = GameObjectManager::GetInstance();

	//	GraphicsObjectNode* pGNode = GraphicsObjectManager::Add(meshName, shaderName, materialName, generateBoundingGraphics);
	//	pGNode->SetTexture(textureName);
	//	assert(pGNode);

	//	GameObject* pGameObject = new GameObject(pGNode, GameObject::TYPE::RIGID_3D, objName, new BoundingSphere());

	//	if (pParent == nullptr)
	//	{
	//		// Insert null as root node and return it
	//		GraphicsObjectNode* pRoot = GraphicsObjectManager::Add(MeshName::NULL_MESH, ShaderName::NULL_SHADER, MaterialName::NULL_MAT, generateBoundingGraphics);
	//		GameObject* pNullGORoot = new GameObject(pRoot, GameObject::TYPE::ROOT_3D, "Mesh GameObject Root", new BoundingNull());

	//		inst->poRootTree->Insert(pNullGORoot, inst->poRootTree->GetRoot());
	//		inst->poRootTree->Insert(pGameObject, pNullGORoot);

	//		return pNullGORoot;
	//	}
	//	else
	//	{
	//		inst->poRootTree->Insert(pGameObject, pParent);

	//		return pGameObject;
	//	}
	//}

	//GameObject* GameObjectManager::Add(MeshName meshName, ShaderName shaderName, 
	//	MaterialName materialName, const char* const objName, GameObject* pParent, bool generateBoundingGraphics)
	//{
	//	GameObjectManager* inst = GameObjectManager::GetInstance();

	//	GraphicsObjectNode* pGNode = GraphicsObjectManager::Add(meshName, shaderName, materialName, generateBoundingGraphics);
	//	assert(pGNode);

	//	GameObject* pGameObject = new GameObject(pGNode, GameObject::TYPE::RIGID_3D, objName, new BoundingSphere());


	//	if (pParent == nullptr)
	//	{
	//		// Insert null as root node and return it
	//		GraphicsObjectNode* pRoot = GraphicsObjectManager::Add(MeshName::NULL_MESH, ShaderName::NULL_SHADER, MaterialName::NULL_MAT, generateBoundingGraphics);
	//		GameObject* pNullGORoot = new GameObject(pRoot, GameObject::TYPE::ROOT_3D, "Mesh GameObject Root", new BoundingNull());

	//		inst->poRootTree->Insert(pNullGORoot, inst->poRootTree->GetRoot());
	//		inst->poRootTree->Insert(pGameObject, pNullGORoot);

	//		return pNullGORoot;
	//	}
	//	else
	//	{
	//		inst->poRootTree->Insert(pGameObject, pParent);

	//		return pGameObject;
	//	}
	//}

	GameObject* GameObjectManager::Add(ProtoNode& protoNode, ShaderName shaderName, MaterialName materialName, const char* pName,
									   TextureName textureName,  GameObject* pParent, bool generateBoundingGraphics)
	{
		GameObjectManager* inst = GameObjectManager::GetInstance();

		// Insert null as root node for Proto
		GraphicsObjectNode* pRoot = GraphicsObjectManager::Add(MeshName::NULL_MESH, ShaderName::NULL_SHADER, MaterialName::NULL_MAT, false);
		GameObject* pNullGORoot = new GameObject(pRoot, GameObject::TYPE::ROOT_3D, protoNode.GetName(), new BoundingNull());
		pNullGORoot->SetName(pName);

		if (pParent == nullptr)
		{
			inst->poRootTree->Insert(pNullGORoot, inst->poRootTree->GetRoot());
		}
		else
		{
			inst->poRootTree->Insert(pNullGORoot, pParent);
		}

		// Insert meshes with null root as parent
		ProtoNode* pCur = (ProtoNode*)protoNode.GetForward();
		while (pCur && pCur->GetRootProto() == &protoNode) 
		{
			GraphicsObjectNode* pGraph = GraphicsObjectManager::Add(*pCur, shaderName, materialName, generateBoundingGraphics);
			GameObject* pGO = new GameObject(pGraph, GameObject::TYPE::RIGID_3D, pCur->GetName(), new BoundingSphere());
			inst->poRootTree->Insert(pGO, pNullGORoot);

			if (textureName != TextureName::UNINITIALIZED)
			{
				if (textureName == TextureName::DEFAULT)
				{
					pGraph->SetTexture(*pCur->pTexture);
				}
				else
				{
					pGraph->SetTexture(textureName);
				}
			}

			pCur = (ProtoNode*)pCur->GetForward();
		}

		return pNullGORoot;
	}


	GameObjectAnim* GameObjectManager::Add(ProtoNode& protoNode, ShaderName shaderName, MaterialName materialName,
		AnimController& animController, const char* pName, TextureName textureName, GameObject* pParent, bool generateBoundingGraphics)
	{
		GameObjectManager* inst = GameObjectManager::GetInstance();

		// Insert Null mesh as root node for Proto
		GraphicsObjectNode* pRoot = GraphicsObjectManager::Add(MeshName::NULL_MESH, ShaderName::NULL_SHADER, MaterialName::NULL_MAT, false);
		GameObjectAnimSkin* pGORoot = new GameObjectAnimSkin(GameObject::TYPE::ROOT_3D, animController, pRoot, "Null Root", new BoundingNull());
		pGORoot->SetName(pName);

		if (pParent == nullptr)
		{
			inst->poRootTree->Insert(pGORoot, inst->poRootTree->GetRoot());
		}
		else
		{
			inst->poRootTree->Insert(pGORoot, pParent);
		}
		
		// Get Armature if it exists
		Armature* pArmature = nullptr;
		if (ArmData* pArmData = protoNode.GetArmatureData())
		{
			pArmature = ArmatureManager::Add(*pArmData, animController);
			animController.SetArmature(*pArmature);
		}

		// Insert meshes under null root
		//ProtoNode* pRootMeshProto = ProtoManager::FindByGLTFNodeIndex(protoNode, boneMap->NodeIndex);
		ProtoNode* pCur = (ProtoNode*)protoNode.GetForward();
		while (pCur && pCur->GetRootProto() == &protoNode)
		{
			GraphicsObjectNode* pAnimatedGraphicObj = GraphicsObjectManager::Add(*pCur, shaderName, materialName, generateBoundingGraphics, pArmature);

			if (textureName != TextureName::UNINITIALIZED)
			{
				if (textureName == TextureName::DEFAULT)
				{
					pAnimatedGraphicObj->SetTexture(*pCur->pTexture);
				}
				else
				{
					pAnimatedGraphicObj->SetTexture(textureName);
				}
			}

			GameObjectAnimSkin* pAnimatedGameObject = new GameObjectAnimSkin(GameObject::TYPE::ANIMATED_3D, animController, pAnimatedGraphicObj, protoNode.GetName(), new BoundingSphere());
			inst->poRootTree->Insert(pAnimatedGameObject, pGORoot);

			pCur = (ProtoNode*)pCur->GetForward();
		}
	
		return pGORoot;
	}

	GameObject* GameObjectManager::Add(Image& image, ShaderName shaderName, GameObject* pParent, bool generateBoundingGraphics)
	{
		GameObjectManager* inst = GameObjectManager::GetInstance();

		GraphicsObjectNode* pGNode = GraphicsObjectManager::Add(image, shaderName, MaterialName::SPRITE, generateBoundingGraphics);
		assert(pGNode);

		GameObject* pGameObject = new GameObject(pGNode, GameObject::TYPE::RIGID_2D, image.GetName(), new BoundingRect());

		if (pParent == nullptr)
		{
			// Insert null as root node and return it
			GraphicsObjectNode* pRoot = GraphicsObjectManager::Add(MeshName::NULL_MESH, ShaderName::NULL_SHADER, MaterialName::NULL_MAT, generateBoundingGraphics);
			GameObject* pNullGORoot = new GameObject(pRoot, GameObject::TYPE::ROOT_2D, "Sprite Root", new BoundingNull());

			inst->poRootTree->Insert(pNullGORoot, inst->poRootTree->GetRoot());
			inst->poRootTree->Insert(pGameObject, pNullGORoot);

			return pNullGORoot;
		}
		else
		{
			inst->poRootTree->Insert(pGameObject, pParent);
			
			return pGameObject;
		}
	}

	GameObject* GameObjectManager::AddRoot2D(const char* const rootName, GameObject* pParent)
	{
		GameObjectManager* inst = GameObjectManager::GetInstance();

		GraphicsObjectNode* pRoot = GraphicsObjectManager::Add(MeshName::NULL_MESH, ShaderName::NULL_SHADER, MaterialName::NULL_MAT, false);
		GameObject* pNullGORoot = new GameObject(pRoot, GameObject::TYPE::ROOT_2D, rootName, new BoundingNull());

		if (!pParent)
		{
			inst->poRootTree->Insert(pNullGORoot, inst->poRootTree->GetRoot());
		}
		else
		{
			inst->poRootTree->Insert(pNullGORoot, pParent);
		}

		return pNullGORoot;
	}

	GameObject* GameObjectManager::AddRoot3D(const char* const rootName, GameObject* pParent)
	{
		GameObjectManager* inst = GameObjectManager::GetInstance();

		GraphicsObjectNode* pRoot = GraphicsObjectManager::Add(MeshName::NULL_MESH, ShaderName::NULL_SHADER, MaterialName::NULL_MAT, false);
		GameObject* pNullGORoot = new GameObject(pRoot, GameObject::TYPE::ROOT_3D, rootName, new BoundingNull());

		if (!pParent)
		{
			inst->poRootTree->Insert(pNullGORoot, inst->poRootTree->GetRoot());
		}
		else
		{
			inst->poRootTree->Insert(pNullGORoot, pParent);
		}

		return pNullGORoot;
	}

	void GameObjectManager::InsertProtoChildren(ProtoNode& pNode, GameObjectAnim* pParent, ShaderName shaderName, MaterialName materialName,
		AnimController& animController, BoneMap* boneMap, TextureName textureName, bool generateBoundingGraphicsSphere)
	{
		assert(boneMap);

		GameObjectManager* inst = GameObjectManager::GetInstance();

		for (unsigned int i = 0; i < boneMap[pParent->BoneIndex].ChildCount; i++)
		{
			ProtoNode* pChildNode = ProtoManager::FindByGLTFNodeIndex(pNode, boneMap[pParent->BoneIndex].poChildren[i]);
			GraphicsObjectNode* pAnimatedChild = GraphicsObjectManager::Add(*pChildNode, shaderName, materialName, generateBoundingGraphicsSphere);
			if (textureName != TextureName::UNINITIALIZED)
			{
				pAnimatedChild->SetTexture(textureName);
			}
			GameObjectAnim* pChildGO = new GameObjectAnimSkin(GameObject::TYPE::ANIMATED_3D, animController, pAnimatedChild, pChildNode->GetName(), new BoundingSphere());
			inst->poRootTree->Insert(pChildGO, pParent);

			InsertProtoChildren(pNode, pChildGO, shaderName, materialName, animController, boneMap, textureName, generateBoundingGraphicsSphere);
		}
	}



	void GameObjectManager::Remove(GameObject& pNode)
	{
		GameObjectManager* inst = GameObjectManager::GetInstance();

		inst->poRootTree->Remove(&pNode);
	}

	void GameObjectManager::ToggleBoundingObjects()
	{
		GameObjectManager* inst = GameObjectManager::GetInstance();

		inst->DrawBoundingObjects = !inst->DrawBoundingObjects;
	}

	void GameObjectManager::SetScale(GameObject* pObj, const Vec3& scale)
	{
		pObj->SetScale(scale);
	}

	void GameObjectManager::SetPos(GameObject* pObj, const Vec3& pos)
	{
		pObj->SetPos(pos);
	}

	void GameObjectManager::SetRot(GameObject* pObj, const Quat& q)
	{
		pObj->SetRot(q);
	}

	void GameObjectManager::SetLocalRot(GameObject* pObject, const Vec3& r)
	{
		pObject->SetLocalRot(r);
	}

	void GameObjectManager::SetLocalPos(GameObject* pObject, const Vec3& pos)
	{
		pObject->SetPos(pos);
	}

	void GameObjectManager::SetDeltaRot(GameObject* pObj, const Vec3& q)
	{
		pObj->SetDeltaRot(q);
	}

	void GameObjectManager::SetLightColor(GameObject* pObj, const Vec4& color)
	{
		pObj->SetLightColor(color);

		GameObject* pCur = (GameObject*)pObj->GetChild();

		while (pCur)
		{
			SetLightColor(pCur, color);
			pCur = (GameObject*)pCur->GetNextSibling();
		}
	}

	void GameObjectManager::SetLightPos(GameObject* pObj, const Vec3& pos)
	{
		pObj->SetLightPos(pos);

		GameObject* pCur = (GameObject*)pObj->GetChild();

		while (pCur)
		{
			SetLightPos(pCur, pos);
			pCur = (GameObject*)pCur->GetNextSibling();
		}
	}

	void GameObjectManager::SetPhongData(GameObject* pObj, const PhongData& data)
	{
		pObj->SetPhongData(data);

		GameObject* pCur = (GameObject*)pObj->GetChild();

		while (pCur)
		{
			SetPhongData(pCur, data);
			pCur = (GameObject*)pCur->GetNextSibling();
		}
	}

	void GameObjectManager::SetTexture(GameObject* pObj, TextureName name)
	{
		pObj->SetTexture(name);
	}

	void GameObjectManager::SetMessage(GameObjectFont* pObj, const char* pMessage)
	{
		
		assert(pObj);
		pObj->SetMessage(pMessage);
	}

	void GameObjectManager::PrintAll()
	{
		GameObjectManager* inst = GameObjectManager::GetInstance();

		Trace::out("\n");
		Trace::out("------------------------------\n");
		Trace::out("----- Active GameObjects -----\n");
		Trace::out("------------------------------\n");

		inst->poRootTree->Print();
	}

	GameObjectManager* GameObjectManager::GetInstance()
	{
		assert(instance);

		return instance;
	}

	//----------------------------------------------------------------------
	//
	//	GameObjectManager::UI method definitions
	// 
	//----------------------------------------------------------------------
	GameObjectUIRoot* GameObjectManager::UI::AddRoot(UINode& uiNode, const char* const name)
	{
		GameObjectManager* inst = GameObjectManager::GetInstance();

		GraphicsObjectNode* pRoot = GraphicsObjectManager::Add(MeshName::RECT_MESH, ShaderName::COLOR_CONST, MaterialName::BOUNDING_RECT, false);
		GameObjectUIRoot* pNullGORoot = new GameObjectUIRoot(pRoot, GameObject::TYPE::ROOT_UI_2D, uiNode, name);

		inst->poRootTree->Insert(pNullGORoot, inst->poRootTree->GetRoot());

		return pNullGORoot;
	}

	GameObjectUIElement* GameObjectManager::UI::Add(Image& image, ShaderName shaderName, GameObjectUI* pParent, bool generateBoundingGraphics)
	{
		assert(pParent);

		GameObjectManager* inst = GameObjectManager::GetInstance();

		GraphicsObjectNode* pGNode = GraphicsObjectManager::Add(image, shaderName, MaterialName::UI, generateBoundingGraphics);
		assert(pGNode);

		GameObjectUIElement* pGameObject = new GameObjectUIElement(pGNode, GameObject::TYPE::UI_ELEMENT_2D, image.GetName(), image.ImageRect.Width, image.ImageRect.Height);
		
		inst->poRootTree->Insert(pGameObject, pParent);

		return pGameObject;
	}

	GameObjectFont* GameObjectManager::UI::Add(Font& font, const char* const pMessage, ShaderName shaderName, GameObjectUI* pParent, bool generateBoundingGraphics)
	{
		assert(pParent);

		GameObjectManager* inst = GameObjectManager::GetInstance();

		GraphicsObjectNode* pGNode = GraphicsObjectManager::Add(font, pMessage, shaderName, MaterialName::FONT, generateBoundingGraphics);

		GameObjectFont* pGameObject = new GameObjectFont(pGNode, "UI Font", &font, pMessage);

		inst->poRootTree->Insert(pGameObject, pParent);

		return pGameObject;
	}

	
	void GameObjectManager::UI::Remove(GameObjectUIElement& pNode)
	{
		GameObjectManager* inst = GameObjectManager::GetInstance();

		inst->Remove(pNode);
	}

	void GameObjectManager::UI::InsertUIObject(GameObjectUI* pUINode, GameObject* pParent)
	{
		assert(pUINode);
		assert(pParent);

		GameObjectManager* inst = GameObjectManager::GetInstance();

		inst->poRootTree->Insert(pUINode, pParent);
	}

}

