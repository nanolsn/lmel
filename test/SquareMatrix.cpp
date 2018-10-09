
#include "../lmel/SquareMatrix.h"
#include "test.h"

void testSquareMatrix()
{
	using namespace lmel;

	// Creation & assignment
	{
		IntMatrix1D m1(0);
		test(m1 == Matrix1D<int>{ 0 });

		IntMatrix2D m2(0);
		test(m2 == Matrix2D<int>(0));

		IntMatrix3D m3(0);
		test(m3 == Matrix3D<int>(0));

		DoubleMatrix2D dm1(0.0);
		SquareMatrix<double, 2> dm2 =
		{
			0.0, 0.0,
			0.0, 0.0
		};
		test(dm1 == dm2);

		DoubleMatrix3D dm3(2.0);
		DoubleMatrix4D dm4(2.0);
		DoubleMatrix5D dm5(2.0);
		DoubleMatrix5D dm6 = dm5;
		test(dm5 == dm6);

		DoubleMatrix4D dm7(6.0);
		dm7 = dm4;
		test(dm7 == dm4);
	}
}
