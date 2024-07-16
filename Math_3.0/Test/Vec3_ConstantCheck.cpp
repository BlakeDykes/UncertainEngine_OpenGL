//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"
#include "MathEngine.h"
using namespace Uncertain;

//---------------------------------------------------------------------------
// Sample TESTS:
//---------------------------------------------------------------------------

TEST(Vec3_ConstantCheck, TestConfig::ALL)
{
#if Vec3_ConstantCheck

	CHECK(Util::isEqual(MATH_PI2, 1.570796f, MATH_TOLERANCE) == true);

#endif
} TEST_END

// ---  End of File ---------------