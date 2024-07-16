#ifndef MESH_H
#define MESH_H

#include "sb7.h"
#include "MathEngine.h"
#include "EngineNames.h"
#include "NodeBase.h"

using namespace Uncertain;

class BoundingObject;

struct Vert_xyzuvn
{
	float x;
	float y;
	float z;
	float u;
	float v;
	float nx;
	float ny;
	float nz;
};

struct Vert_xyz
{
	float x;
	float y;
	float z;

	bool operator==(const Vert_xyz& v) const
	{
		//using fabs
		float xEqual = (float)fabs(this->x - v.x);
		float yEqual = (float)fabs(this->y - v.y);
		float zEqual = (float)fabs(this->z - v.z);

		return xEqual <= Uncertain::MATH_TOLERANCE &&
			yEqual <= Uncertain::MATH_TOLERANCE &&
			zEqual <= Uncertain::MATH_TOLERANCE;
	}
};

struct Vert_NxNyNz
{
	float nx;
	float ny;
	float nz;

	Vert_NxNyNz& operator+=(const Uncertain::Vec3& v)
	{
		this->nx += v.x();
		this->ny += v.y();
		this->nz += v.z();

		return *this;
	}

};

struct Vert_uv
{
	float u;
	float v;
};

struct Vert_weight
{
	float wa;
	float wb;
	float wc;
	float wd;
};

struct Vert_joint
{
	unsigned int ja;
	unsigned int jb;
	unsigned int jc;
	unsigned int jd;
};


struct Two_index
{
	unsigned int v0;
	unsigned int v1;
};

struct Tri_index
{
	unsigned int v0;
	unsigned int v1;
	unsigned int v2;
};

class Mesh
{
public:
	EngineNames::MeshName Name;
	int NumVerts;
	int NumTris;
	GLuint VAO;
	GLuint VBO_Verts;
	GLuint VBO_Norms;
	GLuint VBO_Texts;
	GLuint VBO_Index;
	GLuint VBO_Weight;
	GLuint VBO_Joint;

	Mesh();
	Mesh(EngineNames::MeshName name, BoundingObject* _poBounding);
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;
	virtual ~Mesh();

	void CalculateNormals(int numVerts, int numTris, Vert_xyz* verts, Tri_index* indices, Vert_NxNyNz* pNormalsOut);
	
	void Wash();
	bool Compare(Mesh& pNode);
	const char* GetName();
	void SetName(EngineNames::MeshName name);
	void Print();

	BoundingObject* poBounding;

	virtual const Mat4& GetInvBindMats() const;
	virtual unsigned int GetInvBindCount() const;

protected:
	virtual void CreateVAO(const char* const pMeshFileName) = 0;
};



#endif