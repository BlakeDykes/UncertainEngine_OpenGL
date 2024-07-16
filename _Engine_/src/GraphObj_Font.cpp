#include "GraphObj_Font.h"
#include "CameraManager.h"
#include "Camera2D.h"
#include "Mesh.h"
#include "Glyph.h"
#include "Texture.h"
#include "UIStyle.h"

GraphObj_Font::GraphObj_Font(const MeshNode* const _pMeshNode, const ShaderObject* const _pShader)
	: GraphicsObject(MaterialName::FONT, _pMeshNode, _pShader), pFont(nullptr), pMessage(nullptr), 
	poVerts(new DynamicVec2[4]()), poLightColor(new Vec4(1.0f, 1.0f, 1.0f)), StartingX(0.0f),
	poScreenRect(new Mat4(Mat4::IDENTITY_MAT4))
{
}


GraphObj_Font::~GraphObj_Font()
{
	delete this->poScreenRect;
	delete this->poLightColor;
	delete[] this->poVerts;
}

void GraphObj_Font::Render()
{
	// Early break if no message
	if (!this->pMessage)
	{
		return;
	}

	this->SetState();
	this->SetDataGPU();
	this->RestoreState();
}

void GraphObj_Font::SetState()
{
	glActiveTexture(GL_TEXTURE0);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);

	//glEnable(GL_BLEND);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GraphObj_Font::SetDataGPU()
{
	assert(this->pFont);

	Camera2D* pCam = CameraManager::GetActive2D();

	this->pShaderObj->SetActive();
	glBindVertexArray(this->GetMesh()->VAO);

	glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float*)this->poLightColor);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&pCam->getProjMatrix());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&pCam->getViewMatrix());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&this->GetWorld());

	int messageSize = strlen(this->pMessage);
	Glyph* pGlyph = nullptr;
	
	float scale = this->poWorld->m0();
	assert(this->poWorld->m0() == this->poWorld->m5());

	float w, h;
	float maxHeight = 0.0f;
	float totalWidth = 0.0f;

	for (int i = 0; i < messageSize; i++)
	{
		pGlyph = this->pFont->GetGlyph(int(this->pMessage[i]));

		totalWidth += (pGlyph->ImageRect.Width + 5.0f) * scale;

	}

	// Left justified
	this->StartingX = 0.0f;
	float currentX = this->StartingX;

	for (int i = 0; i < messageSize; i++)
	{
		pGlyph = this->pFont->GetGlyph(int(this->pMessage[i]));

		if (pGlyph->ImageRect.Height * scale > maxHeight)
		{
			maxHeight = pGlyph->ImageRect.Height * scale;
		}

		w = pGlyph->ImageRect.Width * 0.5f * scale;
		h = pGlyph->ImageRect.Height * 0.5f * scale;

		currentX += w;

		this->poVerts[0].Set(currentX - w,  h);
		this->poVerts[1].Set(currentX + w,  h);
		this->poVerts[2].Set(currentX + w, -h);
		this->poVerts[3].Set(currentX - w, -h);

		glBindTexture(GL_TEXTURE_2D, pGlyph->pText->GetID());
		glBindBuffer(GL_ARRAY_BUFFER, this->pMeshNode->GetMesh()->VBO_Verts);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(DynamicVec2) * 4, (void*)this->poVerts);

		Draw();

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		currentX += (w + (5.0f * scale));
	}

	this->SetScreenRect(this->StartingX, this->poWorld->m13(), totalWidth, maxHeight);
}

void GraphObj_Font::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->NumTris, GL_UNSIGNED_INT, 0);
}

void GraphObj_Font::RestoreState()
{
	glDisable(GL_BLEND);
}

void GraphObj_Font::Wash()
{
	this->pFont = nullptr;
	this->pMessage = nullptr;
	this->poVerts[0].Set(0.0f, 0.0f);
	this->poVerts[1].Set(0.0f, 0.0f);
	this->poVerts[2].Set(0.0f, 0.0f);
	this->poVerts[3].Set(0.0f, 0.0f);
	this->StartingX = 0.0f;
}

void GraphObj_Font::SetFont(Font& font)
{
	this->pFont = &font;
}

void GraphObj_Font::SetMessage(const char* const _pMessage)
{
	this->pMessage = _pMessage;
}

void GraphObj_Font::SetLightColor(const Vec4& lightColor)
{
	this->poLightColor->set(lightColor);
}

void GraphObj_Font::SetUIStyle(const UIStyle& uiStyle)
{
	this->pUIStyle = &uiStyle;
}

void GraphObj_Font::SetScreenRect(float x, float y, float width, float height)
{
	this->poScreenRect->m0(width);
	this->poScreenRect->m5(height);
	this->poScreenRect->m12(x);
	this->poScreenRect->m13(y);
}

void GraphObj_Font::DynamicVec2::Set(float _x, float _y)
{
	this->x = _x;
	this->y = _y;
}
