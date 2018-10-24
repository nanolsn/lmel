#pragma once

#include "square_matrix.h"

namespace lmel
{
	template <typename T, unsigned N>
	inline T determinant(const square_matrix<T, N> & m)
	{
		T det = 0;

		for (unsigned i = 0; i < N; ++i)
			det += (i % 2 == 0 ? 1 : -1) * m.data[0][i] * determinant(m.minor(0, i));

		return det;
	}

	template <typename T>
	inline T determinant(const square_matrix<T, 2> & m)
	{
		return m.data[0][0] * m.data[1][1] - m.data[1][0] * m.data[0][1];
	}

	template <typename T>
	inline T determinant(const square_matrix<T, 1> & m)
	{
		return m.data[0][0];
	}
}