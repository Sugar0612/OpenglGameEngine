#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <string>

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


public:
	void use();

private:
	void checkCompileErrors(unsigned int ID, std::string type);
};

#endif // !SHADER_H