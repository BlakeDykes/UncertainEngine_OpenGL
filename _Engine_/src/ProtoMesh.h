#ifndef PROTO_MESH_H
#define PROTO_MESH_H

#include "Mesh.h"

class MeshData;

class ProtoMesh : public Mesh
{
public:
	ProtoMesh(const char* const pMeshFileName);
	ProtoMesh(MeshData& meshData);

	ProtoMesh() = delete;
	ProtoMesh(const ProtoMesh&) = delete;
	ProtoMesh& operator=(const ProtoMesh&) = delete;
	virtual ~ProtoMesh();

	virtual const Mat4& GetInvBindMats() const override { return *this->poInvBind; }
	virtual unsigned int GetInvBindCount() const override { return this->InvBindCount; }

private:
	virtual void CreateVAO(const char* const pMeshFileName) override;
	void CreateVAOFromProto(MeshData& meshData);

	Mat4* poInvBind;
	unsigned int InvBindCount;
};

#endif // !PROTO_MESH_H
