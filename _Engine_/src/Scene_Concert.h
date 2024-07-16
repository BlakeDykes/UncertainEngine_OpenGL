#ifndef SCENE_DEMO_ONE_H
#define SCENE_DEMO_ONE_H

#include "Scene.h"
#include "_Time.h"
#include "_Timer.h"

class GameObjectFont;

namespace Uncertain
{
	class AnimController;

	class Scene_Concert : public Scene
	{
	public:
		Scene_Concert();
		Scene_Concert(const Scene_Concert&) = delete;
		const Scene_Concert& operator=(const Scene_Concert&) = delete;
		virtual ~Scene_Concert() = default;

		virtual void Load();
		virtual void Unload();
		virtual void Update();

	private:
		void GenerateBandTimedEvents();
		void GenerateAudienceTimedEvents();

		AnimController* pClaireController;
		AnimController* pGrandmaController;
		AnimController* pKnightController;
		AnimController* pMouseController;
		AnimController* pPumpkinController;
		AnimController* pVanguardController;
		AnimController* pPaladinController_Cheer_1;
		AnimController* pPaladinController_Cheer_2;
		AnimController* pPaladinController_Dance;
		AnimController* pPaladinController_Static;
		AnimController* pMichelleController_Cheer_1;
		AnimController* pMichelleController_Cheer_2;
		AnimController* pMichelleController_Dance;
		AnimController* pNinjaController_Cheer_1;
		AnimController* pNinjaController_Cheer_2;
		AnimController* pNinjaController_Dance;
		AnimController* pNinjaController_Static;
		AnimController* pOrtizController_Cheer_1;
		AnimController* pOrtizController_Cheer_2;
		AnimController* pOrtizController_Dance;
		AnimController* pZombieGirlController_Cheer_1;
		AnimController* pZombieGirlController_Cheer_2;
		AnimController* pZombieGirlController_Dance;

		_Time DebugTime;
		_Timer DebugTimer;
		GameObjectFont* pCountFont;
		const char* pCountPreMessage;
		char CounterMessageBuffer[64];

		_Time BandUpdateTime;
		_Time CurBandTime;
		_Timer BandTimer;

		_Time AudienceUpdateTime;
		_Time CurAudienceTime;
		_Timer AudienceTimer;


	};
}



#endif // !SCENE_DEMO_ONE_H
