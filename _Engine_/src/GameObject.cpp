//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <math.h>
#include "GameObject.h"
#include "Game.h"
#include "ShaderObject.h"
#include "Mesh.h"
#include "GraphicsObjectManager.h"
#include "Camera.h"
#include "CameraManager.h"
#include "BoundingObjectWrapper.h"

using namespace Uncertain;

extern Game* pGame;

GameObject::GameObject(GraphicsObjectNode* pGraphNode, TYPE type, BoundingObject* _poBounding)
	: poWorld(new Mat4(Mat4::Special::Identity)),
	poScale(new Vec3(1.0f, 1.0f, 1.0f)),
	poRotate(new Quat(Quat::Special::Identity)),
	poTrans(new Vec3(0.0f, 0.0f, 0.0f)),
	poLocalRotate(new Vec3(0.0f, 0.0f, 0.0f)),
	poLocalTransform(new Vec3(0.0f, 0.0f, 0.0f)),
	poDeltaRot(new Vec3(0.0f, 0.0f, 0.0f)),
	pGraphObjNode(pGraphNode),
	poBoundingObject(_poBounding),
	Type(type)
{
}

GameObject::GameObject(GraphicsObjectNode* pGraphNode, TYPE type, const char* const nodeName, BoundingObject* _poBounding)
	: PCSNode(nodeName),
	poWorld(new Mat4(Mat4::Special::Identity)),
	poScale(new Vec3(1.0f, 1.0f, 1.0f)),
	poRotate(new Quat(Quat::Special::Identity)),
	poTrans(new Vec3(0.0f, 0.0f, 0.0f)),
	poLocalRotate(new Vec3(0.0f, 0.0f, 0.0f)),
	poLocalTransform(new Vec3(0.0f, 0.0f, 0.0f)),
	poDeltaRot(new Vec3(0.0f, 0.0f, 0.0f)),
	pGraphObjNode(pGraphNode),
	poBoundingObject(_poBounding),
	Type(type)
{
	assert(pGraphObjNode);
}

GameObject::~GameObject()
{
	delete this->poWorld;
	delete this->poTrans;
	delete this->poRotate;
	delete this->poScale;
	delete this->poLocalTransform;
	delete this->poLocalRotate;
	delete this->poDeltaRot;
	delete this->poBoundingObject;

	if (this->pGraphObjNode)
	{
		GraphicsObjectManager::Remove(*this->pGraphObjNode);
	}
}

void GameObject::Update(_Time currentTime)
{
	this->privUpdate(currentTime);

	this->privUpdateBoundingObject(*this->poBoundingObject);
}

void GameObject::privUpdate(_Time currentTime)
{
	AZUL_UNUSED_VAR(currentTime);

	*this->poLocalRotate += *this->poDeltaRot;

	GameObject* pParentObj = (GameObject*)this->GetParent();
	Mat4 parentMat;
	if (pParentObj)
	{
		parentMat = *pParentObj->poWorld;
	}
	else
	{
		parentMat = Mat4::Special::Identity;
	}

	Mat4 scale(Mat4::Scale::XYZ, *this->poScale);
	Mat4 trans(Mat4::Trans::XYZ, *this->poTrans);
	Mat4 localTrans(Mat4::Trans::XYZ, *this->poLocalTransform);
	Mat4 localRot(Mat4::Rot3::XYZ, this->poLocalRotate->x(), this->poLocalRotate->y(), this->poLocalRotate->z());

	*this->poWorld = scale * localRot * localTrans * (*this->poRotate) * trans * parentMat;

	this->pGraphObjNode->SetWorld(*this->poWorld);
}

void GameObject::privUpdateBoundingObject(BoundingObject& boundingOut)
{
	this->pGraphObjNode->UpdateBoundingObject(boundingOut);
}

void GameObject::Draw(bool drawBoundingObject)
{
	GraphicsObject* pGraphObj = this->GetGraphicsObject();
	assert(pGraphObj);

	pGraphObjNode->Render(drawBoundingObject);
}

void GameObject::SetWorld(Mat4* _pWorld)
{
	*this->poWorld = *_pWorld;
}

void GameObject::SetPos(const Vec3& pos)
{
	*this->poTrans = pos;
}

void GameObject::SetRot(const Quat& quat)
{
	*this->poRotate = quat;
}

void GameObject::SetDeltaRot(const Vec3& q)
{	
	*this->poDeltaRot = q;
}

void GameObject::SetScale(const Vec3& scale)
{
	*this->poScale = scale;
}

void GameObject::SetLocalRot(const Vec3& r)
{
	*this->poLocalRotate = r;
}

void GameObject::SetLocalPos(const Vec3& pos)
{
	*this->poLocalTransform = pos;
}

void GameObject::AdjustTrans(const Vec3& v)
{
	this->poTrans->set(poTrans->x() + v.x(),
						poTrans->y() + v.y(),
						poTrans->z() + v.z());
}

void GameObject::AdjustLocalRot(const Vec3& v)
{
	this->poLocalRotate->set(poLocalRotate->x() + v.x(),
							 poLocalRotate->y() + v.y(),
							 poLocalRotate->z() + v.z());
}

void GameObject::AdjustScale(const Vec3& v)
{
	this->poScale->set(poScale->x() + v.x(),
						poScale->y() + v.y(),
						poScale->z() + v.z());
}

void GameObject::SetLightColor(const Vec4& color)
{
	this->pGraphObjNode->SetLightColor(color);
}

void GameObject::SetLightPos(const Vec3& pos)
{
	this->pGraphObjNode->SetLightPos(pos);
}

void GameObject::SetPhongData(const PhongData& data)
{
	this->pGraphObjNode->SetPhongData(data);
}

void GameObject::SetTexture(TextureName name)
{
	this->pGraphObjNode->SetTexture(name);
}

bool GameObject::Is3D()
{
	switch (this->Type)
	{
	case TYPE::GO_TREE_ROOT:
	case TYPE::ROOT_3D:
	case TYPE::RIGID_3D:
	case TYPE::ANIMATED_3D:
		return true;

	case TYPE::ROOT_2D:
	case TYPE::ROOT_UI_2D:
	case TYPE::UI_ELEMENT_2D:
	case TYPE::RIGID_2D:
	case TYPE::ANIMATED_2D:
	case TYPE::FONT_2D:
		return false;

	default:
		assert(false);
		return false;
	}
}

void GameObject::Wash()
{
	this->poWorld->set(Mat4::Special::Identity);
	this->poTrans->set(0.0f, 0.0f, 0.0f);

	if (this->pGraphObjNode)
	{
		GraphicsObjectManager::Remove(*this->pGraphObjNode);
		this->pGraphObjNode = nullptr;
	}
}
