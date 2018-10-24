
#include "../lmel/matrix.h"
#include "test.h"

void test_matrix()
{
	using namespace lmel;

	// Creation & assignment
	{
		matrix<int, 2, 3> m =
		{
			1, 2, 3,
			4, 5, 6
		};

		int_matrix<3, 2> m2 =
		{
			1, 4,
			2, 5,
			3, 6
		};

		test(m.get_transpose() == m2);
		test(m == m2.get_transpose());

		int_matrix<3, 2> m3 = m2;
		test(m3 == m2);
		test(m2 == m3);
		test(m == m);
	}
}