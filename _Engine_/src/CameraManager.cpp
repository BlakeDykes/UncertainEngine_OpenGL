#include "CameraManager.h"
#include "DLinkManager.h"
#include "Game.h"
#include "DLinkIterator.h"
#include "Camera2DManager.h"
#include "Camera3DManager.h"

namespace Uncertain
{


	CameraManager* CameraManager::instance = nullptr;

	CameraManager::CameraManager(Game& game, int initialReserve, int deltaGrow)
		: pGame(&game)
	{
		this->poHelperData = new CameraHelperData();

		this->Manager3D = Camera3DManager::Create(initialReserve, deltaGrow, this->pGame->GetInfo());
		this->Manager2D = Camera2DManager::Create(initialReserve, deltaGrow, this->pGame->GetInfo());
	}

	CameraManager::~CameraManager()
	{
		delete this->poHelperData;
	}

	void CameraManager::Create(Game& game, int initialReserve, int deltaGrow)
	{
		assert(!instance);

		if (!instance)
		{
			instance = new CameraManager(game, initialReserve, deltaGrow);
		}
	}

	void CameraManager::Destroy()
	{
		CameraManager* inst = CameraManager::GetInstance();

		delete inst->Manager2D;
		delete inst->Manager3D;

		delete inst;

		CameraManager::instance = nullptr;
	}

	void CameraManager::Update()
	{
		CameraManager* inst = CameraManager::GetInstance();

		inst->Manager3D->Update();
		inst->Manager2D->Update();
	}

	Camera3D* CameraManager::GetActive3D()
	{
		CameraManager* inst = CameraManager::GetInstance();

		return inst->Manager3D->GetActive();
	}

	void CameraManager::SetActive3D(CameraName name)
	{
		CameraManager* inst = CameraManager::GetInstance();

		inst->Manager3D->SetActive(name);
	}

	Camera3D* CameraManager::Find3D(CameraName name)
	{
		CameraManager* inst = CameraManager::GetInstance();

		return inst->Manager3D->Find(name);
	}

	void CameraManager::SetActive2D(CameraName name)
	{
		CameraManager* inst = CameraManager::GetInstance();

		inst->Manager2D->SetActive(name);
	}

	void CameraManager::CycleActive3D()
	{
		CameraManager* inst = CameraManager::GetInstance();

		inst->Manager3D->CycleActive();
	}

	Camera2D* CameraManager::GetActive2D()
	{
		CameraManager* inst = CameraManager::GetInstance();
		
		return inst->Manager2D->GetActive();
	}

	Camera2D* CameraManager::Find2D(CameraName name)
	{
		CameraManager* inst = CameraManager::GetInstance();

		return inst->Manager2D->Find(name);
	}

	void CameraManager::CycleActive2D()
	{
		CameraManager* inst = CameraManager::GetInstance();

		inst->Manager2D->CycleActive();
	}

	Camera* CameraManager::Add(CameraName name)
	{
		CameraManager* inst = CameraManager::GetInstance();

		Camera::TYPE type = Camera::GetType(name);

		switch (type)
		{
		case Uncertain::Camera::TYPE::ORTHO_2D:
			return inst->Manager2D->Add(name, inst->pGame->GetInfo());
		case Uncertain::Camera::TYPE::PERSPECTIVE_3D:
			return inst->Manager3D->Add(name, inst->pGame->GetInfo());
		case Uncertain::Camera::TYPE::UNINITIALIZED:
		default:
			assert(false);
			return nullptr;
		}
	}

	void CameraManager::Remove(Camera& pNode)
	{
		CameraManager* inst = CameraManager::GetInstance();

		Camera::TYPE type = pNode.GetType();
		
		switch (type)
		{
		case Uncertain::Camera::TYPE::ORTHO_2D:
			inst->Manager2D->Remove(pNode);
			break;
		case Uncertain::Camera::TYPE::PERSPECTIVE_3D:
			inst->Manager3D->Remove(pNode);
			break;
		case Uncertain::Camera::TYPE::UNINITIALIZED:
		default:
			assert(false);
			break;
		}
	}

	void CameraManager::PrintAll()
	{
		CameraManager* inst = CameraManager::GetInstance();

		inst->Manager3D->PrintAll();
		inst->Manager2D->PrintAll();
	}

	void CameraManager::PrintActive3DCam()
	{
		CameraManager* inst = CameraManager::GetInstance();

		inst->Manager3D->PrintActive();
	}

	CameraManager* CameraManager::GetInstance()
	{
		assert(instance);

		return instance;
	}

	void CameraManager::ResetDefault()
	{
		CameraManager* inst = CameraManager::GetInstance();

		inst->Manager2D->ResetDefault(inst->pGame->GetInfo());
		inst->Manager3D->ResetDefault(inst->pGame->GetInfo());
	}

	void CameraManager::SetDefault3D(CameraName name)
	{
		CameraManager* inst = CameraManager::GetInstance();

		inst->Manager3D->SetDefault(name, inst->pGame->GetInfo());
	}

	void CameraManager::SetDefault2D(CameraName name)
	{
		CameraManager* inst = CameraManager::GetInstance();

		Engine::APPINFO info = inst->pGame->GetInfo();

		inst->Manager2D->SetDefault(name, info);
	}

