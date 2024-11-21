#include "../include/camera.h"

Matrix4d Camera::lookAt(const Vector3& target, const Vector3& worldUp) {
    // Calculate forward, right, and up vectors
    Vector3 forward = (target - cameraPosition).normalize();
    Vector3 right = worldUp.cross(forward).normalize();
    Vector3 up = forward.cross(right);

    // Create rotation matrix
    Matrix4d rotation({{
        { right.x,    up.x,    -forward.x,   0 },
        { right.y,    up.y,    -forward.y,   0 },
        { right.z,    up.z,    -forward.z,   0 },
        { 0,          0,       0,           1 }
    }});

    // Create translation matrix
    Matrix4d translation({{
        { 1, 0, 0, -cameraPosition.x },
        { 0, 1, 0, -cameraPosition.y },
        { 0, 0, 1, -cameraPosition.z },
        { 0, 0, 0, 1 }
    }});

    // Combine rotation and translation
    return rotation * translation;
}