#include <iostream>
#include "lmel/SquareMatrix.h"
#include "lmel/Vector.h"

using namespace lmel;

template <typename T, unsigned N>
void show(const SquareMatrix<T, N> & mat)
{
	for (unsigned i = 0; i < mat.rows; ++i) {
		for (unsigned j = 0; j < mat.cols; ++j)
			std::cout << mat(i, j) << " ";

		std::cout << "\n";
	}
}

void test(bool condition)
{
	std::cout << (condition ? "OK." : "Fail!") << "\n";
}

int main()
{
	Vector<double, 6> v(12);

	SquareMatrix<int, 3> m33_1 =
	{
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	};

	SquareMatrix<int, 3> m33_2 =
	{
		2, 2, 2,
		4, 3, 2,
		4, 4, 4
	};

	auto res_1 = m33_1 * m33_2;
	SquareMatrix<int, 3> m33_3 =
	{
		22, 20, 18,
		52, 47, 42,
		82, 74, 66
	};

	test(res_1 == m33_3);
	
	getchar();
	return 0;
}