#ifndef IMAGE_H
#define IMAGE_H

#include "DLink.h"
#include "EngineNames.h"
#include "Rect.h"

class Texture;

namespace Uncertain
{
	static const unsigned int IMAGE_NAME_SIZE = 16;

	class Image : public DLink
	{
	public:
		Image();
		Image(const Image&) = delete;
		Image& operator=(const Image&) = delete;
		virtual ~Image() = default;

		SpriteSheetName GetSpriteSheetName() const { return this->SName; }
		void SetName(const char* name);

		void Set(SpriteSheetName sName, Texture* _pText, const char* pName, float x, float y, float width, float height);

		const char* GetName() override;
		virtual bool Compare(NodeBase& pNode) override;
		virtual void Print() override;
		virtual void Wash() override;

		SpriteSheetName SName;
		Texture* pText;
		Rect ImageRect;

	private:
		char Name[IMAGE_NAME_SIZE];
	};
}

#endif // !IMAGE_H
