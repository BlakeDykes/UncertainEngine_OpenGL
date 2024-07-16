#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include "Camera.h"

namespace Uncertain
{
	class Camera2D : public Camera
	{
	public:
		Camera2D();
		Camera2D(const Camera2D&) = delete;
		Camera2D& operator=(const Camera2D&) = delete;
		virtual ~Camera2D();

		virtual void updateCamera() override;
		void setOrtho(const float xMin, const float yMin, const float zMin,
			const float xMax, const float yMax, const float zMax);

		virtual CullResult CullTest(GameObject* pGameObject) override;

	private:
		virtual void privUpdateProjectionMat4() override;

		float XMin;
		float YMin;
		float ZMin;
		float XMax;
		float YMax;
		float ZMax;
	};
}

#endif // !CAMERA_2D_H
