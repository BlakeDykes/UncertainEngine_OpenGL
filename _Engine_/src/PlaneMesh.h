#ifndef PLANE_MESH_H
#define PLANE_MESH_H

#include "Mesh.h"

class PlaneMesh : public Mesh
{
public:
	PlaneMesh(const char* const pMeshFileName);
	PlaneMesh() = delete;
	PlaneMesh(const PlaneMesh&) = delete;
	PlaneMesh& operator=(const PlaneMesh&) = delete;
	virtual ~PlaneMesh();

private:
	virtual void CreateVAO(const char* const pMeshFileName) override;
};


#endif // !PLANE_MESH_H
