#include "Camera2DManager.h"
#include "DLinkManager.h"
#include "DLinkIterator.h"
#include "Camera.h"

namespace Uncertain
{
	Camera2DManager::Camera2DManager(int initialReserve, int deltaGrow)
		: ManagerBase(*new DLinkManager(), *new DLinkManager()), pActive(nullptr)
	{
		// Defaults defined here to respect alignment
		this->DEFAULT_UP_VEC = Vec3(0.0f, 1.0f, 0.0f);
		this->DEFAULT_LOOK_AT_VEC = Vec3(0.0f, 0.0f, 0.0f);
		this->DEVAULT_POS_VEC = Vec3(0.0f, 0.0f, 2.0f);
		this->DEFAULT_CAMERA_SPEED = 0.03f;
		this->DEFAULT_CAMERA_ROTATE_SPEED = .03f;
		this->DEFAULT_Z_MIN = 0.25f;
		this->DEFAULT_Z_MAX = 1000.0f;

		this->poCompNode = new Camera2D();
		this->SetReserve(initialReserve, deltaGrow);
	}

	Camera2DManager* Camera2DManager::Create(int intialReserve, int deltaGrow, Engine::APPINFO info)
	{
		Camera2DManager* pMan = new Camera2DManager(intialReserve, deltaGrow);

		pMan->Add(CameraName::MAIN_2D, info);

		return pMan;
	}

	Camera2DManager::~Camera2DManager()
	{
		delete this->poCompNode;
	}

	void Camera2DManager::Update()
	{
		if (this->pActive)
		{
			this->pActive->updateCamera();
		}
	}

	Camera2D* Camera2DManager::Add(CameraName name, Engine::APPINFO info)
	{
		Camera2D* pCam = (Camera2D*)BaseAdd();

		pCam->SetName(name);
		this->SetDefault(*pCam, info);

		if (this->pActive == nullptr)
		{
			this->pActive = pCam;
		}

		return pCam;
	}

	void Camera2DManager::Remove(Camera& camera)
	{
		this->BaseRemove(camera);
	}

	Camera2D* Camera2DManager::Find(CameraName name)
	{
		this->poCompNode->SetName(name);

		return (Camera2D*)this->BaseFind(*this->poCompNode);
	}

	void Camera2DManager::SetActive(CameraName name)
	{
		Camera2D* pCam = this->Find(name);
		assert(pCam);

		this->pActive = pCam;
	}

	void Camera2DManager::CycleActive()
	{
		assert(this->pActive);

		this->pActive = (Camera2D*)this->pActive->GetNext();

		if (!this->pActive)
		{
			this->pActive = (Camera2D*)this->poActive->GetFirst();
		}
	}

	void Camera2DManager::ResetDefault(Engine::APPINFO info)
	{
		this->SetDefault(*this->pActive, info);
	}

	void Camera2DManager::SetDefault(CameraName name, Engine::APPINFO info)
	{
		Camera2D* pCam = this->Find(name);
		assert(pCam);

		pCam->setViewport(0, 0, info.windowWidth, info.windowHeight);

		pCam->setOrtho((float)-info.windowWidth / 2.0f, (float)info.windowWidth / 2.0f,
						(float)-info.windowHeight / 2.0f, (float)info.windowHeight/ 2.0f,
						Camera2DManager::DEFAULT_Z_MIN, Camera2DManager::DEFAULT_Z_MAX);
		
		pCam->setOrientAndPosition(Camera2DManager::DEFAULT_UP_VEC,
									Camera2DManager::DEFAULT_LOOK_AT_VEC,
									Camera2DManager::DEVAULT_POS_VEC);
	}

	void Camera2DManager::SetDefault(Camera2D& cam, Engine::APPINFO info)
	{
		cam.setViewport(0, 0, info.windowWidth, info.windowHeight);

		cam.setOrtho((float)-info.windowWidth / 2.0f, (float)info.windowWidth / 2.0f,
						(float)-info.windowHeight / 2.0f, (float)info.windowHeight / 2.0f,
						Camera2DManager::DEFAULT_Z_MIN, Camera2DManager::DEFAULT_Z_MAX);

		cam.setOrientAndPosition(Camera2DManager::DEFAULT_UP_VEC,
									Camera2DManager::DEFAULT_LOOK_AT_VEC,
									Camera2DManager::DEVAULT_POS_VEC);
	}

	void Camera2DManager::PrintAll()
	{
		Trace::out("\n");
		Trace::out("---------------------------\n");
		Trace::out("------- 2D Cameras --------\n");
		Trace::out("---------------------------\n");

		BasePrintAll();
	}

	NodeBase* Camera2DManager::CreateNode()
	{
		return new Camera2D();
	}

}