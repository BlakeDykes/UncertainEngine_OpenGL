#ifndef TEXTURE_MAN_H
#define TEXTURE_MAN_H

#include "ManagerBase.h"
#include "EngineNames.h"
#include "sb7.h"
#include "TextureNode.h"

class Texture;
class TextureData;

class TextureManager : public ManagerBase
{
public:

	TextureManager() = delete;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator =(const TextureManager&) = delete;

	static void Create(int initialReserved = 5, int deltaGrow = 5);
	static void Destroy();

	static TextureNode* Add(TextureName name, TextureNode::TYPE nodeType);
	static TextureNode* Add(TextureName name, TextureData& textData);
	static TextureNode* Add(TextureName name, ModelTextureData& data);
	static TextureNode* Add(SpriteSheetData& data, SpriteSheetName ssName, Glyph*& pGlyphsOut);
	static TextureNode* Find(TextureName name);
	static TextureNode* Find(NodeBase::Handle nodeID);
	static Texture* FindTexture(TextureName name, unsigned int modelMatIndex = UINT_MAX);
	static void FindAndAssign(TextureName name, Texture*& textureOut, unsigned int modelMatIndex = UINT_MAX);
	static GLuint FindID(TextureName name, unsigned int modelMatIndex = UINT_MAX);

	static void Remove(TextureNode& pNode);
	
	//static void PrintAll();

protected:
	virtual NodeBase* CreateNode() override;

private:
	static TextureManager* instance;
	TextureNode* pCompNode;

	TextureManager(int initialReserved, int deltaGrow);
	static TextureManager* GetInstance();
	virtual ~TextureManager();
	//void InitAll();

	void Clear();
};

#endif
