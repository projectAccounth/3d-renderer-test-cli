#include "../include/algorithms.h"
#include "../include/mainHeader.h"

void replaceAtCursorPos(int x, int y, char ch) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    DWORD written;
	
	wchar_t chr = ch;
    // Move cursor and write the character
    WriteConsoleOutputCharacter(hConsole, &ch, 1, pos, &written);
}

void bresenham(Point2 p0, Point2 p1) {

	int height = tilesCountY;
	if (height == 0) return;

	int width = tilesCountX;

	auto isInsideBounds = [width, height](int x, int y) -> bool {
		return x >= 0 && x < width && y >= 0 && y < height;
	};

	if (std::isnan(p0.x) || std::isnan(p0.y) || std::isnan(p1.x) || std::isnan(p1.y)) {
		// std::cout << "Warning: Line endpoints contain invalid vertices. Skipping line.\n";
		return;
	}


	// Round the doubleing-point coordinates to integers for Bresenham
	int x0 = static_cast<int>(std::round(p0.x));
	int y0 = static_cast<int>(std::round(p0.y));
	int x1 = static_cast<int>(std::round(p1.x));
	int y1 = static_cast<int>(std::round(p1.y));

	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;

	if (x0 == x1) sx = 0;
	if (y0 == y1) sy = 0;

	// Calculate the absolute differences in coordinates
	int dx = std::abs(x1 - x0);
	int dy = -std::abs(y1 - y0);

	// Initialize the error term for integer precision
	int error = dx + dy;

	p0 = { static_cast<double>(x0), static_cast<double>(y0) };

	while (true) {
		// Use the integer rounded coordinates to set the image at the pixel location
		if (isInsideBounds(x0, y0)) {
			replaceAtCursorPos(x0, y0, '#');
		}

		p0 = { static_cast<double>(x0), static_cast<double>(y0) }; // Update the last rounded point

		if (x0 == x1 && y0 == y1) return;

		int e2 = 2 * error;

		if (e2 >= dy) {
			error += dy;
			x0 += sx;
		}

		if (e2 <= dx) {
			error += dx;
			y0 += sy;
		}
	}
}

void transformObject(
	EulerAngles& objectRotationAngles, Point3 objectWorldPos,
	EulerAngles& cameraRotationAngles, Point3 cameraPosition,
	Point3 displayPosition,
	std::vector<Point3>& localVertices,
	std::vector<Point2>& projectedVertices
) {
	size_t vertexCount = localVertices.size();
	std::vector<Point3> worldVertices(vertexCount);
	std::vector<Point3> viewVertices(vertexCount);

	// Step 1: Object Local Transformation
	Matrix3d objectRotation = EulerToMatrixLH(objectRotationAngles);
	for (size_t i = 0; i < vertexCount; ++i) {
		worldVertices[i] = objectRotation * localVertices[i];
	}

	// Step 2: World Transformation
	for (size_t i = 0; i < vertexCount; ++i) {
		worldVertices[i] = worldVertices[i] + objectWorldPos;
	}

	// Step 3: Camera Transformation
	Matrix3d cameraRotation = EulerToMatrixLH(cameraRotationAngles);
	for (size_t i = 0; i < vertexCount; ++i) {
		viewVertices[i] = cameraRotation * (worldVertices[i] - cameraPosition);
	}

	// Step 4: Projection with Clipping
	const double nearPlane = 0.1; // Minimum Z-distance for rendering
	const double EPSILON = 1e-6;

	projectedVertices.resize(vertexCount);
	for (size_t i = 0; i < vertexCount; ++i) {
		if (viewVertices[i].z < nearPlane) {
			// Mark invalid points
			projectedVertices[i] = { std::nanf(""), std::nanf("") };
			continue;
		}

		if (std::abs(viewVertices[i].z) > EPSILON) {
			projectedVertices[i].x = (displayPosition.z / viewVertices[i].z) * viewVertices[i].x + displayPosition.x;
			projectedVertices[i].y = (displayPosition.z / viewVertices[i].z) * viewVertices[i].y + displayPosition.y;
		}
		else {
			projectedVertices[i].x = displayPosition.x;
			projectedVertices[i].y = displayPosition.y;
		}
	}
	displayPosition = Point3(cameraPosition.x, cameraPosition.y, cameraPosition.z + 10);
}

void updateAngles(EulerAngles camRotation, Point3& camPos, Point3& displayPos,
	std::vector<Vector3> d_vs, std::vector<Point3> vertices,
	std::vector<Point2> projectionPs) {
	const double nearPlane = 0.1;
	const double farPlane = 1000.0;
	const double EPSILON = 1e-6;

	if (d_vs.size() != vertices.size() || projectionPs.size() != vertices.size()) {
		// std::cerr << "Size mismatch between vectors!" << std::endl;
		return;
	}

	Matrix3d rotationMatrix = EulerToMatrixLH(camRotation);

	for (size_t i = 0; i < vertices.size(); ++i) {
		Point3 relativePos = vertices[i] - camPos;
		d_vs[i] = rotationMatrix * Vector3(relativePos);

		// Skip vertices outside the frustum
		if (d_vs[i].z < nearPlane || d_vs[i].z > farPlane) {
			projectionPs[i] = { std::nanf(""), std::nanf("") };
			continue;
		}

		if (std::abs(d_vs[i].z) > EPSILON) { // Valid depth
			projectionPs[i].x = (displayPos.z / d_vs[i].z) * d_vs[i].x + displayPos.x;
			projectionPs[i].y = (displayPos.z / d_vs[i].z) * d_vs[i].y + displayPos.y;
		}
		else {
			projectionPs[i] = { std::nanf(""), std::nanf("") }; // Invalid projection
		}
	}
	displayPos = Point3(camPos.x, camPos.y, camPos.z + 10);
}

