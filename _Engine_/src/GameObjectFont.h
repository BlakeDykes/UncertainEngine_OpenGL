#ifndef GAME_OBJ_FONT_H
#define GAME_OBJ_FONT_H

#include "GameObject2D.h"
#include "Font.h"

class DebugObject;

class GameObjectFont : public GameObject2D
{
public:

	GameObjectFont(GraphicsObjectNode* pGraphNode, const char* pName, Font* _pFont, const char* _pMessage);

	GameObjectFont() = delete;
	GameObjectFont(const GameObjectFont&) = delete;
	GameObjectFont& operator = (const GameObjectFont&) = delete;
	virtual ~GameObjectFont();

	void SetMessage(const char* message);

	virtual void Draw(bool drawBoundingObject) override;

	void SetDebugObject(DebugObject& debugObject);
	void RemoveDebugObject() { this->pDebugObject = nullptr; }

protected:
	virtual void privUpdate(_Time currentTime) override;
	virtual void privUpdateBoundingObject(BoundingObject& boundingOut);

	const char* pMessage;
	Font* pFont;
	DebugObject* pDebugObject;

};

#endif // !GAME_OBJ_FONT_H
