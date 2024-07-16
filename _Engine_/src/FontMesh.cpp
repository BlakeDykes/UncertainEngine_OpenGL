#include "FontMesh.h"

Tri_index triList_font[] = {
	{0, 2, 1},
	{2, 0, 3}
};

Vert_uv fontData_uv[] = {

	{0.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},

	{0.0f, 1.0f}
};

#define FONT_DATA_NUM_VERTS 4;
#define FONT_TRILIST_NUM_TRIANGLES (int)(sizeof(triList_font)/sizeof(Tri_index));

FontMesh::FontMesh(const char* const pMeshFileName)
{
	this->CreateVAO(pMeshFileName);
}

void FontMesh::CreateVAO(const char* const pMeshFileName)
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

	this->NumTris = FONT_TRILIST_NUM_TRIANGLES;
	this->NumVerts = FONT_DATA_NUM_VERTS;

	//-----------------------------
	// Send data to GPU
	//-----------------------------

	// Vert data - Dynamic Draw
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Verts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(float) * 2 * this->NumVerts), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// Text data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Texts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_uv) * this->NumVerts), fontData_uv, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_uv), 0);
	glEnableVertexAttribArray(2);

	// Index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->VBO_Index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->NumTris), triList_font, GL_STATIC_DRAW);
}