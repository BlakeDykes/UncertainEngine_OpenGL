#ifndef GLYPH_H
#define GLYPH_H

#include "Image.h"

namespace Uncertain
{
	class Glyph : public Image
	{
	public:
		Glyph();
		Glyph(const Image&) = delete;
		Glyph& operator=(const Glyph&) = delete;
		virtual ~Glyph() = default;

		void SetGlyph(SpriteSheetName sName, Texture* _pText, const char* pName, int key, float x, float y, float width, float height);
		
		void SetKey(int key);
		int GetKey() const;

		virtual void Wash() override;

	private:
		int Key;
	};
}

#endif // !GLYPH_H
