
#include "../lmel/square_matrix.h"
#include "test.h"

void test_square_matrix() {
    using namespace lmel;

    // Creation & assignment
    {
        int_matrix1d m1(0);
        test(m1 == matrix1d<int>{0});

        int_matrix2d m2(0);
        test(m2 == matrix2d<int>(0));

        int_matrix3d m3(0);
        test(m3 == matrix3d<int>(0));

        double_matrix2d dm1(0.0);
        square_matrix<double, 2> dm2 =
                {
                        0.0, 0.0,
                        0.0, 0.0
                };
        test(dm1 == dm2);

        double_matrix3d dm3(2.0);
        double_matrix4d dm4(2.0);
        double_matrix5d dm5(2.0);
        double_matrix5d dm6 = dm5;
        test(dm5 == dm6);

        double_matrix4d dm7(6.0);
        dm7 = dm4;
        test(dm7 == dm4);

        double_matrix3d mc = make_square_matrix_from_cols({
                                                                  double_vector3d{1, 2, 3},
                                                                  double_vector3d{1, 2, 5},
                                                                  double_vector3d{8, 8, 8}
                                                          });

        double_matrix3d mcw =
                {
                        1, 1, 8,
                        2, 2, 8,
                        3, 5, 8
                };
        test(mc == mcw);

        double_matrix3d mr = make_square_matrix_from_rows({
                                                                  double_vector3d{1, 2, 3},
                                                                  double_vector3d{1, 2, 5},
                                                                  double_vector3d{8, 8, 8}
                                                          });

        double_matrix3d mrw =
                {
                        1, 2, 3,
                        1, 2, 5,
                        8, 8, 8
                };
        test(mr == mrw);

        int_matrix3d id =
                {
                        1, 0, 0,
                        0, 1, 0,
                        0, 0, 1
                };
        test(id == make_id_matrix<int, 3>());

        int_matrix3d m;
        int_matrix3d empty =
                {
                        0, 0, 0,
                        0, 0, 0,
                        0, 0, 0
                };
        test(m == empty);

        int_matrix5d mi(5);
        double_matrix5d md = mi;
        test(md == mi);

        int_matrix1d mi1(5);
        double_matrix1d md1 = mi1;
        test(md1 == mi1);

        int_matrix<3, 3> m33(9);
        int_matrix3d m3d = m33;
        int_matrix3d m3d2(9);
        test(m3d == m3d2);

        int_matrix1d m1d(22);
        int_matrix1d m1d2(8);
        m1d = m1d2;
        test(m1d == m1d2);
    }

    // Get row/col/diagonal
    {
        int_matrix5d m1(0);
        m1(0, 0) = 5;
        m1(0, 2) = 1;
        test(m1.get_row(0) == int_vector5d{5, 0, 1, 0, 0});

        int_matrix3d m2(9);
        m2(0, 0) = 1;
        m2(1, 0) = 2;
        test(m2.get_col(0) == int_vector3d{1, 2, 9});

        int_matrix3d m3 =
                {
                        1, 2, 34,
                        5, 6, 7,
                        8, 9, 0
                };
        test(m3.get_diagonal() == int_vector3d{1, 6, 0});
    }

    // Math operations
    {
        int_matrix2d m1(1);
        int_matrix2d m2 =
                {
                        2, 2,
                        2, 0
                };
        int_matrix2d m3 =
                {
                        3, 3,
                        3, 1
                };
        test(m1 + m2 == m3);

        int_matrix2d m4 =
                {
                        -1, -1,
                        -1, 1
                };
        test(m1 - m2 == m4);

        int_matrix2d m5 =
                {
                        4, 2,
                        4, 2
                };
        test(m1 * m2 == m5);

        int_matrix1d h1(4);
        int_matrix1d h2(1);
        test(h1 + h2 == int_matrix1d(5));
        test(h1 - h2 == int_matrix1d(3));
        test(h1 * h2 == int_matrix1d(4));

        int_matrix3d n1(5);
        int_matrix3d n2(10);
        int_matrix3d n3(15);
        n1 += n2;
        test(n1 == n3);

        n1 -= n2;
        test(n1 == int_matrix3d(5));

        n1 *= n2;
        test(n1 == int_matrix3d(150));

        n1 /= 15;
        test(n1 == int_matrix3d(10));

        n1 += 2;
        test(n1 == int_matrix3d(12));

        n1 *= 2;
        test(n1 == int_matrix3d(24));

        n1 -= 4;
        test(n1 == int_matrix3d(20));

        test(n1 + 1 == int_matrix3d(21));
        test(n1 / 2 == int_matrix3d(10));
        test(n1 - 4 == int_matrix3d(16));
        test(n1 * 2 == int_matrix3d(40));

        int_matrix2d z1 =
                {
                        1, 2,
                        3, 4
                };
        int_matrix2d z2 =
                {
                        5, 5,
                        5, 1
                };
        int_matrix2d z3 =
                {
                        15, 7,
                        35, 19
                };
        test(z1 * z2 == z3);

        int_matrix2d z4 =
                {
                        15, 35,
                        7, 19
                };
        z3.transpose();
        test(z3 == z4);

        int_matrix2d z5 =
                {
                        15, 7,
                        35, 19
                };

        test(z5.get_transpose() == z4);
    }

    // Vector product
    {
        int_matrix3d m =
                {
                        1, 2, 2,
                        2, 2, 4,
                        1, 1, 4
                };

        int_vector3d v = {1, 2, 3};
        test(m * v == int_vector3d{11, 18, 15});

        test(int_matrix1d(6) * int_vector1d(6) == int_vector1d(36));
    }

    // Operations order
    {
        int_matrix3d m1 =
                {
                        2, 5, 4,
                        -6, 2, 3,
                        7, 6, 2
                };

        int_matrix3d m2 =
                {
                        1, 2, 3,
                        6, 5, -4,
                        7, 2, -7
                };

        int_vector3d v1 = {4, 2, 3};
        int_vector3d res = {146, -59, -134};

        test(m2 * m1 * v1 == res);
        test((m2 * m1) * v1 == res);
        test(m2 * (m1 * v1) == res);
    }

    // Compare operations
    {
        int_matrix2d m1(12);
        int_matrix2d m2(12);
        test(m1 == m2);
        test(m2 == m1);

        m2(1, 1) = 7;
        test(m1 != m2);
        test(m2 != m1);

        test(m2 == m2);
        test(m1 == m1);
    }

    // Minor
    {
        int_matrix3d m1(12);
        int_matrix2d m2 = m1.minor(0, 0);
        test(m2 == int_matrix2d(12));

        int_matrix3d m3 =
                {
                        1, 2, 3,
                        4, 5, 6,
                        7, 8, 9
                };
        int_matrix2d m4 =
                {
                        1, 3,
                        7, 9
                };
        test(m3.minor(1, 1) == m4);

        int_matrix1d m5 = m4.minor(0, 0);
        test(m5 == int_matrix1d(9));
    }
}
