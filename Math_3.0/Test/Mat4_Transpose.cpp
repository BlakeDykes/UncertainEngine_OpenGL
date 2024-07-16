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

TEST(Mat4_Transpose, TestConfig::ALL)
{
#if Mat4_Transpose

	Vec4 v0(1.0f, 2.0f, 3.0f, 4.0f);
	Vec4 v1(5.0f, 6.0f, 7.0f, 8.0f);
	Vec4 v2(9.0f, 10.0f, 11.0f, 12.0f);
	Vec4 v3(13.0f, 14.0f, 15.0f, 16.0f);

	Mat4 A(v0, v1, v2, v3);

	CHECK(A[m0] == 1.0f);
	CHECK(A[m1] == 2.0f);
	CHECK(A[m2] == 3.0f);
	CHECK(A[m3] == 4.0f);
	CHECK(A[m4] == 5.0f);
	CHECK(A[m5] == 6.0f);
	CHECK(A[m6] == 7.0f);
	CHECK(A[m7] == 8.0f);
	CHECK(A[m8] == 9.0f);
	CHECK(A[m9] == 10.0f);
	CHECK(A[m10] == 11.0f);
	CHECK(A[m11] == 12.0f);
	CHECK(A[m12] == 13.0f);
	CHECK(A[m13] == 14.0f);
	CHECK(A[m14] == 15.0f);
	CHECK(eq_float(A[m15],16.0f));

	A.T();

	CHECK(A[m0] == 1.0f);
	CHECK(A[m1] == 5.0f);
	CHECK(A[m2] == 9.0f);
	CHECK(A[m3] == 13.0f);
	CHECK(A[m4] == 2.0f);
	CHECK(A[m5] == 6.0f);
	CHECK(A[m6] == 10.0f);
	CHECK(A[m7] == 14.0f);
	CHECK(A[m8] == 3.0f);
	CHECK(A[m9] == 7.0f);
	CHECK(A[m10] == 11.0f);
	CHECK(A[m11] == 15.0f);
	CHECK(A[m12] == 4.0f);
	CHECK(A[m13] == 8.0f);
	CHECK(A[m14] == 12.0f);
	CHECK(eq_float(A[m15],16.0f));

#endif
} TEST_END

// --- End of File ---
