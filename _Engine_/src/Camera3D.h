#ifndef CAMERA_3D_H
#define CAMERA_3D_H

#include "Camera.h"

namespace Uncertain
{
	class Camera3D : public Camera
	{
	public:

		Camera3D();
		Camera3D(const Camera3D&) = delete;
		Camera3D& operator=(const Camera3D&) = delete;
		virtual ~Camera3D();

		virtual void updateCamera() override;

		virtual CullResult CullTest(GameObject* pGameObject) override;

		void setPerspective(const float fov_deg, const float aspectRatio, const float nearDist, const float farDist);

		void getFieldOfView(float& Value) const;
		void setFieldOfView(const float Value);
		void adjustFieldOfView(bool positiveAdjust);

		void getNearDist(float& Value) const;
		void setNearDist(const float Value);

		void getNearTopLeft(Vec3& vOut) const;
		void getNearTopRight(Vec3& vOut) const;
		void getNearBottomLeft(Vec3& vOut) const;
		void getNearBottomRight(Vec3& vOut) const;
		void getFarTopLeft(Vec3& vOut) const;
		void getFarTopRight(Vec3& vOut) const;
		void getFarBottomLeft(Vec3& vOut) const;
		void getFarBottomRight(Vec3& vOut) const;

	private:
		void privCalcFrustumVerts(void);
		void privCalcFrustumCollisionNormals(void);
		void privCalcPlaneHeightWidth(void);

		virtual void privUpdateProjectionMat4(void) override;

		// world space coords for viewing frustum
		Vec3	NearTopLeft;
		Vec3	NearTopRight;
		Vec3	NearBottomLeft;

		Vec3	NearBottomRight;
		Vec3	FarTopLeft;
		Vec3	FarTopRight;
		Vec3	FarBottomLeft;

		Vec3	FarBottomRight;

		// Normals of the frustum
		Vec3	FrontNorm;
		Vec3	BackNorm;
		Vec3	RightNorm;

		Vec3	LeftNorm;
		Vec3	TopNorm;
		Vec3	BottomNorm;

		// -------------------------------------------------------
		// unaligned data below this point:
		// -------------------------------------------------------

		// Define the frustum inputs

		float	NearDist;
		float	FarDist;
		float	Fovy;
		float	AspectRatio;

		// Screen size in world space
		float	NearHeight;
		float	NearWidth;
		float	FarHeight;
		float	FarWidth;
	};
}

#endif // !CAMERA_3D_H
