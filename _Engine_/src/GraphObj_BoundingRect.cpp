#include "GraphObj_BoundingRect.h"
#include "Mesh.h"
#include "CameraManager.h"

Vec4* poLightColor;
Vec3* poScale;
Vec3* poTrans;

GraphObj_BoundingRect::GraphObj_BoundingRect(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj)
	: GraphicsObject(MaterialName::COLOR_CONST, _pMeshNode, _pShaderObj), 
	poLightColor(new Vec4(0.0f, 1.0f, 0.0f, 1.0f))
{
}

GraphObj_BoundingRect::~GraphObj_BoundingRect()
{
	delete this->poLightColor;
}

void GraphObj_BoundingRect::SetState()
{
	glDisable(GL_CULL_FACE);
}

void GraphObj_BoundingRect::SetDataGPU()
{
	this->pShaderObj->SetActive();

	glBindVertexArray(this->GetMesh()->VAO);

	Camera2D* pCam = CameraManager::GetActive2D();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&pCam->getProjMatrix());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&pCam->getViewMatrix());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)this->poWorld);
	glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float*)this->poLightColor);
}

void GraphObj_BoundingRect::Draw()
{
	glDrawElements(GL_LINES, 2 * this->GetMesh()->NumTris, GL_UNSIGNED_INT, 0);
}

void GraphObj_BoundingRect::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphObj_BoundingRect::SetLightColor(const Vec4& color)
{
	this->poLightColor->set(color);
}
