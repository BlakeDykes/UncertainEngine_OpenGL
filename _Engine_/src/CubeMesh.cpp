#include "CubeMesh.h"
#include "File.h"
#include "MeshFileHdr.h"
#include "BoundingSphere.h"

using namespace Uncertain;

#define WRITE_DATA_TO_FILE 0

#if WRITE_DATA_TO_FILE

Tri_index triList_cube[] =
{
	{  1,  0,  2 }, 
	{  4,  3,  5 }, 
	{  7,  6,  8 },
	{ 10,  9, 11 },
	{ 13, 12, 14 },
	{ 16, 15, 17 },
	{ 19, 18, 20 },
	{ 22, 21, 23 },
	{ 25, 24, 26 },
	{ 28, 27, 29 },
	{ 31, 30, 32 },
	{ 34, 33, 35 }
};

Vert_xyz cubeData_xyz[] =
{

	// Triangle 0
	{ -1.0f,  1.0f, -1.0f },
	{ -1.0f, -1.0f, -1.0f },
	{ 1.0f, -1.0f,  -1.0f },

	// Triangle 1
	{ 1.0f,  -1.0f, -1.0f },
	{ 1.0f,   1.0f, -1.0f },
	{ -1.0f,  1.0f, -1.0f },
	
	// Triangle 2
	{ 1.0f, -1.0f, -1.0f },
	{ 1.0f, -1.0f,  1.0f },
	{ 1.0f,  1.0f, -1.0f },
	
	// Triangle 3
	{ 1.0f, -1.0f,  1.0f },
	{ 1.0f,  1.0f,  1.0f },
	{ 1.0f,  1.0f, -1.0f },
	
	// Triangle 4
	{ 1.0f, -1.0f,  1.0f },
	{ -1.0f, -1.0f, 1.0f },
	{ 1.0f,  1.0f,  1.0f },
	
	// Triangle 5
	{ -1.0f, -1.0f,  1.0f },
	{ -1.0f,  1.0f,  1.0f },
	{ 1.0f,   1.0f,  1.0f },
	
	// Triangle 6
	{ -1.0f, -1.0f,  1.0f },
	{ -1.0f, -1.0f, -1.0f },//
	{ -1.0f,  1.0f,  1.0f },
	
	// Triangle 7
	{ -1.0f, -1.0f, -1.0f },
	{ -1.0f,  1.0f, -1.0f },
	{ -1.0f,  1.0f,  1.0f },
	
	// Triangle 8
	{ -1.0f, -1.0f,  1.0f },
	{ 1.0f, -1.0f,   1.0f },
	{ 1.0f, -1.0f,  -1.0f },
	
	// Triangle 9
	{ 1.0f, -1.0f,  -1.0f },
	{ -1.0f, -1.0f, -1.0f },
	{ -1.0f, -1.0f,  1.0f },
	
	// Triangle 10
	{ -1.0f,  1.0f, -1.0f },
	{ 1.0f,  1.0f,  -1.0f },
	{ 1.0f,  1.0f,   1.0f },
	
	// Triangle 11
	{ 1.0f,  1.0f,   1.0f },
	{ -1.0f,  1.0f,  1.0f },
	{ -1.0f,  1.0f, -1.0f }
};

Vert_uv cubeData_uv[] =
{
	// Triangle 0
	{ 0.0f, 0.0f },
	{ 0.0f, 1.0f },
	{ 1.0f, 1.0f },

	// Triangle 1
	{ 1.0f, 1.0f },
	{ 1.0f, 0.0f },
	{ 0.0f, 0.0f },

	// Triangle 2
	{ 0.0f, 1.0f },
	{ 1.0f, 1.0f },
	{ 0.0f, 0.0f },

	// Triangle 3
	{ 1.0f, 1.0f },
	{ 1.0f, 0.0f },
	{ 0.0f, 0.0f },

	// Triangle 4
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 1.0f, 0.0f },

	// Triangle 5
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },

	// Triangle 6
	{ 0.0f, 0.0f },
	{ 0.0f, 1.0f },
	{ 1.0f, 0.0f },

	// Triangle 7
	{ 0.0f, 1.0f },
	{ 1.0f, 1.0f },
	{ 1.0f, 0.0f },

	// Triangle 8
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f },

	// Triangle 9
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f },

	// Triangle 10
	{ 0.0f, 1.0f },
	{ 1.0f, 1.0f },
	{ 1.0f, 0.0f },

	// Triangle 11
	{ 1.0f, 0.0f },
	{ 0.0f, 0.0f },
	{ 0.0f, 1.0f }
};

Vert_NxNyNz cubeData_nxnynz[sizeof(cubeData_xyz)/sizeof(Vert_xyz)];


#define CUBE_DATA_NUM_VERTS (int)(sizeof(cubeData_xyz)/sizeof(Vert_xyz));
#define TRILIST_NUM_TRIANGLES (int)(sizeof(triList_cube)/sizeof(Tri_index));

#endif // WRITE_DATA_TO_FILE


CubeMesh::CubeMesh(const char* const pMeshFileName)
	:Mesh(MeshName::CUBE_MESH, new BoundingSphere())
{
	this->CreateVAO(pMeshFileName);
}

