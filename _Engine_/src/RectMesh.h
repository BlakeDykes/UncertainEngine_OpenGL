#ifndef RECT_MESH_H
#define RECT_MESH_H

#include "Mesh.h"

class RectMesh : public Mesh
{
public:
	RectMesh(const char* const pMeshFileName);
	RectMesh() = delete;
	RectMesh(const RectMesh&) = delete;
	RectMesh& operator=(const RectMesh&) = delete;
	virtual ~RectMesh();

private:
	virtual void CreateVAO(const char* const pMeshFileName) override;
};


#endif // !SPRITE_MESH_H
