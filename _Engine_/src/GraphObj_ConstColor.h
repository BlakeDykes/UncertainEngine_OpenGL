#ifndef GRAPH_OBJ_COLOR_BY_POS_H
#define GRAPH_OBJ_COLOR_BY_POS_H

#include "GraphicsObject.h"

class GraphObj_ConstColor : public GraphicsObject
{
public:
	Vec4* poLightColor;

	GraphObj_ConstColor(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj);
	virtual ~GraphObj_ConstColor();

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	virtual void SetLightColor(const Vec4& color) override;

};

#endif