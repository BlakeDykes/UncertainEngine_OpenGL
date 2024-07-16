//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "MathEngine.h"
using namespace Uncertain;

//---------------------------------------------------------------------------
// TESTS:
//---------------------------------------------------------------------------

TEST(Vec4_Get_Accessors, TestConfig::ALL)
{
#if Vec4_Get_Accessors

	Vec4 A(2.0f, 3.0f, 4.0f, 5.0f);

	CHECK(A.x() == 2.0f);
	CHECK(A.y() == 3.0f);
	CHECK(A.z() == 4.0f);
	CHECK(A.w() == 5.0f);

#endif
} TEST_END

// ---  End of File ---------------