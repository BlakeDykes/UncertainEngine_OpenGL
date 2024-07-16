#ifndef MESH_CUBE_H
#define MESH_CUBE_H

#include "Mesh.h"

class CubeMesh : public Mesh
{
public:
	CubeMesh(const char* const pMeshFileName);
	CubeMesh() = delete;
	CubeMesh(const CubeMesh&) = delete;
	CubeMesh& operator=(const CubeMesh&) = delete;
	virtual ~CubeMesh();

private:
	virtual void CreateVAO(const char* const pMeshFileName) override;
};

#endif // !CUBE_Mesh_H

