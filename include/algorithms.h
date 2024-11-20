#pragma once

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "mainHeader.h"
#include "point.h"
#include "vector.h"
#include "matrix.h"
#include "angles.h"

void bresenham(Point2 p0, Point2 p1);

void transformObject(
	EulerAngles& objectRotationAngles, Point3 objectWorldPos,
	EulerAngles& cameraRotationAngles, Point3 cameraPosition,
	Point3 displayPosition,
	std::vector<Point3>& localVertices,
	std::vector<Point2>& projectedVertices
);

void updateAngles(EulerAngles camRotation, Point3& camPos, Point3& displayPos, std::vector<Vector3> d_vs, std::vector<Point3> vertices, std::vector<Point2> projectionPs);

void resetAllImages();

void updateImage(std::vector<Point3>& vertices, std::vector<Point2>& projectP, double nearPlane, Point3 displayPosition);

Point3 calculateCentroid(const std::vector<Point3>& vertices);

void updateAll(
	EulerAngles& objectRotationAngles, Point3 objectWorldPos,
	EulerAngles& cameraRotationAngles, Point3& cameraPosition,
	Point3& displayPosition,
	std::vector<Point3>& localVertices,
	std::vector<Point2>& projectedVertices,
	std::vector<Vector3>& d_vs
);

#endif /* ALGORITHMS_H */
