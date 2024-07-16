#ifndef NULL_MESH_H
#define NULL_MESH_H

#include "Mesh.h"

class NullMesh : public Mesh
{
public:
	NullMesh(const char* const pMeshFileName);
	NullMesh();
	NullMesh(const NullMesh&) = delete;
	NullMesh& operator=(const NullMesh&) = delete;
	virtual ~NullMesh() = default;

private:
	virtual void CreateVAO(const char* const pMeshFileName) override;
};

#endif