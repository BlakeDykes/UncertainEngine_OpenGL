#include "GameObjectUIRoot.h"
#include "UINode.h"

GameObjectUIRoot::GameObjectUIRoot(GraphicsObjectNode* pGraphNode, TYPE type, UINode& uiNode, const char* const nodeName)
	: GameObjectUI(pGraphNode, type, nodeName, 1.0f, 1.0f), pUINode(&uiNode)
{
}

GameObjectUIRoot::~GameObjectUIRoot()
{
}

void GameObjectUIRoot::Draw(bool drawBoundingObject)
{
	if (drawBoundingObject)
	{
		GraphicsObject* pGraphObj = this->GetGraphicsObject();
		assert(pGraphObj);

		pGraphObjNode->Render(drawBoundingObject);
	}
}

void GameObjectUIRoot::Wash()
{
	this->pUINode = nullptr;
}

void GameObjectUIRoot::privUpdate(_Time currentTime)
{
	AZUL_UNUSED_VAR(currentTime);

	*this->poScale = this->pUINode->Scale();
	*this->poTrans = this->pUINode->Trans();
	*this->poRotate = this->pUINode->Rot();
	*this->poWorld = this->pUINode->World();

	this->pGraphObjNode->SetWorld(*this->poWorld);
}
