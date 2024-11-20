#pragma once

// Include guard
#ifndef PROGRAM_H
#define PROGRAM_H

#include "mainHeader.h"
#include "vector.h"
#include "angles.h"

class Program {
public:
	// Called on program exit
	void onQuit();

	// All program controls go here
	void programControls(EulerAngles& camRotation, Point3& position,
		Point3& displayPos, std::vector<Vector3>& d_vs,
		std::vector<Point3>& vertices, std::vector<Point2>& projectionPs,
		EulerAngles& boxRotation);
};

#endif /* PROGRAM_H */
