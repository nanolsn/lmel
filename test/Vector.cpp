
#include "../lmel/Vector.h"
#include "test.h"

void testVector()
{
	using namespace lmel;

	// Creation & assignment
	{
		Vector<int, 1> v1(12);
		test(v1 == Vector<int, 1>{ 12 });

		Vector<int, 2> v2 = { 12, 4 };
		test(v2 == Vector<int, 2>{ 12, 4 });

		Vector<double, 3> v3 = { 5.0, 2.2, 4.34 };

		Vector<unsigned, 4> v4(0);
		test(v4 == Vector<unsigned, 4>{ 0, 0, 0, 0 });

		Vector<unsigned, 4> v5 = v4;
		test(v4 == v5);

		Vector<unsigned, 4> v6(0);
		v6 = v4;
		test(v4 == v6);
		test(v5 == v6);
	}

	// Compare operations
	{
		Vector<double, 2> v1(3.0);
		Vector<double, 2> v2 = { 3.0, 3.0 };
		test(v1 == v2);
		test(v2 == v1);

		Vector<double, 3> v3 = { 4.0, 7.0, 8.0 };
		Vector<double, 3> v4 = { 4.1, 7.0, 8.0 };
		test(v3 != v4);
		test(v4 != v3);
	}

	// get/set
	{
		const Vector<int, 3> v1(12);
		Vector<int, 3> v2(42);
		v2(0) = v1(2);
		test(v2 == Vector<int, 3>{ 12, 42, 42 });

		Vector<unsigned, 2> v3(0);
		v3(0) = 4;
		test(v3 == Vector<unsigned, 2>{ 4, 0 });
	}
}
