#pragma once

#ifndef BOXES_H
#define BOXES_H

#include "algorithms.h"

class Box {
public:
	std::vector<Point3> vertices;

	int boxSize;

	Box() : boxSize(1),
			vertices({Point3(1, 1, 1), Point3(1, 1, 0), Point3(0, 1, 1), Point3(0, 1, 0),
					  Point3(1, 0, 1), Point3(1, 0, 0), Point3(0, 0, 1), Point3(0, 0, 0) })
			{}

    Box(Point3 p1, int boxSize) :
        boxSize(boxSize),
        vertices({
            Point3(p1.x, p1.y, p1.z),                               // 0: Bottom-front-left
            Point3(p1.x + boxSize, p1.y, p1.z),                     // 1: Bottom-front-right
            Point3(p1.x + boxSize, p1.y, p1.z - boxSize),           // 2: Bottom-back-right
            Point3(p1.x, p1.y, p1.z - boxSize),                     // 3: Bottom-back-left
            Point3(p1.x, p1.y - boxSize, p1.z),                     // 4: Top-front-left
            Point3(p1.x + boxSize, p1.y - boxSize, p1.z),           // 5: Top-front-right
            Point3(p1.x + boxSize, p1.y - boxSize, p1.z - boxSize), // 6: Top-back-right
            Point3(p1.x, p1.y - boxSize, p1.z - boxSize)            // 7: Top-back-left
            }) {}
};

class BoxManager {
public:
	std::vector<Box> boxes;

	void add(Box box);
};

#endif /* BOXES_H */
