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

TEST(Mat4_Special_isEqual_true, TestConfig::ALL)
{
#if Mat4_Special_isEqual_true

	Vec4 V0(1.0f, 2.0f, 3.0f, 4.0f);
	Vec4 V1(5.0f, 6.0f, 7.0f, 8.0f);
	Vec4 V2(9.0f, 10.0f, 11.0f, 12.0f);
	Vec4 V3(13.0f, 14.0f, 15.0f, 16.0f);

	Mat4 A(V0, V1, V2, V3);

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

	Vec4 V4(1.0f, 2.0f, 3.0f, 4.0f);
	Vec4 V5(5.0f, 6.0f, 7.0f, 8.0f);
	Vec4 V6(9.0f, 10.0f, 11.0f, 12.0f);
	Vec4 V7(13.0f, 14.0f, 15.0f, 16.0f);

	Mat4 B(V4, V5, V6, V7);

	CHECK(B[m0] == 1.0f);
	CHECK(B[m1] == 2.0f);
	CHECK(B[m2] == 3.0f);
	CHECK(B[m3] == 4.0f);
	CHECK(B[m4] == 5.0f);
	CHECK(B[m5] == 6.0f);
	CHECK(B[m6] == 7.0f);
	CHECK(B[m7] == 8.0f);
	CHECK(B[m8] == 9.0f);
	CHECK(B[m9] == 10.0f);
	CHECK(B[m10] == 11.0f);
	CHECK(B[m11] == 12.0f);
	CHECK(B[m12] == 13.0f);
	CHECK(B[m13] == 14.0f);
	CHECK(B[m14] == 15.0f);
	CHECK(eq_float(B[m15],16.0f));

	const bool value = A.isEqual(B);

	CHECK(value == true);

#endif
} TEST_END

// ---  End of File ---
