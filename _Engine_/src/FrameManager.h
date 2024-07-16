#ifndef FRAME_MANAGER_H
#define FRAME_MANAGER_H


#include "ManagerBase.h"
#include "EngineNames.h"
#include "AnimNames.h"

class ShaderObject;
class DLinkManager;
class AnimData;

namespace Uncertain
{
	class FrameBucket;

	class FrameManager : public ManagerBase
	{
	public:

		FrameManager() = delete;
		FrameManager(const FrameManager&) = delete;
		FrameManager& operator =(const FrameManager&) = delete;

		static void Create(int initialReserved = 20, int deltaGrow = 5);
		static void Destroy();

		static FrameBucket* Add(AnimName name);

		static FrameBucket* Find(AnimName name);

		static void Remove(FrameBucket& pNode);

	protected:
		virtual NodeBase* CreateNode() override;

	private:
		FrameManager(int initialReserved, int deltaGrow);
		static FrameManager* GetInstance();
		virtual ~FrameManager();
		void Clear();

		static FrameManager* instance;


		FrameBucket* pCompNode;
		ShaderObject* pBoneComputeSO;
	};
}


#endif // !FRAME_MANAGER_H
