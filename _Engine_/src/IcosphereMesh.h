#ifndef ICO_MESH_H
#define ICO_MESH_H

#include "Mesh.h"

class IcosphereMesh : public Mesh
{
public:
	IcosphereMesh(const char* const pMeshFileName);
	IcosphereMesh() = delete;
	IcosphereMesh(const IcosphereMesh&) = delete;
	IcosphereMesh& operator=(const IcosphereMesh&) = delete;
	virtual ~IcosphereMesh();

private:
	virtual void CreateVAO(const char* const pMeshFileName) override;
};


#endif // !ICO_MESH_H