#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "ManagerBase.h"
#include "EngineNames.h"
#include "UINode.h"
#include "Font.h"

using namespace Uncertain;

class GameObjectUIElement;
class GameObjectFont;

class UIManager : public ManagerBase
{
public:
	UIManager() = delete;
	UIManager(const UIManager&) = delete;
	UIManager& operator =(const UIManager&) = delete;

	static void Create(int initialReserved = 5, int deltaGrow = 5);
	static void Destroy();

	static void Update();
	
	static UINode* AddNode(UIName name, UIStyle* style = nullptr);
	static void RemoveNode(UINode& pNode);
	static UINode* FindNode(UIName name);

	static GameObjectUIElement* AddElement(UINode& uiNode, Image& imageName, ShaderName shaderName = ShaderName::SPRITE_FLAT, GameObjectUI* pParent = nullptr);
	static GameObjectFont* AddFont(UINode& uiNode, Font& font, const char* const pMessage = nullptr, ShaderName shaderName = ShaderName::FONT_FLAT, GameObjectUI* pParent = nullptr);
	static void RemoveElement(GameObjectUIElement& element);

	static void PrintAll();

protected:
	virtual NodeBase* CreateNode() override;

private:
	static UIManager* instance;

	UIManager(int initialReserved, int deltaGrow);
	static UIManager* GetInstance();
	virtual ~UIManager();

	void Clear();

	UINode* poCompNode;
	UIStyle* poDefaultNodeStyle;
};

#endif // !MESH_NODE_MAN_H
