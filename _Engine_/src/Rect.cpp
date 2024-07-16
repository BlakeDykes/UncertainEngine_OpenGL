#include "Rect.h"

namespace Uncertain
{
	Rect::Rect(float x, float y, float width, float height)
		:X(x), Y(y), Width(width), Height(height)
	{
	}
	
	Rect::Rect()
		:X(0), Y(0), Width(0), Height(0)
	{
	}

	Rect::Rect(const Rect& r)
	{
		this->X = r.X;
		this->Y = r.Y;
		this->Width = r.Width;
		this->Height = r.Height;
	}

	Rect& Rect::operator=(const Rect& r)
	{
		if (this != &r)
		{
			this->X = r.X;
			this->Y = r.Y;
			this->Width = r.Width;
			this->Height = r.Height;
		}

		return *this;
	}

	void Rect::Clear()
	{
		this->X = 0;
		this->Y = 0;
		this->Width = 0;
		this->Height = 0;
	}

	void Rect::Set(float x, float y, float width, float height)
	{
		this->X = x;
		this->Y = y;
		this->Width = width;
		this->Height = height;
	}
}