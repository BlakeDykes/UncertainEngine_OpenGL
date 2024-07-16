#ifndef MESH_NODE_H
#define MESH_NODE_H

#include "DLink.h"
#include "EngineNames.h"

class Mesh;

class MeshNode : public DLink
{
public:
	MeshNode();
	MeshNode(const MeshNode&) = delete;
	MeshNode& operator=(const MeshNode&) = delete;
	virtual ~MeshNode();

	void Set(MeshName name, Mesh* pMesh);
	Mesh* GetMesh() const { return this->poMesh; }
	unsigned int GetNodeIndex() const { return this->NodeIndex; }
	void SetNodeIndex(unsigned int boneIndex) { this->NodeIndex = boneIndex; }
	virtual const char* GetName() override;

	virtual bool Compare(NodeBase& pNode) override;
	virtual void Print() override;
	virtual void Wash() override;

private:
	Mesh* poMesh;
	unsigned int NodeIndex;
};

#endif