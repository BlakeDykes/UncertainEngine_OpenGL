#include "GraphObj_Wireframe.h"
#include "Mesh.h"
#include "ShaderObject.h"
#include "CameraManager.h"

using namespace Uncertain;

extern Mat4* pProjectionMatrix;

GraphObj_Wireframe::GraphObj_Wireframe(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj)
	: GraphicsObject(MaterialName::WIREFRAME, _pMeshNode, _pShaderObj)
{
	this->poLightColor = new Vec4();
	this->poLightColor->set(DEFAULT_LIGHT_COLOR);

	assert(this->poWorld);
	assert(_pMeshNode);
	assert(_pShaderObj);
}

GraphObj_Wireframe::~GraphObj_Wireframe()
{
	delete this->poLightColor;
}

void GraphObj_Wireframe::SetState()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);
}

void GraphObj_Wireframe::SetDataGPU()
{
	this->pShaderObj->SetActive();

	glBindVertexArray(this->GetMesh()->VAO);

	GraphicsObject::SetDataGPU();
	
	glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float*)this->poLightColor);
}

void GraphObj_Wireframe::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->NumTris, GL_UNSIGNED_INT, 0);
}

void GraphObj_Wireframe::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GraphObj_Wireframe::SetLightColor(const Vec4& color)
{
	this->poLightColor->set(color);
}