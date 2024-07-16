#include "GraphicsObject.h"
#include "Mesh.h"
#include "CameraManager.h"
#include "Texture.h"
#include "UIStyle.h"

using namespace Uncertain;

const Vec4 GraphicsObject::DEFAULT_LIGHT_COLOR = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
const Vec3 GraphicsObject::DEFAULT_LIGHT_POS = Vec3(0.0f, 0.5f, 0.5f);

GraphicsObject::GraphicsObject(MaterialName name, const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj, bool isNull)
	: RenderMaterial(name), pMeshNode(_pMeshNode), pShaderObj(_pShaderObj), bIsNull(isNull)
{
	this->poWorld = new Mat4(Mat4::Special::Identity);

	assert(this->poWorld);
	assert(_pMeshNode);
	assert(_pShaderObj);
}

GraphicsObject::~GraphicsObject()
{
	delete this->poWorld;
}

void GraphicsObject::Render()
{
	this->SetState();
	this->SetDataGPU();
	this->Draw();
	this->RestoreState();
}

void GraphicsObject::SetDataGPU()
{
	Camera3D* pCam = CameraManager::GetActive3D();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&pCam->getProjMatrix());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&pCam->getViewMatrix());
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&this->GetWorld());
}


void GraphicsObject::SetTexture(TextureName name, unsigned int modelMatIndex)
{
	AZUL_UNUSED_VAR(name);
	AZUL_UNUSED_VAR(modelMatIndex);
}

void GraphicsObject::SetTexture(Texture& text)
{
	AZUL_UNUSED_VAR(text);
}

void GraphicsObject::SetLightColor(const Vec4& lightColor)
{
	AZUL_UNUSED_VAR(lightColor);
}

void GraphicsObject::SetLightPos(const Vec3& lightPos)
{
	AZUL_UNUSED_VAR(lightPos);
}

void GraphicsObject::SetPhongData(const PhongData& _pData)
{
	AZUL_UNUSED_VAR(_pData);
}

void GraphicsObject::SetFont(Font& font)
{
	AZUL_UNUSED_VAR(font);

}
void GraphicsObject::SetMessage(const char* const _pMessage)
{
	AZUL_UNUSED_VAR(_pMessage);
}

void GraphicsObject::SetBoneWorldResultBuffer(SSBO& boneResultBuffer)
{
	AZUL_UNUSED_VAR(boneResultBuffer);
}

void GraphicsObject::SetUIStyle(const UIStyle& uiStyle)
{	
	AZUL_UNUSED_VAR(uiStyle);
}

void GraphicsObject::SetScale(const Vec3& v)
{
	AZUL_UNUSED_VAR(v);
}

void GraphicsObject::SetTrans(const Vec3& v)
{
	AZUL_UNUSED_VAR(v);
}

void GraphicsObject::Print()
{
	Trace::out("---Graphics Material: 0x%p\n", this);
	Trace::out("------Name: %s\n", Stringify(this->Name));
	Trace::out("------ID: %d\n", this->MatID);
	Trace::out("------Mesh: %s\n", Stringify(this->pMeshNode->GetMesh()->Name));
	Trace::out("------Shader: %s\n", Stringify(this->pShaderObj->Name));
}

void GraphicsObject::Wash()
{
	this->bIsNull = false;
	this->pShaderObj = nullptr;
	this->pMeshNode = nullptr;
	this->MatID = -1;
	this->Name = MaterialName::UNINITIALIZED;
}
