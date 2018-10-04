#include <iostream>
#include "Matrix.h"

using namespace lmel;

template <typename T>
void show(const Matrix<T> & mat)
{
	for (unsigned i = 0; i < mat.rows; ++i) {
		for (unsigned j = 0; j < mat.cols; ++j)
			std::cout << mat.get(i * mat.cols + j) << " ";

		std::cout << "\n";
	}
}

int main()
{
	Matrix<int> mat(0);
	Matrix<int> mat0(0);

	std::cout << (mat == mat0 ? "EQ!\n" : "NEQ!\n");

	mat(0, 0) = 1;
	mat(1, 0) = 1;
	mat(2, 0) = 3;
	mat(3, 0) = 1;

	mat(3, 3) = 4;

	show(mat);

	std::cout << "\n";

	mat.transpose();
	Matrix<int> mat2 = mat * 2;

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

	getchar();
	return 0;
}