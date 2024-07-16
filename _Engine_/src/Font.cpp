#include "Font.h"
#include "Glyph.h"
#include "ImageManager.h"
#include "Texture.h"

namespace Uncertain
{

	Font::Font()
		: SName(SpriteSheetName::UNINITIALIZED), poGlyphs(new Glyph[96]())
	{
	}


	Font::~Font()
	{
		delete[] this->poGlyphs;
	}

	void Font::Set(SpriteSheetName ssName)
	{
		this->SName = ssName;
	}

	Glyph* Font::GetGlyph(int key)
	{
		return &this->poGlyphs[key - 32];
	}

	Glyph* Font::GetGlyphList()
	{
		return this->poGlyphs;
	}

	const char* Font::GetName()
	{
		return Stringify(this->SName);
	}

	bool Font::Compare(NodeBase& pNode)
	{
		Font* pFont = (Font*)&pNode;

		return this->SName == pFont->SName;
	}

	void Font::Print()
	{
		Trace::out("--- Font	- 0x%d\n", this);
		Trace::out("	Name	- %s\n", Stringify(this->SName));
		Trace::out("	Glyphs  - 0x%d\n", this->poGlyphs);

		for (int i = 0; i < 96; i++)
		{
			Trace::out("	- %d\n", i);
			Trace::out("		Name	- %s\n", this->poGlyphs[i].GetName());
			Trace::out("		Key		- %d\n", this->poGlyphs[i].GetKey());
			Trace::out("		Texture	- %s\n", this->poGlyphs[i].pText->AssetName);
			Trace::out("		Rect	- (%f, %f, %f, %f)\n", this->poGlyphs[i].ImageRect.X, 
				this->poGlyphs[i].ImageRect.Y,
				this->poGlyphs[i].ImageRect.Width,
				this->poGlyphs[i].ImageRect.Height);
		}
	}

	void Font::Wash()
	{
		for (int i = 0; i < 96; i++)
		{
			this->poGlyphs[i].Wash();
		}
	}

}