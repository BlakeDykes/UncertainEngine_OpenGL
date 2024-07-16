#ifndef ARMATURE_MANAGER_H
#define ARMATURE_MANAGER_H

#include "ManagerBase.h"
#include "EngineNames.h"
#include "MathEngine.h"

class ShaderObject;

namespace Uncertain
{
	class AnimController;
	class Armature;
	class ArmData;
	class DLinkManager;

	class ArmatureManager : public ManagerBase
	{
	public:
		
		ArmatureManager() = delete;
		ArmatureManager(const ArmatureManager&) = delete;
		ArmatureManager& operator =(const ArmatureManager&) = delete;

		static void Update();

		static void Create(int initialReserved = 5, int deltaGrow = 5);
		static void Destroy();

		static Armature* Add(ArmatureName name, const AnimController& animController);
		static Armature* Add(const ArmData& data, const AnimController& animController);

		static ArmData* FindArmData(ArmatureName name);

		static void Remove(Armature& pNode);

	protected:
		virtual NodeBase* CreateNode() override;

	private:
		ArmData* privFindArmData(ArmatureName name);
		void LoadArmatureData();
		ArmatureManager(int initialReserved, int deltaGrow);
		static ArmatureManager* GetInstance();
		virtual ~ArmatureManager();
		void Clear();

		static ArmatureManager* instance;


		Armature* pCompNode;
		ShaderObject* pBoneComputeSO;

		DLinkManager* poLoadedArmatures;
		
	};
}


#endif // !ARMATURE_MANAGER_H
