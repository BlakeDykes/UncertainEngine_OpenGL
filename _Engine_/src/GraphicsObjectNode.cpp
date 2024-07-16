#include "GraphicsObjectNode.h"
#include "GraphicsObjectManager.h"
#include "GraphicsObject.h"
#include "Mesh.h"
#include "BoundingObjectWrapper.h"
#include "UIStyle.h"

GraphicsObjectNode::GraphicsObjectNode()
	: poObject(nullptr), poBoundingGraphicsObject(nullptr)
{
}

GraphicsObjectNode::~GraphicsObjectNode()
{
	if (poBoundingGraphicsObject)
	{
		delete this->poBoundingGraphicsObject;
	}

	if (poObject)
	{
		delete this->poObject;
	}
}

void GraphicsObjectNode::Set(MATERIAL_ID id, GraphicsObject* pGraphObj)
{
	this->poObject = pGraphObj;
	this->poObject->SetID(id);
}

void GraphicsObjectNode::Render(bool drawBoundingObj)
{
	if (drawBoundingObj && this->poBoundingGraphicsObject)
	{
		this->poBoundingGraphicsObject->Render();
	}

	if (this->poObject)
	{
		this->poObject->Render();
	}
}

void GraphicsObjectNode::SetBoundingGraphicsObject(GraphicsObject* pSphereObject)
{
	this->poBoundingGraphicsObject = pSphereObject;
}

const char* GraphicsObjectNode::GetName()
{
	if (this->poObject)
	{
		return this->poObject->GetName();
	}
	else
	{
		return nullptr;
	}
}

bool GraphicsObjectNode::Compare(NodeBase& pNode)
{
	if (this->poObject)
	{
		return this->poObject->Compare((GraphicsObject&)pNode);
	}
	else
	{
		return false;
	}
}

void GraphicsObjectNode::Print()
{
	if (this->poObject)
	{
		this->poObject->Print();
	}
}

void GraphicsObjectNode::Wash()
{
	if (this->poObject)
	{
		delete this->poObject;
		this->poObject = nullptr;
	}
}

void GraphicsObjectNode::SetWorld(const Uncertain::Mat4& _world)
{
	if (this->poObject)
	{
		this->poObject->SetWorld(_world);
	}
}

void GraphicsObjectNode::SetTexture(TextureName name, unsigned int modelMatIndex)
{
	if (this->poObject)
	{
		this->poObject->SetTexture(name, modelMatIndex);
	}
}

void GraphicsObjectNode::SetTexture(Texture& text)
{
	if (this->poObject)
	{
		this->poObject->SetTexture(text);
	}
}

void GraphicsObjectNode::SetLightColor(const Vec4& lightColor)
{
	if (this->poObject)
	{
		this->poObject->SetLightColor(lightColor);
	}
}

void GraphicsObjectNode::SetLightPos(const Vec3& lightPos)
{
	if (this->poObject)
	{
		this->poObject->SetLightPos(lightPos);
	}
}

void GraphicsObjectNode::SetPhongData(const PhongData& data)
{
	if (this->poObject)
	{
		this->poObject->SetPhongData(data);
	}
}

void GraphicsObjectNode::SetBoneWorldResultBuffer(SSBO& boneResultBuffer)
{
	if (this->poObject)
	{
		this->poObject->SetBoneWorldResultBuffer(boneResultBuffer);
	}
}

void GraphicsObjectNode::SetUIStyle(const UIStyle& uiStyle)
{
	if (this->poObject)
	{
		this->poObject->SetUIStyle(uiStyle);
	}
}

void GraphicsObjectNode::UpdateBoundingObject(BoundingObject& boundingOut)
{
	boundingOut.Update(this->poObject->GetWorld(), this->poObject->GetMesh());

	if (this->poBoundingGraphicsObject)
	{
		boundingOut.UpdateGraphicsObject(this->poBoundingGraphicsObject);
	}
}

void GraphicsObjectNode::UpdateBoundingObjectFromGraphObj(BoundingObject& boundingOut)
{
	boundingOut.Set(*this->poObject->GetScreenRect());

	if (this->poBoundingGraphicsObject)
	{
		boundingOut.UpdateGraphicsObject(this->poBoundingGraphicsObject);
	}
}
