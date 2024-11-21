#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include "mainHeader.h"
#include "vector.h"

class Matrix2d {
public:
	std::array<std::array<double, 2>, 2> mat;

	Matrix2d() : mat({{{0, 0}, {0, 0}}}) {}
	Matrix2d(std::array<std::array<double, 2>, 2> arr) : mat(arr) {}

	Matrix2d operator+(const Matrix2d& other) const;

	Matrix2d operator-(const Matrix2d& other) const;

	Matrix2d operator*(const Matrix2d& other) const;

	Matrix2d operator*(double scalar) const;

	Matrix2d transpose() const;

	Matrix2d inverse() const;

	double determinant() const;
};

class Matrix3d {
public:
	std::array<std::array<double, 3>, 3> mat;

	Matrix3d() : mat({{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}) {}
	Matrix3d(std::array<std::array<double, 3>, 3> arr) : mat(arr) {}

	Matrix3d operator+(const Matrix3d& other) const;

	Matrix3d operator-(const Matrix3d& other) const;

	Matrix3d operator*(const Matrix3d& other) const;

	Matrix3d transpose() const;

	Matrix3d adjugate() const;

	Matrix3d inverse() const;

	Matrix3d operator*(double scalar) const;

	Vector3 operator*(const Vector3& other) const;

	Point3 operator*(const Point3& other) const;

	double determinant() const;
};
class Matrix4d {
public:
	std::array<std::array<double, 4>, 4> mat;

	Matrix4d() : mat({{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}}) {}
	Matrix4d(std::array<std::array<double, 4>, 4> arr) : mat(arr) {}

	Matrix4d operator+(const Matrix4d& other) const;

	Matrix4d operator-(const Matrix4d& other) const;

	Matrix4d operator*(const Matrix4d& other);

	Matrix4d transpose() const;

	Matrix4d adjugate() const;

	Matrix4d inverse() const;

	Matrix4d operator*(double scalar) const;

	double determinant() const;

	Matrix3d subMat(int row, int col) const;

	double minor(int row, int col) const;
};

#endif /* MATRIX_H */
