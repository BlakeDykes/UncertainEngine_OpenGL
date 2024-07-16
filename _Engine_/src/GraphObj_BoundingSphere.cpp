#include "GraphObj_BoundingSphere.h"
#include "Mesh.h"
#include "ShaderObject.h"
#include "CameraManager.h"

using namespace Uncertain;

extern Mat4* pProjectionMatrix;

GraphObj_BoundingSphere::GraphObj_BoundingSphere(const MeshNode* const _pMeshNode, const ShaderObject* const _pShaderObj)
	: GraphicsObject(MaterialName::BOUNDING_SPHERE, _pMeshNode, _pShaderObj)
{
	this->poLightColor = new Vec4(0.0f, 1.0f, 0.0f, 0.0f);
	this->poScale = new Vec3();
	this->poTrans = new Vec3();
	assert(this->poWorld);
	assert(_pMeshNode);
	assert(_pShaderObj);
}

GraphObj_BoundingSphere::~GraphObj_BoundingSphere()
{
	delete this->poLightColor;
	delete this->poScale;
	delete this->poTrans;
}

void GraphObj_BoundingSphere::SetState()
{
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GraphObj_BoundingSphere::SetDataGPU()
{
	this->pShaderObj->SetActive();

	glBindVertexArray(this->GetMesh()->VAO);

	Mat4 world = this->GetWorld();
	Mat4 scale(Mat4::Scale::XYZ, *this->poScale);
	Mat4 trans(Mat4::Trans::XYZ, *this->poTrans);

	world *= scale * trans;
	Mat4 view = CameraManager::GetActive3D()->getViewMatrix();
	Mat4 proj = CameraManager::GetActive3D()->getProjMatrix();

	glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&view);
	glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float*)&world);
	glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float*)this->poLightColor);
}

void GraphObj_BoundingSphere::Draw()
{
	glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->NumTris, GL_UNSIGNED_INT, 0);
}

void GraphObj_BoundingSphere::RestoreState()
{
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glFrontFace(GL_CCW);
}

void GraphObj_BoundingSphere::SetLightColor(const Vec4& color)
{
	this->poLightColor->set(color);
}

void GraphObj_BoundingSphere::SetScale(const Vec3& v)
{
	this->poScale->set(v);
}

void GraphObj_BoundingSphere::SetTrans(const Vec3& v)
{
	this->poTrans->set(v);
}