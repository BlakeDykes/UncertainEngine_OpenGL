#include "Texture.h"

Texture::Texture()
	: Color(), TextureID(0), MinFilter(GL_LINEAR), MagFilter(GL_LINEAR), 
	WrapModeS(GL_CLAMP_TO_EDGE), WrapModeT(GL_CLAMP_TO_EDGE), ActiveCount(0),
	Width(0), Height(0), bTextEnabled(false), bBaseColorEnabled(false)
{
	memset(this->AssetName, 0x0, TEXTURE_ASSET_NAME_SIZE);
}

Texture::Texture(const char* const assetName, 
					 Texture::BaseColor baseColor,
					 GLuint textureID,
					 GLenum minFilter,
					 GLenum magFilter,
					 GLenum wrapModeS,
					 GLenum wrapModeT,
					 unsigned int width,
					 unsigned int height,
					 bool textEnabled,
					 bool baseColorEnabled)
	: Color(baseColor), TextureID(textureID), MinFilter(minFilter), MagFilter(magFilter), WrapModeS(wrapModeS),
	WrapModeT(wrapModeT), Width(width), Height(height), bTextEnabled(textEnabled), bBaseColorEnabled(baseColorEnabled)
{
	memcpy(this->AssetName, assetName, TEXTURE_ASSET_NAME_SIZE - 1);
}

void Texture::Set(const char* const assetName,
					  Texture::BaseColor baseColor,
					  GLuint textureID,
					  GLenum minFilter,
					  GLenum magFilter,
					  GLenum wrapModeS,
					  GLenum wrapModeT,
					  unsigned int width,
					  unsigned int height,
					  bool textEnabled,
					  bool baseColorEnabled)
{
	memcpy(this->AssetName, assetName, TEXTURE_ASSET_NAME_SIZE - 1);
	this->Color = baseColor;
	this->TextureID = textureID;
	this->MinFilter = minFilter;
	this->MagFilter = magFilter;
	this->WrapModeS = wrapModeS;
	this->WrapModeT = wrapModeT;
	this->Width = width;
	this->Height = height;
	this->bTextEnabled = textEnabled;
	this->bBaseColorEnabled = baseColorEnabled;
}

void Texture::Print() const
{
	Trace::out("Texture ------- 0x%p\n", this);
	Trace::out("---Name:		%s\n", this->AssetName);
	Trace::out("---ID:			%d\n", this->TextureID);
	Trace::out("---MinFilter:	%d\n", this->MinFilter);
	Trace::out("---MagFilter:	%d\n", this->MagFilter);
	Trace::out("---WrapModeS:	%d\n", this->WrapModeS);
	Trace::out("---WrapModeT:	%d\n", this->WrapModeT);
}

Texture::BaseColor::BaseColor()
	: r(1.0f), g(1.0f), b(1.0f), a(1.0f)
{
}

Texture::BaseColor::BaseColor(const TextureData::BaseColorFactor& baseColor)
	: r(baseColor.r), g(baseColor.g), b(baseColor.b), a(baseColor.a)
{
}

Texture::BaseColor::BaseColor(float _r, float _g, float _b, float _a)
	: r(_r), g(_g), b(_b), a(_a)
{
}

const Texture::BaseColor& Texture::BaseColor::operator=(const BaseColor& baseColor)
{
	if (this != &baseColor)
	{
		this->r = baseColor.r;
		this->g = baseColor.g;
		this->b = baseColor.b;
		this->a = baseColor.a;
	}

	return *this;
}

Texture::BaseColor::BaseColor(const BaseColor& baseColor)
{
	this->r = baseColor.r;
	this->g = baseColor.g;
	this->b = baseColor.b;
	this->a = baseColor.a;
}
