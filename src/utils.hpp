#pragma once
#include "shader.hpp"

#define HEIGHT 900
#define WIDTH 1600

constexpr float ASP = (float)WIDTH / (float)HEIGHT;
constexpr float angleOfView = 3.1419f / 3.0f;

inline GLuint VAO, VBO, EBO;
inline shader sProgram;

namespace utils {
	void initializeScene();
	void frameHandler(GLFWwindow* window, GLdouble time);
	void destroyScene(GLFWwindow* window);
}
