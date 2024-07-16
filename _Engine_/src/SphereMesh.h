#ifndef SPHERE_MESH_H
#define SPHERE_MESH_H

#include "Mesh.h"

class SphereMesh : public Mesh
{
public:
	SphereMesh(const char* const pMeshFileName);
	SphereMesh() = delete;
	SphereMesh(const SphereMesh&) = delete;
	SphereMesh& operator=(const SphereMesh&) = delete;
	virtual ~SphereMesh();

private:
	virtual void CreateVAO(const char* const pMeshFileName) override;
};


#endif // !SPHERE_MESH_H
