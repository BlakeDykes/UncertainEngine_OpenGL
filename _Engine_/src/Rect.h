#ifndef RECT_H
#define RECT_H

namespace Uncertain
{
	class Rect
	{
	public:
		Rect(float x, float y, float width, float height);
		Rect();
		Rect(const Rect&);
		Rect& operator=(const Rect&);
		~Rect() = default;

		void Clear();
		void Set(float x, float y, float width, float height);


		float X;
		float Y;
		float Width;
		float Height;
	};
}

#endif