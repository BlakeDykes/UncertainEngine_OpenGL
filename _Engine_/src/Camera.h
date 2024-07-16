#ifndef CAMERA_H
#define CAMERA_H

#include "EngineNames.h"
#include "DLink.h"
#include "MathEngine.h"
#include "GameObject.h"

namespace Uncertain
{
	struct CameraHelperData : public Align16
	{
		Vec3 pos;
		Vec3 tar;
		Vec3 up;
		Vec3 upNorm;
		Vec3 forwardNorm;
		Vec3 rightNorm;

		void Clear();
	};

	class Camera : public DLink, public Align16
	{
	public:

		enum class CullResult
		{
			CULL_INSIDE,
			CULL_OUTSIDE
		};

		enum class TYPE
		{
			ORTHO_2D,
			PERSPECTIVE_3D,

			UNINITIALIZED
		};

		// Default constructor
		Camera(TYPE type);

		Camera() = delete;
		Camera(const Camera&) = delete;
		Camera& operator = (const Camera&) = delete;
		virtual ~Camera();

		void setViewport(const int inX, const int inY, const int width, const int height);
		void setOrientAndPosition(const Vec3& Up_Vec3, const Vec3& inLookAt_pt, const Vec3& pos_pt);

		virtual CullResult CullTest(GameObject* pGameObject);

		virtual void updateCamera(void);

		// Get the matrices for rendering
		Mat4& getViewMatrix();
		Mat4& getProjMatrix();

		// accessors
		void getPos(Vec3& outPos) const;
		void getDir(Vec3& outDir) const;
		void getUp(Vec3& outUp) const;
		void getLookAt(Vec3& outLookAt) const;
		void getRight(Vec3& outRight) const;

		int getScreenWidth() const;
		int getScreenHeight() const;

		// helper functions
		void GetHelper(CameraHelperData& helperData);
		void SetHelper(CameraHelperData& helperData);

		static TYPE GetType(CameraName name);
		TYPE GetType() const { return this->CameraType; }
		void SetType(const TYPE type) { this->CameraType = type; }
		void SetName(CameraName name);

		virtual const char* GetName() override;
		virtual bool Compare(NodeBase& pNode) override;
		virtual void Print() override;
		virtual void Wash() override;


	private:  // methods should never be public
		void privSetViewState(void);
		virtual void privUpdateProjectionMat4(void);

	protected:  
		void proUpdateViewMat4(void);

		// Projection Mat4
		Mat4	projMat4;
		Mat4	viewMat4;

		// camera unit Vec3ors (up, dir, right)
		Vec3	vUp;
		Vec3	vDir;
		Vec3	vRight;  // derived by up and dir
		Vec3	vPos;

		Vec3	vLookAt;

		TYPE CameraType;

		// viewports
		int		viewport_x;
		int		viewport_y;
		int		viewport_width;
		int		viewport_height;

		CameraName Name;

	};
}


#endif