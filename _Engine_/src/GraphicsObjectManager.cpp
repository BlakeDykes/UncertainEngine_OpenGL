#include "GraphicsObjectManager.h"
#include "GraphicsObjectNode.h"
#include "GraphicsObject.h"
#include "MeshNodeManager.h"
#include "MeshNode.h"
#include "ShaderManager.h"
#include "ShaderObject.h"
#include "DLinkManager.h"
#include "GraphicsObjects_Wrapper.h"
#include "ImageManager.h"
#include "Image.h"
#include "AnimController.h"

GraphicsObjectManager* GraphicsObjectManager::instance = nullptr;

GraphicsObjectManager::GraphicsObjectManager(int initialReserve, int deltaGrow)
	:ManagerBase(*new DLinkManager(), *new DLinkManager())
{
	this->SetReserve(initialReserve, deltaGrow);
}

GraphicsObjectManager::~GraphicsObjectManager()
{
	this->BaseClear();
	delete this->poCompNode;
}

void GraphicsObjectManager::Create(int initialReserve, int deltaGrow)
{
	assert(initialReserve >= 0);
	assert(deltaGrow > 0);
	assert(!instance);

	if (!instance)
	{
		instance = new GraphicsObjectManager(initialReserve, deltaGrow);

		instance->poCompNode = new GraphicsObjectNode();
	}
}

void GraphicsObjectManager::Destroy()
{
	GraphicsObjectManager* inst = GraphicsObjectManager::GetInstance();

	delete inst;

	instance = nullptr;
}

GraphicsObjectNode* GraphicsObjectManager::Add(MeshName meshName, ShaderName shaderName, MaterialName matName, bool generateBoundingSphere)
{
	GraphicsObjectManager* inst = GraphicsObjectManager::GetInstance();

	GraphicsObjectNode* pNode = (GraphicsObjectNode*)inst->BaseAdd();

	MeshNode* pMeshNode = MeshNodeManager::Find(meshName);
	assert(pMeshNode);

	ShaderObject* pShader = ShaderManager::Find(shaderName);
	assert(pShader);

	GraphicsObject* pGraphObj = inst->GenerateMaterial(matName, *pMeshNode, *pShader);
	if (generateBoundingSphere)
	{
		pNode->SetBoundingGraphicsObject(inst->GenerateMaterial(
			MaterialName::BOUNDING_SPHERE, 
			*MeshNodeManager::Find(MeshName::SPHERE_MESH), 
			*ShaderManager::Find(ShaderName::COLOR_CONST)));
	}

	pNode->Set(++inst->MaterialCount, pGraphObj);

	return pNode;
}

GraphicsObjectNode* GraphicsObjectManager::Add(ProtoNode& protoNode, ShaderName shaderName, MaterialName matName, bool generateBoundingSphere, Armature* armature)

{
	GraphicsObjectManager* inst = GraphicsObjectManager::GetInstance();

	GraphicsObjectNode* pNode = (GraphicsObjectNode*)inst->BaseAdd();

	ShaderObject* pShader = ShaderManager::Find(shaderName);
	assert(pShader);

	GraphicsObject* pGraphObj = inst->GenerateMaterial(matName, *protoNode.pMesh, *pShader, nullptr, armature);
	if (generateBoundingSphere)
	{
		pNode->SetBoundingGraphicsObject(inst->GenerateMaterial(
			MaterialName::BOUNDING_SPHERE,
			*MeshNodeManager::Find(MeshName::SPHERE_MESH),
			*ShaderManager::Find(ShaderName::COLOR_CONST)));
	}

	pNode->Set(++inst->MaterialCount, pGraphObj);

	return pNode;
}

GraphicsObjectNode* GraphicsObjectManager::Add(Image& image, ShaderName shaderName, MaterialName matName, bool generateBoundingSphere)
{
	GraphicsObjectManager* inst = GraphicsObjectManager::GetInstance();

	GraphicsObjectNode* pNode = (GraphicsObjectNode*)inst->BaseAdd();

	MeshNode* pMeshNode = MeshNodeManager::Find(MeshName::SPRITE_MESH);
	assert(pMeshNode);

	ShaderObject* pShader = ShaderManager::Find(shaderName);
	assert(pShader);

	GraphicsObject* pGraphObj = inst->GenerateMaterial(matName, *pMeshNode, *pShader, &image);

	if (generateBoundingSphere)
	{
		pNode->SetBoundingGraphicsObject(inst->GenerateMaterial(
			MaterialName::BOUNDING_RECT,
			*MeshNodeManager::Find(MeshName::RECT_MESH),
			*ShaderManager::Find(ShaderName::COLOR_CONST)));
	}

	pNode->Set(++inst->MaterialCount, pGraphObj);

	return pNode;
}

