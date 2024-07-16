#ifndef MESH_NODE_MAN_H
#define MESH_NODE_MAN_H

#include "ManagerBase.h"
#include "EngineNames.h"
#include "Camera3D.h"
#include "Camera2D.h"

class Mesh;
class MeshNode;
class MeshData;

using namespace Uncertain;

class MeshNodeManager : public ManagerBase
{
public:
	MeshNodeManager() = delete;
	MeshNodeManager(const MeshNodeManager&) = delete;
	MeshNodeManager& operator =(const MeshNodeManager&) = delete;

	static void Create(int initialReserved = 5, int deltaGrow = 5);
	static void Destroy();

	static MeshNode* Add(MeshName name, const char* const pFileName = nullptr, Camera* pCamera = nullptr);
	static MeshNode* Add(MeshData& meshData);
	static MeshNode* Find(MeshName name);
	static MeshNode* Find(NodeBase::Handle nodeID);
	static void Remove(MeshNode& pNode);

	static void PrintAll();

protected:
	virtual NodeBase* CreateNode() override;

private:
	MeshNodeManager(int initialReserved, int deltaGrow);
	static MeshNodeManager* GetInstance();
	virtual ~MeshNodeManager();
	void Clear();

	Mesh* GenerateMesh(MeshName name, const char* const pFileName = nullptr, Camera* pCamera = nullptr);

	static MeshNodeManager* instance;
	MeshNode* pCompNode;
};

#endif // !MESH_NODE_MAN_H
