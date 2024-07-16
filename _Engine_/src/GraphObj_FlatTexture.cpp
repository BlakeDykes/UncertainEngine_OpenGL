#include "GraphObj_FlatTexture.h"
#include "Mesh.h"
#include "TextureManager.h"
#include "Texture.h"

using namespace Uncertain;

extern Mat4* pProjectionMatrix;

GraphObj_FlatTexture::GraphObj_FlatTexture(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj, TextureName name)
	: GraphicsObject(MaterialName::TEXT_FLAT, _pMeshNode, _pShaderObj), pTexture(nullptr)
{
	TextureManager::FindAndAssign(name, this->pTexture);
	assert(this->pTexture);

	assert(this->poWorld);
	assert(_pMeshNode);
	assert(_pShaderObj);
}

GraphObj_FlatTexture::GraphObj_FlatTexture(const MeshNode* const _pMeshNode, const ShaderObject* _pShaderObj)
	:GraphicsObject(MaterialName::TEXT_FLAT, _pMeshNode, _pShaderObj), pTexture(nullptr)
{
	TextureManager::FindAndAssign(TextureName::UNINITIALIZED, this->pTexture);

	assert(this->poWorld);
	assert(_pMeshNode);
	assert(_pShaderObj);
}

GraphObj_FlatTexture::~GraphObj_FlatTexture()
{
	if (this->pTexture)
	{
		this->pTexture->ManageActiveCount(-1);
		this->pTexture = nullptr;
	}
}

void GraphObj_FlatTexture::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	if (this->pTexture->bTextEnabled)
	{
		glBindTexture(GL_TEXTURE_2D, this->pTexture->GetID());
	}

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphObj_FlatTexture::SetDataGPU()
{
	this->pShaderObj->SetActive();

	glBindVertexArray(this->GetMesh()->VAO);

	GraphicsObject::SetDataGPU();
}

void GraphObj_FlatTexture::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->NumTris, GL_UNSIGNED_INT, 0);
}

void GraphObj_FlatTexture::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

void GraphObj_FlatTexture::SetTexture(TextureName name, unsigned int modelMatIndex)
{
	if (this->pTexture)
	{
		this->pTexture->ManageActiveCount(-1);
	}

	this->pTexture = TextureManager::FindTexture(name, modelMatIndex);
	assert(this->pTexture);

	this->pTexture->ManageActiveCount(1);
}

void GraphObj_FlatTexture::SetTexture(Texture& text)
{
	if (this->pTexture)
	{
		this->pTexture->ManageActiveCount(-1);
	}

	this->pTexture = &text;
	assert(this->pTexture);
	
	this->pTexture->ManageActiveCount(1);
}

void GraphObj_FlatTexture::Wash()
{
	if (this->pTexture)
	{
		this->pTexture->ManageActiveCount(-1);
		this->pTexture = nullptr;
	}

	GraphicsObject::Wash();
}