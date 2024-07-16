#ifndef GRAPH_OBJ_NULL_H
#define GRAPH_OBJ_NULL_H

#include "GraphicsObject.h"

class GraphObj_Null : public GraphicsObject
{
public:
	GraphObj_Null(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj);

	virtual void SetState() override;
	virtual void SetDataGPU() override;
	virtual void Draw() override;
	virtual void RestoreState() override;
};

#endif