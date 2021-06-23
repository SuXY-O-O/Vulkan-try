#pragma once
#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class MyTool
{
public:
	static void rotate(glm::vec3& source, float x, float y, float z, bool turn_z);
	static void panning(glm::vec3& source, float x, float y, float z);
};

