#include "RectMesh.h"
#include "BoundingObjectWrapper.h"

using namespace Uncertain;

Two_index twoList_rect[] = {
	{0, 1},
	{1, 2},
	{2, 3},
	{3, 0}
};

Vert_xyz rectData_xyz[] = {

	{ -0.5f,  0.5f, 0.0f},		// Left-Top
	{  0.5f,  0.5f, 0.0f},		// Right-Top
	{  0.5f, -0.5f, 0.0f},		// Right-Bottom
	{ -0.5f, -0.5f, 0.0f },		// Left-Bottom
};

#define RECT_DATA_NUM_VERTS (int)(sizeof(rectData_xyz)/sizeof(Vert_xyz));
#define RECT_TWOLIST_NUM_LINES (int)(sizeof(twoList_rect)/sizeof(Two_index));


void RectMesh::CreateVAO(const char* const pMeshFileName)
{
	AZUL_UNUSED_VAR(pMeshFileName);

	// Create a VAO
	glGenVertexArrays(1, &this->VAO);
	assert(this->VAO);
	glBindVertexArray(this->VAO);

	// Create VBOs
	glGenBuffers(1, &this->VBO_Verts);
	assert(this->VBO_Verts != 0);

	glGenBuffers(1, &this->VBO_Index);
	assert(this->VBO_Index);

	this->NumTris = RECT_TWOLIST_NUM_LINES;
	this->NumVerts = RECT_DATA_NUM_VERTS;

	//-----------------------------
	// Send data to GPU
	//-----------------------------
	// Vert data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Verts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyz) * this->NumVerts), rectData_xyz, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyz), 0);
	glEnableVertexAttribArray(0);

	// Index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->VBO_Index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Two_index) * this->NumTris), twoList_rect, GL_STATIC_DRAW);
}

RectMesh::RectMesh(const char* const pMeshFileName)
	:Mesh(MeshName::SPRITE_MESH, new BoundingRect())
{
	this->CreateVAO(pMeshFileName);
}

RectMesh::~RectMesh()
{

}