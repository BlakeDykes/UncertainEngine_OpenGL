#include "UIManager.h"
#include "DLinkManager.h"
#include "DLinkIterator.h"
#include "GameObjectManager.h"
#include "GameObjectUIElement.h"
#include "GameObjectUIRoot.h"

UIManager* UIManager::instance = nullptr;

UIManager::UIManager(int initialReserved, int deltaGrow)
	: ManagerBase(*new DLinkManager(), *new DLinkManager)
{
	this->poCompNode = new UINode();
	this->poDefaultNodeStyle = new UIStyle();
	this->SetReserve(initialReserved, deltaGrow);
}

UIManager::~UIManager()
{
	delete this->poCompNode;
	delete this->poDefaultNodeStyle;
}

void UIManager::Create(int initialReserved, int deltaGrow)
{
	assert(!instance);

	if (!instance)
	{
		instance = new UIManager(initialReserved, deltaGrow);
	}
}

void UIManager::Update()
{
	UIManager* inst = UIManager::GetInstance();

	DLinkIterator* pIt = (DLinkIterator*)inst->poActive->GetIterator();

	UINode* pCur = (UINode*)pIt->First();
	UINode* pTemp = nullptr;

	while (!pIt->IsDone())
	{
		pTemp = (UINode*)pIt->Next();
		pCur->Update();
		pCur = pTemp;
	}
}

void UIManager::Destroy()
{
	UIManager* inst = UIManager::GetInstance();

	delete inst;

	instance = nullptr;
}

UINode* UIManager::AddNode(UIName name, UIStyle* style)
{
	UIManager* inst = UIManager::GetInstance();

	// Using style.mZindex for priority add
	UINode* pNode = (UINode*)inst->BaseAdd(style ? style->ZIndex() : 1);

	GameObjectUIRoot* root = GameObjectManager::UI::AddRoot(*pNode, Stringify(name));

	pNode->Set(name, root);
	
	// Link style if provided, if not then set to default
	style ? pNode->LinkStyle(*style) : pNode->SetStyle(*inst->poDefaultNodeStyle);

	return pNode;
}

void UIManager::RemoveNode(UINode& pNode)
{
	UIManager* inst = UIManager::GetInstance();

	inst->BaseRemove(pNode);
}

UINode* UIManager::FindNode(UIName name)
{
	UIManager* inst = UIManager::GetInstance();

	inst->poCompNode->SetName(name);

	return (UINode*)inst->BaseFind(*inst->poCompNode);
}

GameObjectUIElement* UIManager::AddElement(UINode& uiNode, Image& image, ShaderName shaderName, GameObjectUI* pParent)
{
	return GameObjectManager::UI::Add(image, shaderName, pParent ? pParent : uiNode.GetRootGO());
}

GameObjectFont* UIManager::AddFont(UINode& uiNode, Font& font, const char* const pMessage, ShaderName shaderName, GameObjectUI* pParent)
{
	GameObjectFont* pFont = GameObjectManager::UI::Add(font, pMessage, shaderName, pParent ? pParent : uiNode.GetRootGO());
	pFont->GetGraphicsObject()->SetUIStyle(uiNode.GetStyle());

	return pFont;
}


void UIManager::RemoveElement(GameObjectUIElement& element)
{
	GameObjectManager::UI::Remove(element);
}

void UIManager::PrintAll()
{
	UIManager* inst = UIManager::GetInstance();

	Trace::out("\n");
	Trace::out("--------------------------\n");
	Trace::out("-------- UI Nodes --------\n");
	Trace::out("--------------------------\n");

	inst->BasePrintAll();
}

NodeBase* UIManager::CreateNode()
{
	return new UINode();
}

UIManager* UIManager::GetInstance()
{
	assert(instance);
	return instance;
}

void UIManager::Clear()
{
	UIManager* inst = UIManager::GetInstance();

	inst->BaseClear();
}
