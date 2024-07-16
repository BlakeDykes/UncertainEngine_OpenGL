#include "ProtoMesh.h"
#include "ProtoData_Wrapper.h"
#include "MeshData.h"
#include "BoundingSphere.h"

using namespace Uncertain;

ProtoMesh::ProtoMesh(const char* const pMeshFileName)
	:Mesh(MeshName::PROTO_MESH, new BoundingSphere()), poInvBind(nullptr), InvBindCount(0)
{
	this->CreateVAO(pMeshFileName);
}

ProtoMesh::ProtoMesh(MeshData& meshData)
	: Mesh(MeshName::PROTO_MESH, new BoundingSphere()), poInvBind(nullptr), InvBindCount(0)
{
	this->CreateVAOFromProto(meshData);
}

void ProtoMesh::CreateVAOFromProto(MeshData& meshData)
{
	assert(meshData.VBOVert.TargetType == VBOData::VBO_TARGET::ARRAY_BUFFER);
	assert(meshData.VBOVert.VboType == VBOData::VBO_TYPE::VEC3);
	assert(meshData.VBOVert.ComponentType == VBOData::VBO_COMPONENT::FLOAT);

	assert(meshData.VBONorm.TargetType == VBOData::VBO_TARGET::ARRAY_BUFFER);
	assert(meshData.VBONorm.VboType == VBOData::VBO_TYPE::VEC3);
	assert(meshData.VBONorm.ComponentType == VBOData::VBO_COMPONENT::FLOAT);

	assert(meshData.VBOUV.TargetType == VBOData::VBO_TARGET::ARRAY_BUFFER);
	assert(meshData.VBOUV.VboType == VBOData::VBO_TYPE::VEC2);
	assert(meshData.VBOUV.ComponentType == VBOData::VBO_COMPONENT::FLOAT);

	//assert(meshData.VBOIndex.TargetType == VBOData::VBO_TARGET::ELEMENT_ARRAY_BUFFER);
	assert(meshData.VBOIndex.VboType == VBOData::VBO_TYPE::SCALAR);
	assert(meshData.VBOIndex.ComponentType == VBOData::VBO_COMPONENT::UNSIGNED_INT);

	// Create a VAO
	glGenVertexArrays(1, &this->VAO);
	assert(this->VAO);
	glBindVertexArray(this->VAO);

	// Create VBOs
	glGenBuffers(1, &this->VBO_Verts);
	assert(this->VBO_Verts != 0);

	glGenBuffers(1, &this->VBO_Norms);
	assert(this->VBO_Norms != 0);

	glGenBuffers(1, &this->VBO_Texts);
	assert(this->VBO_Texts != 0);

	glGenBuffers(1, &this->VBO_Index);
	assert(this->VBO_Index);

	glGenBuffers(1, &this->VBO_Weight);
	assert(this->VBO_Weight);

	glGenBuffers(1, &this->VBO_Joint);
	assert(this->VBO_Joint);

	this->NumVerts = (int)meshData.VBOVert.Count;
	this->NumTris = (int)meshData.VBOIndex.Count;
	assert(this->NumVerts > 0);
	assert(this->NumTris > 0);

	this->poBounding->Set(*meshData.poBounding);

	// Vert data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Verts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(meshData.VBOVert.DataSize), meshData.VBOVert.poData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyz), 0);
	glEnableVertexAttribArray(0);

	// Norm data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Norms);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(meshData.VBONorm.DataSize), meshData.VBONorm.poData, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_NxNyNz), 0);
	glEnableVertexAttribArray(1);

	// Text data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Texts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(meshData.VBOUV.DataSize), meshData.VBOUV.poData, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_uv), 0);
	glEnableVertexAttribArray(2);

	// Index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->VBO_Index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(meshData.VBOIndex.DataSize), meshData.VBOIndex.poData, GL_STATIC_DRAW);

	// Skinning Data
	if (meshData.poSkinData)
	{
		assert(meshData.poSkinData->VBOWeights.TargetType == VBOData::VBO_TARGET::ARRAY_BUFFER);
		assert(meshData.poSkinData->VBOWeights.VboType == VBOData::VBO_TYPE::VEC4);
		assert(meshData.poSkinData->VBOWeights.ComponentType == VBOData::VBO_COMPONENT::FLOAT);

		assert(meshData.poSkinData->VBOJoints.TargetType == VBOData::VBO_TARGET::ARRAY_BUFFER);
		assert(meshData.poSkinData->VBOJoints.VboType == VBOData::VBO_TYPE::VEC4);
		assert(meshData.poSkinData->VBOJoints.ComponentType == VBOData::VBO_COMPONENT::UNSIGNED_INT);

		assert(meshData.poSkinData->VBOInvBind.VboType == VBOData::VBO_TYPE::MAT4);
		assert(meshData.poSkinData->VBOInvBind.ComponentType == VBOData::VBO_COMPONENT::FLOAT);

		// Weights
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Weight);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(meshData.poSkinData->VBOWeights.DataSize), meshData.poSkinData->VBOWeights.poData, GL_STATIC_DRAW);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vert_weight), 0);
		glEnableVertexAttribArray(4);

		// Joints
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Joint);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(meshData.poSkinData->VBOJoints.DataSize), meshData.poSkinData->VBOJoints.poData, GL_STATIC_DRAW);
		glVertexAttribIPointer(5, 4, GL_UNSIGNED_INT, sizeof(Vert_joint), 0);
		glEnableVertexAttribArray(5);

		// Local invBind data
		assert(meshData.poSkinData->VBOInvBind.DataSize == sizeof(Mat4) * meshData.poSkinData->VBOInvBind.Count);
		this->InvBindCount = meshData.poSkinData->VBOInvBind.Count;
		this->poInvBind = new Mat4[InvBindCount]();
		memcpy_s(this->poInvBind, this->InvBindCount * sizeof(Mat4), meshData.poSkinData->VBOInvBind.poData, meshData.poSkinData->VBOInvBind.DataSize);
	}
}


