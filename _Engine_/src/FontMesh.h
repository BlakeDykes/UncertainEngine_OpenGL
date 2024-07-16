#ifndef FONT_MESH_H
#define FONT_MESH_H

#include "Mesh.h"

class FontMesh : public Mesh
{
public:
	FontMesh(const char* const pMeshFileName);
	FontMesh() = delete;
	FontMesh(const FontMesh&) = delete;
	FontMesh& operator=(const FontMesh&) = delete;
	virtual ~FontMesh() = default;

private:
	virtual void CreateVAO(const char* const pMeshFileName) override;
};


#endif // !SPRITE_MESH_H
