
#include "../lmel/square_matrix.h"
#include "../lmel/determinant.h"
#include "test.h"

void test_determinant() {
    using namespace lmel;

    {
        int_matrix1d m1(42);
        test(determinant(m1) == 42);

        int_matrix2d m2 =
                {
                        1, 2,
                        4, 3
                };
        test(determinant(m2) == -5);

        double_matrix3d m3 =
                {
                        1, 2, 3,
                        4, 5, 6,
                        7, 8, 12
                };
        test(determinant(m3) == -9);
    }
}