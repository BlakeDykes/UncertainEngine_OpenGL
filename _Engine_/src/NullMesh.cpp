#include "NullMesh.h"
#include "BoundingRect.h"

NullMesh::NullMesh(const char* const pMeshFileName)
	: Mesh(MeshName::NULL_MESH, new BoundingRect())
{
	AZUL_UNUSED_VAR(pMeshFileName);
}

NullMesh::NullMesh()
	: Mesh(MeshName::NULL_MESH, new BoundingRect())
{
}

void NullMesh::CreateVAO(const char* const pMeshFileName)
{
	AZUL_UNUSED_VAR(pMeshFileName);
}