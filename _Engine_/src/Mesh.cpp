#include "Mesh.h"
#include "MathEngine.h"
#include "BoundingObjectWrapper.h"

using namespace Uncertain;

Mesh::Mesh()
	:Name(MeshName::UNINITIALIZED), NumVerts(0), NumTris(0)
	, VAO(0), VBO_Verts(0), VBO_Norms(0), VBO_Texts(0), VBO_Index(0), 
	 VBO_Weight(0), VBO_Joint(0), poBounding(nullptr)
{
}

Mesh::Mesh(EngineNames::MeshName name, BoundingObject* _poBounding)
	: Name(name), NumVerts(0), NumTris(0), VAO(0), VBO_Verts(0),
	 VBO_Norms(0), VBO_Texts(0), VBO_Index(0), VBO_Weight(0), VBO_Joint(0), poBounding(_poBounding)
{
}

Mesh::~Mesh()
{
	delete this->poBounding;
}

void Mesh::CalculateNormals(int numVerts, int numTris, Vert_xyz* verts, Tri_index* indices, Vert_NxNyNz* pNormalsOut)
{

	Vec3 a;
	Vec3 b;
	Vec3 cross;

	for (int i = 0; i < numVerts; i++)
	{
		pNormalsOut[i].nx = 0.0f;
		pNormalsOut[i].ny = 0.0f;
		pNormalsOut[i].nz = 0.0f;
	}

	for (int i = 0; i < numTris; i++)
	{
		unsigned int i0 = indices[i].v0;
		unsigned int i1 = indices[i].v1;
		unsigned int i2 = indices[i].v2;

		// v0 - v1
		a = Vec3(verts[i1].x - verts[i0].x, verts[i1].y - verts[i0].y, verts[i1].z - verts[i0].z);

		// v2 - v1
		b = Vec3(verts[i2].x - verts[i0].x, verts[i2].y - verts[i0].y, verts[i2].z - verts[i0].z);

		cross = a.cross(b);

		pNormalsOut[i0] += cross;
		pNormalsOut[i1] += cross;
		pNormalsOut[i2] += cross;
	}

	Vec3 sum;
	bool* summed = new bool[(unsigned int)numVerts]();
	int* indicesAlike = new int[(unsigned int)numVerts]();


	memset(summed, false, ((unsigned int)numVerts) * sizeof(bool));
	memset(indicesAlike, -1, ((unsigned int)numVerts) * sizeof(int));

	for (int i = 0; i < numVerts; i++)
	{
		indicesAlike[0] = i;

		if (summed[i] == false)
		{
			sum = Vec3(pNormalsOut[i].nx, pNormalsOut[i].ny, pNormalsOut[i].nz);
			int alikeCount = 0;
			for (int k = i + 1; k < numVerts; k++)
			{
				if (verts[i] == verts[k] && summed[k] == false)
				{
					indicesAlike[++alikeCount] = k;
					sum += Vec3(pNormalsOut[k].nx, pNormalsOut[k].ny, pNormalsOut[k].nz);
				}
			}

			sum.norm();

			for(int j = 0; j <= alikeCount; j++)
			{
				pNormalsOut[indicesAlike[j]].nx = sum.x();
				pNormalsOut[indicesAlike[j]].ny = sum.y();
				pNormalsOut[indicesAlike[j]].nz = sum.z();
				summed[indicesAlike[j]] = true;
				indicesAlike[j] = -1;
			}
		}
	}

	delete[]indicesAlike;
	delete[]summed;


	/*Trace::out("\n----------Printing Normals---------------------\n");
	Trace::out("count - %d\n", numVerts);
	for (int k = 0; k < numVerts; k++)
	{
		Trace::out("%f, %f, %f\n", pNormalsOut[k].nx, pNormalsOut[k].ny, pNormalsOut[k].nz);
	}*/
}

void Mesh::Wash()
{
	this->Name = MeshName::UNINITIALIZED;
	this->NumVerts = 0;
	this->NumTris = 0;
	this->VAO = 0;
	VBO_Verts = 0;
	VBO_Texts = 0;
	VBO_Norms = 0;
	VBO_Index = 0;
	VBO_Joint = 0;
	VBO_Weight = 0;
}

bool Mesh::Compare(Mesh& pNode)
{
	return this->Name == pNode.Name;
}

const char* Mesh::GetName()
{
	return Stringify(this->Name);
}

void Mesh::SetName(MeshName name)
{
	this->Name = name;
}

void Mesh::Print()
{
	Trace::out("---Mesh: 0x%p\n");
	Trace::out("---Name: %s\n", Stringify(this->Name));
}

const Mat4& Mesh::GetInvBindMats() const
{
	assert(false);
	Mat4* temp = new Mat4();
	return *temp;;
}

unsigned int Mesh::GetInvBindCount() const
{
	assert(false);
	return 0;
}


