#ifndef SCENE_DEMO_ONE_H
#define SCENE_DEMO_ONE_H

#include "Scene.h"
#include "AnimTime.h"
#include "AnimTimer.h"

class GameObjectFont;

namespace Azul
{
	class Scene_Demo1 : public Scene
	{
	public:
		Scene_Demo1();
		Scene_Demo1(const Scene_Demo1&) = delete;
		const Scene_Demo1& operator=(const Scene_Demo1&) = delete;
		virtual ~Scene_Demo1() = default;

		virtual void Load();
		virtual void Unload();
		virtual void Update();

	private:

	};
}



#endif // !SCENE_DEMO_ONE_H
