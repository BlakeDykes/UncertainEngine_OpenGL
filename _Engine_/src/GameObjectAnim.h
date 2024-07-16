#ifndef GAME_OBJECT_ANIM_H
#define GAME_OBJECT_ANIM_H

#include "GameObject.h"
#include "ShaderObject.h"
#include "Mesh.h"
#include "GraphicsObject.h"

namespace Uncertain
{
	class AnimController;

	class GameObjectAnim : public GameObject
	{
	public:
		GameObjectAnim(GameObject::TYPE type, AnimController& animController, GraphicsObjectNode* pGraphicsObject, const char* pName, BoundingObject* poBounding);

		GameObjectAnim() = delete;
		GameObjectAnim(const GameObjectAnim&) = delete;
		GameObjectAnim& operator=(GameObjectAnim&) = delete;
		virtual ~GameObjectAnim();

		virtual void Update(_Time currTime);
		virtual void SetIndex(unsigned int i) = 0;

		unsigned int BoneIndex;
		AnimController* pAnimController;
	};
}

#endif