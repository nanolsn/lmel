#include <iostream>
#include "SquareMatrix.h"

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

int main()
{
	SquareMatrix<int, 4> mat(0);
	SquareMatrix<int, 4> mat0(0);

	std::cout << (mat == mat0 ? "EQ!\n" : "NEQ!\n");

	// Init matrix with values
	SquareMatrix<int, 4> nums =
	{
		1, 3, 4, 5,
		1, 1, 4, 5,
		1, 0, 1, 5,
		1, 0, 0, 1
	};

	show(nums);

	std::cout << "\n";

	mat(0, 0) = 1;
	mat(1, 0) = 1;
	mat(2, 0) = 3;
	mat(3, 0) = 1;

	mat(3, 3) = 4;

	show(mat);

	std::cout << "\n";

	mat.transpose();
	SquareMatrix<int, 4> mat2 = mat * 2;

	show(mat2);

	std::cout << (mat == mat2 ? "\nEQ!\n" : "\nNEQ!\n");

	mat = mat + mat;
	show(mat);

	std::cout << "\n";

	mat += mat;
	show(mat);

	std::cout << "\n";

	mat *= mat2;
	show(mat);

	std::cout << "\n";

	SquareMatrix<int, 3> m2 = 
	{
		2, 1, 5,
		-2, 0, 5,
		4, 3, 2
	};

	std::cout << "Det: " << determinant(m2) << "\n";

	std::cout << "\n";

	SquareMatrix<int, 3> min = mat.minor(0, 3);

	std::cout << "Minor:\n";

	show(min);

	std::cout << "\n";

	SquareMatrix<int, 1> m1(3);
	SquareMatrix<int, 1> m12 = { 12 };

	show(m1 * m12 * 2);

	std::cout << "\n";

	getchar();
	return 0;
}