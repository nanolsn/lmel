
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

	// Get row/col
	{
		IntMatrix5D m1(0);
		m1(0, 0) = 5;
		m1(0, 2) = 1;
		test(m1.getRow(0) == IntVector5D{ 5, 0, 1, 0, 0 });

		IntMatrix3D m2(9);
		m2(0, 0) = 1;
		m2(1, 0) = 2;
		test(m2.getCol(0) == IntVector3D{ 1, 2, 9 });
	}

	// Math operations
	{
		IntMatrix2D m1(1);
		IntMatrix2D m2 =
		{
			2, 2,
			2, 0
		};
		IntMatrix2D m3 =
		{
			3, 3,
			3, 1
		};
		test(m1 + m2 == m3);

		IntMatrix2D m4 =
		{
			-1, -1,
			-1,  1
		};
		test(m1 - m2 == m4);

		IntMatrix2D m5 =
		{
			4, 2,
			4, 2
		};
		test(m1 * m2 == m5);

		IntMatrix1D h1(4);
		IntMatrix1D h2(1);
		test(h1 + h2 == IntMatrix1D(5));
		test(h1 - h2 == IntMatrix1D(3));
		test(h1 * h2 == IntMatrix1D(4));

		IntMatrix3D n1(5);
		IntMatrix3D n2(10);
		IntMatrix3D n3(15);
		n1 += n2;
		test(n1 == n3);

		n1 -= n2;
		test(n1 == IntMatrix3D(5));

		n1 *= n2;
		test(n1 == IntMatrix3D(150));

		n1 /= 15;
		test(n1 == IntMatrix3D(10));

		n1 += 2;
		test(n1 == IntMatrix3D(12));

		n1 *= 2;
		test(n1 == IntMatrix3D(24));

		n1 -= 4;
		test(n1 == IntMatrix3D(20));

		test(n1 + 1 == IntMatrix3D(21));
		test(n1 / 2 == IntMatrix3D(10));
		test(n1 - 4 == IntMatrix3D(16));
		test(n1 * 2 == IntMatrix3D(40));

		IntMatrix2D z1 =
		{
			1, 2,
			3, 4
		};
		IntMatrix2D z2 =
		{
			5, 5,
			5, 1
		};
		IntMatrix2D z3 =
		{
			15, 7,
			35, 19
		};
		test(z1 * z2 == z3);

		IntMatrix2D z4 =
		{
			15, 35,
			7, 19
		};
		z3.transpose();
		test(z3 == z4);
	}

	// Compare operations
	{
		IntMatrix2D m1(12);
		IntMatrix2D m2(12);
		test(m1 == m2);
		test(m2 == m1);

		m2(1, 1) = 7;
		test(m1 != m2);
		test(m2 != m1);

		test(m2 == m2);
		test(m1 == m1);
	}

	// Minor
	{
		IntMatrix3D m1(12);
		IntMatrix2D m2 = m1.minor(0, 0);
		test(m2 == IntMatrix2D(12));

		IntMatrix3D m3 =
		{
			1, 2, 3,
			4, 5, 6,
			7, 8, 9
		};
		IntMatrix2D m4 =
		{
			1, 3,
			7, 9
		};
		test(m3.minor(1, 1) == m4);

		IntMatrix1D m5 = m4.minor(0, 0);
		test(m5 == IntMatrix1D(9));
	}
}
