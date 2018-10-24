# LMEL
Line Math Engine Library

## Getting Started

```
// Create double 3x3 matrix with 1.0 value
double_matrix3d matrix(1.0);

// Multiply the matrix by 12
matrix *= 12;

// Set 42 value in the matrix
matrix(0, 0) = 42.0;

// Get the first row from the matrix
double_vector3d first_row = matrix.get_row(0);

// Get the second value from vector
double val = first_row(1);

// Get the matrix determinant
double det = determinant(matrix);
```
