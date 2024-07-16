#ifndef CAMERA_MAN_H
#define CAMERA_MAN_H


#include "ManagerBase.h"
#include "EngineNames.h"
#include "Camera.h"
#include "Camera2DManager.h"
#include "Camera3DManager.h"

class Game;

namespace Uncertain
{

	class CameraManager
	{

	public:
		CameraManager() = delete;
		CameraManager(const CameraManager&) = delete;
		CameraManager& operator =(const CameraManager&) = delete;

		static void Create(Game& game, int initialReserve = 2, int deltaGrow = 1);
		static void Destroy();

		static void Update();

		static Camera* Add(CameraName name);
		static void Remove(Camera& camera);

		static Camera3D* GetActive3D();
		static void SetActive3D(CameraName name);
		static Camera3D* Find3D(CameraName name);
		static void SetDefault3D(CameraName name);
		static void CycleActive3D();

		static Camera2D* Find2D(CameraName name);
		static void SetActive2D(CameraName name);
		static Camera2D* GetActive2D();
		static void SetDefault2D(CameraName name);
		static void CycleActive2D();
		
		static void PrintAll();
		static void PrintActive3DCam();

		static void ResetDefault();
		static void Translate(Axis axis, Camera::TYPE type, const float distance = 0.0f, CameraName name = CameraName::UNINITIALIZED);
		static void Rotate(Axis axis, Camera::TYPE type, const float radians = 0.0f, CameraName name = CameraName::UNINITIALIZED);

	private:
		CameraManager(Game& game, int initialReserve, int deltaGrow);
		static CameraManager* GetInstance();
		~CameraManager();

		static CameraManager* instance;

		Camera3DManager* Manager3D;
		Camera2DManager* Manager2D;

		Game* pGame;
		Camera* poCompNode;
		CameraHelperData* poHelperData;

	};
}



#endif