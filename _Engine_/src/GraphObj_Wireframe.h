#ifndef GRAPH_OBJ_WIREFRAME_H
#define GRAPH_OBJ_WIREFRAME_H

#include "GraphicsObject.h"

class GraphObj_Wireframe : public GraphicsObject
{
public:
	Vec4* poLightColor;

	GraphObj_Wireframe(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj);
	virtual ~GraphObj_Wireframe();

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;

	virtual void SetLightColor(const Vec4& color) override;
};

#endif // !GRAPH_OBJ_WIREFRAME_H
