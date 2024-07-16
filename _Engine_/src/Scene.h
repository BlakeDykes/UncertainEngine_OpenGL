#ifndef SCENE_H
#define SCENE_H

namespace Uncertain
{
	class Scene
	{
	public:

		Scene() = default;
		Scene(const Scene&) = delete;
		const Scene& operator=(const Scene&) = delete;
		virtual ~Scene() = default;

		virtual void Load() = 0;
		virtual void Unload() = 0;
		virtual void Update() = 0;
	};
}

#endif // !SCENE_H
