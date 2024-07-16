#ifndef GRAPH_OBJ_CONST_COLOR_H
#define GRAPH_OBJ_CONST_COLOR_H

#include "GraphicsObject.h"

class GraphObj_LightColor : public GraphicsObject
{
public:
	Vec4* poLightColor;
	Vec3* poLightPos;

	GraphObj_LightColor(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj);
	virtual ~GraphObj_LightColor();

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	virtual void SetLightPos(const Vec3& pos) override;
	virtual void SetLightColor(const Vec4& color) override;
};


#endif