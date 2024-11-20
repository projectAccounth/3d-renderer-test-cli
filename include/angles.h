#pragma once

#ifndef ANGLES_H
#define ANGLES_H

#include "mainHeader.h"
#include "matrix.h"
#include "point.h"

class EulerAngles {
public:  
    double pitch; // x-rotation
    double yaw;   // y-rotation
    double roll;  // z-rotation

    EulerAngles() : pitch(0), yaw(0), roll(0) {}
    EulerAngles(double pitch, double yaw, double roll) : pitch(pitch), yaw(yaw), roll(roll) {}
};

Matrix3d EulerToMatrix(EulerAngles& angle);

Matrix3d EulerToMatrixLH(EulerAngles& angle);


void movePointForward(Point3& pointPosition, EulerAngles &angles, double distance);

void movePointRight(Point3& pointPosition, EulerAngles &angles, double distance);

void movePointBack(Point3& pointPosition, EulerAngles &angles, double distance);

void movePointLeft(Point3& pointPosition, EulerAngles &angles, double distance);


#endif /* ANGLE_H */
