#ifndef TEXTURE_NODE_H
#define TEXTURE_NODE_H

#include "DLink.h"
#include "EngineNames.h"
#include "sb7.h"
#include "Glyph.h"

class Texture;
class TextureMap;
class TextureData;
class ModelTextureData;
class SpriteSheetData;

using namespace Uncertain;

class TextureNode : public DLink
{
public:

	enum class TYPE
	{
		SINGLE,
		MULTI,
		FONT,

		UNINITIALIZED
	};

	TextureNode();
	TextureNode(const TextureNode&) = delete;
	TextureNode& operator=(const TextureNode&) = delete;
	virtual ~TextureNode();

	void Set(TextureName name, TYPE nodeType);
	void Set(TextureName name, TextureData& data);
	void Set(SpriteSheetData& data, SpriteSheetName ssName, Glyph*& pGlyphsOut);
	void Set(TextureName name, ModelTextureData& data);
	Texture* GetTexture(const unsigned int modelMatIndex = UINT_MAX);

	virtual const char* GetName() override;
	virtual bool Compare(NodeBase& pNode) override;
	virtual void Wash() override;

	void SetName(TextureName name);

private:
	void SetSingle(TextureName name, TextureData& data);
	void SetMulti(TextureName name, ModelTextureData& data);
	void SetFont(TextureName name, SpriteSheetName ssName, Glyph*& pGlyphsOut, SpriteSheetData& data);

	void LoadTexture(TextureData& textData, GLuint*& textureID);
	void LoadTexture(const char* const assetName, GLuint*& textureID, TextureData& textDataOut);
	void LoadTexture(TextureData& textData, GLuint*& textureID, int& x, int& y, int& width, int& height);
	bool LoadRawTexture(TextureData& textData);
	bool LoadTGATexture(const char* szFileName, GLint minFilter, GLint magFilter, GLint wrapModeS, GLint wrapModeT);
	GLbyte* gltReadTGABits(const char* szFileName, GLint* iWidth, GLint* iHeight, GLint* iComponents, GLenum* eFormat);

	TextureName Name;
	TYPE NodeType;
	unsigned int TextureCount;
	TextureMap* poTextureMap;
	Texture* poTextures;
	
};

#endif // !TEXTURE_NODE_H