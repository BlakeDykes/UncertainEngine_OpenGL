#ifndef CAM_3D_MANAGER_H
#define CAM_3D_MANAGER_H

#include "ManagerBase.h"
#include "EngineNames.h"
#include "Camera3D.h"
#include "MathEngine.h"
#include "Engine.h"

namespace Uncertain
{
	class Camera3DManager : public ManagerBase, public Align16
	{
	public:


		Camera3DManager() = delete;
		Camera3DManager(const Camera3DManager&) = delete;
		Camera3DManager& operator=(const Camera3DManager&) = delete;
		virtual ~Camera3DManager();

		static Camera3DManager* Create(int initialReserve, int deltaGrow, Engine::APPINFO info);

		void Update();

		Camera3D* GetActive() const { return this->pActive; }
		void SetActive(CameraName name);
		void CycleActive();

		Camera3D* Add(CameraName name, Engine::APPINFO info);
		void Remove(Camera& camera);
		Camera3D* Find(CameraName name);

		void ResetDefault(Engine::APPINFO info);
		void SetDefault(CameraName name, Engine::APPINFO info);
		void SetDefault(Camera3D& cam, Engine::APPINFO info);

		float GetDefaultMoveSpeed() const { return this->DEFAULT_CAMERA_SPEED; }
		float GetDefaultRotateSpeed() const { return this->DEFAULT_CAMERA_ROTATE_SPEED; }

		void PrintAll();
		void PrintActive();

	protected:
		virtual NodeBase* CreateNode() override;

	private:
		Camera3DManager(int initialReserve, int deltaGrow);

		Vec3  DEFAULT_UP_VEC;
		Vec3  DEFAULT_LOOK_AT_VEC;
		Vec3  DEVAULT_POS_VEC;
		float DEFAULT_CAMERA_SPEED;
		float DEFAULT_CAMERA_ROTATE_SPEED;
		float DEFAULT_FOV;
		float DEFAULT_Z_MIN;
		float DEFAULT_Z_MAX;
		Camera3D* pActive;
		Camera3D* poCompNode;
		char  padding[4];
	};
}

#endif // !CAM_3D_MANAGER_H
