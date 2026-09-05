#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class shader {
	bool checkErrors(GLint targetEntity, GLuint target);
	GLuint ID;
public:
	shader();
	shader(const char* vertPath, const char* fragPath);
	void shutdown();
	GLuint getID();
	void use();
	void setFloatValue(const char* name, float value);
	void setFloatPermanentValue(const char* name, float value);
	void setVec2Value(const char* name, const glm::vec2& value);
	void setVec2PermanentValue(const char* name, const glm::vec2& value);
	void setMat2x2Value(const char* name, const glm::mat2x2& value);
	void setMat4x4Value(const char* name, const glm::mat4x4& value);
	void setMat4x4PermanentValue(const char* name, const glm::mat4x4& value);
};

