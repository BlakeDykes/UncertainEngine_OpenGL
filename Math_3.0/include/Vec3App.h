//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef Vec3App_H
#define Vec3App_H

#include "Vec3.h"

namespace Uncertain
{
	class Vec3App
	{

	public:
		static void Lerp(Vec3 &out, const Vec3 &a, const Vec3 &b, const float t);
		static void LerpArray(Vec3 *out, const Vec3 *a, const Vec3 *b, const float t, const int numVects);
	};
}


#endif 

/**** END of VectApp.h *******************************************************/
