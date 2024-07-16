#ifndef TORUS_MESH_H
#define TORUS_MESH_H

#include "Mesh.h"

class TorusMesh : public Mesh
{
public:
	TorusMesh(const char* const pMeshFileName);
	TorusMesh() = delete;
	TorusMesh(const TorusMesh&) = delete;
	TorusMesh& operator=(const TorusMesh&) = delete;
	virtual ~TorusMesh();

private:
	virtual void CreateVAO(const char* const pMeshFileName) override;
};


#endif // !ICO_MESH_H