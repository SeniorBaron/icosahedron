#include "shader.hpp"
#include "windows.h"
#include <fstream>

char errBufAscii[256];
char16_t errMsg[256];

std::string getSource(const char* path) {
	std::string content;
	std::ifstream fileStream(path, std::ios::in);
	std::string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}


void copy_convert(const char* string, char16_t* emptyBuf) {
	size_t i;
	for (i = 0; string[i] != '\0'; ++i) {
		emptyBuf[i] = (char16_t)string[i];
	}
	emptyBuf[i] = (char16_t)'\0';
}

///////////////////////////////////////////////////////////////////////////

bool shader::checkErrors(GLint targetEntity, GLuint target) {
	switch (targetEntity) {

		case GL_VERTEX_SHADER: {
			GLint status;
			glGetShaderiv(target, GL_COMPILE_STATUS, &status);
			if (status != 1) {
				glGetShaderInfoLog(target, 512, nullptr, errBufAscii);
				copy_convert(errBufAscii, errMsg);
				glfwTerminate();
				MessageBox(NULL, (LPCWSTR)errMsg, (LPCWSTR)u"vertex shader compilation failed\n", MB_OK);
				return true;
			}
			break;
		}
		case GL_FRAGMENT_SHADER: {
			GLint status;
			glGetShaderiv(target, GL_COMPILE_STATUS, &status);
			if (status != 1) {
				glGetShaderInfoLog(target, 512, nullptr, errBufAscii);
				copy_convert(errBufAscii, errMsg);
				glfwTerminate();
				MessageBox(NULL, (LPCWSTR)errMsg, (LPCWSTR)u"fragment shader compilation failed\n", MB_OK);
				return true;
			}
			break;
		}
		case GL_LINK_STATUS: {
			GLint status;
			glGetProgramiv(target, GL_LINK_STATUS, &status);
			if (status != 1) {
				glGetProgramInfoLog(target, 512, nullptr, errBufAscii);
				copy_convert(errBufAscii, errMsg);
				glfwTerminate();
				MessageBox(NULL, (LPCWSTR)errMsg, (LPCWSTR)u"shaders linking failed\n", MB_OK);
				return true;
			}
			break;
		}
	}
	return false;
}

shader::shader() {
	this->ID = (GLuint)((1llu << 32) - 1);
}

shader::shader(const char* vertPath, const char* fragPath) {
	bool createStatus = false;

	std::string vsource, fsource;

	try {
		vsource = getSource(vertPath);
		fsource = getSource(fragPath);
	}
	catch (std::ifstream::failure& error) {
		copy_convert(error.what(), errMsg);
		MessageBox(nullptr, (LPCWSTR)errMsg, (LPCWSTR)u"failed to open Source file", MB_OK);
		abort();
	}
	
	const char* vertexShaderSource = vsource.c_str();
	const char* fragmentShaderSource = fsource.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);

	glCompileShader(vertexShader);
	createStatus = (createStatus || checkErrors(GL_VERTEX_SHADER, vertexShader));

	glCompileShader(fragmentShader);
	createStatus = (createStatus || checkErrors(GL_FRAGMENT_SHADER, fragmentShader));

	GLuint newProgram = glCreateProgram();
	glAttachShader(newProgram, vertexShader);
	glAttachShader(newProgram, fragmentShader);
	glLinkProgram(newProgram);
	createStatus = (createStatus || checkErrors(GL_LINK_STATUS, newProgram));


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	if (createStatus) abort();

	this->ID = newProgram;
}

void shader::shutdown() {
	glDeleteProgram(this->ID);
}

GLuint shader::getID() {
	return this->ID;
}

void shader::use() {
	glUseProgram(this->ID);
}

void shader::setFloatValue(const char* name, float value) {
	glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void shader::setFloatPermanentValue(const char* name, float value) {
	glProgramUniform1f(this->ID, glGetUniformLocation(this->ID, name), value);
}

void shader::setVec2Value(const char* name, const glm::vec2& value) {
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void shader::setVec2PermanentValue(const char* name, const glm::vec2& value) {
	glProgramUniform2f(this->ID, glGetUniformLocation(this->ID, name), value.x, value.y);
}

void shader::setMat2x2Value(const char* name, const glm::mat2x2& value) {
	glUniformMatrix2fv(
		glGetUniformLocation(this->ID, name),
		1,
		GL_FALSE,
		&value[0][0]
	);
}

void shader::setMat4x4Value(const char* name, const glm::mat4x4& value) {
	glUniformMatrix4fv(
		glGetUniformLocation(this->ID, name),
		1,
		GL_FALSE,
		&value[0][0]
	);
}

void shader::setMat4x4PermanentValue(const char* name, const glm::mat4x4& value) {
	glProgramUniformMatrix4fv(
		this->ID,
		glGetUniformLocation(this->ID, name),
		1,
		GL_FALSE,
		&value[0][0]
	);
}
