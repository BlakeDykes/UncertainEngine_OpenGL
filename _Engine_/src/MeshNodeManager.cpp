#include "MeshNodeManager.h"
#include "DLinkManager.h"
#include "MeshNode.h"
#include "Mesh.h"
#include "MeshWrapper.h"

MeshNodeManager* MeshNodeManager::instance = nullptr;

MeshNodeManager::MeshNodeManager(int initialReserved, int deltaGrow)
	:ManagerBase(*new DLinkManager(), *new DLinkManager())
{
	this->SetReserve(initialReserved, deltaGrow);
}

MeshNodeManager::~MeshNodeManager()
{
	this->BaseClear();
	delete this->pCompNode;
}


void MeshNodeManager::Create(int initialReserved, int deltaGrow)
{
	assert(initialReserved >= 0);
	assert(deltaGrow > 0);
	assert(!instance);

	if (!instance)
	{
		instance = new MeshNodeManager(initialReserved, deltaGrow);

		Add(MeshName::NULL_MESH);
		Add(MeshName::SPHERE_MESH);
		Add(MeshName::RECT_MESH);
		Add(MeshName::SPRITE_MESH);
		Add(MeshName::FONT_MESH);

		instance->pCompNode = new MeshNode();
		instance->pCompNode->Set(MeshName::NULL_MESH, new NullMesh(GetFileName(MeshName::NULL_MESH)));
	}
}

void MeshNodeManager::Destroy()
{
	MeshNodeManager* inst = MeshNodeManager::GetInstance();

	delete inst;

	instance = nullptr;
}

MeshNode* MeshNodeManager::Add(MeshName name, const char* const pFileName, Camera* pCamera)
{
	MeshNodeManager* inst = MeshNodeManager::GetInstance();

	MeshNode* pNode = (MeshNode*)inst->BaseAdd();

	Mesh* pMesh = inst->GenerateMesh(name, pFileName, pCamera);

	pNode->Set(name, pMesh);

	return pNode;
}

MeshNode* MeshNodeManager::Add(MeshData& meshData)
{
	MeshNodeManager* inst = MeshNodeManager::GetInstance();

	MeshNode* pNode = (MeshNode*)inst->BaseAdd();

	Mesh* pMesh = new ProtoMesh(meshData);

	pNode->Set(MeshName::PROTO_MESH, pMesh);

	return pNode;
}

MeshNode* MeshNodeManager::Find(MeshName name)
{
	MeshNodeManager* inst = MeshNodeManager::GetInstance();

	inst->pCompNode->GetMesh()->SetName(name);

	return (MeshNode*)inst->BaseFind(*inst->pCompNode);
}

MeshNode* MeshNodeManager::Find(NodeBase::Handle nodeID)
{
	MeshNodeManager* inst = MeshNodeManager::GetInstance();

	return (MeshNode*)inst->BaseFindByHandle(nodeID);
}

void MeshNodeManager::Remove(MeshNode& pNode)
{
	MeshNodeManager* inst = MeshNodeManager::GetInstance();

	inst->BaseRemove(pNode);
}

void MeshNodeManager::PrintAll()
{
	MeshNodeManager* inst = MeshNodeManager::GetInstance();

	Trace::out("\n");
	Trace::out("----------------------------\n");
	Trace::out("------ Active MeshNodes ----\n");
	Trace::out("----------------------------\n");

	inst->BasePrintAll();
}

NodeBase* MeshNodeManager::CreateNode()
{
	return new MeshNode();
}

MeshNodeManager* MeshNodeManager::GetInstance()
{
	assert(instance);
	return instance;
}

void MeshNodeManager::Clear()
{
	this->BaseClear();
}

Mesh* MeshNodeManager::GenerateMesh(MeshName name, const char* const pFileName, Camera* pCamera)
{
	Mesh* pMesh = nullptr;

	const char* const file = pFileName ? pFileName : GetFileName(name);

	switch (name)
	{
	case EngineNames::MeshName::CUBE_MESH:
		pMesh = new CubeMesh(file);
		break;
	case EngineNames::MeshName::SPHERE_MESH:
		pMesh = new SphereMesh(file);
		break;
	case EngineNames::MeshName::RECT_MESH:
		pMesh = new RectMesh(file);
		break;
	case EngineNames::MeshName::PLANE_MESH:
		pMesh = new PlaneMesh(file);
		break;
	case EngineNames::MeshName::CONE_MESH:
		pMesh = new ConeMesh(file);
		break;
	case EngineNames::MeshName::TORUS_MESH:
		pMesh = new TorusMesh(file);
		break;
	case EngineNames::MeshName::ICOSPHERE_MESH:
		pMesh = new IcosphereMesh(file);
		break;
	case EngineNames::MeshName::CAMERA_MESH:
		assert(pCamera->GetType() == Camera::TYPE::PERSPECTIVE_3D);
		pMesh = new CameraMesh(file, (Camera3D*)pCamera);
		break;
	case EngineNames::MeshName::PROTO_MESH:
		pMesh = new ProtoMesh(file);
		break;
	case EngineNames::MeshName::SPRITE_MESH:
		pMesh = new SpriteMesh(file);
		break;
	case EngineNames::MeshName::FONT_MESH:
		pMesh = new FontMesh(file);
		break;
	case EngineNames::MeshName::NULL_MESH:
		pMesh = new NullMesh(file);
		break;
	case EngineNames::MeshName::UNINITIALIZED:
		break;
	default:
		assert(false);
		break;
	}

	return pMesh;
}