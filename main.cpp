#include <iostream>
#include "lmel/SquareMatrix.h"
#include "lmel/Vector.h"

using namespace lmel;

template <typename T, unsigned N>
void show(const Vector<T, N> & v)
{
	for (unsigned i = 0; i < v.size; ++i)
		std::cout << v(i) << " ";
}

template <typename T, unsigned N>
void show(const SquareMatrix<T, N> & mat)
{
	for (unsigned i = 0; i < mat.rows; ++i)
	{
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

	std::cout << "\n";

	auto v1 = m33_1.getRow(0);
	auto v2 = m33_1.getCol(2);

	show(v1);
	std::cout << "\n";
	show(v2);

	std::cout << "\n";

	SquareMatrix<int, 1> m11_1(12);

	auto v21 = m11_1.getRow(0);
	auto v22 = m11_1.getCol(0);

	show(v21);
	std::cout << "\n";
	show(v22);
	
	getchar();
	return 0;
}