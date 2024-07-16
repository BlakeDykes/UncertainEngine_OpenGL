#ifndef GRAPH_OBJ_BOUNDING_RECT_H
#define GRAPH_OBJ_BOUNDING_RECT_H

#include "GraphicsObject.h"

class GraphObj_BoundingRect : public GraphicsObject
{
public:
	Vec4* poLightColor;

	GraphObj_BoundingRect(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj);
	virtual ~GraphObj_BoundingRect();

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	virtual void SetLightColor(const Vec4& color) override;

};

#endif