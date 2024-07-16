#include "Camera2D.h"

namespace Uncertain
{
	Camera2D::Camera2D()
		: Camera(TYPE::ORTHO_2D)
	{
	}

	Camera2D::~Camera2D()
	{

	}

	void Camera2D::updateCamera()
	{
		this->privUpdateProjectionMat4();
		this->proUpdateViewMat4();
	}

	void Camera2D::setOrtho(const float xMin, const float xMax, const float yMin,
		const float yMax, const float zMin, const float zMax)
	{
		this->XMin = xMin;
		this->YMin = yMin;
		this->ZMin = zMin;
		this->XMax = xMax;
		this->YMax = yMax;
		this->ZMax = zMax;
	}

	void Camera2D::privUpdateProjectionMat4()
	{
		assert(this->CameraType == Camera::TYPE::ORTHO_2D);

		this->projMat4[m0] = 2.0f / (this->XMax - this->XMin);
		this->projMat4[m1] = 0.0f;
		this->projMat4[m2] = 0.0f;
		this->projMat4[m3] = 0.0f;

		this->projMat4[m4] = 0.0f;
		this->projMat4[m5] = 2.0f / (this->YMax - this->YMin);
		this->projMat4[m6] = 0.0f;
		this->projMat4[m7] = 0.0f;

		this->projMat4[m8] = 0.0f;
		this->projMat4[m9] = 0.0f;
		this->projMat4[m10] = -2.0f / (this->ZMax - this->ZMin);
		this->projMat4[m11] = 0.0f;

		this->projMat4[m12] = 0;
		this->projMat4[m13] = 0;
		this->projMat4[m14] = -(this->ZMax + this->ZMin) / (this->ZMax - this->ZMin);
		this->projMat4[m15] = 1.0f;
	}

	// TODO : Implement
	Camera::CullResult Camera2D::CullTest(GameObject* pGameObject)
	{
		AZUL_UNUSED_VAR(pGameObject);
		return CullResult::CULL_INSIDE;
	}
}

