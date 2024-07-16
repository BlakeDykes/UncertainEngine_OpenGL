#ifndef ARMATURE_H
#define ARMATURE_H

#include "sb7.h"
#include "PCSTree.h"
#include "MathEngine.h"
#include "EngineNames.h"
#include "SSBO.h"
#include "DLink.h"

class ShaderObject;
class ArmatureData;

namespace Uncertain
{
	class AnimController;
	struct Bone;

	// Local Armature data managed by ArmatureManager
	class ArmData : public DLink
	{
	public:
		ArmatureName Name;
		unsigned int JointDepth;
		unsigned int JointCount;
		unsigned int* poJointTable;

		ArmData();
		ArmData(ArmatureName name, ArmatureData& data);
		ArmData(const ArmData&) = delete;
		const ArmData& operator=(const ArmData&) = delete;
		virtual ~ArmData();

		void Set(ArmatureName name, ArmatureData& data);

		virtual void Wash() override;
		virtual bool Compare(NodeBase& pNode) override;
		virtual const char* GetName() override;
	};

	// Armature objects used to update BoneWorldMat
	class Armature : public DLink
	{
	public:
		Armature();
		Armature(const Armature&) = delete;
		Armature& operator =(const Armature&) = delete;
		virtual ~Armature();

		void Update(ShaderObject* pBoneComputeSO);

		void Set(const AnimController& pAnimController, const ArmData& armData);

		void MarkForDelete() { bShouldDelete = true; }
		bool ShouldDelete() const { return this->bShouldDelete; }

		SSBO& GetBoneResultBuffer() { return *this->poSSBO_BoneWorldBuf; }
		unsigned int GetJointCount() const { return this->pJointData->JointCount; }

		virtual void Wash() override;
		virtual bool Compare(NodeBase& pNode) override;
		virtual const char* GetName() override;

	private:

		SSBO* pSSBO_LocalBoneBuf; 
		SSBO* poSSBO_JointTableBuf;
		SSBO* poSSBO_BoneWorldBuf; 

		const ArmData* pJointData;
		Mat4* poBoneWorld;

		const AnimController* pAnimController;

		bool bShouldDelete;

	};

}


#endif // !ARMATURE_H
