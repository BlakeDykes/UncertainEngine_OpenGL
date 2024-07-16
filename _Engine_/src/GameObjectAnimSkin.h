#ifndef GAME_OBJECT_ANIM_SKIN_H
#define GAME_OBJECT_ANIM_SKIN_H

#include "GameObjectAnim.h"

namespace Uncertain
{
	class Armature;

	class GameObjectAnimSkin : public GameObjectAnim
	{
	public:
		GameObjectAnimSkin(GameObject::TYPE type, AnimController& animController, GraphicsObjectNode* pGraphicsObject, const char* pName, BoundingObject* poBounding);

		GameObjectAnimSkin(const GameObjectAnimSkin&) = delete;
		GameObjectAnimSkin& operator=(GameObjectAnimSkin&) = delete;
		virtual ~GameObjectAnimSkin();

		virtual void Update(_Time currTime) override;
		virtual void SetIndex(unsigned int i) override;

		Mat4 GetBoneOrientation() const;
		void SetBoneOrientation(const Mat4& m);

	private:
		virtual void privUpdate(_Time currTime) override;

	};
}

#endif // !GAME_OBJECT_ANIM_SKIN_H
