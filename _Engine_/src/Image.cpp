#include "Image.h"
#include "Texture.h"

namespace Uncertain
{
	Image::Image()
		:  SName(SpriteSheetName::UNINITIALIZED), pText(nullptr), ImageRect(Rect()), Name("null_image")
	{
	}

	void Image::SetName(const char* pName)
	{
		strncpy_s(this->Name, IMAGE_NAME_SIZE, pName, _TRUNCATE);
	}

	const char* Image::GetName()
	{
		return this->Name;
	}

	bool Image::Compare(NodeBase& pNode)
	{
		Image* pComp = (Image*)&pNode;

		return ((memcmp(this->Name, pComp->Name, IMAGE_NAME_SIZE) == 0) && this->SName == pComp->SName);
	}

	void Image::Set(SpriteSheetName sName, Texture* _pText, const char* pName, float x, float y, float width, float height)
	{
		this->SName = sName;
		this->pText = _pText;
		this->ImageRect = Rect(x, y, width, height);
		strncpy_s(this->Name, IMAGE_NAME_SIZE, pName, _TRUNCATE);
	}

	void Image::Print()
	{
		Trace::out("--- Image - &d\n", this);
		Trace::out("		   Name - %s\n", this->Name);
		Trace::out("		Texture - %s\n", this->pText->AssetName);
		Trace::out("		   Rect - (%f, %f, %f, %f)\n", this->ImageRect.X, this->ImageRect.Y, this->ImageRect.Width, this->ImageRect.Height);
	}

	void Image::Wash()
	{
		this->SName = SpriteSheetName::UNINITIALIZED;
		strncpy_s(this->Name, IMAGE_NAME_SIZE, "null_image", _TRUNCATE);
		this->pText = nullptr;
		this->ImageRect.Clear();
	}
}