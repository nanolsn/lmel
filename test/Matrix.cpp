
#include "../lmel/Matrix.h"
#include "test.h"

void testMatrix()
{
	using namespace lmel;

	// Creation & assignment
	{
		Matrix<int, 2, 3> m =
		{
			1, 2, 3,
			4, 5, 6
		};

		IntMatrix<3, 2> m2 =
		{
			1, 4,
			2, 5,
			3, 6
		};

		test(m.getTranspose() == m2);
		test(m == m2.getTranspose());

		IntMatrix<3, 2> m3 = m2;
		test(m3 == m2);
		test(m2 == m3);
		test(m == m);
	}
}