#include "Glyph.h"

namespace Uncertain
{
	Glyph::Glyph()
		: Key(-1)
	{
	}

	void Glyph::SetGlyph(SpriteSheetName sName, Texture* _pText, const char* pName, int key, float x, float y, float width, float height)
	{
		this->SName = sName;
		this->pText = _pText;
		this->Key = key;
		this->ImageRect = Rect(x, y, width, height);
		this->SetName(pName);
	}

	void Glyph::SetKey(int key) 
	{ 
		this->Key = key; 
	}

	int Glyph::GetKey() const 
	{ 
		return this->Key;
	}

	void Glyph::Wash()
	{
		Image::Wash();
		this->Key = 0;
	}

}

