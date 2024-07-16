#include "GraphObj_LightColor.h"
#include "Mesh.h"

GraphObj_LightColor::GraphObj_LightColor(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj)
	:GraphicsObject(MaterialName::COLOR_LIGHT, _pMeshNode, _pShaderObj)
{
	this->poLightColor = new Vec4();
	this->poLightPos = new Vec3();

	this->poLightColor->set(DEFAULT_LIGHT_COLOR);
	this->poLightPos->set(DEFAULT_LIGHT_POS);
}

GraphObj_LightColor::~GraphObj_LightColor()
{
	delete this->poLightColor;
	delete this->poLightPos;
}

void GraphObj_LightColor::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphObj_LightColor::SetDataGPU()
{
	this->pShaderObj->SetActive();

	glBindVertexArray(this->GetMesh()->VAO);

	GraphicsObject::SetDataGPU();

	glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float*)this->poLightPos);
	glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float*)this->poLightColor);
}

void GraphObj_LightColor::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->NumTris, GL_UNSIGNED_INT, 0);
}

void GraphObj_LightColor::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphObj_LightColor::SetLightPos(const Vec3& pos)
{
	this->poLightPos->set(pos);
}

void GraphObj_LightColor::SetLightColor(const Vec4& color)
{
	this->poLightColor->set(color);
}
