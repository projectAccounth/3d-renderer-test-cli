// C++ SDL2 Template for Visual Studio 2022

#include "../include/mainHeader.h"
#include "../include/program.h"
#include "../include/point.h"
#include "../include/angles.h"
#include "../include/vector.h"
#include "../include/algorithms.h"
#include "../include/boxes.h"


// window's color, change please
BoxManager boxManager;

Point3 camPos(tilesCountX / 2, tilesCountY / 2, -30); // C_xyz
Point3 displayPos(tilesCountX / 2, tilesCountY / 2, -20); // E_xyz

EulerAngles camRotation(0, 0, 0); // theta_xyz
EulerAngles boxRotation(0, 0, 0);



double camFOV = 2 * std::atan(std::pow(tilesCountX, 2) / 4 * std::abs(displayPos.z));

std::vector<Vector3> d_vs(16, Vector3(0, 0, 0)); // D_xyz

std::vector<Point2> projectionPs(16, Point2(0, 0)); // B_xy


int normalBoxSize = 50;

int main(int argc, char* argv[]) {
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 1; j++) {
			boxManager.add(Box(Point3(0 + normalBoxSize * i, 0, 0 + normalBoxSize * j), normalBoxSize));
		}
	}

	std::vector<Point3> totalVertices = boxManager.boxes[0].vertices;

	for (int i = 1; i < boxManager.boxes.size(); i++) {
		totalVertices.insert(totalVertices.end(), boxManager.boxes[i].vertices.begin(), boxManager.boxes[i].vertices.end());
	}

	Program program;

	bool isRunning = true;

	resetAllImages();
	updateAll(boxRotation, calculateCentroid(totalVertices),
			camRotation, camPos,
			displayPos, totalVertices,
			projectionPs, d_vs);

	while (isRunning) {
		program.programControls(camRotation, camPos, displayPos, d_vs, totalVertices, projectionPs, boxRotation);
	}
	program.onQuit();

	return 0;
}