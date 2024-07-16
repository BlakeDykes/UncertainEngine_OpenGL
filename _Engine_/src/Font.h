#ifndef FONT_H
#define FONT_H

#include "DLink.h"
#include "EngineNames.h"
#include "SpriteSheetData.h"

namespace Uncertain
{
	class Glyph;

	class Font : public DLink
	{
	public:
		Font();
		Font(const Font&) = delete;
		Font& operator=(const Font&) = delete;
		virtual ~Font();

		void Set(SpriteSheetName ssName);

		Glyph* GetGlyph(int key);
		SpriteSheetName GetSSName() const { return this->SName; }
		Glyph* GetGlyphList();

		const char* GetName() override;
		virtual bool Compare(NodeBase& pNode) override;
		virtual void Print() override;
		virtual void Wash() override;

	private:
		SpriteSheetName SName;
		Glyph* poGlyphs;

	};
}


#endif