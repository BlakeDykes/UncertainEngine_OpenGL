#include "TextureMap.h"

TextureMap::TextureMap()
	: LocalIndex(UINT_MAX), ModelMatIndex(UINT_MAX)
{
}

void TextureMap::Set(unsigned int localIndex, unsigned int modelMatIndex)
{
	this->LocalIndex = localIndex;
	this->ModelMatIndex = modelMatIndex;
}

bool TextureMap::operator==(const unsigned int modelMatIndex)
{
	return this->ModelMatIndex == modelMatIndex;
}

bool TextureMap::operator!=(const unsigned int modelMatIndex)
{
	return this->ModelMatIndex != modelMatIndex;
}

unsigned int TextureMap::GetLocalIndex() const
{
	return this->LocalIndex;
}
