#include "GameObjectAnim.h"
#include "AnimController.h"
#include "BoundingSphere.h"
#include "Armature.h"

namespace Uncertain
{
	GameObjectAnim::GameObjectAnim(GameObject::TYPE type, AnimController& animController, GraphicsObjectNode* pGraphicsObject, const char* pName, BoundingObject* poBounding)
		:GameObject(pGraphicsObject, type, pName, poBounding), BoneIndex((unsigned int) -1), pAnimController(&animController)
	{
		//if (type != TYPE::ROOT_3D)
		//{
		//	//this->BoneIndex = pAnimController->GetBoneIndex(pGraphicsObject->GetGraphObj()->GetMeshNodeIndex());
		//}
	}

	GameObjectAnim::~GameObjectAnim()
	{
		if (this->pAnimController)
		{
			pAnimController->MarkForDelete();
		}
	}

	void GameObjectAnim::Update(_Time currTime)
	{
	}
}