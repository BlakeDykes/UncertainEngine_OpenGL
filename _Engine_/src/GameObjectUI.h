#ifndef GAME_OBJ_UI_H
#define GAME_OBJ_UI_H

#include "GameObject2D.h"

class GameObjectUI : public GameObject2D
{
public:

	GameObjectUI(GraphicsObjectNode* pGraphNode, TYPE type, const char* const nodeName
		, const float origWidth, const float origHeight);

	GameObjectUI() = delete;
	GameObjectUI(const GameObjectUI&) = delete;
	GameObjectUI& operator = (const GameObjectUI&) = delete;
	virtual ~GameObjectUI();

};

#endif