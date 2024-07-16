#ifndef SCENE_MS3_H
#define SCENE_MS3_H

#include "Scene.h"
#include "_Time.h"
#include "_Timer.h"

class GameObjectFont;

namespace Uncertain
{
	class Scene_MS3 : public Scene
	{
	public:
		Scene_MS3();
		Scene_MS3(const Scene_MS3&) = delete;
		const Scene_MS3& operator=(const Scene_MS3&) = delete;
		virtual ~Scene_MS3() = default;

		virtual void Load();
		virtual void Unload();
		virtual void Update();

	private:
		_Time DebugTime;
		_Timer DebugTimer;
		GameObjectFont* pCountFont;
		const char* pCountPreMessage;
		char CounterMessageBuffer[64];
	};
}



#endif // !SCENE_MS3_H
