#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	std::string vertexString;
	std::string fragmentString;

	const char* vertexSource;
	const char* fragmentSource;

	unsigned int vertexShader;
	unsigned int fragmentShader;

	/* Shader Program */
	unsigned int shaderProgram;

	void UniformMat(const char* name, glm::mat4 mat);
	void SetUniform3f(const char* uniName, float x, float y, float z);
	void SetUniform3f_vec(const char* uniName, glm::vec3 vec);
	void SetUniform1f(const char* uniName, float x);
public:
	void use();

private:
	void checkCompileErrors(unsigned int ID, std::string type);
};

#endif // !SHADER_H