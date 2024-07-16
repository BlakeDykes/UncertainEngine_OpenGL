#ifndef GRAPH_OBJ_BOUNDING_SPHERE_H
#define GRAPH_OBJ_BOUNDING_SPHERE_H

#include "GraphicsObject.h"

class GraphObj_BoundingSphere : public GraphicsObject
{
public:
	Vec4* poLightColor;
	Vec3* poScale;
	Vec3* poTrans;

	GraphObj_BoundingSphere(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj);
	virtual ~GraphObj_BoundingSphere();

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	virtual void SetLightColor(const Vec4& color) override;
	virtual void SetScale(const Vec3& v) override;
	virtual void SetTrans(const Vec3& v) override;

};

#endif