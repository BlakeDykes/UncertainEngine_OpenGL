#include "GraphObj_SkinTextPointLight.h"

#include "Mesh.h"
#include "ShaderObject.h"
#include "TextureManager.h"
#include "Texture.h"
#include "CameraManager.h"
#include "Armature.h"

using namespace Uncertain;

GraphObj_SkinTextPointLight::GraphObj_SkinTextPointLight(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj, SSBO& boneResultBuffer)
	: GraphicsObject(MaterialName::SKIN_TEXT_POINT_LIGHT, _pMeshNode, _pShaderObj), pBoneResultBuffer(&boneResultBuffer), pTexture(nullptr)
{
	assert(this->poWorld);
	assert(_pMeshNode);
	assert(_pShaderObj);

	TextureManager::FindAndAssign(TextureName::UNINITIALIZED, this->pTexture);
	this->poLightColor = new Vec4();
	this->poLightPos = new Vec3();

	this->poLightColor->set(DEFAULT_LIGHT_COLOR);
	this->poLightPos->set(DEFAULT_LIGHT_POS);
	this->poBaseColor = new Vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

GraphObj_SkinTextPointLight::~GraphObj_SkinTextPointLight()
{
	delete this->poBaseColor;
	delete this->poLightPos;
	delete this->poLightColor;

	if (this->pTexture)
	{
		this->pTexture->ManageActiveCount(-1);
		this->pTexture = nullptr;
	}
}

void GraphObj_SkinTextPointLight::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	if (this->pTexture->bTextEnabled)
	{
		glBindTexture(GL_TEXTURE_2D, this->pTexture->TextureID);
	}

	//void * data = this->pBoneResultBuffer->Map(SSBO::Access::READ_ONLY);
	//memcpy_s(this->poBoneResult, NumBones * sizeof(Mat4), data, NumBones * sizeof(Mat4));
	//this->pBoneResultBuffer->UnMap();

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GraphObj_SkinTextPointLight::SetDataGPU()
{
	this->pShaderObj->SetActive();


	Camera3D* pCam = CameraManager::GetActive3D();
	Mesh* pMesh = this->GetMesh();

	glBindVertexArray(pMesh->VAO);

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&pCam->getProjMatrix());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&pCam->getViewMatrix());
	glUniform4fv(this->pShaderObj->GetLocation("vBaseColorFactor"), 1, (float*)this->poBaseColor);
	glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float*)this->poLightPos);
	glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float*)this->poLightColor);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("invBind_matrix"), pMesh->GetInvBindCount(), GL_FALSE, (float*)&pMesh->GetInvBindMats());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&this->GetWorld());

	this->pBoneResultBuffer->Bind(2);

	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void GraphObj_SkinTextPointLight::Draw()
{
	//The starting point of the IBO
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->NumTris, GL_UNSIGNED_INT, 0);
}

void GraphObj_SkinTextPointLight::RestoreState()
{
	glDisable(GL_BLEND);
}

void GraphObj_SkinTextPointLight::SetTexture(TextureName name, unsigned int modelMatIndex)
{
	if (this->pTexture)
	{
		this->pTexture->ManageActiveCount(-1);
	}

	this->pTexture = TextureManager::FindTexture(name, modelMatIndex);
	assert(this->pTexture);

	this->pTexture->ManageActiveCount(1);

	if (this->pTexture->bBaseColorEnabled)
	{
		this->poBaseColor->set(pTexture->Color.r, pTexture->Color.g, pTexture->Color.b, pTexture->Color.a);
	}
}

void GraphObj_SkinTextPointLight::SetTexture(Texture& text)
{
	if (this->pTexture)
	{
		this->pTexture->ManageActiveCount(-1);
	}

	this->pTexture = &text;
	assert(this->pTexture);

	this->pTexture->ManageActiveCount(1);

	if (this->pTexture->bBaseColorEnabled)
	{
		this->poBaseColor->set(pTexture->Color.r, pTexture->Color.g, pTexture->Color.b, pTexture->Color.a);
	}
}

void GraphObj_SkinTextPointLight::SetLightColor(const Vec4& lightColor)
{
	this->poLightColor->set(lightColor);
}

void GraphObj_SkinTextPointLight::SetLightPos(const Vec3& lightPos)
{
	this->poLightPos->set(lightPos);
}

void GraphObj_SkinTextPointLight::SetBoneWorldResultBuffer(SSBO& boneResultBuffer)
{
	this->pBoneResultBuffer = &boneResultBuffer;
}

void GraphObj_SkinTextPointLight::Wash()
{
	if (this->pTexture)
	{
		this->pTexture->ManageActiveCount(-1);
		this->pTexture = nullptr;
	}

	delete this->poLightColor;
	delete this->poLightPos;

	GraphicsObject::Wash();
}