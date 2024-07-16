#include "TextureNode.h"
#include "Texture.h"
#include "TextureData.h"
#include "ModelTextureData.h"
#include "TextureMap.h"
#include "ProtoData_Wrapper.h"
#include "ProtoToOpenGL.h"
#include "TGA.h"
#include "SpriteSheetData.h"

TextureNode::TextureNode()
	: Name(TextureName::UNINITIALIZED), NodeType(TYPE::UNINITIALIZED), 
	TextureCount(0), poTextureMap(nullptr), poTextures(nullptr)
{
}

TextureNode::~TextureNode()
{
	if (poTextureMap)
	{
		delete[] poTextureMap;
		poTextureMap = nullptr;
	}
	if (poTextures)
	{
		delete[] poTextures;
		poTextures = nullptr;
	}
}

void TextureNode::Set(TextureName name, TYPE nodeType)
{
	assert(!poTextures);
	assert(!poTextureMap);

	switch (nodeType)
	{
	case TextureNode::TYPE::SINGLE:
	{
		TextureData data;
		const char* fileName = GetFileName(name);
		assert(fileName);

		ProtoData_Wrapper::ReadFromFile(fileName, data);

		SetSingle(name, data);
		break;
	}

	case TextureNode::TYPE::MULTI:
	{
		ModelTextureData data;
		const char* fileName = GetFileName(name);
		assert(fileName);

		ProtoData_Wrapper::ReadFromFile(fileName, data);

		SetMulti(name, data);

		break;
	}

	case TextureNode::TYPE::FONT:
	case TextureNode::TYPE::UNINITIALIZED:
	default:
		assert(false);
		break;
	}
}

void TextureNode::Set(TextureName name, TextureData& data)
{
	assert(!poTextures);
	assert(!poTextureMap);

	SetSingle(name, data);
}

void TextureNode::Set(SpriteSheetData& data, SpriteSheetName ssName, Glyph*& pGlyphsOut)
{
	assert(!poTextures);
	assert(!poTextureMap);

	SetFont(TextureName::FONT, ssName, pGlyphsOut, data);
}

void TextureNode::Set(TextureName name, ModelTextureData& data)
{
	assert(!poTextures);
	assert(!poTextureMap);

	SetMulti(name, data);
}


Texture* TextureNode::GetTexture(const unsigned int modelMatIndex)
{
	if (TextureCount == 0 || !poTextures)
	{
		return nullptr;
	}

	if (modelMatIndex == UINT_MAX || TextureCount == 1)
	{
		return poTextures;
	}

	TextureMap* pCurMap = poTextureMap;
	for (unsigned int i = 0; i < TextureCount; i++)
	{
		if (*pCurMap == modelMatIndex)
		{
			return &poTextures[pCurMap->GetLocalIndex()];
		}

		pCurMap++;
	}

	return nullptr;
}

const char* TextureNode::GetName()
{
	return Stringify(Name);
}

bool TextureNode::Compare(NodeBase& pNode)
{
	TextureNode* pComp = (TextureNode*)&pNode;

	return this->Name == pComp->Name;
}

void TextureNode::Wash()
{
	Name = TextureName::UNINITIALIZED;
	NodeType = TYPE::UNINITIALIZED;
	TextureCount = 0;

	if (poTextureMap)
	{
		delete[] poTextureMap;
		poTextureMap = nullptr;
	}

	if (poTextures)
	{
		delete[] poTextures;
		poTextures = nullptr;
	}
}

void TextureNode::SetName(TextureName name)
{
	this->Name = name;
}

void TextureNode::SetSingle(TextureName name, TextureData& data)
{
	GLuint textureID;
	GLuint* pTextureID = &textureID;


	this->poTextures = new Texture[1]();
	this->poTextureMap = new TextureMap[1]();
	
	if (data.bTextEnabled)
	{
		LoadTexture(data, pTextureID);
	}
	
	this->poTextures->Set(
		data.pFileName,
		Texture::BaseColor(data.BaseColor),
		textureID,
		ProtoToOpenGL::Get(data.MinFilter),
		ProtoToOpenGL::Get(data.MagFilter),
		ProtoToOpenGL::Get(data.WrapS),
		ProtoToOpenGL::Get(data.WrapT),
		data.Width,
		data.Height,
		data.bTextEnabled,
		data.bBaseColorEnabled
	);

	this->poTextureMap->Set(0, data.MaterialIndex);

	this->TextureCount = 1;
	this->NodeType = TYPE::SINGLE;
	this->Name = name;
}

