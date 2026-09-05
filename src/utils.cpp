#include "utils.hpp"
#include "camera.hpp"
#include "animation.h"

const float a = (glm::sqrt(5.f) + 1.f) * 0.5f ;
float verticies[] = {
	a, 1., 0.,
	a, -1., 0.,
	-a, -1., 0.,
	-a, 1., 0.,

	1., 0., a,
	-1., 0., a,
	-1., 0., -a,
	1., 0., -a,

	0., a, 1.,
	0., a, -1.,
	0., -a, -1.,
	0., -a, 1
};

int indicies[]{
	4, 5, 8,
	4, 8, 0,
	4, 0, 1,
	4, 1, 11,
	4, 11, 5,

	5, 8, 3,
	8, 0, 9,
	0, 1, 7,
	1, 11, 10,
	11, 5, 2,

	3, 9, 8,
	9, 7, 0,
	7, 10, 1,
	10, 2, 11,
	2, 3, 5,
	
	3, 9, 6,
	9, 7, 6,
	7, 10, 6,
	10, 2, 6,
	2, 3, 6,
};

camera goPro;

void utils::initializeScene() {

	float ang = glm::radians(15.f);

	goPro = camera(3.1419f / 3.0f, ASP, 6.f * glm::vec3(0.0f, glm::sin(ang), glm::cos(ang)), glm::vec2(0.0f, -ang));

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36, verticies, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 60, indicies, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // verticies coords
	glEnableVertexAttribArray(0);

	ang = glm::half_pi<float>() - glm::atan(2.f / (glm::sqrt(5.f) + 1.f));

	sProgram = shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
	sProgram.setMat4x4PermanentValue("iCameraView", goPro.getView());
	sProgram.setMat4x4PermanentValue("iProject", goPro.getProjection());
	sProgram.setMat4x4PermanentValue("iModelRotation", glm::rotate(glm::mat4x4(1.f), ang, glm::vec3(0.f, 0.f, 1.f)));

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2.0f);
}

void utils::frameHandler(GLFWwindow* window, GLdouble time) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	time = fmod(time, 16.5f);

	sProgram.use();
	sProgram.setMat4x4Value("iMove", animate::drammaticMovement(time - 1.f));
	sProgram.setMat4x4Value("iRotate", animate::drammaticRotation(time - 1.f));
	

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void utils::destroyScene(GLFWwindow* window) {
	glfwDestroyWindow(window);
	sProgram.shutdown();
	glfwTerminate();
	exit(0x0);
}