ProtoMesh::~ProtoMesh()
{
	if (this->poInvBind)
	{
		delete[] poInvBind;
		poInvBind = nullptr;
	}
}

void ProtoMesh::CreateVAO(const char* const pMeshFileName)
{
	// Create a VAO
	glGenVertexArrays(1, &this->VAO);
	assert(this->VAO);
	glBindVertexArray(this->VAO);

	// Create VBOs
	glGenBuffers(1, &this->VBO_Verts);
	assert(this->VBO_Verts != 0);

	glGenBuffers(1, &this->VBO_Norms);
	assert(this->VBO_Norms != 0);

	glGenBuffers(1, &this->VBO_Texts);
	assert(this->VBO_Texts != 0);

	glGenBuffers(1, &this->VBO_Index);
	assert(this->VBO_Index);

	MeshData mesh;

	bool res;
	res = ProtoData_Wrapper::ReadFromFile(pMeshFileName, mesh);
	assert(res);

	assert(mesh.VBOVert.TargetType == VBOData::VBO_TARGET::ARRAY_BUFFER);
	assert(mesh.VBOVert.VboType == VBOData::VBO_TYPE::VEC3);
	assert(mesh.VBOVert.ComponentType == VBOData::VBO_COMPONENT::FLOAT);

	assert(mesh.VBONorm.TargetType == VBOData::VBO_TARGET::ARRAY_BUFFER);
	assert(mesh.VBONorm.VboType == VBOData::VBO_TYPE::VEC3);
	assert(mesh.VBONorm.ComponentType == VBOData::VBO_COMPONENT::FLOAT);

	assert(mesh.VBOUV.TargetType == VBOData::VBO_TARGET::ARRAY_BUFFER);
	assert(mesh.VBOUV.VboType == VBOData::VBO_TYPE::VEC2);
	assert(mesh.VBOUV.ComponentType == VBOData::VBO_COMPONENT::FLOAT);

	assert(mesh.VBOIndex.TargetType == VBOData::VBO_TARGET::ELEMENT_ARRAY_BUFFER);
	assert(mesh.VBOIndex.VboType == VBOData::VBO_TYPE::SCALAR);
	assert(mesh.VBOIndex.ComponentType == VBOData::VBO_COMPONENT::UNSIGNED_INT);

	this->NumVerts = (int)mesh.VBOVert.Count;
	this->NumTris = (int)mesh.VBOIndex.Count;
	assert(this->NumVerts > 0);
	assert(this->NumTris > 0);

	// Vert data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Verts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mesh.VBOVert.DataSize), mesh.VBOVert.poData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyz), 0);
	glEnableVertexAttribArray(0);

	// Norm data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Norms);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mesh.VBONorm.DataSize), mesh.VBONorm.poData, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_NxNyNz), 0);
	glEnableVertexAttribArray(1);

	// Text data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Texts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mesh.VBOUV.DataSize), mesh.VBOUV.poData, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_uv), 0);
	glEnableVertexAttribArray(2);

	// Index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->VBO_Index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(mesh.VBOIndex.DataSize), mesh.VBOIndex.poData, GL_STATIC_DRAW);

	// Skinning Data
	if (mesh.poSkinData)
	{
		assert(mesh.poSkinData->VBOWeights.TargetType == VBOData::VBO_TARGET::ARRAY_BUFFER);
		assert(mesh.poSkinData->VBOWeights.VboType == VBOData::VBO_TYPE::VEC4);
		assert(mesh.poSkinData->VBOWeights.ComponentType == VBOData::VBO_COMPONENT::FLOAT);

		assert(mesh.poSkinData->VBOJoints.TargetType == VBOData::VBO_TARGET::ARRAY_BUFFER);
		assert(mesh.poSkinData->VBOJoints.VboType == VBOData::VBO_TYPE::VEC4);
		assert(mesh.poSkinData->VBOJoints.ComponentType == VBOData::VBO_COMPONENT::UNSIGNED_INT);

		assert(mesh.poSkinData->VBOInvBind.VboType == VBOData::VBO_TYPE::MAT4);
		assert(mesh.poSkinData->VBOInvBind.ComponentType == VBOData::VBO_COMPONENT::FLOAT);

		glGenBuffers(1, &this->VBO_Joint);
		assert(this->VBO_Texts != 0);

		glGenBuffers(1, &this->VBO_Index);
		assert(this->VBO_Index);

		// Weights
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Weight);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mesh.poSkinData->VBOWeights.DataSize), mesh.poSkinData->VBOWeights.poData, GL_STATIC_DRAW);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vert_weight), 0);
		glEnableVertexAttribArray(4);

		// Joints
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Joint);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mesh.poSkinData->VBOJoints.DataSize), mesh.poSkinData->VBOJoints.poData, GL_STATIC_DRAW);
		glVertexAttribIPointer(5, 4, GL_UNSIGNED_INT, sizeof(Vert_joint), 0);
		glEnableVertexAttribArray(5);

		// Local invBind data
		assert(mesh.poSkinData->VBOInvBind.DataSize == sizeof(Mat4) * mesh.poSkinData->VBOInvBind.Count);
		this->InvBindCount = mesh.poSkinData->VBOInvBind.Count;
		this->poInvBind = new Mat4[InvBindCount]();
		memcpy_s(this->poInvBind, this->InvBindCount * sizeof(Mat4), mesh.poSkinData->VBOInvBind.poData, mesh.poSkinData->VBOInvBind.DataSize);

	}
}