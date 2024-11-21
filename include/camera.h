#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "mainHeader.h"
#include "angles.h"
#include "matrix.h"

class Camera {
public:
    Point3 cameraPosition;
    EulerAngles cameraAngles;

    Camera() : cameraPosition(Point3(0, 0, 0)), cameraAngles(EulerAngles(0, 0, 0)) {}
    Camera(double posX, double posY, double posZ, EulerAngles camAngles) :
        cameraPosition(Point3(posX, posY, posZ)),
        cameraAngles(camAngles) {}

    Matrix4d lookAt(const Vector3& target, const Vector3& worldUpVector);
};

#endif /* CAMERA_H */