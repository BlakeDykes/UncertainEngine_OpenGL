#ifndef MESH_CAMERA_H
#define MESH_CAMERA_H

#include "Mesh.h"
#include "Camera3D.h"

using namespace Uncertain;

class CameraMesh : public Mesh
{
public:
	CameraMesh(const char* const pMeshFileName, Camera3D* _pCamera);
	CameraMesh() = delete;
	CameraMesh(const CameraMesh&) = delete;
	CameraMesh& operator=(const CameraMesh&) = delete;
	virtual ~CameraMesh();

	Camera3D* pCamera;

private:
	virtual void CreateVAO(const char* const pMeshFileName) override;
};

#endif // !MESH_CAMERA_H