void TextureNode::SetMulti(TextureName name, ModelTextureData& data)
{

	this->TextureCount = data.TextureCount;
	this->poTextures = new Texture[TextureCount]();
	this->poTextureMap = new TextureMap[TextureCount]();
	TextureData* pCurData = data.Textures;

	for (unsigned int i = 0; i < TextureCount; i++)
	{
		GLuint textureID;
		GLuint* pTextureID = &textureID;

		if (pCurData->bTextEnabled)
		{
			LoadTexture(*pCurData, pTextureID);
		}

		this->poTextures[i].Set(
			pCurData->pFileName,
			Texture::BaseColor(pCurData->BaseColor),
			textureID,
			ProtoToOpenGL::Get(pCurData->MinFilter),
			ProtoToOpenGL::Get(pCurData->MagFilter),
			ProtoToOpenGL::Get(pCurData->WrapS),
			ProtoToOpenGL::Get(pCurData->WrapT),
			pCurData->Width,
			pCurData->Height,
			pCurData->bTextEnabled,
			pCurData->bBaseColorEnabled
		);

		this->poTextureMap[i].Set(i, pCurData->MaterialIndex);

		pCurData++;
	}

	this->NodeType = TYPE::MULTI;
	this->Name = name;
}

void TextureNode::SetFont(TextureName name, SpriteSheetName ssName, Glyph*& pGlyphsOut, SpriteSheetData& data)
{
	// Spritesheets should be singles/multi
	assert(data.Type == SpriteSheetData::TYPE::FONT);
	
	this->Name = name;
	this->TextureCount = data.ImageCount;

	this->poTextures = new Texture[TextureCount]();

	// Create SubTexture for each glyph
	for (unsigned int i = 0; i < data.ImageCount; i++)
	{
		GLuint textureID;
		GLuint* pTextureID = &textureID;

		if (data.pText->bTextEnabled)
		{
			LoadTexture(*data.pText,
						pTextureID,
						data.pImages[i]->X,
						data.pImages[i]->Y,
						data.pImages[i]->Width,
						data.pImages[i]->Height);
		}

		this->poTextures[i].Set(
			data.pImages[i]->ImageName,
			Texture::BaseColor(data.pText->BaseColor),
			textureID,
			ProtoToOpenGL::Get(data.pText->MinFilter),
			ProtoToOpenGL::Get(data.pText->MagFilter),
			ProtoToOpenGL::Get(data.pText->WrapS),
			ProtoToOpenGL::Get(data.pText->WrapT),
			data.pImages[i]->X,
			data.pImages[i]->Y,
			data.pText->bTextEnabled,
			data.pText->bBaseColorEnabled
		);

		
		pGlyphsOut[i].SetGlyph(ssName,
								  &this->poTextures[i],
								  data.pImages[i]->ImageName,
								  data.pImages[i]->GetKey(),
								  (float)data.pImages[i]->X,
								  (float)data.pImages[i]->Y,
								  (float)data.pImages[i]->Width,
								  (float)data.pImages[i]->Height);

	}
	
	
}




void TextureNode::LoadTexture(TextureData& textData, GLuint*& textureID)
{
	glGenTextures(1, textureID);
	glBindTexture(GL_TEXTURE_2D, *textureID);

	assert(textData.AsIs == false);

	this->LoadRawTexture(textData);
}


void TextureNode::LoadTexture(const char* const assetName, GLuint*& textureID, TextureData& textDataOut)
{
	// Get a ID(handl)
	glGenTextures(1, textureID);

	// Bind it
	glBindTexture(GL_TEXTURE_2D, *textureID);

	TextureData text;

	ProtoData_Wrapper::ReadFromFile(assetName, textDataOut);

	bool res = LoadRawTexture(textDataOut);
	assert(res);
}

