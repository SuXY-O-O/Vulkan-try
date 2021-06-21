#include "mytool.h"
#include <math.h>
#define PI 3.1415926

void MyTool::rotate(glm::vec3& source, float x, float y, float z)
{
	float ax = x / 180 * PI;
	float ay = y / 180 * PI;
	float az = z / 180 * PI;
	glm::mat3x3 rx = { 
		{1, 0, 0}, 
		{0, cos(ax), -sin(ax)}, 
		{0, sin(ax), cos(ax)} 
	};
	glm::mat3x3 ry = {
		{cos(ay), 0, sin(ay)},
		{0, 1, 0},
		{-sin(ay), 0, cos(ay)}
	};
	glm::mat3x3 rz = {
		{cos(az), -sin(az), 0},
		{sin(az), cos(az), 0},
		{0, 0, 1}
	};
	source.z -= 0.5f;
	source.z *= 2;
	source = rx * ry * rz * source;
	source.z /= 2;
	source.z += 0.5f;
	return;
}

void MyTool::panning(glm::vec3& source, float x, float y, float z)
{
	source.x += x;
	source.y += y;
	source.z += z;
}
