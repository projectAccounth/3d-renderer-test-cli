#include "../include/program.h"
#include "../include/mainHeader.h"
#include "../include/algorithms.h"

void Program::onQuit() {
	
}

void Program::programControls(EulerAngles& camRotation, Point3& position,
	Point3& displayPos, std::vector<Vector3>& d_vs,
	std::vector<Point3>& vertices, std::vector<Point2>& projectionPs,
	EulerAngles &boxRotation) {

	// Getting keyboardState
	if (_kbhit()) {
		switch (_getch()) {
			case 'a': {
			resetAllImages();
				movePointLeft(position, camRotation, 1);
				// std::cout << "Camera position: " << position.x << ' ' << position.y << '\n';
				updateAll(boxRotation, calculateCentroid(vertices),
					camRotation, position,
					displayPos, vertices,
					projectionPs, d_vs);
			break;
			}
			case 'd' : {
				resetAllImages();
				movePointRight(position, camRotation, 1);
				// std::cout << "Camera position: " << position.x << ' ' << position.y << '\n';
				updateAll(boxRotation, calculateCentroid(vertices),
					camRotation, position,
					displayPos, vertices,
					projectionPs, d_vs);
			break;
			}		
			case 's': {
				resetAllImages();
				movePointBack(position, camRotation, 1);
				// std::cout << "Camera position: " << position.x << ' ' << position.y << '\n';
				updateAll(boxRotation, calculateCentroid(vertices),
					camRotation, position,
					displayPos, vertices,
					projectionPs, d_vs);
			break;
			}
			case 'w': {
				resetAllImages();
				movePointForward(position, camRotation, 1);
				// std::cout << "Camera position: " << position.x << ' ' << position.y << '\n';
				updateAll(boxRotation, calculateCentroid(vertices),
					camRotation, position,
					displayPos, vertices,
					projectionPs, d_vs);
			}
			case 'q': {
				resetAllImages();
				position.y -= 1;
				// std::cout << "Camera position: " << position.x << ' ' << position.y << '\n';
				updateAll(boxRotation, calculateCentroid(vertices),
					camRotation, position,
					displayPos, vertices,
					projectionPs, d_vs);
			break;
			}
			case 'e': {
				resetAllImages();
				position.y += 1;
				// std::cout << "Camera position: " << position.x << ' ' << position.y << '\n';
				updateAll(boxRotation, calculateCentroid(vertices),
					camRotation, position,
					displayPos, vertices,
					projectionPs, d_vs);
			break;
			}
			case 'l': {
				resetAllImages();
				camRotation.yaw -= M_PI / 16;
				updateAll(boxRotation, calculateCentroid(vertices),
					camRotation, position,
					displayPos, vertices,
					projectionPs, d_vs);
					break;
			}
			case 'i': {
				resetAllImages();
				camRotation.pitch -= M_PI / 16;
				updateAll(boxRotation, calculateCentroid(vertices),
					camRotation, position,
					displayPos, vertices,
					projectionPs, d_vs);
					break;
			}
			case 'k': {
				resetAllImages();
				camRotation.pitch += M_PI / 16;
				updateAll(boxRotation, calculateCentroid(vertices),
					camRotation, position,
					displayPos, vertices,
					projectionPs, d_vs);
					break;
			}
			case 'j': {
				resetAllImages();
				camRotation.yaw += M_PI / 16;
				updateAll(boxRotation, calculateCentroid(vertices),
					camRotation, position,
					displayPos, vertices,
					projectionPs, d_vs);
					break;
			}
		}
	}
}