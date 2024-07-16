#include "Armature.h"
#include "BoneMap.h"
#include "Mesh.h"
#include "AnimController.h"
#include "Bone.h"
#include "SSBO.h"
#include "ShaderObject.h"
#include "ShaderManager.h"
#include "ArmatureData.h"

namespace Uncertain
{
	Armature::Armature()
		: pSSBO_LocalBoneBuf(), poSSBO_JointTableBuf(new SSBO()), poSSBO_BoneWorldBuf(new SSBO()),
		 pJointData(nullptr), poBoneWorld(nullptr), pAnimController(nullptr), bShouldDelete(true)
	{
	}

	Armature::~Armature()
	{
		if (poBoneWorld)
		{
			delete[] poBoneWorld;
			poBoneWorld = nullptr;
		}

		delete poSSBO_BoneWorldBuf;
		delete poSSBO_JointTableBuf;
	}

	void Armature::Update(ShaderObject* pBoneComputeSO)
	{
		assert(pJointData->JointCount == pAnimController->GetNumBones());

		this->pSSBO_LocalBoneBuf = pAnimController->GetBoneResultSSBO();

		glBindVertexArray(0);

		pBoneComputeSO->SetActive();
		
		// Bind and Dispatch
		pSSBO_LocalBoneBuf->Bind(0);
		poSSBO_JointTableBuf->Bind(1);
		poSSBO_BoneWorldBuf->Bind(2);

		glUniform1ui(pBoneComputeSO->GetLocation("boneCount"), (GLuint)pJointData->JointCount);
		glUniform1ui(pBoneComputeSO->GetLocation("jointDepth"), (GLuint)pJointData->JointDepth);

		pBoneComputeSO->Dispatch(1 + (pJointData->JointCount/ 10), 1, 1);

		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	}

	void Armature::Set(const AnimController& animController, const ArmData& armData)
	{
		bShouldDelete = false;

		assert(armData.JointCount == animController.GetNumBones());

		this->pJointData = &armData;

		poBoneWorld = new Mat4[pJointData->JointCount]();
		this->pAnimController = &animController;

		this->poSSBO_JointTableBuf->Set(pJointData->JointCount * pJointData->JointDepth, sizeof(unsigned int), pJointData->poJointTable, GL_STATIC_DRAW);
		this->poSSBO_BoneWorldBuf->Set(pJointData->JointCount, sizeof(Mat4), poBoneWorld, GL_DYNAMIC_COPY);
	}
	
	void Armature::Wash()
	{
		this->bShouldDelete = true;
		this->pAnimController = nullptr;
		this->pJointData = nullptr;

		if (this->poBoneWorld)
		{
			delete[] poBoneWorld;
			poBoneWorld = nullptr;
		}
	}

	bool Armature::Compare(NodeBase& pNode)
	{
		Armature* pComp = (Armature*)&pNode;

		if (!this->pAnimController && !pComp->pAnimController)
		{
			return this->pJointData->Name == pComp->pJointData->Name;
		}

		if ((this->pAnimController && !pComp->pAnimController) ||
			!pAnimController && pComp->pAnimController)
		{
			return false;
		}

		return this->pJointData->Name == pComp->pJointData->Name &&
					this->pAnimController->GetHandle() == pComp->pAnimController->GetHandle();
	}

	const char* Armature::GetName()
	{
		return Stringify(pJointData->Name);
	}



	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	// ----- ArmData implementation begins
	// -----------------------------------------------------------------------------
	// -----------------------------------------------------------------------------
	ArmData::ArmData()
		: Name(ArmatureName::UNINITIALIZED), JointDepth(0), JointCount(0), poJointTable(nullptr)
	{
	}

	ArmData::ArmData(ArmatureName name, ArmatureData& data)
	{
		this->Name = name;
		this->JointCount = data.JointCount;
		this->JointDepth = data.JointDepth;

		size_t tableSize = JointCount * JointDepth;
		this->poJointTable = new unsigned int[tableSize]();

		tableSize *= sizeof(unsigned int);

		memcpy_s(poJointTable, tableSize, data.poJointTable, tableSize);
	}

	ArmData::~ArmData() 
	{ 
		if (poJointTable) 
		{ 
			delete[] poJointTable; 
		}
	}

	void ArmData::Set(ArmatureName name, ArmatureData& data)
	{
		this->Name = name;

		if (this->poJointTable)
		{
			delete[] this->poJointTable;
		}

		this->JointCount = data.JointCount;
		this->JointDepth = data.JointDepth;
		
		size_t tableSize = JointCount * JointDepth;
		this->poJointTable = new unsigned int[tableSize]();

		tableSize *= sizeof(unsigned int);

		memcpy_s(poJointTable, tableSize, data.poJointTable, tableSize);
	}

	void ArmData::Wash()
	{
		this->Name = ArmatureName::UNINITIALIZED;
		this->JointCount = 0;
		this->JointDepth = 0;
		
		if (this->poJointTable)
		{
			delete [] this->poJointTable;
			this->poJointTable = nullptr;
		}
	}

	bool ArmData::Compare(NodeBase& pNode)
	{
		ArmData* pComp = (ArmData*)&pNode;

		return this->Name == pComp->Name;
	}
	const char* ArmData::GetName()
	{
		return Stringify(Name);
	}
}
