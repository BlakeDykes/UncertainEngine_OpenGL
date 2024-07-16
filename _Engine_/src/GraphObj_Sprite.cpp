#include "GraphObj_Sprite.h"
#include "Texture.h"
#include "Camera2D.h"
#include "CameraManager.h"
#include "Mesh.h"

GraphObj_Sprite::GraphObj_Sprite(const MeshNode* const _pMeshNode, const ShaderObject* const _pShader, Image* const _pImage)
	: GraphicsObject(MaterialName::SPRITE, _pMeshNode, _pShader), pImage(_pImage)
{
	float w = this->pImage->ImageRect.Width / (float)this->pImage->pText->Width;
	float h = this->pImage->ImageRect.Height / (float)this->pImage->pText->Height;
	float u = this->pImage->ImageRect.X / (float)this->pImage->pText->Width;
	float v = this->pImage->ImageRect.Y / (float)this->pImage->pText->Height;
	Mat4 scale(Mat4::Scale::XYZ, w, h, 1.0f);
	Mat4 trans(Mat4::Trans::XYZ, u, v, 0.0f);
	
	this->poMatrix_uv = new Mat4(scale * trans);
	this->poMatrix_orig = new Mat4(Mat4::Scale::XYZ, this->pImage->ImageRect.Width, this->pImage->ImageRect.Height, 1.0f);
	//*this->poMatrix_orig *= Mat4(Mat4::Trans::XYZ, Vec3(0.0f, 0.0f, -1.0f));
}

GraphObj_Sprite::~GraphObj_Sprite()
{
	delete this->poMatrix_orig;
	delete this->poMatrix_uv;
}


void GraphObj_Sprite::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, this->pImage->pText->GetID());

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);

}

void GraphObj_Sprite::SetDataGPU()
{
	Camera2D* pCam = CameraManager::GetActive2D();

	this->pShaderObj->SetActive();
	glBindVertexArray(this->GetMesh()->VAO);
	
	Mat4 tmpMatrix = *this->poMatrix_orig * this->GetWorld();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&pCam->getProjMatrix());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&pCam->getViewMatrix());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&tmpMatrix);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("uv_matrix"), 1, GL_FALSE, (float*)this->poMatrix_uv);

}

void GraphObj_Sprite::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->NumTris, GL_UNSIGNED_INT, 0);
}

void GraphObj_Sprite::RestoreState()
{
	glDisable(GL_BLEND);
}

void GraphObj_Sprite::Wash()
{
	this->pImage = nullptr;
	this->poMatrix_orig = nullptr;
	this->poMatrix_uv = nullptr;
}
