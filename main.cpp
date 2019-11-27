
#include <iostream>
#include "lmel/matrix.h"
#include "lmel/square_matrix.h"
#include "lmel/vector.h"
#include "lmel/quaternion.h"

using namespace lmel;
using namespace std;

template<typename T, size_t N>
void show(const vector<T, N> &vec) {
    for (size_t i = 0; i < vec.size; ++i)
        cout << vec(i) << " ";
}

template<typename T, size_t N>
void show(const square_matrix<T, N> &mat) {
    for (size_t i = 0; i < mat.rows; ++i) {
        for (size_t j = 0; j < mat.cols; ++j)
            cout << mat(i, j) << " ";

        cout << "\n";
    }
}

template<typename T, size_t N, size_t M>
void show(const matrix<T, N, M> &mat) {
    for (size_t i = 0; i < mat.rows; ++i) {
        for (size_t j = 0; j < mat.cols; ++j)
            cout << mat(i, j) << " ";

        cout << "\n";
    }
}

template<typename T>
void show(const quaternion<T> &qt) {
    cout << qt.x << " " << qt.y << " " << qt.z << " " << qt.w << "\n";
}

#include "test/vector.cpp"
#include "test/matrix.cpp"
#include "test/square_matrix.cpp"
#include "test/determinant.cpp"
#include "test/quaternion.cpp"

int main() {
    cout << "Run tests:\n";
    test_vector();
    test_matrix();
    test_square_matrix();
    test_determinant();
    test_quaternion();

    quaternion<double> q(double_vector3d{1.0, 0.0, 0.0}, 1.0);
    show(q);

    cout << "\n";

    show(q.get_rotation_matrix3d());

    cout << "\n";

    show(make_id_quaternion<double>());

    return 0;
}
