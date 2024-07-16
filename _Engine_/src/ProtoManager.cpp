#include "ProtoManager.h"
#include "DLinkManager.h"
#include "MeshNodeManager.h"
#include "TextureManager.h"
#include "ProtoData_Wrapper.h"
#include "MeshData.h"
#include "MeshNode.h"
#include "Texture.h"
#include "ArmatureManager.h"
#include "Armature.h"


namespace Uncertain
{
	ProtoManager* ProtoManager::instance = nullptr;

	ProtoManager::ProtoManager()
	{
		ProtoNode* protoRoot = new ProtoNode("Root Proto Node");
		this->poRootTree = new PCSTree();
		assert(this->poRootTree);
		this->poRootTree->Insert(protoRoot, nullptr);
	}

	ProtoManager::~ProtoManager()
	{
		delete this->poRootTree;
	}


	void ProtoManager::Create()
	{
		assert(!instance);

		if (!instance)
		{
			instance = new ProtoManager();
		}
	}

	void ProtoManager::Destroy()
	{
		ProtoManager* inst = ProtoManager::GetInstance();

		delete inst;
		instance = nullptr;
	}

	ProtoNode* ProtoManager::Add(ModelName name, ProtoNode* pParent)
	{
		ProtoManager* inst = ProtoManager::GetInstance();

		// Insert null root
		ProtoNode* pRoot = new ProtoNode(Stringify(name));
		if (pParent == nullptr)
		{
			inst->poRootTree->Insert(pRoot, inst->poRootTree->GetRoot());
		}
		else
		{
			inst->poRootTree->Insert(pRoot, pParent);
		}

		// Insert all meshes under null root
		ModelData model;
		ProtoData_Wrapper::ReadFromFile(GetFileName(name), model);
		MeshData* mesh = model.Meshes;

		for (unsigned int i = 0; i < model.MeshCount; i++)
		{
			MeshNode* pMeshNode = MeshNodeManager::Add(*mesh);
			ProtoNode* pNode = new ProtoNode(mesh->pMeshName, mesh->NodeIndex, pMeshNode, nullptr, nullptr, pRoot);
			inst->poRootTree->Insert(pNode, pRoot);

			mesh++;
		}

		return pRoot;
	}

	ProtoNode* ProtoManager::Add(ModelName name, TextureName textureName, ArmatureName armatureName, ProtoNode* pParent)
	{
		ProtoManager* inst = ProtoManager::GetInstance();

		// Insert null root
		ProtoNode* protoRoot = new ProtoNode(Stringify(name));

		// protoRoot gets ArmData, if any exists
		if (armatureName != ArmatureName::UNINITIALIZED)
		{
			ArmData* armData = ArmatureManager::FindArmData(armatureName);
			protoRoot->SetArmatureData(*armData);
		}

		if (pParent == nullptr)
		{
			inst->poRootTree->Insert(protoRoot, inst->poRootTree->GetRoot());
		}
		else
		{
			inst->poRootTree->Insert(protoRoot, pParent);
		}

		// Add all mesheses under protoRoot
		ModelData model;
		ProtoData_Wrapper::ReadFromFile(GetFileName(name), model);
		MeshData* mesh = model.Meshes;

		for (unsigned int i = 0; i < model.MeshCount; i++)
		{
			ProtoNode* pNode = nullptr;
			Texture* pText = nullptr;
			if (textureName != TextureName::UNINITIALIZED)
			{
				pText = TextureManager::FindTexture(textureName, mesh->MaterialIndex);
			}

			MeshNode* pMeshNode = MeshNodeManager::Add(*mesh);
			pNode = new ProtoNode(mesh->pMeshName, mesh->NodeIndex, pMeshNode, pText, nullptr, protoRoot);
			inst->poRootTree->Insert(pNode, protoRoot);

			mesh++;

		}

		return protoRoot;
	}

	void ProtoManager::Remove(ProtoNode& pNode)
	{
		ProtoManager* inst = ProtoManager::GetInstance();
		inst->poRootTree->Remove(&pNode);
	}

	ProtoNode* ProtoManager::FindByGLTFNodeIndex(ProtoNode& parent, unsigned int index)
	{
	
		PCSTreeForwardIterator pIt(&parent);

		ProtoNode* pCur = (ProtoNode*)pIt.First();

		while (!pIt.IsDone() && pCur->pRootProto == &parent)
		{
			if (pCur->NodeIndex == index)
			{
				return pCur;
			}

			pCur = (ProtoNode*)pIt.Next();
		}

		return nullptr;
	}


	void ProtoManager::PrintAll()
	{
		ProtoManager* inst = ProtoManager::GetInstance();

		Trace::out("\n");
		Trace::out("---------------------------\n");
		Trace::out("---------- Protos ---------\n");
		Trace::out("---------------------------\n");

		inst->poRootTree->Print();
	}

	ProtoManager* ProtoManager::GetInstance()
	{
		assert(instance);
		return instance;
	}
}
