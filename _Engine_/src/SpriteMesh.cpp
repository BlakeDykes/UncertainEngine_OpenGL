#include "SpriteMesh.h"
#include "File.h"
#include "MeshFileHdr.h"
#include "BoundingRect.h"

using namespace Uncertain;

Tri_index triList_sprite[] = {
	{0, 2, 1},
	{2, 0, 3}
};

Vert_xyz spriteData_xyz[] = {

	// Triangle 0
	{ -0.5f,  0.5f, 0.0f}, //0
	{  0.5f,  0.5f, 0.0f}, //1
	{  0.5f, -0.5f, 0.0f}, //2

	// Triangle 1
	{ -0.5f, -0.5f, 0.0f },  //3
};

Vert_uv spriteData_uv[] = {

	{0.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},

	{0.0f, 1.0f}
};

#define SPRITE_DATA_NUM_VERTS (int)(sizeof(spriteData_xyz)/sizeof(Vert_xyz));
#define SPRITE_TRILIST_NUM_TRIANGLES (int)(sizeof(triList_sprite)/sizeof(Tri_index));


void SpriteMesh::CreateVAO(const char* const pMeshFileName)
{
	AZUL_UNUSED_VAR(pMeshFileName);

	// Create a VAO
	glGenVertexArrays(1, &this->VAO);
	assert(this->VAO);
	glBindVertexArray(this->VAO);

	// Create VBOs
	glGenBuffers(1, &this->VBO_Verts);
	assert(this->VBO_Verts != 0);

	glGenBuffers(1, &this->VBO_Texts);
	assert(this->VBO_Texts != 0);

	glGenBuffers(1, &this->VBO_Index);
	assert(this->VBO_Index);

	this->NumTris = SPRITE_TRILIST_NUM_TRIANGLES;
	this->NumVerts = SPRITE_DATA_NUM_VERTS;

	//-----------------------------
	// Send data to GPU
	//-----------------------------

	// Vert data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Verts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyz)* this->NumVerts), spriteData_xyz, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyz), 0);
	glEnableVertexAttribArray(0);

	// Text data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Texts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_uv)* this->NumVerts), spriteData_uv, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_uv), 0);
	glEnableVertexAttribArray(2);

	// Index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->VBO_Index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index)* this->NumTris), triList_sprite, GL_STATIC_DRAW);
}

SpriteMesh::SpriteMesh(const char* const pMeshFileName)
	:Mesh(MeshName::SPRITE_MESH, new BoundingRect())
{
	this->CreateVAO(pMeshFileName);
}

SpriteMesh::~SpriteMesh()
{

}