GraphicsObjectNode* GraphicsObjectManager::Add(Font& font, const char* const pMessage, ShaderName shaderName, MaterialName matName, bool generateBoundingSphere)
{
	GraphicsObjectManager* inst = GraphicsObjectManager::GetInstance();

	GraphicsObjectNode* pNode = (GraphicsObjectNode*)inst->BaseAdd();

	MeshNode* pMeshNode = MeshNodeManager::Find(MeshName::FONT_MESH);
	assert(pMeshNode);

	ShaderObject* pShader = ShaderManager::Find(shaderName);
	assert(pShader);

	GraphicsObject* pGraphObj = inst->GenerateMaterial(matName, *pMeshNode, *pShader);
	pGraphObj->SetFont(font);
	pGraphObj->SetMessage(pMessage);

	if (generateBoundingSphere)
	{
		pNode->SetBoundingGraphicsObject(inst->GenerateMaterial(
			MaterialName::BOUNDING_RECT,
			*MeshNodeManager::Find(MeshName::RECT_MESH),
			*ShaderManager::Find(ShaderName::COLOR_CONST)));
	}

	pNode->Set(++inst->MaterialCount, pGraphObj);

	return pNode;
}



void GraphicsObjectManager::Remove(GraphicsObjectNode& graphObj)
{
	GraphicsObjectManager* inst = GraphicsObjectManager::GetInstance();

	inst->BaseRemove(graphObj);
}

void GraphicsObjectManager::PrintAll()
{
	GraphicsObjectManager* inst = GraphicsObjectManager::GetInstance();

	Trace::out("\n");
	Trace::out("---------------------------------------\n");
	Trace::out("------ Active GraphicsObject Nodes ----\n");
	Trace::out("---------------------------------------\n");

	inst->BasePrintAll();

}

NodeBase* GraphicsObjectManager::CreateNode()
{
	return new GraphicsObjectNode();
}

GraphicsObjectManager* GraphicsObjectManager::GetInstance()
{
	assert(instance);

	return instance;
}

GraphicsObject* GraphicsObjectManager::GenerateMaterial(MaterialName matName, MeshNode& meshNode, ShaderObject& shader, Image* pImage, Armature* armature)
{
	GraphicsObject* pGraphObj = nullptr;

	switch (matName)
	{
	case EngineNames::MaterialName::COLOR_CONST:
		pGraphObj = new GraphObj_ConstColor(&meshNode, &shader);
		break;
	case EngineNames::MaterialName::COLOR_LIGHT:
		pGraphObj = new GraphObj_LightColor(&meshNode, &shader);
		break;
	case EngineNames::MaterialName::COLOR_PHONG_LIGHT:
		pGraphObj = new GraphObj_PhongColor(&meshNode, &shader);
		break;
	case EngineNames::MaterialName::TEXT_FLAT:
		pGraphObj = new GraphObj_FlatTexture(&meshNode, &shader);
		break;
	case EngineNames::MaterialName::TEXT_POINT_LIGHT:
		pGraphObj = new GraphObj_TextureLight(&meshNode, &shader);
		break;
	case EngineNames::MaterialName::SKIN_TEXT_POINT_LIGHT:
		assert(armature);
		pGraphObj = new GraphObj_SkinTextPointLight(&meshNode, &shader, armature->GetBoneResultBuffer());
		break;
	case EngineNames::MaterialName::SPRITE:
		assert(pImage);
		pGraphObj = new GraphObj_Sprite(&meshNode, &shader, pImage);
		break;
	case EngineNames::MaterialName::UI:
		assert(pImage);
		pGraphObj = new GraphObj_UI(&meshNode, &shader, pImage);
		break;
	case EngineNames::MaterialName::FONT:
		pGraphObj = new GraphObj_Font(&meshNode, &shader);
		break;
	case EngineNames::MaterialName::WIREFRAME:
		pGraphObj = new GraphObj_Wireframe(&meshNode, &shader);
		break;
	case EngineNames::MaterialName::BOUNDING_SPHERE:
		pGraphObj = new GraphObj_BoundingSphere(&meshNode, &shader);
		break;
	case EngineNames::MaterialName::BOUNDING_RECT:
		pGraphObj = new GraphObj_BoundingRect(&meshNode, &shader);
		break;
	case EngineNames::MaterialName::NULL_MAT:
		pGraphObj = new GraphObj_Null(&meshNode, &shader);
		break;

	case EngineNames::MaterialName::UNINITIALIZED:
	case EngineNames::MaterialName::PROTO:
	default:
		assert(false);
		break;
	}

	return pGraphObj;
}

