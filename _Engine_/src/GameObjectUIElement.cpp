#include "GameObjectUIElement.h"
#include "GameObjectUIRoot.h"

GameObjectUIElement::GameObjectUIElement(GraphicsObjectNode* pGraphNode, TYPE type, const char* const nodeName
	, const float origHeight, const float origWidth)
	: GameObjectUI(pGraphNode, type, nodeName, origHeight, origWidth)
{
}

GameObjectUIElement::~GameObjectUIElement()
{

}

void GameObjectUIElement::privUpdate(_Time currentTime)
{
	AZUL_UNUSED_VAR(currentTime);

	GameObjectUIRoot* pParentObj = (GameObjectUIRoot*)this->GetParent();

	Mat4 scale(Mat4::Scale::XYZ, *this->poScale);
	Mat4 trans(Mat4::Trans::XYZ, *this->poTrans);
	Mat4 parentTrans(Mat4::Trans::XYZ, pParentObj->Trans());

	*this->poWorld = scale * (*this->poRotate) * trans * pParentObj->Rot() * parentTrans;

	this->pGraphObjNode->SetWorld(*this->poWorld);

}

