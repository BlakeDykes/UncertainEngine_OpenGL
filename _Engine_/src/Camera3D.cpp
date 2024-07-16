#include "Camera3D.h"
#include "BoundingSphere.h"

namespace Uncertain
{
	Camera3D::Camera3D()
		: Camera(Camera::TYPE::PERSPECTIVE_3D)
	{
		assert(((unsigned int)(&this->projMat4) & 0xF) == 0x0);
	}

	Camera3D::~Camera3D()
	{
	}

	void Camera3D::updateCamera()
	{
		// First find the near height/width, far height/width
		this->privCalcPlaneHeightWidth();

		// Find the frustum physical verts
		this->privCalcFrustumVerts();

		// find the frustum collision normals
		this->privCalcFrustumCollisionNormals();

		// update the projection Mat4
		this->privUpdateProjectionMat4();

		// update the view Mat4
		this->proUpdateViewMat4();
	}

	Camera::CullResult Camera3D::CullTest(GameObject* pGameObject)
	{
		BoundingSphere* pSphere = (BoundingSphere*)pGameObject->GetBoundingObject();
		
		CullResult result = CullResult::CULL_INSIDE;

		Vec3 a = *pSphere->poCenter - this->NearTopLeft;
		if (a.dot(this->TopNorm) > pSphere->Radius || // Right
			a.dot(this->LeftNorm) > pSphere->Radius ||
			a.dot(this->FrontNorm) > pSphere->Radius)
		{
			result = CullResult::CULL_OUTSIDE;
		}
		else
		{
			a = *pSphere->poCenter - this->FarBottomRight;
				if(a.dot(this->BottomNorm) > pSphere->Radius ||
				   a.dot(this->RightNorm) > pSphere->Radius ||
				   a.dot(this->BackNorm) > pSphere->Radius)
			{
				result = CullResult::CULL_OUTSIDE;
			}
		}

		return result;

	}

	void Camera3D::setPerspective(const float fov_deg, const float aspectRatio, const float nearDist, const float farDist)
	{
		this->NearDist = nearDist;
		this->FarDist = farDist;
		this->Fovy = fov_deg;
		this->AspectRatio = aspectRatio;
	}

	// The projection Mat4 (note it's invertable)
	void Camera3D::privUpdateProjectionMat4(void)
	{
		this->projMat4[m0] = 2.0f * this->NearDist / this->NearWidth;
		this->projMat4[m1] = 0.0f;
		this->projMat4[m2] = 0.0f;
		this->projMat4[m3] = 0.0f;

		this->projMat4[m4] = 0.0f;
		this->projMat4[m5] = 2.0f * this->NearDist / this->NearHeight;
		this->projMat4[m6] = 0.0f;
		this->projMat4[m7] = 0.0f;

		this->projMat4[m8] = 0.0f;
		this->projMat4[m9] = 0.0f;
		this->projMat4[m10] = (this->FarDist + this->NearDist) / (this->NearDist - this->FarDist);
		this->projMat4[m11] = -1.0f;

		this->projMat4[m12] = 0.0f;
		this->projMat4[m13] = 0.0f;
		this->projMat4[m14] = (2.0f * this->FarDist * this->NearDist) / (this->NearDist - this->FarDist);
		this->projMat4[m15] = 0.0f;
	};


