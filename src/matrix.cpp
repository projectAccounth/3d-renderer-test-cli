#include "../include/matrix.h"

Matrix2d Matrix2d::operator*(const Matrix2d& other) const {
    Matrix2d result;
    for (int i = 0; i < 2; ++i) { 
        for (int j = 0; j < 2; ++j) {
            result.mat[i][j] = 0; // Initialize the element to zero
            for (int k = 0; k < 2; ++k) { // Summing the products
                result.mat[i][j] += mat[i][k] * other.mat[k][j];
            }
        }
    }
    return result;
}

Matrix2d Matrix2d::operator+(const Matrix2d& other) const {
    Matrix2d result;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            result.mat[i][j] = mat[i][j] + other.mat[i][j];
        }
    }
    return result;
}

Matrix2d Matrix2d::operator*(double scalar) const {
    Matrix2d result;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            result.mat[i][j] = mat[i][j] * scalar;
        }
    }
    return result;
}

Matrix2d Matrix2d::operator-(const Matrix2d& other) const {
    Matrix2d result;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            result.mat[i][j] = mat[i][j] - other.mat[i][j];
        }
    }
    return result;
}


double Matrix2d::determinant() const {
    return mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];
}

Matrix2d Matrix2d::transpose() const {
    Matrix2d result;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            result.mat[i][j] = mat[j][i];
        }
    }
    return result;
}

Matrix2d Matrix2d::inverse() const {
    double mul = (1.0 / determinant());
    return Matrix2d({{{mat[1][1], -mat[0][1]}, {-mat[1][0], mat[0][0]}}}) * mul;
}

Matrix3d Matrix3d::operator*(const Matrix3d& other) const {
    Matrix3d result;

    for (int i = 0; i < 3; ++i) { 
        for (int j = 0; j < 3; ++j) {
            result.mat[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                result.mat[i][j] += mat[i][k] * other.mat[k][j];
            }
        }
    }

    return result;
}

Matrix3d Matrix3d::operator+(const Matrix3d& other) const {
    Matrix3d result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.mat[i][j] = mat[i][j] + other.mat[i][j];
        }
    }
    return result;
}

Matrix3d Matrix3d::operator-(const Matrix3d& other) const {
    Matrix3d result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.mat[i][j] = mat[i][j] - other.mat[i][j];
        }
    }
    return result;
}

Matrix3d Matrix3d::operator*(double scalar) const {
    Matrix3d result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.mat[i][j] = mat[i][j] * scalar;
        }
    }
    return result;
}

Vector3 Matrix3d::operator*(const Vector3& vector) const {
    Vector3 result;

    result.x = mat[0][0] * vector.x + mat[0][1] * vector.y + mat[0][2] * vector.z;
    result.y = mat[1][0] * vector.x + mat[1][1] * vector.y + mat[1][2] * vector.z;
    result.z = mat[2][0] * vector.x + mat[2][1] * vector.y + mat[2][2] * vector.z;

    return result;
}

Point3 Matrix3d::operator*(const Point3& other) const {
    Point3 result;

    result.x = mat[0][0] * other.x + mat[0][1] * other.y + mat[0][2] * other.z;
    result.y = mat[1][0] * other.x + mat[1][1] * other.y + mat[1][2] * other.z;
    result.z = mat[2][0] * other.x + mat[2][1] * other.y + mat[2][2] * other.z;

    return result;
}

double Matrix3d::determinant() const {
    return mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) -
           mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
           mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
}

Matrix3d Matrix3d::transpose() const {
    Matrix3d result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.mat[i][j] = mat[j][i];
        }
    }
    return result;
}

Matrix3d Matrix3d::adjugate() const {
    return Matrix3d({{
        {
            (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]), 
            -(mat[0][1] * mat[2][2] - mat[0][2] * mat[2][1]), 
            (mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1])
        },
        {
            -(mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]), 
            (mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0]), 
            -(mat[0][0] * mat[1][2] - mat[0][2] * mat[1][0])
        },
        {
            (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]), 
            -(mat[0][0] * mat[2][1] - mat[0][1] * mat[2][0]), 
            (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0])
        }
    }});
}

Matrix3d Matrix3d::inverse() const {
    double det = determinant();
    if (det == 0.0) {
        std::cerr << ("Matrix is singular and cannot be inverted.");
        return Matrix3d();
    }
    return adjugate() * (1 / determinant());
}

Matrix4d Matrix4d::operator+(const Matrix4d& other) const {
    Matrix4d result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.mat[i][j] = mat[i][j] + other.mat[i][j];
        }
    }
    return result;
};

Matrix4d Matrix4d::operator-(const Matrix4d& other) const {
    Matrix4d result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.mat[i][j] = mat[i][j] - other.mat[i][j];
        }
    }
    return result;
};

Matrix4d Matrix4d::operator*(const Matrix4d& other){
    Matrix4d result;
    // Perform matrix multiplication
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result.mat[i][j] += mat[i][k] * other.mat[k][j];
            }
        }
    }
    return result;
};

Matrix4d Matrix4d::operator*(double scalar) const {
    Matrix4d result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.mat[i][j] = mat[i][j] * scalar;
        }
    }
    return result;
}

double Matrix4d::determinant() const {
    Matrix3d minor;
    double det = 0;

    // Iterate over the first row
    for (int i = 0; i < 4; ++i) {
        // Get the 3x3 submatrix after removing row 0 and column i
        int row = 0;
        for (int j = 1; j < 4; ++j) {
            int col = 0;
            for (int k = 0; k < 4; ++k) {
                if (k == i) continue; // Skip the element in the i-th column
                minor.mat[row][col] = mat[j][k];
                col++;
            }
            row++;
        }
        // Alternate the signs (positive and negative) for the cofactor expansion
        double sign = (i % 2 == 0) ? 1 : -1;
        det += sign * mat[0][i] * minor.determinant();
    }

    return det;
}

Matrix3d Matrix4d::subMat(int row, int col) const {
    Matrix3d submatrix;

    int subRow = 0; // Row index for submatrix
    for (int i = 0; i < 4; ++i) {
        if (i == row) continue; // Skip the specified row

        int subCol = 0; // Column index for submatrix
        for (int j = 0; j < 4; ++j) {
            if (j == col) continue; // Skip the specified column

            submatrix.mat[subRow][subCol] = mat[i][j];
            ++subCol;
        }
        ++subRow;
    }

    // return the 3x3 submatrix
    return submatrix;
}

Matrix4d Matrix4d::adjugate() const {
    Matrix4d res;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            res.mat[j][i] = minor(i, j) * ((i + j) % 2 == 0 ? 1 : -1); // Transpose while assigning
        }
    }

    return res;
}

double Matrix4d::minor(int row, int col) const {
    return subMat(row, col).determinant();
}

Matrix4d Matrix4d::inverse() const {
    return adjugate() * (1 / determinant());
}

Matrix4d Matrix4d::transpose() const {
    Matrix4d result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.mat[i][j] = mat[j][i];
        }
    }
    return result;
}