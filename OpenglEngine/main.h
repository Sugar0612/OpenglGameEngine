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
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 /*0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,*/
	 0.8f, 0.8f, 0.f
};

unsigned int indices[] = {
	0, 1, 2,
	2, 1, 3
};

const char* vertexShaderSource = 
"#version 330 core		\n"
"layout(location = 0) in vec3 aPos;					\n"
"													\n"
"void main()										\n"
"{													\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}												    \n";

const char* fragmentShaderSource =
"#version 330 core							 \n"
"out vec4 FragColor;						 \n"
"											 \n"
"void main()								 \n"
"{											 \n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}											 \n";

unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;

#endif // !MAIN_H
