//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MathEngine.h"
#include "PCSNode.h"
#include "GraphicsObjectNode.h"
#include "GraphicsObjects_Wrapper.h"
#include "_Time.h"

using namespace Uncertain;

class ShaderObject;
class Mesh;
class BoundingObject;

class GameObject : public PCSNode
{
public:

	enum class TYPE
	{
		GO_TREE_ROOT,

		ROOT_3D,
		RIGID_3D,
		ANIMATED_3D,

		ROOT_2D,
		ROOT_UI_2D,
		UI_ELEMENT_2D,
		RIGID_2D,
		ANIMATED_2D,
		FONT_2D
	};

	GameObject() = delete;
	GameObject(const GameObject&) = delete;
	GameObject& operator = (const GameObject&) = delete;
	virtual ~GameObject();

	GameObject(GraphicsObjectNode* pGraphNode, TYPE type, BoundingObject* _poBounding);
	GameObject(GraphicsObjectNode* pGraphNode, TYPE type, const char* const nodeName, BoundingObject* _poBounding);

	virtual void Update(_Time currentTime);
	virtual void Draw(bool drawBoundingObject);

	void SetWorld(Uncertain::Mat4* _pWorld);
	void SetPos(const Vec3& pos);
	void SetRot(const Quat& q);
	void SetDeltaRot(const Vec3& q);
	virtual void SetScale(const Vec3& scale);
	void SetLocalRot(const Vec3& r);
	void SetLocalPos(const Vec3& pos);

	void AdjustTrans(const Vec3& v);
	void AdjustLocalRot(const Vec3& v);
	void AdjustScale(const Vec3& v);

	const Vec3* const GetLocalTrans() const { return this->poTrans; }
	const Vec3* const GetLocalRot() const { return this->poLocalRotate; }
	const Vec3* const GetLocalScale() const { return this->poScale; }

	void SetLightColor(const Vec4& color);
	void SetLightPos(const Vec3& pos);
	void SetPhongData(const PhongData& data);

	void SetTexture(TextureName name);

	Uncertain::Mat4* GetWorld() { return this->poWorld; }
	const Vec3& Trans() const { return *this->poTrans; }
	const Vec3& Scale() const { return *this->poScale; }
	const Quat& Rot() const { return *this->poRotate; }

	GraphicsObject* GetGraphicsObject() { return this->pGraphObjNode->GetGraphObj(); }
	BoundingObject* GetBoundingObject() const { return this->poBoundingObject; }

	bool Is3D();

	virtual void Wash() override;

protected:
	virtual void privUpdateBoundingObject(BoundingObject& boundingOut);
	virtual void privUpdate(_Time currentTime);

	Mat4* poWorld;
	Vec3* poScale;
	Quat* poRotate;
	Vec3* poTrans;
	Vec3* poLocalRotate;
	Vec3* poLocalTransform;
	Vec3* poDeltaRot;
	GraphicsObjectNode* pGraphObjNode;
	BoundingObject* poBoundingObject;
	GameObject::TYPE Type;

};

#endif
