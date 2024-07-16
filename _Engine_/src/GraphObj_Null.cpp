#include "GraphObj_Null.h"

GraphObj_Null::GraphObj_Null(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj)
	:GraphicsObject(MaterialName::NULL_MAT, _pMeshNode, _pShaderObj, true)
{
}

void GraphObj_Null::SetState()
{
}

void GraphObj_Null::SetDataGPU()
{
}

void GraphObj_Null::Draw()
{
}

void GraphObj_Null::RestoreState()
{
}