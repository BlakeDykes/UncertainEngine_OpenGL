#include "GameObjectUI.h"

GameObjectUI::GameObjectUI(GraphicsObjectNode* pGraphNode, TYPE type, const char* const nodeName
	, const float origWidth, const float origHeight)
	: GameObject2D(pGraphNode, type, nodeName, origWidth, origHeight)
{
}

GameObjectUI::~GameObjectUI()
{
}
