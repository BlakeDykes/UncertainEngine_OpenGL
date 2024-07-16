#include "TextureManager.h"
#include "TextureNode.h"
#include "Texture.h"
#include "DLinkManager.h"
#include "TextureData.h"
#include "ProtoToOpenGL.h"
#include "ProtoData_Wrapper.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager(int initialReserved, int deltaGrow)
	:ManagerBase(*new DLinkManager(), *new DLinkManager())
{
	this->pCompNode = new TextureNode();

	this->SetReserve(initialReserved, deltaGrow);
}

TextureManager::~TextureManager()
{
	this->Clear();
	delete this->pCompNode;
}

void TextureManager::Create(int initialReserved, int deltaGrow)
{
	assert(!instance);

	if (!instance)
	{
		instance = new TextureManager(initialReserved, deltaGrow);
	}
}

void TextureManager::Destroy()
{
	TextureManager* inst = TextureManager::GetInstance();

	delete inst;
	instance = nullptr;
}

TextureNode* TextureManager::Add(TextureName name, TextureNode::TYPE nodeType)
{
	TextureManager* inst = TextureManager::GetInstance();

	TextureNode* pNode = (TextureNode*)inst->BaseAdd();

	pNode->Set(name, nodeType);

	return pNode;
}

TextureNode* TextureManager::Add(TextureName name, TextureData& textData)
{
	TextureManager* inst = TextureManager::GetInstance();

	TextureNode* pNode = (TextureNode*)inst->BaseAdd();

	pNode->Set(name, textData);

	return pNode;
}


TextureNode* TextureManager::Add(TextureName name, ModelTextureData& data)
{
	TextureManager* inst = TextureManager::GetInstance();

	TextureNode* pNode = (TextureNode*)inst->BaseAdd();

	pNode->Set(name, data);

	return pNode;
}

TextureNode* TextureManager::Add(SpriteSheetData& data, SpriteSheetName ssName, Glyph*& pGlyphsOut)
{
	TextureManager* inst = TextureManager::GetInstance();

	TextureNode* pNode = (TextureNode*)inst->BaseAdd();

	pNode->Set(data, ssName, pGlyphsOut);

	return pNode;
}

TextureNode* TextureManager::Find(TextureName name)
{
	TextureManager* inst = TextureManager::GetInstance();

	inst->pCompNode->SetName(name);

	return (TextureNode*)inst->BaseFind(*inst->pCompNode);
}

TextureNode* TextureManager::Find(NodeBase::Handle nodeID)
{
	TextureManager* inst = TextureManager::GetInstance();

	return (TextureNode*)inst->BaseFindByHandle(nodeID);
}

Texture* TextureManager::FindTexture(TextureName name, unsigned int modelMatIndex)
{
	if (name == TextureName::UNINITIALIZED)
	{
		return nullptr;
	}

	TextureNode* pNode = TextureManager::Find(name);

	return pNode->GetTexture(modelMatIndex);
}


void TextureManager::FindAndAssign(TextureName name, Texture*& textureOut, unsigned int modelMatIndex)
{
	TextureManager* inst = TextureManager::GetInstance();
	Texture* pText = inst->FindTexture(name, modelMatIndex);

	if (pText)
	{
		if (textureOut)
		{
			textureOut->ManageActiveCount(-1);
		}

		textureOut = pText;

		textureOut->ManageActiveCount(1);
	}
}


GLuint TextureManager::FindID(TextureName name, unsigned int modelMatIndex)
{
	TextureManager* inst = TextureManager::GetInstance();

	Texture* pText = inst->FindTexture(name, modelMatIndex);
	assert(pText);

	return pText->GetID();
}

void TextureManager::Remove(TextureNode& pNode)
{
	TextureManager* inst = TextureManager::GetInstance();

	inst->BaseRemove(pNode);
}

//void TextureManager::PrintAll()
//{
//	TextureManager* inst = TextureManager::GetInstance();
//
//	Trace::out("\n");
//	Trace::out("-------------------------------\n");
//	Trace::out("----- Active TextureNodes -----\n");
//	Trace::out("-------------------------------\n");
//
//	inst->BasePrintAll();
//}

NodeBase* TextureManager::CreateNode()
{
	return new TextureNode();
}


void TextureManager::Clear()
{
	this->BaseClear();
}


TextureManager* TextureManager::GetInstance()
{
	assert(instance);
	return instance;
}

