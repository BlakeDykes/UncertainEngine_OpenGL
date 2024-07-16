#ifndef CONE_MESH_H
#define CONE_MESH_H

#include "Mesh.h"

class ConeMesh : public Mesh
{
public:
	ConeMesh(const char* const pMeshFileName);
	ConeMesh() = delete;
	ConeMesh(const ConeMesh&) = delete;
	ConeMesh& operator=(const ConeMesh&) = delete;
	virtual ~ConeMesh();

private:
	virtual void CreateVAO(const char* const pMeshFileName) override;
};


#endif // !CONE_MESH_H