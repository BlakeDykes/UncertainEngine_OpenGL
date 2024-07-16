#ifndef GRAPH_OBJ_NODE_H
#define GRAPH_OBJ_NODE_H

#include "DLink.h"
#include "MathEngine.h"
#include "EngineNames.h"
#include "GraphicsObjects_Wrapper.h"

class Mesh;
class ShaderObject;
class GraphicsObject;
class BoundingObject;
class UIStyle;

using namespace Uncertain;

class GraphicsObjectNode : public DLink
{
public:

	GraphicsObjectNode();
	GraphicsObjectNode(const GraphicsObjectNode&) = delete;
	GraphicsObjectNode& operator=(const GraphicsObjectNode&) = delete;
	virtual ~GraphicsObjectNode();

	void Render(bool drawBoundingSpheres);

	void Set(MATERIAL_ID id, GraphicsObject* pGraphObj);

	GraphicsObject* GetGraphObj() const { return this->poObject; }
	bool IsNull() { return poObject->IsNull(); }

	void SetWorld(const Mat4& _world);

	void SetTexture(TextureName name, unsigned int modelMatIndex = UINT_MAX);
	void SetTexture(Texture& text);
	void SetLightColor(const Vec4& lightColor);
	void SetLightPos(const Vec3& lightPos);
	void SetPhongData(const PhongData& data);
	void SetBoneWorldResultBuffer(SSBO& boneResultBuffer);
	void SetBoundingGraphicsObject(GraphicsObject* pSphereObject);
	void SetUIStyle(const UIStyle& uiStyle);
	void UpdateBoundingObject(BoundingObject& boundingOut);
	void UpdateBoundingObjectFromGraphObj(BoundingObject& boundingOut);


	virtual const char* GetName() override;
	virtual bool Compare(NodeBase& pNode) override;
	virtual void Print() override;
	virtual void Wash() override;

private:
	GraphicsObject* poObject;
	GraphicsObject* poBoundingGraphicsObject;
};

#endif