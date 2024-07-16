#include "GraphObj_TextureLight.h"
#include "Mesh.h"
#include "ShaderObject.h"
#include "TextureManager.h"
#include "Texture.h"

using namespace Uncertain;

extern Mat4* pProjectionMatrix;

GraphObj_TextureLight::GraphObj_TextureLight(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj,
	TextureName textName, Vec4& lightColor, Vec3& lightPos)
	:GraphicsObject(MaterialName::TEXT_POINT_LIGHT, _pMeshNode, _pShaderObj), pTexture(nullptr)
{
	assert(this->poWorld);
	assert(_pMeshNode);
	assert(_pShaderObj);

	TextureManager::FindAndAssign(textName, this->pTexture);
	this->poLightColor = new Vec4(lightColor);
	this->poLightPos = new Vec3(lightPos);
	this->poBaseColor = new Vec4(1.0f, 1.0f, 1.0f, 1.0f);

}

GraphObj_TextureLight::GraphObj_TextureLight(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj)
	: GraphicsObject(MaterialName::TEXT_POINT_LIGHT, _pMeshNode, _pShaderObj), pTexture(nullptr)
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

GraphObj_TextureLight::~GraphObj_TextureLight()
{
	if (this->pTexture)
	{
		this->pTexture->ManageActiveCount(-1);
		this->pTexture = nullptr;
	}

	delete this->poLightColor;
	delete this->poLightPos;
	delete this->poBaseColor;
}

void GraphObj_TextureLight::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	if (this->pTexture->bTextEnabled)
	{
		glBindTexture(GL_TEXTURE_2D, this->pTexture->TextureID);
	}

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GraphObj_TextureLight::SetDataGPU()
{
	this->pShaderObj->SetActive();

	glBindVertexArray(this->GetMesh()->VAO);

	GraphicsObject::SetDataGPU();

	glUniform4fv(this->pShaderObj->GetLocation("vBaseColorFactor"), 1, (float*)this->poBaseColor);
	glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float*)this->poLightPos);
	glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float*)this->poLightColor);
}

void GraphObj_TextureLight::Draw()
{
	//The starting point of the IBO
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->NumTris, GL_UNSIGNED_INT, 0);
}

void GraphObj_TextureLight::RestoreState()
{
	glDisable(GL_BLEND);
}

void GraphObj_TextureLight::SetTexture(TextureName name, unsigned int modelMatIndex)
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

void GraphObj_TextureLight::SetTexture(Texture& text)
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

void GraphObj_TextureLight::SetLightColor(const Vec4& lightColor)
{
	this->poLightColor->set(lightColor);
}

void GraphObj_TextureLight::SetLightPos(const Vec3& lightPos)
{
	this->poLightPos->set(lightPos);
}

void GraphObj_TextureLight::Wash()
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