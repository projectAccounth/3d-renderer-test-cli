#pragma once

// Include guard
#ifndef MAIN_HDR_H
#define MAIN_HDR_H

#define WINDOW_HEIGHT_OFFSET 40
// These are the window width and height, can be c8hanged
#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 520

const int tilesCountX = 120, tilesCountY = 48;

const double nearPlane = 0.1f;

#define M_PI 3.14159565358979323846264338327

// Includes for the program

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <functional>
#include <variant>
#include <type_traits>
#include <array>
#include <cmath>
#include <conio.h>
#include <windows.h>

const std::vector<std::array<int, 4>> faces = {
    {0, 1, 2, 3}, // Bottom face
    {7, 6, 5, 4}, // Top face
    {4, 5, 1, 0}, // Front face
    {2, 1, 5, 6}, // Right face
    {6, 7, 3, 2}, // Back face
    {7, 4, 0, 3}  // Left face
};

enum textAlign {
    LEFT,
    CENTER,
    RIGHT
};

#endif /* MAIN_HDR_H */
