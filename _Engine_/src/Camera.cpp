#include "sb7.h"
#include "MathEngine.h"
#include "Camera.h"

namespace Uncertain
{

	// default constructor
	Camera::Camera(TYPE type)
		: CameraType(type), Name(CameraName::UNINITIALIZED)
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::updateCamera(void)
	{
		//Define in base class
		assert(false);
	}

	void Camera::GetHelper(CameraHelperData& helperData)
	{
		this->getPos(helperData.pos);
		this->getLookAt(helperData.tar);
		this->getUp(helperData.upNorm);
		helperData.up = helperData.pos + helperData.upNorm;

		helperData.forwardNorm = helperData.tar - helperData.pos;
		helperData.forwardNorm.norm();

		this->getRight(helperData.rightNorm);

	}

	void Camera::SetHelper(CameraHelperData& helperData)
	{
		Vec3 upVec3 = helperData.up - helperData.pos;
		this->setOrientAndPosition(upVec3, helperData.tar, helperData.pos);
	}

	int Camera::getScreenWidth() const
	{
		return this->viewport_width;
	}

	int Camera::getScreenHeight() const
	{
		return this->viewport_height;
	}

	// Just a pass through to setup the view port screen sub window
	void Camera::setViewport(const int inX, const int inY, const int width, const int height)
	{
		this->viewport_x = inX;
		this->viewport_y = inY;
		this->viewport_width = width;
		this->viewport_height = height;

		this->privSetViewState();
	};

	// Simple wrapper
	void Camera::privSetViewState(void)
	{
		glViewport(this->viewport_x, this->viewport_y, this->viewport_width, this->viewport_height);
	};

	void Camera::privUpdateProjectionMat4(void)
	{
		// Define in base class
		assert(false);
	}

	void Camera::setOrientAndPosition(const Vec3& inUp, const Vec3& inLookAt, const Vec3& inPos)
	{
		assert(((unsigned int)&inUp & 0xF) == 0x0);
		assert(((unsigned int)&inPos & 0xF) == 0x0);
		assert(((unsigned int)&inLookAt & 0xF) == 0x0);

		// Remember the up, lookAt and right are unit, and are perpendicular.
		// Treat lookAt as king, find Right Vec3, then correct Up to insure perpendiculare.
		// Make sure that all Vec3ors are unit Vec3ors.
		this->vLookAt = inLookAt;

		// Point out of the screen into your EYE
		this->vDir = (inPos - inLookAt).getNorm();

		// Clean up the Vec3ors (Right hand rule)
		this->vRight = inUp.cross(this->vDir).getNorm();

		this->vUp = this->vDir.cross(this->vRight).getNorm();

		this->vPos = inPos;
	};

	void Camera::proUpdateViewMat4(void)
	{
		// This functions assumes the your vUp, vRight, vDir are still unit
		// And perpendicular to each other
		//  view = Rot(orient) * trans(-(eye.basis) )

		this->viewMat4[m0] = this->vRight[x];
		this->viewMat4[m1] = this->vUp[x];
		this->viewMat4[m2] = this->vDir[x];
		this->viewMat4[m3] = 0.0f;

		this->viewMat4[m4] = this->vRight[y];
		this->viewMat4[m5] = this->vUp[y];
		this->viewMat4[m6] = this->vDir[y];
		this->viewMat4[m7] = 0.0f;

		this->viewMat4[m8] = this->vRight[z];
		this->viewMat4[m9] = this->vUp[z];
		this->viewMat4[m10] = this->vDir[z];
		this->viewMat4[m11] = 0.0f;

		// Change of basis (dot with the basis Vec3ors)
		this->viewMat4[m12] = -vPos.dot(vRight);
		this->viewMat4[m13] = -vPos.dot(vUp);
		this->viewMat4[m14] = -vPos.dot(vDir);
		this->viewMat4[m15] = 1.0f;
	};

	Camera::CullResult Camera::CullTest(GameObject* pGameObject)
	{
		// Define in derived class
		assert(false);
		AZUL_UNUSED_VAR(pGameObject);
		return CullResult::CULL_OUTSIDE;
	}

	// Accessor mess:
	Mat4& Camera::getViewMatrix(void)
	{
		return this->viewMat4;
	}

	Mat4& Camera::getProjMatrix(void)
	{
		return this->projMat4;
	}

	void Camera::getPos(Vec3& outPos) const
	{
		outPos = this->vPos;
	}

	void  Camera::getDir(Vec3& outDir) const
	{
		outDir = this->vDir;
	}

	void  Camera::getUp(Vec3& outUp) const
	{
		outUp = this->vUp;
	}

	void Camera::getLookAt(Vec3& outLookAt) const
	{
		outLookAt = this->vLookAt;
	}

	void Camera::getRight(Vec3& outRight) const
	{
		outRight = this->vRight;
	}
	void Camera::SetName(CameraName name)
	{
		this->Name = name;
	}

	const char* Camera::GetName()
	{
		return Stringify(this->Name);
	}

	bool Camera::Compare(NodeBase& pNode)
	{
		Camera* pComp = (Camera*)&pNode;

		return this->Name == pComp->Name;
	}

	void Camera::Print()
	{
		Trace::out("---Camera: 0x%p\n", this);
		Trace::out("------Name: %s\n", Stringify(this->Name));
		Debug::Print("Projection Mat4:", this->projMat4);
		Debug::Print("View Mat4:", this->viewMat4);
	}

	void Camera::Wash()
	{
		this->Name = CameraName::UNINITIALIZED;
		this->projMat4.clear();
		this->viewMat4.clear();
		this->vUp.clear();
		this->vDir.clear();
		this->vRight.clear();
		this->vPos.clear();
		this->vLookAt.clear();
		this->viewport_x = 0;
		this->viewport_y = 0;
		this->viewport_width = 0;
		this->viewport_height = 0;
	}


	void CameraHelperData::Clear()
	{
		this->pos.clear();
		this->tar.clear();
		this->up.clear();
		this->upNorm.clear();
		this->forwardNorm.clear();
		this->rightNorm.clear();
	}

	Camera::TYPE Camera::GetType(CameraName name)
	{
		switch (name)
		{
		case EngineNames::CameraName::MAIN_3D:
		case EngineNames::CameraName::AUX_3D_1:
		case EngineNames::CameraName::EDIT_NEG_X:
		case EngineNames::CameraName::EDIT_NEG_Y:
		case EngineNames::CameraName::EDIT_NEG_Z:
			return TYPE::PERSPECTIVE_3D;

		case EngineNames::CameraName::MAIN_2D:
		case EngineNames::CameraName::AUX_2D_1:
			return TYPE::ORTHO_2D;

		case EngineNames::CameraName::PROTO:
		case EngineNames::CameraName::UNINITIALIZED:
			return TYPE::UNINITIALIZED;

		default:
			//Add name to switch
			assert(false);
			return TYPE::UNINITIALIZED;
			break;
		}
	}
}