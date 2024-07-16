#ifndef GAME_OBJ_UI_ROOT_H
#define GAME_OBJ_UI_ROOT_H

#include "GameObjectUI.h"

class UINode;

class GameObjectUIRoot : public GameObjectUI
{
public:

	GameObjectUIRoot(GraphicsObjectNode* pGraphNode, TYPE type, UINode& uiNode, const char* const nodeName);

	GameObjectUIRoot() = delete;
	GameObjectUIRoot(const GameObjectUIRoot&) = delete;
	GameObjectUIRoot& operator = (const GameObjectUIRoot&) = delete;
	virtual ~GameObjectUIRoot();

	virtual void Draw(bool drawBoundingObject);

	virtual void Wash() override;

private:
	virtual void privUpdate(_Time currentTime) override;

	UINode* pUINode;
};

#endif