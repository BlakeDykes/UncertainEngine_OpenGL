#include "GraphObj_PhongColor.h"
#include "Mesh.h"
#include "CameraManager.h"
#include "Camera.h"

GraphObj_PhongColor::GraphObj_PhongColor(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj)
	:GraphicsObject(MaterialName::COLOR_PHONG_LIGHT, _pMeshNode, _pShaderObj)
{
	this->pData = new PhongData();
}

GraphObj_PhongColor::~GraphObj_PhongColor()
{
	delete this->pData;
}

void GraphObj_PhongColor::SetLightColor(const Vec4& lightColor)
{
	this->pData->LightColor.set(lightColor);
}

void GraphObj_PhongColor::SetLightPos(const Vec3& lightPos)
{
	this->pData->LightPos.set(lightPos);
}

void GraphObj_PhongColor::SetPhongData(const PhongData& data)
{
	this->pData->LightPos				= data.LightPos;
	this->pData->LightColor				= data.LightColor;
	this->pData->KeyLightPos			= data.KeyLightPos;
	this->pData->KeySpecularIntensity 	= data.KeySpecularIntensity;
	this->pData->KeyHighlightSize 		= data.KeyHighlightSize;
	this->pData->AmbientStrength		= data.AmbientStrength;
}

void GraphObj_PhongColor::SetState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphObj_PhongColor::SetDataGPU()
{
	// Get camera position
	CameraManager::GetActive3D()->getPos(this->pData->ViewPos);

	this->pShaderObj->SetActive();

	glBindVertexArray(this->GetMesh()->VAO);

	GraphicsObject::SetDataGPU();

	glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float*)(&(*this->pData).LightPos));
	glUniform3fv(this->pShaderObj->GetLocation("vColor"), 1, (float*)(&(*this->pData).LightColor));
	glUniform3fv(this->pShaderObj->GetLocation("viewPosition"), 1, (float*)&(*this->pData).ViewPos);
	glUniform1f(this->pShaderObj->GetLocation("keySpecularIntensity"), this->pData->KeySpecularIntensity);
	glUniform1f(this->pShaderObj->GetLocation("keyHighlightSize"), this->pData->KeyHighlightSize);
	glUniform1f(this->pShaderObj->GetLocation("ambientStrength"), this->pData->AmbientStrength);
}

void GraphObj_PhongColor::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->NumTris, GL_UNSIGNED_INT, 0);
}

void GraphObj_PhongColor::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphObj_PhongColor::Wash()
{
	this->pData->Clear();
}

void PhongData::Clear()
{
	LightPos.set(0.0f, 1.0f, 0.0f);
	LightColor.set(1.0f, 0.0f, 1.0f);
	KeyLightPos.set(0.0f, 1.0f, 0.0f);
	ViewPos.set(0.0f, 0.0f, -4.5f);
	KeySpecularIntensity = 1.0f;
	KeyHighlightSize = 1.0f;
	AmbientStrength = 0.5f;
}