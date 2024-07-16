#ifndef TEXTURE_H
#define TEXTURE_H

#include "DLink.h"
#include "sb7.h"
#include "EngineNames.h"
#include "TextureData.h"


class Texture
{
public:

	struct BaseColor
	{
		float r;
		float g;
		float b;
		float a;

		BaseColor();
		BaseColor(const TextureData::BaseColorFactor& baseColor);
		BaseColor(float _r, float _g, float _b, float _a);

		const BaseColor& operator=(const BaseColor& baseColor);
		BaseColor(const BaseColor& baseColor);
		~BaseColor() = default;
	};

	static const unsigned int TEXTURE_ASSET_NAME_SIZE = 64;

	char AssetName[TEXTURE_ASSET_NAME_SIZE];
	BaseColor Color;
	GLuint TextureID;
	GLenum MinFilter;
	GLenum MagFilter;
	GLenum WrapModeS;
	GLenum WrapModeT;
	int ActiveCount;
	unsigned int Width;
	unsigned int Height;
	bool bTextEnabled;
	bool bBaseColorEnabled;

	Texture();
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	~Texture() = default;

	Texture(const char* const assetName,
			BaseColor baseColor,
			GLuint textureID,
			GLenum minFilter,
			GLenum magFilter,
			GLenum wrapModeS,
			GLenum wrapModeT,
			unsigned int width,
			unsigned int height,
			bool textEnabled,
			bool baseColorEnabled
	);

	void Set(const char* const assetName,
			 BaseColor baseColor,
			 GLuint textureID,
			 GLenum minFilter,
			 GLenum magFilter,
			 GLenum wrapModeS,
			 GLenum wrapModeT,
			 unsigned int width,
			 unsigned int height,
			 bool textEnabled,
			 bool baseColorEnabled);

	const GLuint GetID() const { return this->TextureID; }
	const int GetActiveCount() const { return this->ActiveCount; }
	void ManageActiveCount(int change) { this->ActiveCount += change; }

	void Print() const;

private:

};

#endif // !TEXTURE_H