	void CameraManager::Translate(Axis axis, Camera::TYPE type, float distance, CameraName name)
	{
		CameraManager* inst = CameraManager::GetInstance();

		Camera* pCam = nullptr;

		float delta = distance;

		switch (type)
		{
		case Uncertain::Camera::TYPE::ORTHO_2D:
			if (name == CameraName::UNINITIALIZED)
			{
				pCam = (Camera*)inst->Manager2D->GetActive();
			}
			else
			{
				pCam = inst->Manager2D->Find(name);
			}
			if (delta == 0.0f)
			{
				delta = inst->Manager2D->GetDefaultMoveSpeed();
			}
			break;
		case Uncertain::Camera::TYPE::PERSPECTIVE_3D:
			if (name == CameraName::UNINITIALIZED)
			{
				pCam = (Camera*)inst->Manager3D->GetActive();
			}
			else
			{
				pCam = inst->Manager3D->Find(name);
			}
			if (delta == 0.0f)
			{
				delta = inst->Manager3D->GetDefaultMoveSpeed();
			}
			break;
		case Uncertain::Camera::TYPE::UNINITIALIZED:
		default:
			assert(false);
			break;
		}

		if (axis == Axis::NEG_X || axis == Axis::NEG_Y || axis == Axis::NEG_Z)
		{
			delta *= -1.0f;
		}

		assert(pCam);

		inst->poHelperData->Clear();

		pCam->GetHelper(*inst->poHelperData);

		switch (axis)
		{
		case EngineNames::Axis::NEG_X:
		case EngineNames::Axis::X:
			inst->poHelperData->pos = inst->poHelperData->pos + delta * inst->poHelperData->rightNorm;
			inst->poHelperData->tar = inst->poHelperData->tar + delta * inst->poHelperData->rightNorm;
			inst->poHelperData->up = inst->poHelperData->up + delta * inst->poHelperData->rightNorm;
			break;
		case EngineNames::Axis::NEG_Y:
		case EngineNames::Axis::Y:
			inst->poHelperData->pos = inst->poHelperData->pos + delta * inst->poHelperData->upNorm;
			inst->poHelperData->tar = inst->poHelperData->tar + delta * inst->poHelperData->upNorm;
			inst->poHelperData->up = inst->poHelperData->up + delta * inst->poHelperData->upNorm;
			break;
		case EngineNames::Axis::NEG_Z:
		case EngineNames::Axis::Z:
			assert(pCam->GetType() != Camera::TYPE::ORTHO_2D);
			inst->poHelperData->pos = inst->poHelperData->pos + delta * inst->poHelperData->forwardNorm;
			inst->poHelperData->tar = inst->poHelperData->tar + delta * inst->poHelperData->forwardNorm;
			inst->poHelperData->up = inst->poHelperData->up + delta * inst->poHelperData->forwardNorm;
			break;
		default:
			assert(false);
			break;
		}

		pCam->SetHelper(*inst->poHelperData);

		//Trace::out("Look At - {%f, %f, %f}\n", inst->poHelperData->tar.x(), inst->poHelperData->tar.y(), inst->poHelperData->tar.z());
		//Trace::out("Pos     - {%f, %f, %f}\n", inst->poHelperData->pos.x(), inst->poHelperData->pos.y(), inst->poHelperData->pos.z());
	}

	void CameraManager::Rotate(Axis axis,  Camera::TYPE type, float radians, CameraName name)
	{
		CameraManager* inst = CameraManager::GetInstance();

		Camera* pCam = nullptr;

		float delta = radians;

		switch (type)
		{
		case Uncertain::Camera::TYPE::ORTHO_2D:
			if (name == CameraName::UNINITIALIZED)
			{
				pCam = (Camera*)inst->Manager2D->GetActive();
			}
			else
			{
				pCam = inst->Manager2D->Find(name);
			}
			if (delta == 0.0f)
			{
				delta = inst->Manager2D->GetDefaultRotateSpeed();
			}
			break;
		case Uncertain::Camera::TYPE::PERSPECTIVE_3D:
			if (name == CameraName::UNINITIALIZED)
			{
				pCam = inst->Manager3D->GetActive();
			}
			else
			{
				pCam = inst->Manager3D->Find(name);
			}
			if (delta == 0.0f)
			{
				delta = inst->Manager3D->GetDefaultRotateSpeed();
			}
			break;
		case Uncertain::Camera::TYPE::UNINITIALIZED:
		default:
			assert(false);
			break;
		}

		assert(pCam);

		inst->poHelperData->Clear();

		pCam->GetHelper(*inst->poHelperData);

		Mat4 Trans(Mat4::Trans::XYZ, inst->poHelperData->tar);
		Mat4 NegTrans(Mat4::Trans::XYZ, -inst->poHelperData->tar);

		Mat4 Rot;

		if (axis == Axis::NEG_X || axis == Axis::NEG_Y || axis == Axis::NEG_Z)
		{
			delta *= -1.0f;
		}

		switch (axis)
		{
		case EngineNames::Axis::NEG_X:
		case EngineNames::Axis::X:
			Rot.set(Mat4::Rot::AxisAngle, inst->poHelperData->rightNorm, delta);
			break;
		case EngineNames::Axis::NEG_Y:
		case EngineNames::Axis::Y:
			Rot.set(Mat4::Rot::AxisAngle, inst->poHelperData->upNorm, delta);
			break;
		case EngineNames::Axis::NEG_Z:
		case EngineNames::Axis::Z:
			Rot.set(Mat4::Rot::AxisAngle, inst->poHelperData->forwardNorm, delta);
			break;
		default:
			assert(false);
			break;
		}

		Mat4 M = NegTrans * Rot * Trans;

		inst->poHelperData->up *= M;
		inst->poHelperData->pos *= M;
		inst->poHelperData->tar *= M;

		pCam->SetHelper(*inst->poHelperData);

	}
}



