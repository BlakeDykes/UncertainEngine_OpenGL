#ifndef SPRITE_MESH_H
#define SPRITE_MESH_H

#include "Mesh.h"

class SpriteMesh : public Mesh
{
public:
	SpriteMesh(const char* const pMeshFileName);
	SpriteMesh() = delete;
	SpriteMesh(const SpriteMesh&) = delete;
	SpriteMesh& operator=(const SpriteMesh&) = delete;
	virtual ~SpriteMesh();

private:
	virtual void CreateVAO(const char* const pMeshFileName) override;
};


#endif // !SPRITE_MESH_H
