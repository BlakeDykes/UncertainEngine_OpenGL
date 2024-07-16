#include "GameObject2D.h"
#include "BoundingObjectWrapper.h"

GameObject2D::GameObject2D(GraphicsObjectNode* pGraphicsObject,
	GameObject::TYPE type,
	const char* pName,
	const float origWidth,
	const float origHeight)
	: GameObject(pGraphicsObject, type, pName, new BoundingRect()), AspectRatio(origWidth / origHeight)
{
	assert(origWidth >= 0.0f);
	assert(origHeight >= 0.0f);

	if (AspectRatio >= 1.0f)
	{
		this->poScale->set(1.0f / AspectRatio, 1.0f, 1.0f);
	}
	else
	{
		this->poScale->set(1.0f, 1.0f * AspectRatio, 1.0f);
	}

	this->poBoundingObject->Set(*this->poWorld);
}

GameObject2D::~GameObject2D()
{

}

void GameObject2D::Update(_Time currTime)
{
	this->privUpdate(currTime);

	this->privUpdateBoundingObject(*this->poBoundingObject);
}

void GameObject2D::privUpdate(_Time currTime)
{
	AZUL_UNUSED_VAR(currTime);
}

void GameObject2D::SetAspectRatio(float width, float height)
{
	assert(width >= 0.0f);
	assert(height >= 0.0f);

	this->AspectRatio = width / height;

	if (AspectRatio >= 1.0f)
	{
		this->poScale->set(
			this->poScale->x() * (1.0f / AspectRatio), 
			this->poScale->y(), 
			1.0f);
	}
	else
	{
		this->poScale->set(
			this->poScale->x(), 
			this->poScale->y() * AspectRatio, 
			1.0f);
	}
}

void GameObject2D::SetPos(const float x, const float y)
{
	this->poTrans->set(x, y, -1.0f);
}

void GameObject2D::SetRot(const float angle)
{
	this->poRotate->set(Quat::Rot1::Z, angle);
}

void GameObject2D::SetWidth_AR(const float width)
{
	this->poScale->set(width, (width / this->AspectRatio), 1.0f);
}

void GameObject2D::SetHeight_AR(const float height)
{
	this->poScale->set((height * this->AspectRatio), height, 1.0f);

}

void GameObject2D::SetScale(const Vec3& scale)
{
	this->poScale->set(scale.x(), scale.y(), 1.0f);
}
