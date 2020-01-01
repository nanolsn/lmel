
#include "../lmel/vector.h"
#include "test.h"

void test_vector() {
    using namespace lmel;

    // Creation & assignment
    {
        vector<int, 1> v1(12);
        test(v1 == vector<int, 1>{12});

        vector<int, 2> v2 = {12, 4};
        test(v2 == vector<int, 2>{12, 4});

        vector<double, 3> v3 = {5.0, 2.2, 4.34};

        vector<unsigned, 4> v4(0);
        test(v4 == vector<unsigned, 4>{0, 0, 0, 0});

        vector<unsigned, 4> v5 = v4;
        test(v4 == v5);

        vector<unsigned, 4> v6(0);
        v6 = v4;
        test(v4 == v6);
        test(v5 == v6);

        int_vector3d v;
        test(v == int_vector3d{0, 0, 0});

        int_vector5d vi(5);
        double_vector5d vd = vi;
        test(vd == vi);
    }

    // Compare operations
    {
        vector<double, 2> v1(3.0);
        vector<double, 2> v2 = {3.0, 3.0};
        test(v1 == v2);
        test(v2 == v1);

        vector<double, 3> v3 = {4.0, 7.0, 8.0};
        vector<double, 3> v4 = {4.1, 7.0, 8.0};
        test(v3 != v4);
        test(v4 != v3);
    }

    // get/set
    {
        const vector<int, 3> v1(12);
        vector<int, 3> v2(42);
        v2(0) = v1(2);
        test(v2 == vector<int, 3>{12, 42, 42});

        vector<unsigned, 2> v3(0);
        v3(0) = 4;
        test(v3 == vector<unsigned, 2>{4, 0});
    }

    // Cross product
    {
        int_vector3d v1 = {1, 2, 3};
        int_vector3d v2 = {4, 5, 6};
        test(cross(v1, v2) == int_vector3d{-3, -6, -3});
    }

    // Normalize
    {
        int_vector3d v = {0, -2, 0};
        v.normalize();
        test(v == int_vector3d{0, -1, 0});

        int_vector3d z = {0, 0, 0};
        test(!z.normalize());
    }
}