	void Camera3D::privCalcFrustumVerts(void)
	{
		// Top Left corner and so forth.  In this form to see the pattern
		// Might be confusing (remember the picture) vDir goes from screen into your EYE
		// so distance from the eye is "negative" vDir
		this->NearTopLeft = this->vPos - this->vDir * this->NearDist + this->vUp * this->NearHeight * 0.5f - this->vRight * this->NearWidth * 0.5f;
		this->NearTopRight = this->vPos - this->vDir * this->NearDist + this->vUp * this->NearHeight * 0.5f + this->vRight * this->NearWidth * 0.5f;
		this->NearBottomLeft = this->vPos - this->vDir * this->NearDist - this->vUp * this->NearHeight * 0.5f - this->vRight * this->NearWidth * 0.5f;
		this->NearBottomRight = this->vPos - this->vDir * this->NearDist - this->vUp * this->NearHeight * 0.5f + this->vRight * this->NearWidth * 0.5f;
		this->FarTopLeft = this->vPos - this->vDir * this->FarDist + this->vUp * this->FarHeight * 0.5f - this->vRight * this->FarWidth * 0.5f;
		this->FarTopRight = this->vPos - this->vDir * this->FarDist + this->vUp * this->FarHeight * 0.5f + this->vRight * this->FarWidth * 0.5f;
		this->FarBottomLeft = this->vPos - this->vDir * this->FarDist - this->vUp * this->FarHeight * 0.5f - this->vRight * this->FarWidth * 0.5f;
		this->FarBottomRight = this->vPos - this->vDir * this->FarDist - this->vUp * this->FarHeight * 0.5f + this->vRight * this->FarWidth * 0.5f;
	};

	void Camera3D::privCalcFrustumCollisionNormals(void)
	{
		// Normals of the frustum around nearTopLeft
		Vec3 A = this->NearBottomLeft - this->NearTopLeft;
		Vec3 B = this->NearTopRight - this->NearTopLeft;
		Vec3 C = this->FarTopLeft - this->NearTopLeft;

		this->FrontNorm = A.cross(B);
		this->FrontNorm.norm();

		this->LeftNorm = C.cross(A);
		this->LeftNorm.norm();

		this->TopNorm = B.cross(C);
		this->TopNorm.norm();

		// Normals of the frustum around farBottomRight
		A = this->FarBottomLeft - this->FarBottomRight;
		B = this->FarTopRight - this->FarBottomRight;
		C = this->NearBottomRight - this->FarBottomRight;

		this->BackNorm = A.cross(B);
		this->BackNorm.norm();

		this->RightNorm = B.cross(C);
		this->RightNorm.norm();

		this->BottomNorm = C.cross(A);
		this->BottomNorm.norm();
	};

	// Goal, calculate the near height / width, same for far plane 
	void Camera3D::privCalcPlaneHeightWidth(void)
	{

		this->NearHeight = 2.0f * tanf((this->Fovy * MATH_PI / 180.0f) * .5f) * this->NearDist;
		this->NearWidth = this->NearHeight * this->AspectRatio;

		this->FarHeight = 2.0f * tanf((this->Fovy * MATH_PI / 180.0f) * .5f) * this->FarDist;
		this->FarWidth = this->FarHeight * this->AspectRatio;

	};

	void Camera3D::getFieldOfView(float& Value) const
	{
		Value = this->Fovy;
	};

	void Camera3D::setFieldOfView(const float Value)
	{
		this->Fovy = Value;
	}

	void Camera3D::adjustFieldOfView(bool zoomIn)
	{
		this->Fovy = zoomIn ? this->Fovy - .5f : this->Fovy + .5f;
	}

	void Camera3D::getNearDist(float& Value) const
	{
		Value = this->NearDist;
	}

	void Camera3D::setNearDist(const float Value)
	{
		this->NearDist = Value;
	}

	void Camera3D::getNearTopLeft(Vec3& vOut) const
	{
		vOut = this->NearTopLeft;
	}
	void Camera3D::getNearTopRight(Vec3& vOut) const
	{
		vOut = this->NearTopRight;
	}
	void Camera3D::getNearBottomLeft(Vec3& vOut)const
	{
		vOut = this->NearBottomLeft;
	}
	void Camera3D::getNearBottomRight(Vec3& vOut) const
	{
		vOut = this->NearBottomRight;
	}
	void Camera3D::getFarTopLeft(Vec3& vOut) const
	{
		vOut = this->FarTopLeft;
	}
	void Camera3D::getFarTopRight(Vec3& vOut) const
	{
		vOut = this->FarTopRight;
	}
	void Camera3D::getFarBottomLeft(Vec3& vOut) const
	{
		vOut = this->FarBottomLeft;
	}
	void Camera3D::getFarBottomRight(Vec3& vOut)const
	{
		vOut = this->FarBottomRight;
	}

}