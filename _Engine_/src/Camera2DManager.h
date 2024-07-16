#ifndef CAM_2D_MANAGER_H
#define CAM_2D_MANAGER_H

#include "ManagerBase.h"
#include "EngineNames.h"
#include "Camera2D.h"
#include "MathEngine.h"
#include "Engine.h"

namespace Uncertain
{
	class Camera2DManager : public ManagerBase, public Align16
	{
	public:
		
		Camera2DManager() = delete;
		Camera2DManager(const Camera2DManager&) = delete;
		Camera2DManager& operator=(const Camera2DManager&) = delete;
		virtual ~Camera2DManager();

		static Camera2DManager* Create(int initialReserve, int deltaGrow, Engine::APPINFO info);

		void Update();

		Camera2D* GetActive() const { return this->pActive; }
		void SetActive(CameraName name);
		void CycleActive();

		Camera2D* Add(CameraName name, Engine::APPINFO info);
		void Remove(Camera& camera);
		Camera2D* Find(CameraName name);

		void ResetDefault(Engine::APPINFO info);
		void SetDefault(CameraName name, Engine::APPINFO info);
		void SetDefault(Camera2D& cam, Engine::APPINFO info);

		float GetDefaultMoveSpeed() const { return this->DEFAULT_CAMERA_SPEED; }
		float GetDefaultRotateSpeed() const { return this->DEFAULT_CAMERA_ROTATE_SPEED; }

		void PrintAll();

	protected:
		virtual NodeBase* CreateNode() override;

	private:
		Camera2DManager(int initialReserve, int deltaGrow);

		Vec3 DEFAULT_UP_VEC;
		Vec3 DEFAULT_LOOK_AT_VEC;
		Vec3 DEVAULT_POS_VEC;
		float DEFAULT_CAMERA_SPEED;
		float DEFAULT_CAMERA_ROTATE_SPEED;
		float DEFAULT_Z_MIN;
		float DEFAULT_Z_MAX;
		Camera2D* pActive;
		Camera2D* poCompNode;
		char padding[8];
	};
}

#endif // !CAM_2D_MANAGER_H
