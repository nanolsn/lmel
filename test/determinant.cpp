
#include "../lmel/SquareMatrix.h"
#include "../lmel/determinant.h"
#include "test.h"

void testDeterminant()
{
	using namespace lmel;

	{
		IntMatrix1D m1(42);
		test(determinant(m1) == 42);

		IntMatrix2D m2 =
		{
			1, 2,
			4, 3
		};
		test(determinant(m2) == -5);

		DoubleMatrix3D m3 =
		{
			1, 2, 3,
			4, 5, 6,
			7, 8, 12
		};
		test(determinant(m3) == -9);
	}
}