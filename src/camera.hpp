#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class camera {
	glm::vec3 position;
	glm::vec2 facing;
	float angleOfView;
	float aspect;
public:
	camera();
	camera(
		float angleOfView, 
		float aspect, 
		const glm::vec3 position = glm::vec3(0.0f, 0.0f, 4.0f), 
		const glm::vec2 facing = glm::vec2(0.0f, 0.0f)
	);
	glm::mat4x4 getProjection();
	glm::mat4x4 getView();
};


//nigga

