#include "../include/angles.h"

// 2 totally different implementation!!

Matrix3d EulerToMatrix(EulerAngles& angles) {
    double cp = std::cos(angles.pitch);
    double sp = std::sin(angles.pitch);
    double cy = std::cos(angles.yaw);
    double sy = std::sin(angles.yaw);
    double cr = std::cos(angles.roll);
    double sr = std::sin(angles.roll);

    Matrix3d matrix;

    matrix.mat[0][0] = cy * cr;
    matrix.mat[0][1] = -cy * sr;
    matrix.mat[0][2] = sy;

    matrix.mat[1][0] = sp * sy * cr + cp * sr;
    matrix.mat[1][1] = -sp * sy * sr + cp * cr;
    matrix.mat[1][2] = -sp * cy;

    matrix.mat[2][0] = -cp * sy * cr + sp * sr;
    matrix.mat[2][1] = cp * sy * sr + sp * cr;
    matrix.mat[2][2] = cp * cy;

    return matrix;
}

std::array<Matrix3d, 3> getRotationMatrices(EulerAngles& angle) {
    double sinX = std::sin(angle.pitch), cosX = std::cos(angle.pitch);
    double sinY = std::sin(angle.yaw), cosY = std::cos(angle.yaw);
    double sinZ = std::sin(angle.roll), cosZ = std::cos(angle.roll);

    Matrix3d Rx = { {
        {1, 0, 0},
        {0, cosX, sinX},
        {0, -sinX, cosX}
    } };

    Matrix3d Ry = { {
        {cosY, 0, -sinY},
        {0, 1, 0},
        {sinY, 0, cosY}
    } };

    Matrix3d Rz = { {
        {cosZ, sinZ, 0},
        {-sinZ, cosZ, 0},
        {0, 0, 1}
    } };

    return {Rx, Ry, Rz};
}

Matrix3d EulerToMatrixLH_YXZ(EulerAngles& angle) {
    std::array<Matrix3d, 3> finalAngles = getRotationMatrices(angle);
    // Combine rotations: YXZ
    return finalAngles[1] * finalAngles[0] * finalAngles[2];
}

Matrix3d EulerToMatrixLH_XYZ(EulerAngles& angle) {
    std::array<Matrix3d, 3> finalAngles = getRotationMatrices(angle);
    // Combine rotations: XYZ
    return finalAngles[0] * finalAngles[1] * finalAngles[2];
}

Matrix3d EulerToMatrixLH_ZYX(EulerAngles& angle) {
    std::array<Matrix3d, 3> finalAngles = getRotationMatrices(angle);
    // Combine rotations: ZYX
    return finalAngles[2] * finalAngles[1] * finalAngles[0];
}