void CubeMesh::CreateVAO(const char* const pMeshFileName)
{
	assert(pMeshFileName);
	AZUL_UNUSED_VAR(pMeshFileName);

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

	File::Handle fh;
	File::Error ferror;

	MeshFileHdr meshHdr;

	//-----------------------------
	// Write data from file
	//-----------------------------

#if WRITE_DATA_TO_FILE

	this->NumVerts = CUBE_DATA_NUM_VERTS;
	this->NumTris = TRILIST_NUM_TRIANGLES;

	strncpy_s(meshHdr.ObjName, MeshFileHdr::OBJECT_NAME_SIZE, EngineNames::Stringify(MeshName::CUBE_MESH), _TRUNCATE);

	meshHdr.numVerts = this->NumVerts;
	meshHdr.vertexBufferOffset = 0;
	meshHdr.textsBufferOffset = 0;
	meshHdr.normsBufferOffset = 0;

	meshHdr.numTriList = this->NumTris;
	meshHdr.triListBufferdOffset = 0;


	ferror = File::Open(fh, pMeshFileName, File::Mode::READ_WRITE);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, &meshHdr, sizeof(MeshFileHdr));
	assert(ferror == File::Error::SUCCESS);

	// Write vert buffer
	ferror = File::Tell(fh, meshHdr.vertexBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Write(fh, cubeData_xyz, sizeof(Vert_xyz) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	// Write norm buffer
	this->CalculateNormals(this->NumVerts, this->NumTris, cubeData_xyz, triList_cube, cubeData_nxnynz);
	ferror = File::Tell(fh, meshHdr.normsBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Write(fh, cubeData_nxnynz, sizeof(Vert_NxNyNz) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	// Write index buffer
	ferror = File::Tell(fh, meshHdr.triListBufferdOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Write(fh, triList_cube, sizeof(Tri_index) * this->NumTris);
	assert(ferror == File::Error::SUCCESS);

	// Write texture buffer
	ferror = File::Tell(fh, meshHdr.textsBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Write(fh, cubeData_uv, sizeof(Vert_uv) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Flush(fh);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Position::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, &meshHdr, sizeof(MeshFileHdr));
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Flush(fh);
	assert(ferror == File::Error::SUCCESS);

	MeshFileHdr meshHdr2;

	ferror = File::Seek(fh, File::Position::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh, &meshHdr2, sizeof(MeshFileHdr));
	assert(ferror == File::Error::SUCCESS);

	assert(memcmp(&meshHdr, &meshHdr2, sizeof(MeshFileHdr)) == 0);

	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

#endif

	//-----------------------------
	// Read data from file
	//-----------------------------
	ferror = File::Open(fh, pMeshFileName, File::Mode::READ);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh, &meshHdr, sizeof(MeshFileHdr));
	assert(ferror == File::Error::SUCCESS);

	this->NumVerts = meshHdr.numVerts;
	this->NumTris = meshHdr.numTriList;

	// Create data buffers
	Vert_xyz* data_xyz = new Vert_xyz[(unsigned int)meshHdr.numVerts];
	assert(data_xyz);
	Vert_NxNyNz* data_nxnynz = new Vert_NxNyNz[(unsigned int)meshHdr.numVerts];
	assert(data_nxnynz);
	Vert_uv* data_uv = new Vert_uv[(unsigned int)meshHdr.numVerts];
	assert(data_uv);
	Tri_index* data_TriList = new Tri_index[(unsigned int)meshHdr.numTriList];
	assert(data_TriList);

	// Read verts from meshHdr into buffers
	ferror = File::Seek(fh, File::Position::BEGIN, (int)meshHdr.vertexBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Read(fh, data_xyz, sizeof(Vert_xyz) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Position::BEGIN, (int)meshHdr.normsBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Read(fh, data_nxnynz, sizeof(Vert_uv) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Position::BEGIN, (int)meshHdr.textsBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Read(fh, data_uv, sizeof(Vert_uv) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Seek(fh, File::Position::BEGIN, (int)meshHdr.triListBufferdOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Read(fh, data_TriList, sizeof(Tri_index) * this->NumTris);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);

	//// Calculate Ritter Sphere
	//Vec3* pVerts = new Vec3[(unsigned int)this->NumVerts]();
	//for (int i = 0; i < this->NumVerts; i++)
	//{
	//	pVerts[i].set(data_xyz[i].x, data_xyz[i].y, data_xyz[i].z);

	//}

	//this->poBounding->RitterSphere(pVerts, (unsigned int)this->NumVerts);
	//delete[] pVerts;

	//-----------------------------
	// Send data to GPU
	//-----------------------------

	// Vert data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Verts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyz) * this->NumVerts), data_xyz, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyz), 0);
	glEnableVertexAttribArray(0);

	// Norm data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Norms);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_NxNyNz) * this->NumVerts), data_nxnynz, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_NxNyNz), 0);
	glEnableVertexAttribArray(1);

	// Text data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Texts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_uv)* this->NumVerts), data_uv, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_uv), 0);
	glEnableVertexAttribArray(2);

	// Index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->VBO_Index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->NumTris), data_TriList, GL_STATIC_DRAW);

	delete[] data_xyz;
	delete[] data_uv;
	delete[] data_nxnynz;
	delete[] data_TriList;
}

CubeMesh::~CubeMesh()
{
	// Remove dynamic
}