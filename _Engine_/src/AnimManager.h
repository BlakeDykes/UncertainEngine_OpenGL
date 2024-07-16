#ifndef ANIM_MANAGER_H
#define ANIM_MANAGER_H

#include "ManagerBase.h"
#include "AnimData.h"
#include "_Time.h"
#include "CommandQueue.h"
#include "EngineNames.h"

class GameObjectFont;
class ShaderObject;

namespace Uncertain
{
	class AnimController;
	class TimerManager;

	class AnimManager : public ManagerBase
	{
	public:

		static _Time DEFAULT_ANIM_TIME_ADJUST;
		static _Time MASTER_DELTA;

		AnimManager() = delete;
		AnimManager(const AnimManager&) = delete;
		AnimManager& operator =(const AnimManager&) = delete;

		static void Update();

		static void Create(int initialReserved = 5, int deltaGrow = 5);
		static void Destroy();

		static void AdjustAll(DIRECTION dir, _Time delta = DEFAULT_ANIM_TIME_ADJUST);
		static void ReverseAll();
		static void TogglePlayAll();

		static void AddTimedEvent(Command& command, _Time timeInitiated,
								  int timeTillTrigger, _Time::Duration triggerTimeUnit);
		static _Time GetTime();

		static AnimController* Add(_Time delta = MASTER_DELTA, GameObjectFont* debugMessage = nullptr);
		static AnimController* Find(NodeBase::Handle nodeID);
		static void Remove(AnimController& pNode);

		static void PrintAll();

	protected:
		virtual NodeBase* CreateNode() override;

	private:
		AnimManager(int initialReserved, int deltaGrow);
		static AnimManager* GetInstance();
		virtual ~AnimManager();
		void Clear();

		_Time Delta;
		static AnimManager* instance;
		AnimController* pCompNode;
		bool MasterPlay;
		CommandQueue* pCommandQueue;

		ShaderObject* pAnimMixerSO;

		TimerManager* poTimedEventManager;
	};
}

#endif // !ANIM_MANAGER_H
