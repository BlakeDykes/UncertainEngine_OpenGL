#include "UINode.h"
#include "GraphicsObjectManager.h"
#include "GameObjectManager.h"
#include "GameObjectUIRoot.h"

UINode::UINode()
	: Name(UIName::UNINITIALIZED), poStyle(new UIStyle()), pRootElement(nullptr)
{
}

UINode::~UINode()
{
	delete this->poStyle;
}

void UINode::Update()
{
	this->poStyle->Update();
}

void UINode::SetStyle(UIStyle& style)
{
	*this->poStyle = style;
}

void UINode::LinkStyle(UIStyle& style)
{
	delete this->poStyle;

	this->poStyle = &style;
}

void UINode::Set(UIName name, GameObjectUIRoot* root)
{
	this->Name = name;
	this->pRootElement = root;

	assert(this->pRootElement);
}


void UINode::Wash()
{
	this->Name = UIName::UNINITIALIZED;
	this->poStyle->Clear();

	if (this->pRootElement)
	{
		GameObjectManager::Remove(*this->pRootElement);
	}
}

void UINode::Print()
{
	Trace::out("UI Node ---------- 0x%p\n", this);
	Trace::out("--- Name:     %s\n", Stringify(this->Name));
	Trace::out("--- Root GO : 0x%p\n", this->pRootElement);
	Trace::out("--------------------- 0x%p\n", this);
}

bool UINode::Compare(NodeBase& pNode)
{
	UINode* pComp = (UINode*)&pNode;

	return this->Name == pComp->Name;
}

const char* UINode::GetName()
{
	return Stringify(this->Name);
}

DLink::PriorityCompResult UINode::ComparePriority(int priority)
{
	return this->poStyle->ZIndex() > priority ? DLink::PriorityCompResult::THIS_IS_GREATER_THAN : DLink::PriorityCompResult::THIS_IS_LESS_THAN;
}