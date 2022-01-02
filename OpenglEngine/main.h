#pragma once
#ifndef MAIN_H
#define MAIN_H

/* glfw °´¼üÏìÓ¦ */
void ProcessInput(class GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

unsigned int VAO;
unsigned int VBO;
unsigned int EBO;

float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.f, 0.f, 0.f,
	 0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f,
	 0.0f,  0.5f, 0.0f, 0.f, 0.f, 1.f,
	 /*0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,*/
	 0.8f, 0.8f, 0.f, 0.5f, 0.5f, 0.5f
};

unsigned int indices[] = {
	0, 1, 2,
	2, 1, 3
};

const char* vertexShaderSource = 
"#version 330 core		\n"
"layout(location = 0) in vec3 aPos;					\n"
"layout(location = 1) in vec3 aColor;               \n"
"out vec4 color;                                    \n"
"													\n"
"void main()										\n"
"{													\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   color = vec4(aColor, 1.f);  \n"
"}												    \n";

const char* fragmentShaderSource =
"#version 330 core							 \n"
"out vec4 FragColor;						 \n"
"uniform vec4 vertexColor;                   \n"
"in vec4 color;                              \n"
"											 \n"
"void main()								 \n"
"{											 \n"
"	FragColor = color;						 \n"
"}											 \n";

unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;


float timeValue;
float dynamicColor;


class Shader* shader;
#endif // !MAIN_H
