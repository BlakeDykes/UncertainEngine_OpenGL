#ifndef UI_STYLE_H
#define UI_STYLE_H

#include "MathEngine.h"
#include "Camera2D.h"

using namespace Uncertain;

class UIStyle
{
public:

	enum class X_AREA
	{
		LEFT,
		CENTER,
		RIGHT,

		UNINITIALIZED
	};

	enum class Y_AREA
	{
		TOP,
		CENTER,
		BOTTOM,

		UNINITIALIZED
	};

	UIStyle(Camera2D* cam, float xPercentage, float yPercentage, float widthPercentage, float heightPercentage, float angleRad, int zIndex, bool visible);
	UIStyle(Camera2D* cam, X_AREA xArea, Y_AREA yArea, float widthPercentage, float heightPercentage, float angleRad, int zIndex, bool visible);

	UIStyle();
	UIStyle(const UIStyle&);
	UIStyle& operator=(const UIStyle&);
	~UIStyle();

	void Update();
	void Clear();

	// Getters
	const Mat4& World() const		{ return *poWorld; }
	const Vec3& Trans() const		{ return *poTrans; }
	const Vec3& Scale() const		{ return *poScale; }
	const Quat& Rot() const			{ return *poRot; }
	const int&	ZIndex() const		{ return mZIndex; }
	const bool&	Visible() const		{ return this->mVisible; }

	const float GetRight() const;
	const float GetLeft() const;
	const float GetBottom() const;
	const float GetTop() const;

	// Setters
	void SetArea(X_AREA xArea, Y_AREA yArea);
	void Trans(const float xPercentage, const float yPercentage);
	void Scale(const float widthPercentage, const float heightPercentage);
	void Rot(const float radians);
	void ZIndex(const int z);
	void Visible(const bool v);
	void ToggleVisible();

private:
	const float NormPercentage(const float f) const;

	X_AREA XArea;
	Y_AREA YArea;
	Camera2D* pCam;
	Mat4*	poWorld;
	Vec3*	poTrans;
	Vec3*	poScale;
	Quat*	poRot;
	int		mZIndex;
	bool	mVisible;
};

#endif // !UI_STYLE_H
