#ifndef UI_NODE_H
#define UI_NODE_H

#include "DLink.h"
#include "PCSTree.h"
#include "GameObjectUI.h"
#include "Rect.h"
#include "UIStyle.h"
#include "EngineNames.h"

using namespace Uncertain;

class GameObjectUIRoot;

class UINode : public DLink
{
public:
	UINode();
	UINode(const UINode&) = delete;
	UINode& operator=(const UINode&) = delete;
	virtual ~UINode();

	void SetName(UIName name) { this->Name = name; }
	void Set(UIName name, GameObjectUIRoot* rootUI);

	GameObjectUIRoot* GetRootGO() const { return this->pRootElement; }

	void Update();

	void SetStyle(UIStyle& style);
	void LinkStyle(UIStyle& style);
	const UIStyle& GetStyle() const { return *this->poStyle; }

	const Mat4& World() const { return this->poStyle->World(); }
	const Vec3& Trans() const { return this->poStyle->Trans(); }
	const Vec3& Scale() const { return this->poStyle->Scale(); }
	const Quat& Rot() const { return this->poStyle->Rot(); }
	const int& ZIndex() const { return this->poStyle->ZIndex(); }
	const bool& Visible() const { return this->poStyle->Visible(); }

	virtual void Wash() override;
	virtual void Print() override;
	virtual bool Compare(NodeBase& pNode) override;
	virtual const char* GetName() override;
	virtual PriorityCompResult ComparePriority(int priority);


private:
	UIName Name;
	UIStyle* poStyle;
	GameObjectUIRoot* pRootElement;
};

#endif // !UI_NODE_H
