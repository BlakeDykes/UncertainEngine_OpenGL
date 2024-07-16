#include "GraphObj_ConstColor.h"
#include "Mesh.h"
#include "ShaderObject.h"

using namespace Uncertain;

extern Mat4* pProjectionMatrix;

GraphObj_ConstColor::GraphObj_ConstColor(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj)
	: GraphicsObject(MaterialName::COLOR_CONST, _pMeshNode, _pShaderObj)
{
	this->poLightColor = new Vec4(DEFAULT_LIGHT_COLOR);
	assert(this->poWorld);
	assert(_pMeshNode);
	assert(_pShaderObj);
}

GraphObj_ConstColor::~GraphObj_ConstColor()
{
	delete this->poLightColor;
}

void GraphObj_ConstColor::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphObj_ConstColor::SetDataGPU()
{
	this->pShaderObj->SetActive();

	glBindVertexArray(this->GetMesh()->VAO);

	GraphicsObject::SetDataGPU();
}

void GraphObj_ConstColor::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->NumTris, GL_UNSIGNED_INT, 0);
}

void GraphObj_ConstColor::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphObj_ConstColor::SetLightColor(const Vec4& color)
{
	this->poLightColor->set(color);
}