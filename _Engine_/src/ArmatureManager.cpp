#include "ArmatureManager.h"
#include "DLinkManager.h"
#include "ProtoData_Wrapper.h"
#include "DLinkIterator.h"
#include "Armature.h"
#include "AnimController.h"
#include "ArmatureData.h"
#include "ShaderManager.h"

namespace Uncertain
{
	ArmatureManager* ArmatureManager::instance = nullptr;

	ArmatureManager::ArmatureManager(int initialReserved, int deltaGrow)
		:ManagerBase(*new DLinkManager(), *new DLinkManager()), poLoadedArmatures(new DLinkManager())
	{
		this->SetReserve(initialReserved, deltaGrow);

		this->pBoneComputeSO = ShaderManager::Find(ShaderName::COMPUTE_BONE_WORLD);
	}

	ArmatureManager::~ArmatureManager()
	{
		this->BaseClear();
		delete this->poLoadedArmatures;
		delete this->pCompNode;
	}


	void ArmatureManager::Create(int initialReserved, int deltaGrow)
	{
		assert(initialReserved >= 0);
		assert(deltaGrow > 0);
		assert(!instance);

		if (!instance)
		{
			instance = new ArmatureManager(initialReserved, deltaGrow);

			instance->pCompNode = new Armature();
			instance->LoadArmatureData();
		}
	}

	void ArmatureManager::Destroy()
	{
		ArmatureManager* inst = ArmatureManager::GetInstance();

		delete inst;

		instance = nullptr;
	}

	void ArmatureManager::Update()
	{
		ArmatureManager* inst = ArmatureManager::GetInstance();

		DLinkIterator* pIt = (DLinkIterator*)inst->BaseGetIterator();
		Armature* pCur = (Armature*)pIt->First();
		
		while (!pIt->IsDone())
		{
			if (pCur->ShouldDelete())
			{
				inst->BaseRemove(*pCur);
			}
			else
			{
				pCur->Update(inst->pBoneComputeSO);
			}
			pCur = (Armature*)pIt->Next();
		}

	}

	Armature* ArmatureManager::Add(ArmatureName name, const AnimController& animController)
	{
		ArmatureManager* inst = ArmatureManager::GetInstance();

		ArmData* pArmData = inst->FindArmData(name);
		// If failed, add ArmData in ArmatureManager::LoadArmatureData();
		assert(pArmData);

		Armature* pNode = (Armature*)inst->BaseAdd();

		pNode->Set(animController, *pArmData);

		return pNode;
	}

	Armature* ArmatureManager::Add(const ArmData& data, const AnimController& animController)
	{
		ArmatureManager* inst = ArmatureManager::GetInstance();

		Armature* pNode = (Armature*)inst->BaseAdd();

		pNode->Set(animController, data);

		return pNode;
	}

	void ArmatureManager::Remove(Armature& pNode)
	{
		ArmatureManager* inst = ArmatureManager::GetInstance();

		inst->BaseRemove(pNode);
	}

	ArmData* ArmatureManager::FindArmData(ArmatureName name)
	{
		ArmatureManager* inst = ArmatureManager::GetInstance();

		DLinkIterator* pIt = (DLinkIterator*)inst->poLoadedArmatures->GetIterator();
		ArmData* pCur = (ArmData*)pIt->First();

		while (!pIt->IsDone())
		{
			if (pCur->Name == name)
			{
				return pCur;
			}

			pCur = (ArmData*)pIt->Next();
		}

		return nullptr;
	}

	ArmData* ArmatureManager::privFindArmData(ArmatureName name)
	{
		DLinkIterator* pIt = (DLinkIterator*)this->poLoadedArmatures->GetIterator();
		ArmData* pCur = (ArmData*)pIt->First();

		while (!pIt->IsDone())
		{
			if (pCur->Name == name)
			{
				return pCur;
			}

			pCur = (ArmData*)pIt->Next();
		}

		return nullptr;
	}

	void ArmatureManager::LoadArmatureData()
	{
		ArmatureData armData;
		ArmData* pLocalArm;

		ProtoData_Wrapper::ReadFromFile(GetFileName(ArmatureName::CLAIRE), armData);
		pLocalArm = new ArmData(ArmatureName::CLAIRE, armData);
		this->poLoadedArmatures->Add(*pLocalArm);

		ProtoData_Wrapper::ReadFromFile(GetFileName(ArmatureName::CHICKEN_BOT), armData);
		pLocalArm = new ArmData(ArmatureName::CHICKEN_BOT, armData);
		this->poLoadedArmatures->Add(*pLocalArm);

		ProtoData_Wrapper::ReadFromFile(GetFileName(ArmatureName::GRANDMA), armData);
		pLocalArm = new ArmData(ArmatureName::GRANDMA, armData);
		this->poLoadedArmatures->Add(*pLocalArm);

		ProtoData_Wrapper::ReadFromFile(GetFileName(ArmatureName::KNIGHT), armData);
		pLocalArm = new ArmData(ArmatureName::KNIGHT, armData);
		this->poLoadedArmatures->Add(*pLocalArm);

		ProtoData_Wrapper::ReadFromFile(GetFileName(ArmatureName::MICHELLE), armData);
		pLocalArm = new ArmData(ArmatureName::MICHELLE, armData);
		this->poLoadedArmatures->Add(*pLocalArm);

		ProtoData_Wrapper::ReadFromFile(GetFileName(ArmatureName::MOUSE), armData);
		pLocalArm = new ArmData(ArmatureName::MOUSE, armData);
		this->poLoadedArmatures->Add(*pLocalArm);

		ProtoData_Wrapper::ReadFromFile(GetFileName(ArmatureName::NINJA), armData);
		pLocalArm = new ArmData(ArmatureName::NINJA, armData);
		this->poLoadedArmatures->Add(*pLocalArm);

		ProtoData_Wrapper::ReadFromFile(GetFileName(ArmatureName::ORTIZ), armData);
		pLocalArm = new ArmData(ArmatureName::ORTIZ, armData);
		this->poLoadedArmatures->Add(*pLocalArm);
		
		ProtoData_Wrapper::ReadFromFile(GetFileName(ArmatureName::PALADIN), armData);
		pLocalArm = new ArmData(ArmatureName::PALADIN, armData);
		this->poLoadedArmatures->Add(*pLocalArm);

		ProtoData_Wrapper::ReadFromFile(GetFileName(ArmatureName::PUMPKIN_HULK), armData);
		pLocalArm = new ArmData(ArmatureName::PUMPKIN_HULK, armData);
		this->poLoadedArmatures->Add(*pLocalArm);

		ProtoData_Wrapper::ReadFromFile(GetFileName(ArmatureName::VANGUARD), armData);
		pLocalArm = new ArmData(ArmatureName::VANGUARD, armData);
		this->poLoadedArmatures->Add(*pLocalArm);

		ProtoData_Wrapper::ReadFromFile(GetFileName(ArmatureName::ZOMBIE_GIRL), armData);
		pLocalArm = new ArmData(ArmatureName::ZOMBIE_GIRL, armData);
		this->poLoadedArmatures->Add(*pLocalArm);
	}


	NodeBase* ArmatureManager::CreateNode()
	{
		return new Armature();
	}

	ArmatureManager* ArmatureManager::GetInstance()
	{
		assert(instance);
		return instance;
	}

	void ArmatureManager::Clear()
	{
		this->BaseClear();
	}
}
