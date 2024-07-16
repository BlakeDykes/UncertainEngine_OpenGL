#include "CameraMesh.h"
#include "CameraManager.h"
#include "Camera.h"
#include "MeshFileHdr.h"
#include "File.h"
#include "BoundingSphere.h"

using namespace Uncertain;

#define WRITE_DATA_TO_FILE 0

#if WRITE_DATA_TO_FILE

Tri_index triList_camera[] =
{
	{ 0, 1, 2 },
	{ 0, 2, 3 },
	{ 0, 3, 4 },
	{ 0, 4, 1 },
	{ 1, 2, 3 },
	{ 3, 4, 1 },
	{ 5, 6, 7 },
	{ 7, 8, 5 }
};

Vert_xyz cameraData_xyz[9];

Vert_xyz cameraData_nxnynz[] =
{
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f}
};

Vert_xyz cameraData_uv[] =
{
	{0.0f, 0.0f},
	{0.0f, 0.0f},
	{0.0f, 0.0f},
	{0.0f, 0.0f},
	{0.0f, 0.0f},
	{0.0f, 0.0f},
	{0.0f, 0.0f},
	{0.0f, 0.0f},
	{0.0f, 0.0f},
};

#endif // WRITE_DATA_TO_FILE

CameraMesh::CameraMesh(const char* const pMeshFileName, Camera3D* _pCamera)
	: Mesh(MeshName::CAMERA_MESH, new BoundingSphere()), pCamera(_pCamera)
{
	this->CreateVAO(pMeshFileName);
}

CameraMesh::~CameraMesh()
{
	// not much
}

void CameraMesh::CreateVAO(const char* const pMeshFileName)
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


	Vec3 vTmp;

	this->pCamera->getPos(vTmp);
	cameraData_xyz[0].x = vTmp[x];
	cameraData_xyz[0].y = vTmp[y];
	cameraData_xyz[0].z = vTmp[z];

	this->pCamera->getFarTopRight(vTmp);
	cameraData_xyz[1].x = vTmp[x];
	cameraData_xyz[1].y = vTmp[y];
	cameraData_xyz[1].z = vTmp[z];


	this->pCamera->getFarTopLeft(vTmp);
	cameraData_xyz[2].x = vTmp[x];
	cameraData_xyz[2].y = vTmp[y];
	cameraData_xyz[2].z = vTmp[z];


	this->pCamera->getFarBottomLeft(vTmp);
	cameraData_xyz[3].x = vTmp[x];
	cameraData_xyz[3].y = vTmp[y];
	cameraData_xyz[3].z = vTmp[z];


	this->pCamera->getFarBottomRight(vTmp);
	cameraData_xyz[4].x = vTmp[x];
	cameraData_xyz[4].y = vTmp[y];
	cameraData_xyz[4].z = vTmp[z];


	this->pCamera->getNearTopRight(vTmp);
	cameraData_xyz[5].x = vTmp[x];
	cameraData_xyz[5].y = vTmp[y];
	cameraData_xyz[5].z = vTmp[z];


	this->pCamera->getNearTopLeft(vTmp);
	cameraData_xyz[6].x = vTmp[x];
	cameraData_xyz[6].y = vTmp[y];
	cameraData_xyz[6].z = vTmp[z];


	this->pCamera->getNearBottomLeft(vTmp);
	cameraData_xyz[7].x = vTmp[x];
	cameraData_xyz[7].y = vTmp[y];
	cameraData_xyz[7].z = vTmp[z];

	this->pCamera->getNearBottomRight(vTmp);
	cameraData_xyz[8].x = vTmp[x];
	cameraData_xyz[8].y = vTmp[y];
	cameraData_xyz[8].z = vTmp[z];
	

	#define CAMERA_DATA_NUM_VERTS (int)(sizeof(cameraData_xyz)/sizeof(Vert_xyz));
	#define CAMERA_TRILIST_NUM_TRIANGLES (int)(sizeof(triList_camera)/sizeof(Tri_index));

	this->NumVerts = CAMERA_DATA_NUM_VERTS;
	this->NumTris = CAMERA_TRILIST_NUM_TRIANGLES;

	strncpy_s(meshHdr.ObjName, MeshFileHdr::OBJECT_NAME_SIZE, EngineNames::Stringify(MeshName::CAMERA_MESH), _TRUNCATE);


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
	ferror = File::Write(fh, cameraData_xyz, sizeof(Vert_xyz) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	// Write norm buffer
	ferror = File::Tell(fh, meshHdr.normsBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Write(fh, cameraData_nxnynz, sizeof(Vert_NxNyNz) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	// Write texture buffer
	ferror = File::Tell(fh, meshHdr.textsBufferOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Write(fh, cameraData_uv, sizeof(Vert_uv) * this->NumVerts);
	assert(ferror == File::Error::SUCCESS);

	// Write index buffer
	ferror = File::Tell(fh, meshHdr.triListBufferdOffset);
	assert(ferror == File::Error::SUCCESS);
	ferror = File::Write(fh, triList_camera, sizeof(Tri_index) * this->NumTris);
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
	Vert_uv* data_uv = new Vert_uv[(unsigned int)meshHdr.numVerts];
	assert(data_uv);
	Vert_NxNyNz* data_nxnynz = new Vert_NxNyNz[(unsigned int)meshHdr.numVerts];
	assert(data_nxnynz);
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

	//-----------------------------
	// Send data to GPU
	//-----------------------------

	// Vert data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Verts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyz) * this->NumVerts), data_xyz, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyz), 0);
	glEnableVertexAttribArray(0);

	// Norm data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Norms);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_NxNyNz) * this->NumVerts), data_nxnynz, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_NxNyNz), 0);
	glEnableVertexAttribArray(1);

	// Text data
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_Texts);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_uv) * this->NumVerts), data_uv, GL_STATIC_DRAW);
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
