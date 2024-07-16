#include "GameObjectFont.h"
#include "DebugObject.h"

GameObjectFont::GameObjectFont(GraphicsObjectNode* pGraphNode, const char* pName, Font* _pFont, const char* _pMessage)
	: GameObject2D(pGraphNode, TYPE::FONT_2D, pName, 1.0f, 1.0f), pMessage(_pMessage), pFont(_pFont), pDebugObject(nullptr)
{
}

GameObjectFont::~GameObjectFont()
{	
	if (this->pDebugObject)
	{
		pDebugObject->Wash();
	}
}

void GameObjectFont::SetMessage(const char* message)
{
	this->pMessage = message;
}

void GameObjectFont::Draw(bool drawBoundingObject)
{
	AZUL_UNUSED_VAR(drawBoundingObject);

	GraphicsObject* pGraphObj = this->GetGraphicsObject();
	assert(pGraphObj);

	// Bounding rects not working for font
	pGraphObjNode->Render(false);
}

void GameObjectFont::SetDebugObject(DebugObject& debugObject)
{
	if (this->pDebugObject)
	{
		pDebugObject->Wash();
	}

	pDebugObject = &debugObject;
}

void GameObjectFont::privUpdate(_Time currentTime)
{
	AZUL_UNUSED_VAR(currentTime);

	this->pGraphObjNode->GetGraphObj()->SetMessage(this->pMessage);

	GameObject2D* pParentObj = (GameObject2D*)this->GetParent();

	Mat4 scale(Mat4::Scale::XYZ, *this->poScale);
	Mat4 trans(Mat4::Trans::XYZ, *this->poTrans);
	Mat4 parentTrans(Mat4::Trans::XYZ, pParentObj->Trans());

	*this->poWorld = scale * (*this->poRotate) * trans * pParentObj->Rot() * parentTrans;

	this->pGraphObjNode->SetWorld(*this->poWorld);
}

void GameObjectFont::privUpdateBoundingObject(BoundingObject& boundingOut)
{
	this->pGraphObjNode->UpdateBoundingObjectFromGraphObj(boundingOut);
}
