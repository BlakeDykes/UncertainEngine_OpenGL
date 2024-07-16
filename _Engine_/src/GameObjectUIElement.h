#ifndef GAME_OBJECT_UI_ELE_H
#define GAME_OBJECT_UI_ELE_H

#include "GameObjectUI.h"

class GameObjectUIElement : public GameObjectUI
{
public:
	GameObjectUIElement(GraphicsObjectNode* pGraphNode, TYPE type, const char* const nodeName
		, const float origHeight, const float origWidth);

	GameObjectUIElement() = delete;
	GameObjectUIElement(const GameObjectUIElement&) = delete;
	GameObjectUIElement& operator = (const GameObjectUIElement&) = delete;
	virtual ~GameObjectUIElement();

private:
	virtual void privUpdate(_Time currentTime) override;

};


#endif // !GAME_OBJECT_UI_ELE_H


