#include "UIStyle.h"
#include "CameraManager.h"
#include "Camera2D.h"

UIStyle::UIStyle(Camera2D* cam, float xPercentage, float yPercentage, float widthPercentage, float heightPercentage, float angleRad, int zIndex, bool visible)
	: XArea(X_AREA::UNINITIALIZED), YArea(Y_AREA::UNINITIALIZED), pCam(cam), poWorld(new Mat4()), poTrans(new Vec3()), poScale(new Vec3()),
	poRot(new Quat(Quat::Rot1::Z, angleRad)), mZIndex(zIndex), mVisible(visible)
{
	this->Trans(xPercentage, yPercentage);
	this->Scale(widthPercentage, heightPercentage);
	this->Update();
}

UIStyle::UIStyle()
	: XArea(X_AREA::UNINITIALIZED), YArea(Y_AREA::UNINITIALIZED), poWorld(new Mat4()), poTrans(new Vec3()), poScale(new Vec3()),
	poRot(new Quat(Quat::Special::Identity)), mZIndex(1), mVisible(true)
{
	this->pCam = CameraManager::GetActive2D();

	this->Trans(0.5f, 0.5f);
	this->Scale(0.25f, 0.25f);
	this->Update();
}

UIStyle::UIStyle(Camera2D* cam, X_AREA xArea, Y_AREA yArea, float widthPercentage, float heightPercentage, float angleRad, int zIndex, bool visible)
	: XArea(xArea), YArea(yArea), pCam(cam), poWorld(new Mat4()), poTrans(new Vec3()), poScale(new Vec3()),
	poRot(new Quat(Quat::Rot1::Z, angleRad)), mZIndex(zIndex), mVisible(visible)
{	
	this->Scale(widthPercentage, heightPercentage);
	this->SetArea(xArea, yArea);
	this->Update();
}

UIStyle::~UIStyle()
{
	delete this->poWorld;
	delete this->poTrans;
	delete this->poScale;
	delete this->poRot;
}

UIStyle::UIStyle(const UIStyle& s)
{
	*this->poWorld = *s.poWorld;
	*this->poTrans = *s.poTrans;
	*this->poScale = *s.poScale;
	*this->poRot = *s.poRot;
}

UIStyle& UIStyle::operator=(const UIStyle& s)
{
	if (this != &s)
	{
		*this->poWorld = *s.poWorld;
		*this->poTrans = *s.poTrans;
		*this->poScale = *s.poScale;
		*this->poRot = *s.poRot;
	}

	return *this;
}

void UIStyle::Update()
{
	Mat4 scale(Mat4::Scale::XYZ, *this->poScale);
	Mat4 trans(Mat4::Trans::XYZ, *this->poTrans);

	*this->poWorld = scale * trans * *this->poRot;
}

void UIStyle::Clear()
{
	this->poWorld->clear();
	this->poTrans->clear();
	this->poScale->clear();
	this->poRot->clear();
	this->mZIndex = 1;
	this->mVisible = false;
}



void UIStyle::SetArea(X_AREA xArea, Y_AREA yArea)
{
	assert(this->pCam);
	assert(this->poScale);
	assert(this->poTrans);

	float x = 0.0f;
	float y = 0.0f;
	float width = (float)this->pCam->getScreenWidth();
	float height = (float)this->pCam->getScreenHeight();

	switch (xArea)
	{
	case UIStyle::X_AREA::LEFT:
		x = (this->poScale->x() * 0.5f) - (width * 0.5f);
		break;
	case UIStyle::X_AREA::CENTER:
		x = 0.0f;
		break;
	case UIStyle::X_AREA::RIGHT:
		x = (width * 0.5f) - (this->poScale->x() * 0.5f);
		break;

	case UIStyle::X_AREA::UNINITIALIZED:
	default:
		break;
	}

	switch (yArea)
	{
	case UIStyle::Y_AREA::TOP:
		y = (height * 0.5f) - (this->poScale->y() * 0.5f);
		break;
	case UIStyle::Y_AREA::CENTER:
		y = 0.0f;
		break;
	case UIStyle::Y_AREA::BOTTOM:
		y = (this->poScale->y() * 0.5f) - (height * 0.5f);
		break;

	case UIStyle::Y_AREA::UNINITIALIZED:
	default:
		break;
	}

	this->poTrans->set(x, y, -1.0f);
}

void UIStyle::Trans(const float xPercentage, const float yPercentage)
{
	assert(pCam);

	this->poTrans->set(
		NormPercentage(xPercentage) * (float)this->pCam->getScreenWidth(), 
		NormPercentage(yPercentage) * (float)this->pCam->getScreenHeight(),
		-1.0f);
}

void UIStyle::Scale(const float widthPercentage, const float heightPercentage)
{
	assert(pCam);

	this->poScale->set(
		NormPercentage(widthPercentage) * (float)this->pCam->getScreenWidth(),
		NormPercentage(heightPercentage) * (float)this->pCam->getScreenHeight(),
		1.0f);
}

void UIStyle::Rot(const float radians)
{
	this->poRot->set(Quat::Rot1::Z, radians);
}

void UIStyle::ZIndex(const int z)
{
	this->mZIndex = z;
}

void UIStyle::Visible(const bool v)
{
	this->mVisible = v;
}

void UIStyle::ToggleVisible()
{
	this->mVisible = !this->mVisible;
}

const float UIStyle::NormPercentage(const float f) const
{
	assert(f <= 100.0f);
	assert(f >= -100.0f);

	if (f <= 1.0f && f >= -1.0f)
	{
		return f;
	}
	else
	{
		return f * 0.01f;
	}
}

// TODO: Fix this
const float UIStyle::GetRight() const
{
	assert(this->poScale);
	assert(this->poTrans);

	return this->poScale->x() + this->poTrans->x();
}

const float UIStyle::GetLeft() const
{
	assert(this->poScale);
	assert(this->poTrans);
	
	switch (this->XArea)
	{
	case UIStyle::X_AREA::LEFT:
		return (float)pCam->getScreenWidth() * -0.5f;

	case UIStyle::X_AREA::CENTER:
		return ((float)pCam->getScreenWidth() * -0.5f) - (this->poScale->x() * 0.5f);

	case UIStyle::X_AREA::RIGHT:
		return (float)pCam->getScreenWidth() * 0.5f;

	case UIStyle::X_AREA::UNINITIALIZED:
	default:
		return this->poTrans->x() - (this->poScale->x() * 0.5f);
	}
}

// TODO: Fix this
const float UIStyle::GetTop() const
{
	assert(this->poScale);
	assert(this->poTrans);
	
	return this->poTrans->y() + (this->poScale->y() * 0.5f);
}

// TODO: Fix this
const float UIStyle::GetBottom() const
{
	assert(this->poScale);
	assert(this->poTrans);

	return this->poTrans->y() - (this->poScale->y() * 0.5f);
}