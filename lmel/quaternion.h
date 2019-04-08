#pragma once

#include <initializer_list>
#include <cassert>
#include <math.h>
#include "square_matrix.h"

namespace lmel
{
	template <
		typename T,
		typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
		>
	class quaternion
	{
	public:
		T x;
		T y;
		T z;
		T w;

		// Default constructor
		explicit quaternion(T x = 0, T y = 0, T z = 0, T w = 0)
			: x(x), y(y), z(z), w(w)
		{}

		// Constructor from axis and angle
		quaternion(vector<T, 3> axis, T angle)
		{
			T s = sin(angle / 2);

			x = axis.x() * s;
			y = axis.y() * s;
			z = axis.z() * s;
			w = cos(angle / 2);
		}

		// Initializer list constructor
		quaternion(std::initializer_list<T> il)
		{
			assert(il.size() == 4);

			auto it = il.begin();
			x = *it++;
			y = *it++;
			z = *it++;
			w = *it;
		}

		// Copy constructor
		quaternion(const quaternion & ref)
		{
			x = ref.x;
			y = ref.y;
			z = ref.z;
			w = ref.w;
		}

		// Template copy constructor (for other types)
		template <typename O>
		quaternion(const quaternion<O> & ref)
		{
			x = ref.x;
			y = ref.y;
			z = ref.z;
			w = ref.w;
		}

		// Assignment operator
		quaternion & operator=(const quaternion & val)
		{
			if (&val == this)
				return *this;

			x = val.x;
			y = val.y;
			z = val.z;
			w = val.w;

			return *this;
		}

		// Compare operations:

		bool operator==(const quaternion & m) const
		{
			return
				x == m.x &&
				y == m.y &&
				z == m.z &&
				w == m.w;
		}

		bool operator!=(const quaternion & m) const
		{
			return
				x != m.x ||
				y != m.y ||
				z != m.z ||
				w != m.w;
		}

		square_matrix<T, 3> get_rotation_matrix3d() const
		{
			T sqx = x * x;
			T sqy = y * y;
			T sqz = z * z;
			T sqw = w * w;

			T i = 1 / (sqx + sqy + sqz + sqw);

			T xy = x * y;
			T zw = z * w;
			T xz = x * z;
			T yw = y * w;
			T yz = y * z;
			T xw = x * w;

			return square_matrix<T, 3>
			{
				 (sqx - sqy - sqz + sqw) * i, 2 * (xy - zw) * i, 2 * (xz + yw) * i,
				2 * (xy + zw) * i, (-sqx + sqy - sqz + sqw) * i, 2 * (yz - xw) * i,
				2 * (xz - yw) * i, 2 * (yz + xw) * i, (-sqx - sqy + sqz + sqw) * i
			};
		}
	};

	template <typename T, typename V, typename A>
	quaternion<T> make_quaternion(vector<V, 3> axis, A angle)
	{
		T s = sin(angle / 2);

		return quaternion<T>(
			axis.x() * s,
			axis.y() * s,
			axis.z() * s,
			cos(angle / 2)
			);
	}

	template <typename T, typename V, typename A>
	quaternion<T> make_quaternion(V axis_x, V axis_y, V axis_z, A angle)
	{
		T s = sin(angle / 2);

		return quaternion<T>(
			axis_x * s,
			axis_y * s,
			axis_z * s,
			cos(angle / 2)
			);
	}

	template <typename T>
	quaternion<T> make_id_quaternion()
	{
		return quaternion<T>(1, 0, 0, 0);
	}
}