void TextureNode::LoadTexture(TextureData& textData, GLuint*& textureID, int& x, int& y, int& width, int& height)
{
	assert(textData.poData);

	glGenTextures(1, textureID);
	glBindTexture(GL_TEXTURE_2D, *textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)ProtoToOpenGL::Get(textData.WrapS));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)ProtoToOpenGL::Get(textData.WrapT));

	GLint minFilter = (GLint)ProtoToOpenGL::Get(textData.MinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)ProtoToOpenGL::Get(textData.MagFilter));

	glPixelStorei(GL_UNPACK_ROW_LENGTH, textData.Width);
	unsigned char* subText = textData.poData + ((x + (y * textData.Width)) * textData.Component);

	if (textData.TextType == TextureData::TEXTURE_TYPE::BMP)
	{
		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 ProtoToOpenGL::Get(textData.NComponent),
					 width,
					 height,
					 0,
					 ProtoToOpenGL::Get(textData.EFormat),
					 GL_UNSIGNED_BYTE,
					 subText);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 ProtoToOpenGL::Get(textData.NComponent),
					 width,
					 height,
					 0,
					 ProtoToOpenGL::Get(textData.NComponent),
					 GL_UNSIGNED_BYTE,
					 subText);
	}


	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

	if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
		minFilter == GL_LINEAR_MIPMAP_NEAREST ||
		minFilter == GL_NEAREST_MIPMAP_LINEAR ||
		minFilter == GL_NEAREST_MIPMAP_NEAREST)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

bool TextureNode::LoadRawTexture(TextureData& textData)
{
	assert(textData.poData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)ProtoToOpenGL::Get(textData.WrapS));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)ProtoToOpenGL::Get(textData.WrapT));

	GLint minFilter = (GLint)ProtoToOpenGL::Get(textData.MinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)ProtoToOpenGL::Get(textData.MinFilter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)ProtoToOpenGL::Get(textData.MagFilter));
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (textData.TextType == TextureData::TEXTURE_TYPE::BMP)
	{
		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 ProtoToOpenGL::Get(textData.NComponent),
					 (GLsizei)textData.Width,
					 (GLsizei)textData.Height,
					 0,
					 ProtoToOpenGL::Get(textData.EFormat),
					 GL_UNSIGNED_BYTE,
					 (GLbyte*)textData.poData);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 ProtoToOpenGL::Get(textData.NComponent),
					 (GLsizei)textData.Width,
					 (GLsizei)textData.Height,
					 0,
					 ProtoToOpenGL::Get(textData.NComponent),
					 GL_UNSIGNED_BYTE,
					 (GLbyte*)textData.poData);
	}

	if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
		minFilter == GL_LINEAR_MIPMAP_NEAREST ||
		minFilter == GL_NEAREST_MIPMAP_LINEAR ||
		minFilter == GL_NEAREST_MIPMAP_NEAREST)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	return true;
}

bool TextureNode::LoadTGATexture(const char* szFileName, GLint minFilter, GLint magFilter, GLint wrapModeS, GLint wrapModeT)
{
	GLbyte* pBits;
	int width, height, components;
	GLenum eFormat;

	pBits = gltReadTGABits(szFileName, &width, &height, &components, &eFormat);
	if (!pBits)
	{
		return false;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)wrapModeS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)wrapModeT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)magFilter);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, components, width, height, 0, eFormat, GL_UNSIGNED_BYTE, pBits);


	free(pBits);

	if (minFilter == GL_LINEAR_MIPMAP_LINEAR ||
		minFilter == GL_LINEAR_MIPMAP_NEAREST ||
		minFilter == GL_NEAREST_MIPMAP_LINEAR ||
		minFilter == GL_NEAREST_MIPMAP_NEAREST)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	return true;
}

GLbyte* TextureNode::gltReadTGABits(const char* szFileName, GLint* iWidth, GLint* iHeight, GLint* iComponents, GLenum* eFormat)
{
	FILE* pFile;						// File pointer
	TGAHEADER tgaHeader;				// TGA file header
	unsigned long lImageSize;			// Size in bytes of image
	short sDepth;						// Pixel depth
	GLbyte* pBits = NULL;				// Pointer to bits

	// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*iComponents = GL_RGB;
	*eFormat = GL_RGB;

	fopen_s(&pFile, szFileName, "rb");
	if (pFile == nullptr)
	{
		return nullptr;
	}

	fread(&tgaHeader, 18/*sizeof(TGAHEADER)*/, 1, pFile);

	// Get width, height, and depth of texture
	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Validity checks
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
	{
		return nullptr;
	}

	lImageSize = (unsigned int)tgaHeader.width * (unsigned int)tgaHeader.height * (unsigned int)sDepth;

	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == nullptr)
	{
		return nullptr;
	}

	// Read in the bits
	// Check for read error - catches RLE or other formats
	if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		return nullptr;
	}

	switch (sDepth)
	{
	case 3:
		*eFormat = GL_BGR;
		*iComponents = GL_RGB;
		break;
	case 4:
		*eFormat = GL_BGRA;
		*iComponents = GL_RGBA;
		break;
	case 1:
		assert(false);
		break;
	default:	// RGB
		break;
	}

	fclose(pFile);

	return pBits;
}