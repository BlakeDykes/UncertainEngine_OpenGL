#include "MeshNode.h"
#include "Mesh.h"

MeshNode::MeshNode()
	:poMesh(nullptr), NodeIndex(0)
{
}

MeshNode::~MeshNode()
{
	if (this->poMesh)
	{
		delete this->poMesh;
	}
}

void MeshNode::Set(MeshName name, Mesh* pMesh)
{
	this->poMesh = pMesh;
	this->poMesh->SetName(name);
}


const char* MeshNode::GetName()
{
	if (this->poMesh)
	{
		return this->poMesh->GetName();
	}
	else
	{
		return nullptr;
	}
}

bool MeshNode::Compare(NodeBase& pNode)
{
	if (this->poMesh)
	{
		MeshNode* pComp = (MeshNode*)&pNode;
		assert(pComp->GetMesh());

		return this->poMesh->Compare(*pComp->GetMesh());
	}
	else
	{
		return false;
	}
}

void MeshNode::Print()
{
	Trace::out("MeshNode ----- 0x%p\n", this);

	if (this->poMesh)
	{
		this->poMesh->Print();
	}
	else
	{
		Trace::out("---Mesh: nullptr\n");
	}

	DLink::Print();
}

void MeshNode::Wash()
{
	if (this->poMesh)
	{
		delete this->poMesh;
	}
	this->poMesh = nullptr;
}