void resetAllImages() {
	system("cls");
}

void updateImage(std::vector<Point3>& vertices, std::vector<Point2>& projectP, double nearPlane, Point3 displayPosition) {
	for (int i = 0; i < projectP.size(); i++) {
		for (int j = 0; j < projectP.size(); j++) {
			if (i == j) continue;

			bool isAdjacent3D = false;
			const Point3& pt0_3D = vertices[i];
			const Point3& pt1_3D = vertices[j];
			if (pt0_3D.y == pt1_3D.y && pt0_3D.z == pt1_3D.z) {
				isAdjacent3D = true;
			}
			else if (pt0_3D.x == pt1_3D.x && pt0_3D.z == pt1_3D.z) {
				isAdjacent3D = true;
			}
			else if (pt0_3D.x == pt1_3D.x && pt0_3D.y == pt1_3D.y) {
				isAdjacent3D = true;
			}

			if (!isAdjacent3D) continue;
			bresenham(projectP[i], projectP[j]);
		}
	}
}

bool isAdjacent3D(Point3 p0, Point3 p1) {
	if (p0.y == p1.y && p0.z == p1.z) {
		return true;
	}
	else if (p0.x == p1.x && p0.z == p1.z) {
		return true;
	}
	else if (p0.x == p1.x && p0.y == p1.y) {
		return true;
	}
	return false;
}


void anotherImplementation(std::vector<Point3>& vertices,
	std::vector<Point2>& projectedP,
	double nearPlane,
	Point3 displayPosition,
	std::vector<std::array<int, 4>> boxFaces,
	Point3 cameraPosition,
	EulerAngles camAngles) {

	EulerAngles finalAngle(-camAngles.pitch, -camAngles.yaw, -camAngles.roll);

	// Matrix3d rotationMatrix = EulerToMatrixLH(finalAngle);

	for (auto face : boxFaces) {

		Point3 pt0_3D = (Vector3(vertices[face[0]])).toPoint3();
		Point3 pt1_3D = (Vector3(vertices[face[1]])).toPoint3();
		Point3 pt2_3D = (Vector3(vertices[face[2]])).toPoint3();

		Vector3 U = Vector3(pt1_3D) - Vector3(pt0_3D);
		Vector3 V = Vector3(pt2_3D) - Vector3(pt0_3D);
		Vector3 N = U.cross(V).normalize(); // Normal of the face

		Vector3 cameraDirection = Vector3(pt0_3D) - Vector3(cameraPosition);
		// cameraDirection = rotationMatrix * cameraDirection;
		cameraDirection = cameraDirection.normalize();
		const double epsilon = 1e-6; // Small tolerance value
		if (cameraDirection.dot(N) >= 0) {
			// continue; // Skip rendering this face
		}
		double farPlane = 1000.0; // Example value for the far clipping plane
		for (int i = 0; i < 4; ++i) {
			if (vertices[face[i]].z > farPlane) {
				continue; // Skip rendering this face
			}
		}

		for (int i = 0; i < 4; ++i) {
			int j = (i + 1) % 4; // Next vertex index
			if (isAdjacent3D(vertices[face[i]], vertices[face[j]])) {
				bresenham(projectedP[face[i]], projectedP[face[j]]);
			}
		}
	}
}

Point3 calculateCentroid(const std::vector<Point3>& vertices) {
	Point3 centroid{ 0.0, 0.0, 0.0 }; // Initialize to (0, 0, 0)
	for (const auto& vertex : vertices) {
		centroid.x += vertex.x;
		centroid.y += vertex.y;
		centroid.z += vertex.z;
	}

	size_t vertexCount = vertices.size();
	if (vertexCount > 0) {
		centroid.x /= vertexCount;
		centroid.y /= vertexCount;
		centroid.z /= vertexCount;
	}

	return centroid;
}

void updateAll(
	EulerAngles& objectRotationAngles, Point3 objectWorldPos,
	EulerAngles& cameraRotationAngles, Point3 &cameraPosition,
	Point3 &displayPosition,
	std::vector<Point3>& localVertices,
	std::vector<Point2>& projectedVertices,
	std::vector<Vector3>& d_vs
) {

	updateAngles(cameraRotationAngles, cameraPosition, displayPosition, d_vs, localVertices, projectedVertices);
	transformObject(objectRotationAngles, objectWorldPos, cameraRotationAngles, cameraPosition, displayPosition, localVertices, projectedVertices);
	// updateImage(localVertices, projectedVertices, nearPlane, displayPosition);
	anotherImplementation(localVertices, projectedVertices, nearPlane, displayPosition, faces, cameraPosition, cameraRotationAngles);
}