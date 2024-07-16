//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_QUAT_PROXY_H
#define ENGINE_MATH_QUAT_PROXY_H

namespace Uncertain
{

	struct QuatProxy
	{
	public:
		QuatProxy(const float _x, const float _y, const float _z, const float _w);

		bool operator==(const QuatProxy& mP) const;
		bool operator!=(const QuatProxy& mP) const;
		bool operator<(const QuatProxy& mP) const;
		bool operator<=(const QuatProxy& mP) const;
		bool operator>(const QuatProxy& mP) const;
		bool operator>=(const QuatProxy& mP) const;

		operator float() const;

	private:
		float x;
		float y;
		float z;
		float w;
	};

}

#endif

//--- End of File ---
