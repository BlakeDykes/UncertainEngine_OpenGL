#include "Camera3DManager.h"
#include "DLinkManager.h"
#include "DLinkIterator.h"
#include "Camera.h"

namespace Uncertain
{

	Camera3DManager::Camera3DManager(int initialReserve, int deltaGrow)
		: ManagerBase(*new DLinkManager(), *new DLinkManager()), pActive(nullptr)
	{
		// Defaults defined here to respect alignment
		this->DEFAULT_UP_VEC = Vec3(0.0f, 1.0f, 0.0f);
		this->DEFAULT_LOOK_AT_VEC = Vec3(0.0f, 0.0f, 0.0f);
		this->DEVAULT_POS_VEC = Vec3(0.0f, 0.0f, 0.25f);
		this->DEFAULT_CAMERA_SPEED = 0.01f;
		this->DEFAULT_CAMERA_ROTATE_SPEED = .01f;
		this->DEFAULT_FOV = 50.0f;
		this->DEFAULT_Z_MIN = 0.1f;
		this->DEFAULT_Z_MAX = 500.0f;

		this->poCompNode = new Camera3D();
		this->SetReserve(initialReserve, deltaGrow);
	}

	Camera3DManager* Camera3DManager::Create(int intialReserve, int deltaGrow, Engine::APPINFO info)
	{
		Camera3DManager* pMan = new Camera3DManager(intialReserve, deltaGrow);

		pMan->Add(CameraName::MAIN_3D, info);

		return pMan;
	}

	Camera3DManager::~Camera3DManager()
	{
		delete this->poCompNode;
	}

	void Camera3DManager::Update()
	{
		if (this->pActive)
		{
			this->pActive->updateCamera();
		}
	}

	Camera3D* Camera3DManager::Add(CameraName name, Engine::APPINFO info)
	{
		Camera3D* pCam = (Camera3D*)BaseAdd();

		pCam->SetName(name);
		this->SetDefault(*pCam, info);

		if (this->pActive == nullptr)
		{
			this->pActive = pCam;
		}

		return pCam;
	}

	void Camera3DManager::Remove(Camera& camera)
	{
		this->BaseRemove(camera);
	}

	Camera3D* Camera3DManager::Find(CameraName name)
	{
		this->poCompNode->SetName(name);

		return (Camera3D*)this->BaseFind(*this->poCompNode);
	}

	void Camera3DManager::SetActive(CameraName name)
	{
		Camera3D* pCam = this->Find(name);
		assert(pCam);

		this->pActive = pCam;
	}

	void Camera3DManager::CycleActive()
	{
		assert(this->pActive);

		this->pActive = (Camera3D*)this->pActive->GetNext();

		if (!this->pActive)
		{
			this->pActive = (Camera3D*)this->poActive->GetFirst();
		}
	}

	void Camera3DManager::ResetDefault(Engine::APPINFO info)
	{
		this->SetDefault(*this->pActive, info);
	}

	void Camera3DManager::SetDefault(CameraName name, Engine::APPINFO info)
	{
		Camera3D* pCam = this->Find(name);
		assert(pCam);

		pCam->setViewport(0, 0, info.windowWidth, info.windowHeight);

		pCam->setPerspective(this->DEFAULT_FOV, 
								(float)info.windowWidth / (float)info.windowHeight, 
								this->DEFAULT_Z_MIN,
								this->DEFAULT_Z_MAX);

		pCam->setOrientAndPosition(this->DEFAULT_UP_VEC,
									this->DEFAULT_LOOK_AT_VEC, 
									this->DEVAULT_POS_VEC);
		pCam->updateCamera();
	}

	void Camera3DManager::SetDefault(Camera3D& cam, Engine::APPINFO info)
	{
		cam.setViewport(0, 0, info.windowWidth, info.windowHeight);
		cam.setPerspective(this->DEFAULT_FOV,
							(float)info.windowWidth / (float)info.windowHeight,
							this->DEFAULT_Z_MIN,
							this->DEFAULT_Z_MAX);

		cam.setOrientAndPosition(this->DEFAULT_UP_VEC,
									this->DEFAULT_LOOK_AT_VEC,
									this->DEVAULT_POS_VEC);

		cam.updateCamera();
	}

	void Camera3DManager::PrintAll()
	{
		Trace::out("\n");
		Trace::out("---------------------------\n");
		Trace::out("------- 3D Cameras --------\n");
		Trace::out("---------------------------\n");

		BasePrintAll();
	}

	void Camera3DManager::PrintActive()
	{
		Vec3 pos;
		Vec3 lookAt;
		Vec3 up;

		pActive->getPos(pos);
		pActive->getLookAt(lookAt);
		pActive->getUp(up);

		this->pActive->updateCamera();

		Trace::out("--- Active Orient/Position\n");
		Trace::out("------	 vLookAt - (%f, %f, %f)\n", lookAt.x(), lookAt.y(), lookAt.z());
		Trace::out("------		 vUp - (%f, %f, %f)\n", up.x(), up.y(), up.z());
		Trace::out("------		vPos - (%f, %f, %f)\n", pos.x(), pos.y(), pos.z());
	}

	NodeBase* Camera3DManager::CreateNode()
	{
		return new Camera3D();
	}

}