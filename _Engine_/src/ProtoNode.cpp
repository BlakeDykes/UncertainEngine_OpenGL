#include "ProtoNode.h"
#include "Texture.h"
#include "MeshNode.h"
#include "Armature.h"

namespace Uncertain
{
	ProtoNode::ProtoNode(const char* const pName, unsigned int nodeIndex, MeshNode* mesh, Texture* text, ArmData* arm, ProtoNode* rootProto)
		: NodeIndex(nodeIndex), pMesh(mesh), pTexture(text),pArmData(arm), pRootProto(rootProto), Name{0}
	{
		memcpy_s(this->Name, MeshData::FILE_NAME_SIZE, pName, MeshData::FILE_NAME_SIZE);
	}

	ProtoNode::ProtoNode()
		: NodeIndex(UINT_MAX), pMesh(nullptr), pTexture(nullptr), pArmData(nullptr), pRootProto(nullptr), Name{ 0 }
	{
	}

	ProtoNode::ProtoNode(const char* pName)
		: NodeIndex(UINT_MAX), pMesh(nullptr), pTexture(nullptr), pArmData(nullptr), pRootProto(nullptr), Name{ 0 }
	{
		memcpy_s(this->Name, MeshData::FILE_NAME_SIZE, pName, MeshData::FILE_NAME_SIZE);
	}

	ProtoNode::~ProtoNode()
	{
	}

	void ProtoNode::SetTexture(Texture* pText)
	{
		this->pTexture = pText;
	}

	const char* ProtoNode::GetName()
	{
		return this->Name;
	}

	void ProtoNode::Print()
	{
		Trace::out("- Proto Node: %s\n", this->Name);
		Trace::out("\t			 Mesh : %s\n", this->pMesh->GetName());
		Trace::out("\t		  Texture : %s\n", this->pTexture->AssetName);
		Trace::out("\t	Armature Data : %s\n", this->pArmData->GetName());
		if (this->pRootProto)
		{
			Trace::out("\t		Root Node : %s\n", this->pRootProto->GetName());
		}
		else
		{
			Trace::out("\t		Root Node : NULL\n");
		}
	}

	void ProtoNode::Wash()
	{
		pMesh = nullptr;
		pTexture = nullptr;
		pArmData = nullptr;
		pRootProto = nullptr;
		memset(Name, '\0', ModelData::MODEL_NAME_SIZE);
	}
}
