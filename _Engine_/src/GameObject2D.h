#ifndef GAME_OBJ_2D_H
#define GAME_OBJ_2D_H

#include "GameObject.h"

namespace Uncertain
{
	class GameObject2D : public GameObject
	{
	public:
		GameObject2D() = delete;
		GameObject2D(const GameObject2D&) = delete;
		GameObject2D& operator=(const GameObject2D&) = delete;
		virtual ~GameObject2D();

		GameObject2D(GraphicsObjectNode* pGraphicsObject, 
			GameObject::TYPE type,
			const char* pName, 
			const float origWidth, 
			const float origHeight);

		virtual void Update(_Time currTime) override;

		virtual void SetAspectRatio(float width, float height);

		// Removing Z component from parameters
		void SetPos(const float x, const float y);
		void SetRot(const float angle);
		void SetWidth_AR(const float width);
		void SetHeight_AR(const float height);
		virtual void SetScale(const Vec3& scale) override; // <------------- Breaks Aspect Ratio

		void SetZIndex(int z) { this->ZIndex = z; }
		int GetZIndex() const { return this->ZIndex; }
		void SetActive(bool a) { this->Active = a; }
		int GetActive() const { return this->Active; }
		void ToggleActive() { this->Active = !this->Active; }

	private:
		void privUpdate(_Time currTime);

		// origWidth / origHeight
		float AspectRatio;
		int ZIndex;
		bool Active;
	};
}

#endif // !GAME_OBJ_2D_H
