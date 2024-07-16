#include "GameObjectAnimSkin.h"
#include "AnimController.h"
#include "Armature.h"

GameObjectAnimSkin::GameObjectAnimSkin(GameObject::TYPE type, AnimController& animController, GraphicsObjectNode* pGraphicsObject, const char* pName, BoundingObject* poBounding)
	: GameObjectAnim(type, animController, pGraphicsObject, pName, poBounding)
{
}

GameObjectAnimSkin::~GameObjectAnimSkin()
{
}

void GameObjectAnimSkin::Update(_Time currTime)
{
	this->privUpdate(currTime);

	this->privUpdateBoundingObject(*this->poBoundingObject);
}

void GameObjectAnimSkin::privUpdate(_Time currTime)
{
	AZUL_UNUSED_VAR(currTime);

	GameObject* pParentObj = (GameObject*)this->GetParent();

	*this->poLocalRotate += *this->poDeltaRot;

	Mat4 parentMat;
	if (pParentObj)
	{
		parentMat = *pParentObj->GetWorld();
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

void GameObjectAnimSkin::SetIndex(unsigned int i)
{
	this->BoneIndex = i;
}

Mat4 GameObjectAnimSkin::GetBoneOrientation() const
{
	return Mat4();
}

void GameObjectAnimSkin::SetBoneOrientation(const Mat4& m)
{
	AZUL_UNUSED_VAR(m);
}

