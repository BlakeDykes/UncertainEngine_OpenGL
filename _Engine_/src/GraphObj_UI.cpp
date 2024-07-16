#include "GraphObj_UI.h"
#include "Mesh.h"
#include "Texture.h"
#include "CameraManager.h"
#include "Camera2D.h"

GraphObj_UI::GraphObj_UI(const MeshNode* const _pMeshNode, const ShaderObject* const _pShader, Uncertain::Image* const _pImage)
	:GraphicsObject(MaterialName::UI, _pMeshNode, _pShader), pImage(_pImage)
{
	
	Mat4 scale(Mat4::Scale::XYZ, 
		this->pImage->ImageRect.Width / (float)this->pImage->pText->Width, 
		this->pImage->ImageRect.Height / (float)this->pImage->pText->Height,
		1.0f);

	Mat4 trans(Mat4::Trans::XYZ, 
		this->pImage->ImageRect.X / (float)this->pImage->pText->Width,
		this->pImage->ImageRect.Y / (float)this->pImage->pText->Height,
		1.0f);

	this->poMat4_uv = new Mat4(scale * trans);
}

GraphObj_UI::~GraphObj_UI()
{
	delete this->poMat4_uv;
}

void GraphObj_UI::SetState()
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

void GraphObj_UI::SetDataGPU()
{
	Camera2D* pCam = CameraManager::GetActive2D();
	
	this->pShaderObj->SetActive();
	glBindVertexArray(this->GetMesh()->VAO);

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&pCam->getProjMatrix());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&pCam->getViewMatrix());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&this->GetWorld());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("uv_matrix"), 1, GL_FALSE, (float*)this->poMat4_uv);
}

void GraphObj_UI::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->NumTris, GL_UNSIGNED_INT, 0);
}

void GraphObj_UI::RestoreState()
{
	glDisable(GL_BLEND);
}

void GraphObj_UI::Wash()
{
	this->poMat4_uv = nullptr;
}