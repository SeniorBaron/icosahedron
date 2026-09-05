#include "camera.hpp"

camera::camera() {
	this->angleOfView = glm::radians(60.f);
	this->aspect = 1600.f / 900.f;
	this->position = glm::vec3(0.0f, 0.0f, 4.0f);
	this->facing = glm::vec2(0.0f, 0.0f);
}

camera::camera(float angleOfView, float aspect, const glm::vec3 position, const glm::vec2 facing) {
	this->angleOfView = angleOfView;
	this->aspect = aspect;
	this->position = position;
	this->facing = facing;
}

glm::mat4x4 camera::getProjection() {
	return glm::perspective(this->angleOfView, this->aspect, 0.1f, 25.f);
}

glm::mat4x4 camera::getView() {

	glm::mat4x4 res(1.0f); 
	res = glm::rotate(res, facing.y, glm::vec3(1.f, 0.f, 0.f));
	res = glm::rotate(res, facing.x, glm::vec3(0.f, 1.f, 0.f));
	res = glm::inverse(res);

	res = glm::translate(res, -this->position);
	return res;
}




