#include <iostream>
#include "Matrix4D.h"

using namespace lmel;

template <typename T>
void show(const Matrix4D<T> & mat)
{
	for (unsigned i = 0; i < mat.rows; ++i) {
		for (unsigned j = 0; j < mat.cols; ++j)
			std::cout << mat(i, j) << " ";

		std::cout << "\n";
	}
}

int main()
{
	Matrix4D<int> mat(0);
	Matrix4D<int> mat0(0);

	std::cout << (mat == mat0 ? "EQ!\n" : "NEQ!\n");

	// Init matrix with values
	Matrix4D<int> nums =
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
	Matrix4D<int> mat2 = mat * 2;

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

	std::cout << "Det: " << mat.determinant() << "\n";

	getchar();
	return 0;
}