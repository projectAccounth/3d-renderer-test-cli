#pragma once

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "mainHeader.h"
#include "matrix.h"
#include "angles.h"
#include "camera.h"

void resetAllImages();

Point3 calculateCentroid(const std::vector<Point3>& vertices);

void updateAll(
	EulerAngles& objectRotationAngles, Point3 objectWorldPos,
	Camera &camera,
	Point3& displayPosition,
	std::vector<Point3>& localVertices,
	std::vector<Point2>& projectedVertices,
	std::vector<Vector3>& d_vs
);

#endif /* ALGORITHMS_H */
